#include "Module.h"

#include "Searcher.h"

#include <config/Common.h>

#include <QUdpSocket>

namespace Converter::Network
{
    Module::Module(QObject* parent)
        : QObject(parent)
        , socket_(new QUdpSocket(this))
        , searcher_(new Searcher(this))
    {
        QObject::connect(searcher_, &Searcher::incomingSenderParams, this, &Module::onDeviceConfigReceived);
    }

    void Module::initialize() const
    {
        searcher_->initialize();
        searcher_->start();
    }

    void Module::onDeviceConfigReceived(const QJsonObject& config)
    {
        searcher_->stop();

        const auto data = config["data"].toObject();

        const auto address = data["network"]["address"].toString();
        const auto netport = Config::Common::get().root()["service"]["port"].toInt();

        socket_->bind(QHostAddress(address), netport);

        emit this->incomingDeviceConfig(data);
    }

}
