#pragma once

#include <QQmlApplicationEngine>

class ApplicationEngine final : public QQmlApplicationEngine
{
    Q_OBJECT

public:
    explicit ApplicationEngine(QObject* parent = nullptr);

    /**
     * Initializes application engine
     */
    void initialize();
};
