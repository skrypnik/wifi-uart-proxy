#include "ApplicationEngine.h"

#include <QQmlContext>

ApplicationEngine::ApplicationEngine(QObject* parent)
    : QQmlApplicationEngine(parent)
{

}

void ApplicationEngine::initialize()
{
    this->rootContext()->setContextProperty("engine", this);

    this->addImportPath("qrc:/");

    this->load("qrc:/AppUI/qml/main.qml");
}
