#include "ApplicationEngine.h"

#include <QQmlContext>

#include "network/Module.h"

namespace Converter
{
    ApplicationEngine::ApplicationEngine(QObject* parent)
        : QQmlApplicationEngine(parent)
        , networkModule_(new Network::Module(this))
    {

    }

    void ApplicationEngine::initialize()
    {
        this->rootContext()->setContextProperty("engine", this);

        this->addImportPath("qrc:/");

        this->load("qrc:/AppUI/qml/main.qml");
    }

}