#pragma once

#include <QUdpSocket>
#include <QTimer>

namespace Converter::Network
{
    /**
     * Network device searcher
     */
    class Searcher final : public QTimer
    {
        Q_OBJECT

    public:
        /**
         * Constructs device searcher object
         * @param parent parent QObject to call safe deleter
         */
        explicit Searcher(QObject* parent = nullptr);

        /**
         * Initializes searcher with given port
         */
        void initialize();

        /**
         * Sends broadcast request
         */
        void sendBroadcastRequest() const;

    signals:
        /**
         * Emits, when module receives response on broadcast request
         * @param config device config in JSON format
         */
        void incomingSenderParams(const QJsonObject& config);

    private slots:
        /**
         * Sends broadcast request
         */
        void onSendBroadcastRequest() const;

        /**
         * Incoming data handler
         */
        void onReceiveBroadcastRequest();

    private:
        /**
         * UDP socket for broadcast messaging
         */
        QUdpSocket* socket_;
    };

}
