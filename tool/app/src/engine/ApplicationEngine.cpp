#include "ApplicationEngine.h"

#include "DeviceInfo.h"

#include <QQmlContext>

#include <network/Module.h>

#include <config/Common.h>

namespace Converter
{
    ApplicationEngine::ApplicationEngine(QObject* parent)
        : QQmlApplicationEngine(parent)
        , networkModule_(new Network::Module(this))
        , deviceInfo_(new DeviceInfo(this))
    {
        QObject::connect(networkModule_, &Network::Module::incomingDeviceConfig, deviceInfo_, &DeviceInfo::onIncomingDeviceConfig);
    }

    void ApplicationEngine::initialize()
    {
        Config::Common::get().load();

        this->rootContext()->setContextProperty("engine", this);

        this->addImportPath("qrc:/");

        this->load("qrc:/AppUI/qml/main.qml");

        networkModule_->initialize();
    }

    QVariant ApplicationEngine::device() const
    {
        return QVariant::fromValue(deviceInfo_);
    }
}
