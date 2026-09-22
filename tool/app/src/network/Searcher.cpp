#include "Searcher.h"

#include <QJsonDocument>

#include <config/Common.h>

namespace Converter::Network
{
    Searcher::Searcher(QObject* parent)
        : QTimer(parent)
        , socket_(new QUdpSocket(this))
    {
    }

    void Searcher::initialize()
    {
        this->setInterval(Config::Common::get().root()["service"]["interval"].toInt());

        const auto netport = Config::Common::get().root()["service"]["port"].toInt();

        socket_->bind(QHostAddress::Any, netport);

        QObject::connect(this, &QTimer::timeout, this, &Searcher::onSendBroadcastRequest);

        QObject::connect(socket_, &QUdpSocket::readyRead, this, &Searcher::onReceiveBroadcastRequest);
    }

    void Searcher::sendBroadcastRequest() const
    {
        const auto subnet = Config::Common::get().root()["service"]["subnet"].toString();
        const auto port = Config::Common::get().root()["service"]["port"].toInt();

        QJsonObject root;
        root["request"] = "get";

        socket_->writeDatagram(QJsonDocument(root).toJson(), QHostAddress(subnet), port);

        qDebug() << Q_FUNC_INFO << subnet << port << root;
    }

    void Searcher::onSendBroadcastRequest() const
    {
        this->sendBroadcastRequest();
    }

    void Searcher::onReceiveBroadcastRequest()
    {
        QHostAddress sender;
        QByteArray datagram;
        datagram.resize(static_cast<int>(socket_->pendingDatagramSize()));

        socket_->readDatagram(datagram.data(), datagram.size(), &sender);

        const QJsonDocument doc = QJsonDocument::fromJson(datagram.data());

        if (const auto root = doc.object(); root["response"].toString() == "get") emit this->incomingSenderParams(root);
    }

}
