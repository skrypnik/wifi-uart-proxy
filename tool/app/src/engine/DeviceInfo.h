#pragma once

#include <QJsonObject>
#include <QObject>

namespace Converter
{
    class DeviceInfo final : public QObject
    {
        Q_OBJECT

        /**
         * Wi-Fi access point SSID metaobject property
         */
        Q_PROPERTY( QVariant ssid READ ssid NOTIFY configChanged )

        /**
         * Wi-Fi access point channel metaobject property
         */
        Q_PROPERTY( QVariant channel READ channel NOTIFY configChanged )

        /**
         * Wi-Fi access point password metaobject property
         */
        Q_PROPERTY( QVariant password READ password NOTIFY configChanged )

        /**
         * Network address metaobject property
         */
        Q_PROPERTY( QVariant address READ address NOTIFY configChanged )

        /**
         * Network mask metaobject property
         */
        Q_PROPERTY( QVariant netmask READ netmask NOTIFY configChanged )

        /**
         * Network port metaobject property
         */
        Q_PROPERTY( QVariant netport READ netport NOTIFY configChanged )

        /**
         * UART speed (baud rate) metaobject property
         */
        Q_PROPERTY( QVariant speed READ speed NOTIFY configChanged )

        /**
         * UART bits count metaobject property
         */
        Q_PROPERTY( QVariant bits READ bits NOTIFY configChanged )

        /**
         * UART stop bits count metaobject property
         */
        Q_PROPERTY( QVariant stop READ stop NOTIFY configChanged )

    public:
        /**
         * Constructs object
         * @param parent parent object to safe deletion
         */
        explicit DeviceInfo(QObject* parent = nullptr);

    private:
        /**
         * Wi-Fi access point SSID metaobject getter
         */
        [[nodiscard]] QVariant ssid() const;

        /**
         * Wi-Fi access point channel metaobject getter
         */
        [[nodiscard]] QVariant channel() const;

        /**
         * Wi-Fi access point password metaobject getter
         */
        [[nodiscard]] QVariant password() const;

        /**
         * Network address metaobject getter
         */
        [[nodiscard]] QVariant address() const;

        /**
         * Network mask metaobject getter
         */
        [[nodiscard]] QVariant netmask() const;

        /**
         * Network port metaobject getter
         */
        [[nodiscard]] QVariant netport() const;

        /**
         * UART speed (baud rate) metaobject getter
         */
        [[nodiscard]] QVariant speed() const;

        /**
         * UART bits count metaobject getter
         */
        [[nodiscard]] QVariant bits() const;

        /**
         * UART stop bits count metaobject getter
         */
        [[nodiscard]] QVariant stop() const;

    signals:
        /**
         * Emits, when config is changed
         */
        void configChanged();

    public slots:
        /**
         * Called, when config was parsed from device response
         * @param config device config in JSON format
         */
        void onIncomingDeviceConfig(const QJsonObject& config);

    private:
        /**
         * Device config in JSON format
         */
        QJsonObject config_;
    };

}
