#include "DeviceInfo.h"

namespace Converter
{
    DeviceInfo::DeviceInfo(QObject* parent)
        : QObject(parent)
    {
    }

    QVariant DeviceInfo::ssid() const
    {
        return config_["network"]["ssid"].toString();
    }

    QVariant DeviceInfo::channel() const
    {
        return config_["network"]["channel"].toInt();
    }

    QVariant DeviceInfo::password() const
    {
        return config_["network"]["password"].toString();
    }

    QVariant DeviceInfo::address() const
    {
        return config_["network"]["address"].toString();
    }

    QVariant DeviceInfo::netmask() const
    {
        return config_["network"]["netmask"].toString();
    }

    QVariant DeviceInfo::netport() const
    {
        return config_["network"]["netport"].toInt();
    }

    QVariant DeviceInfo::speed() const
    {
        return config_["network"]["speed"].toInt();
    }

    QVariant DeviceInfo::bits() const
    {
        return config_["network"]["bits"].toInt();
    }

    QVariant DeviceInfo::stop() const
    {
        return config_["network"]["stop"].toInt();
    }

    void DeviceInfo::onIncomingDeviceConfig(const QJsonObject& config)
    {
        config_ = config;

        emit this->configChanged();
    }

}
