#include "DeviceInfo.h"

namespace Converter
{
    DeviceInfo::DeviceInfo(QObject* parent)
        : QObject(parent)
        , ready_(false)
    {
    }

    void DeviceInfo::changeWLANConfig(const QString& ssid, const QString& password, const QString& channel)
    {
        auto network = config_["network"].toObject();
        network["ssid"] = ssid;
        network["password"] = password;
        network["channel"] = channel.toInt();
        config_["network"] = network;

        emit this->configChanged();
    }

    void DeviceInfo::changeELANConfig(const QString& address, const QString& netmask, const QString& port)
    {
        auto network = config_["network"].toObject();
        network["address"] = address;
        network["netmask"] = netmask;
        network["port"] = port.toInt();
        config_["network"] = network;

        emit this->configChanged();
    }

    void DeviceInfo::changeUARTConfig(const QString& speed, const QString& bits, const QString& stop)
    {
        auto uart = config_["uart"].toObject();
        uart["baud_rate"] = speed.toInt();
        uart["bits"] = bits.toInt();
        uart["stop"] = stop.toInt();
        config_["uart"] = uart;

        emit this->configChanged();
    }

    void DeviceInfo::commitChanges()
    {
        emit this->configCommits(config_);
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
        return config_["uart"]["baud_rate"].toInt();
    }

    QVariant DeviceInfo::bits() const
    {
        return config_["uart"]["bits"].toInt();
    }

    QVariant DeviceInfo::stop() const
    {
        return config_["uart"]["stop"].toInt();
    }

    QVariant DeviceInfo::ready() const
    {
        return ready_;
    }

    void DeviceInfo::onIncomingDeviceConfig(const QJsonObject& config)
    {
        config_ = config;
        ready_ = true;

        emit this->configChanged();
    }

}
