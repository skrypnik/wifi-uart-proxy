#include <QGuiApplication>

#include <engine/ApplicationEngine.h>

int main( int argc, char* argv[] )
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    ApplicationEngine engine;
    engine.initializeEngine();

    return QGuiApplication::exec();
}
