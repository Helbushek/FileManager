#pragma once
#include <QObject>
#include <thread>
#include <vector>
#include <QFileInfo>
#include "Ilog.h"
#include "IFileContainer.h"
#include "IRefresher.h"

class FileObserver : public QObject
{
    Q_OBJECT
  private:
    IFileContainer* container;
    ILog *logger;
    IRefresher *refresher;
    unsigned int fileUpdateDisappearInterval = 10;

  private:
    FileObserver();
    FileObserver(IFileContainer *container, ILog *logger, IRefresher *refresher);
    ~FileObserver();
    FileObserver(const FileObserver &) = delete;
    FileObserver &operator=(const FileObserver &) = delete;

    static FileObserver object;

  public:
    static FileObserver &Instance(IFileContainer *container, ILog *logger, IRefresher *refresher);

    void setContainer(IFileContainer *container);
    void setLogger(ILog *logger);
    void setUpdateDisappearInterval(unsigned int interval);

    void start();

  signals:
    void onFileUpdate(IFileContainer *container, int index);
    void onFileRemoval(IFileContainer *container, int index);
    void onFileExistance(IFileContainer *container, int index);

    void onCycleEnd();
};
