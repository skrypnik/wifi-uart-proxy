#include "ApplicationEngine.h"

#include <QQmlContext>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>

#include "transport/Packet.h"

ApplicationEngine::ApplicationEngine(QObject* parent)
    : QQmlApplicationEngine(parent)
    , params_(new ConnectionParams)
    , handler_(new PacketHandler)
    , socket_(new QTcpSocket(this))
    , timer_(new QTimer(this))
{
    QObject::connect(socket_, &QTcpSocket::connected, this, &ApplicationEngine::onConnected);
    QObject::connect(socket_, &QTcpSocket::disconnected, this, &ApplicationEngine::onDisconnected);
    QObject::connect(socket_, &QTcpSocket::readyRead, this, &ApplicationEngine::onReplyReceived);

    QObject::connect(timer_, &QTimer::timeout, this, &ApplicationEngine::onReconnect);
}

void ApplicationEngine::initializeEngine()
{
    qDebug() << Q_FUNC_INFO;

    /// Load UI resources
    this->rootContext()->setContextProperty("engine", this);

    /// Add resource import path
    this->addImportPath("qrc:/");

    /// Load UI resources
    this->load("qrc:/qml/main.qml");
}

void ApplicationEngine::start(const QString &host, const uint16_t port, const int interval) const
{
    qDebug() << Q_FUNC_INFO;

    params_->host_ = host;
    params_->port_ = port;

    timer_->setInterval(interval);
    timer_->start();
}

void ApplicationEngine::send(const QByteArray& data) const
{
    qDebug() << Q_FUNC_INFO;

    socket_->write(data);
}

void ApplicationEngine::stop() const
{
    qDebug() << Q_FUNC_INFO;

    timer_->stop();

    if (socket_->state() == QAbstractSocket::ConnectedState) socket_->disconnectFromHost();
}

void ApplicationEngine::connectToHost() const
{
    qDebug() << Q_FUNC_INFO;

    this->start("192.168.1.1", 80);
}

void ApplicationEngine::disconnectFromHost() const
{
    qDebug() << Q_FUNC_INFO;

    this->stop();
}

void ApplicationEngine::getDeviceInfo() const
{
    qDebug() << Q_FUNC_INFO;

    const auto packet = handler_->generateRequest(0x00, PacketHandler::Operation::GetDeviceInfo);

    this->send(packet);
}

void ApplicationEngine::onConnected()
{
    qDebug() << Q_FUNC_INFO;
}

void ApplicationEngine::onDisconnected()
{
    qDebug() << Q_FUNC_INFO;
}

void ApplicationEngine::onReplyReceived()
{
    qDebug() << Q_FUNC_INFO;

    const auto data = socket_->readAll();

    qDebug() << data.toHex();
}

void ApplicationEngine::onReconnect() const
{
    qDebug() << Q_FUNC_INFO;

    socket_->connectToHost(params_->host_, params_->port_);
}
