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

  public:
    FileObserver(IFileContainer *container, ILog *logger, IRefresher* refresher);
    ~FileObserver();

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
