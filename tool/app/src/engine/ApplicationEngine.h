#pragma once

#include <QQmlApplicationEngine>

#include "network/Module.h"

namespace Converter
{
    /**
    * Network module
    */
    namespace Network { class Module; }

    class ApplicationEngine final : public QQmlApplicationEngine
    {
        Q_OBJECT

    public:
        explicit ApplicationEngine(QObject* parent = nullptr);

        /**
         * Initializes application engine
         */
        void initialize();

    private:
        /**
        * Network module
        */
        Network::Module* networkModule_;
    };

}
