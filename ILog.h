#pragma once
#include <string>
#include <iostream>
#include <QTime>
#include <QObject>
#include "IFileContainer.h"

class ILog : public QObject
{
    Q_OBJECT
  public:
    virtual ~ILog() = default;

    virtual void Log(std::string data) = 0;

  public slots:
    virtual void onFileExistance(IFileContainer *container, const int index) = 0;
    virtual void onFileUpdate(IFileContainer *container, const int index) = 0;
    virtual void onFileRemoval(IFileContainer *container, const int index) = 0;
    virtual void onCycleEnd() = 0;

};

class ConsoleLog : public ILog
{
    Q_OBJECT

  private:
    QTime time = QTime();
    bool logTime = false;
    static std::string qint64_to_string(qint64 value);

  public:
    ~ConsoleLog() = default;

    ConsoleLog(bool logTime);

    void Log(std::string data);

    void cls();

  public slots:
    void onFileExistance(IFileContainer *container, const int index);

    void onFileUpdate(IFileContainer *container, const int index);

    void onFileRemoval(IFileContainer *container, const int index);

    void onCycleEnd();
};
