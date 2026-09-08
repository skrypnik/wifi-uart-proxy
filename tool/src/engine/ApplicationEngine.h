#pragma once

#include <QQmlApplicationEngine>
#include <QVariant>

class PacketHandler;

class QTcpSocket;
class QTimer;

class ApplicationEngine final : public QQmlApplicationEngine
{
    Q_OBJECT

    static constexpr int DefaultReconnectInterval = 1000;

    class ConnectionParams
    {
        friend class ApplicationEngine;

        /**
         * Server address or hostname
         */
        QString host_ = QString("192.168.1.1");

        /**
         * Server port
         */
        quint16 port_ = 23;
    };

public:
    explicit ApplicationEngine(QObject* parent = nullptr);

    /**
     * Initializes application engine
     */
    void initializeEngine();

    /**
     * Starts server connection
     * @param host server address or hostname
     * @param port server port
     * @param interval reconnect interval
     */
    void start(const QString &host, uint16_t port, int interval = DefaultReconnectInterval) const;

    /**
     * Sends raw data to remote host
     * @param data data to send
     */
    void send(const QByteArray& data) const;

    /**
     * Stops server connection
     */
    void stop() const;

public:
    /**
     * Connects to remote host
     */
    Q_INVOKABLE void connectToHost() const;

    /**
     * Disconnects from remote host
     */
    Q_INVOKABLE void disconnectFromHost() const;

    /**
     * Calls get device info request
     */
    Q_INVOKABLE void getDeviceInfo() const;

private slots:
    /**
     * TCP client socket connect handler
     */
    void onConnected();

    /**
     * TCP client socket disconnect handler
     */
    void onDisconnected();

    /**
     * Server reply handler
     */
    void onReplyReceived();

    /**
     * Reconnect timer handler
     */
    void onReconnect() const;

private:
    /**
     * Server connection params
     */
    ConnectionParams* params_;

    /**
     * Packet handler
     */
    PacketHandler* handler_;

    /**
     * TCP client socket to connect the device group
     */
    QTcpSocket* socket_;

    /**
     * Reconnect timer
     */
    QTimer* timer_;
};
