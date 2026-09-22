#pragma once

#include <QJsonObject>

namespace Converter::Config
{
    class Common
    {
        /**
         * Config root object
         */
        QJsonObject root_;

        /**
         * Singleton private constructor
         */
        Common() = default;

        /**
         * Create default config if it doesn't exist
         */
        void createDefault();

    public:
        /**
         * Config files system location
         */
        static const QString ConfigLocation;

        /**
         * Config file name
         */
        static const QString ConfigFileName;

        /**
         * Config file directory
         */
        static const QString ConfigDir;

    public:
        /**
         * Singleton instance getter
         * @return singleton instance
         */
        static Common& get();

    public:
        /**
         * Load data from config file
         */
        bool load();

        /**
         * Save data to config file
         */
        bool save();

        /**
         * Root object getter
         * @return root object
         */
        [[nodiscard]] const QJsonObject& root() const;

        /**
         * Sets config object data
         * @param key root subobject key
         * @param obj new object data
         */
        void setConfigObject(const QString& key, const QJsonObject& obj);

    /**
    * Construction is deprecated
    */
    public:
        Common(const Common&) = delete;
        Common(Common&&) = delete;
        Common& operator=(const Common&) = delete;
        Common& operator=(Common&&) = delete;
    };
}
