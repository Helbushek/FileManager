#pragma once
#include <string>
#include <iostream>
#include <QTime>

class ILog
{
  public:
    virtual void Log(std::string data) = 0;

    virtual void Error(std::string error) = 0;

    virtual void Message(std::string message) = 0;
};

class ConsoleLog : public ILog
{
    QTime time = QTime();

  public:
    ConsoleLog(bool logTime)
    {
        this->logTime = logTime;
    }

    bool logTime = false;
    void Log(std::string data)
    {
        if (logTime)
        {
            std::cout << time.currentTime().toString().toStdString() << " ";
        }
        std::cout << "[LOG] " << data << "\n";
    }

    void Error(std::string error)
    {
    }
    void Message(std::string message)
    {
    }
};
