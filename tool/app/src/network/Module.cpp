#include "Module.h"

#include <QUdpSocket>

namespace Converter::Network
{
    Module::Module(QObject* parent)
        : QObject(parent)
        , socket_(new QUdpSocket(this))
    {
    }

}
