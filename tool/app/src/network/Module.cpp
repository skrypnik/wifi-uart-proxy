#include "Module.h"

#include "Searcher.h"

#include <config/Common.h>

#include <QNetworkDatagram>
#include <QJsonDocument>
#include <QUdpSocket>
#include <QTimer>

namespace Converter::Network
{
    Module::Module(QObject* parent)
        : QObject(parent)
        , socket_(new QUdpSocket(this))
        , searcher_(new Searcher(this))
        , checkTimer_(new QTimer(this))
    {
        QObject::connect(searcher_, &Searcher::incomingSenderParams, this, &Module::onDeviceConfigReceived);

        QObject::connect(checkTimer_, &QTimer::timeout, this, &Module::onSendCheckPacket);
    }

    void Module::initialize() const
    {
        searcher_->initialize();
        searcher_->start();
    }

    void Module::onConfigCommits(const QJsonObject& config) const
    {
        QJsonObject root;
        root["request"] = "set";
        root["data"] = config;

        const auto address = config_["network"].toObject()["address"].toString();
        const auto netport = config_["network"].toObject()["netport"].toInt();

        const auto datagram = QNetworkDatagram(QJsonDocument(root).toJson(), QHostAddress(address), netport);

        socket_->writeDatagram(datagram);
    }

    void Module::onDeviceConfigReceived(const QJsonObject& config)
    {
        searcher_->stop();

        config_ = config["data"].toObject();

        const auto address = config_["network"].toObject()["address"].toString();
        const auto netport = config_["network"].toObject()["netport"].toInt();

        socket_->bind(QHostAddress(address), netport);

        emit this->incomingDeviceConfig(config_);

        checkTimer_->start(1000);
    }

    void Module::onSendCheckPacket()
    {
        QByteArray packet;
        packet.append(9, static_cast<char>(0x00));
        packet.append(8, static_cast<char>(0x30));

        const auto address = config_["network"].toObject()["address"].toString();
        const auto netport = config_["network"].toObject()["netport"].toInt();

        qDebug() << address << netport << packet.toHex();

        const auto datagram = QNetworkDatagram(packet, QHostAddress(address), netport);

        socket_->writeDatagram(datagram);
    }

}
