#include <engine/ApplicationEngine.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Q_INIT_RESOURCE( AppUI );
    Q_INIT_RESOURCE( SimDS );

    Converter::ApplicationEngine engine;
    engine.initialize();

    return QGuiApplication::exec();
}
