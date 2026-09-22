#include "Common.h"

#include <QStandardPaths>
#include <QJsonDocument>
#include <QDir>

namespace Converter::Config
{
    /*static*/ const QString Common::ConfigLocation = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    /*static*/ const QString Common::ConfigFileName = "config.json";
    /*static*/ const QString Common::ConfigDir = "wifi-uart-converter";

    void Common::createDefault()
    {
        QJsonObject application;
        application["title"] = "УППУ Моно DC";

        QJsonObject service;
        service["interval"] = 3000;
        service["subnet"] = "192.168.16.255";
        service["port"] = 16777;

        root_["application"] = application;
        root_["service"] = service;
    }

    /*static*/ Common& Common::get()
    {
        static Common instance;
        return instance;
    }

    bool Common::load()
    {
        const auto configPath = QString("%1/%2").arg(ConfigLocation, ConfigDir);

        if (const QDir dir(configPath); !dir.exists())
        {
            Q_UNUSED( dir.mkdir(configPath) );

            this->createDefault();

            this->save();
        }

        const auto configFile = QString("%1/%2").arg(configPath, ConfigFileName);

        if (!QFile::exists(configFile))
        {
            this->createDefault();

            this->save();
        }

        if (QFile file{configFile}; file.open(QFile::ReadOnly | QFile::Text))
        {
            QJsonParseError error = {QJsonParseError::NoError};
            const auto doc = QJsonDocument::fromJson(file.readAll(), &error);

            if (error.error == QJsonParseError::NoError)
            {
                root_ = doc.object();

                return true;
            }
        }

        return false;
    }

    bool Common::save()
    {
        const auto configPath = QString("%1/%2").arg(ConfigLocation, ConfigDir);

        if (const QDir dir(configPath); !dir.exists())
        {
            Q_UNUSED(dir.mkdir(configPath));

            this->createDefault();
        }

        const auto configFile = QString("%1/%2").arg(configPath, ConfigFileName);

        if (QFile file(configFile); file.open(QFile::WriteOnly | QFile::Text))
        {
            const QJsonDocument doc(root_);
            file.write(doc.toJson());

            return true;
        }

        return false;
    }

    const QJsonObject& Common::root() const
    {
        return root_;
    }

    void Common::setConfigObject(const QString& key, const QJsonObject& obj)
    {
        ///! \todo check key

        root_[key] = obj;

        this->save();
    }

}
