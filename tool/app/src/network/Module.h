#pragma once

#include <QObject>

class QUdpSocket;

namespace Converter::Network
{
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

    private:
        /**
         * UDP socket
         */
        QUdpSocket* socket_;
    };

}