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

        /**
         * Device ready flag metaobject property
         */
        Q_PROPERTY( QVariant ready READ ready NOTIFY configChanged )

    public:
        /**
         * Constructs object
         * @param parent parent object to safe deletion
         */
        explicit DeviceInfo(QObject* parent = nullptr);

    public:
        /**
         * Changes WLAN config params
         * @param ssid Wi-Fi access point SSID
         * @param password Wi-Fi access point password
         * @param channel Wi-Fi access point channel
         */
        Q_INVOKABLE void changeWLANConfig(const QString& ssid, const QString& password, const QString& channel);

        /**
         * Changes ELAN config params
         * @param address Network address
         * @param netmask Network mask
         * @param port Network port
         */
        Q_INVOKABLE void changeELANConfig(const QString& address, const QString& netmask, const QString& port);

        /**
         * Changes UART config params
         * @param speed UART speed (baud rate)
         * @param bits UART bits count
         * @param stop UART stop bits count
         */
        Q_INVOKABLE void changeUARTConfig(const QString& speed, const QString& bits, const QString& stop);

        /**
         * Sends changed config to device
         */
        Q_INVOKABLE void commitChanges();

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

        /**
         * Device ready flag
         */
        [[nodiscard]] QVariant ready() const;

    signals:
        /**
         * Emits, when config is changed
         */
        void configChanged();

        /**
         * Emits, when changed config is send to device
         */
        void configCommits(const QJsonObject& config);

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

        /**
         * Ready flag
         */
        bool ready_;
    };

}
