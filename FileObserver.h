#pragma once
#include <QObject>
#include <thread>
#include <vector>
#include <QFileInfo>
#include "Ilog.h"

class FileObserver : QObject
{
    Q_OBJECT
  private:
    std::vector<QFileInfo> container;
    ILog *logger;
    std::thread t;

  public:
    FileObserver(std::vector<QFileInfo> container, ILog *logger)
    {
        this->container = container;
        this->logger = logger;
    }
    ~FileObserver() = default;

    void start();

  private:
    static std::string qint64_to_string(qint64 value);
    int fileChangeDisappearInterval = 10;
};
