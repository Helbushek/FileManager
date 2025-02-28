#pragma once
#include <QObject>
#include <thread>
#include <vector>
#include <QFileInfo>
#include "Ilog.h"
#include "IFileContainer.h"

class IFileObserver : public QObject
{
    Q_OBJECT
  public:
    virtual ~IFileObserver() = default;

    virtual void start() = 0;

  signals:
    virtual void onFileUpdate(IFileContainer* container, int index) = 0;
    virtual void onFileRemoval(IFileContainer* container, int index) = 0;
    virtual void onFileExistance(IFileContainer* container, int index) = 0;
};

class FileObserver : public IFileObserver
{
    Q_OBJECT
  private:
    IFileContainer* container;
    ILog *logger;
    int _refershRate;
    int fileUpdateDisappearInterval = 1000;

  public:
    FileObserver(IFileContainer *container, ILog *logger, int refreshRate = 1);
    ~FileObserver() = default;

    int refreshRate();
    void setRefreshRate(int refreshRate);

    void start();

  signals:
    void onFileUpdate(IFileContainer *container, int index);
    void onFileRemoval(IFileContainer *container, int index);
    void onFileExistance(IFileContainer *container, int index);
};
