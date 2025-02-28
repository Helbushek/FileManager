#pragma once
#include <QObject>
#include <thread>
#include <vector>
#include <QFileInfo>
#include "Ilog.h"
#include "IFileContainer.h"

class FileObserver : QObject
{
    Q_OBJECT
  private:
    IFileContainer* container;
    ILog *logger;
    std::thread t;
    int _refershRate;

  public:
    FileObserver(IFileContainer* container, ILog *logger, int refreshRate = 1)
    {
        this->container = container;
        this->logger = logger;
        this->_refershRate = refreshRate;
    }
    ~FileObserver() = default;

    int refreshRate();
    void setRefreshRate(int refreshRate);

    void start();

  private:
    static std::string qint64_to_string(qint64 value);
    int fileUpdateDisappearInterval = 1000;
};
