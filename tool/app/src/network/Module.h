#pragma once

#include <QObject>

class QUdpSocket;

namespace Converter::Network
{
    /**
     * Network device searcher
     */
    class Searcher;

    /**
     * Network module
     */
    class Module final : public QObject
    {
        Q_OBJECT

    public:
        /**
         * Constructs object
         * @param parent parent object to safe deletion
         */
        explicit Module(QObject* parent = nullptr);

        /**
         * Initializes network module
         */
        void initialize() const;

    signals:
        /**
         * Emits, when config was parsed from device response
         * @param config device config in JSON format
         */
        void incomingDeviceConfig(const QJsonObject& config);

    private slots:
        /**
         * Incoming device config handler
         * @param config packet with device config in JSON format
         */
        void onDeviceConfigReceived(const QJsonObject& config);

    private:
        /**
         * UDP socket
         */
        QUdpSocket* socket_;

        /**
        * Network device searcher
        */
        Searcher* searcher_;
    };

}