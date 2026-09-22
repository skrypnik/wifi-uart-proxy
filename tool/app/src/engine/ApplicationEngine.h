#pragma once

#include <QQmlApplicationEngine>

#include "network/Module.h"

namespace Converter
{
    /**
     * Device info
     */
    class DeviceInfo;

    /**
    * Network module
    */
    namespace Network { class Module; }

    class ApplicationEngine final : public QQmlApplicationEngine
    {
        Q_OBJECT

        /**
         * Device info metaobject property
         */
        Q_PROPERTY( QVariant device READ device CONSTANT )

    public:
        /**
         * Constructs object
         * @param parent parent object to safe deletion
         */
        explicit ApplicationEngine(QObject* parent = nullptr);

        /**
         * Initializes application engine
         */
        void initialize();

    private:
        /**
         * Device info metaobject getter
         * @return device info
         */
        [[nodiscard]] QVariant device() const;

    private:
        /**
        * Network module
        */
        Network::Module* networkModule_;

        /**
         * Device info
         */
        DeviceInfo* deviceInfo_;
    };

}
