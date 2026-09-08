#include "ApplicationEngine.h"

#include <QQmlContext>

ApplicationEngine::ApplicationEngine(QObject* parent)
    : QQmlApplicationEngine(parent)
{

}

void ApplicationEngine::initialize()
{
    /// Load UI resources
    this->rootContext()->setContextProperty("engine", this);

    /// Add resource import path
    this->addImportPath("qrc:/");

    /// Load UI resources
    this->load("qrc:/qml/main.qml");
}
