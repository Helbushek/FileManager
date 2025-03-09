#include <QDateTime>
#include <QTime>
#include <cstdlib>
#include <math.h>
#include "FileObserver.h"

FileObserver::FileObserver(IFileContainer *container, ILog *logger, IRefresher *refresher)
{
    // initiate variables
    this->container = container;
    this->logger = logger;
    this->refresher = refresher;

    //connect signal - slot relations with logger
    connect(this, &FileObserver::onFileExistance, this->logger, &ILog::onFileExistance);
    connect(this, &FileObserver::onFileUpdate, this->logger, &ILog::onFileUpdate);
    connect(this, &FileObserver::onFileRemoval, this->logger, &ILog::onFileRemoval);
    connect(this, &FileObserver::onCycleEnd, this->logger, &ILog::onCycleEnd);
}

FileObserver::~FileObserver()
{
    // DO NOT delete pointers, it will cause unexpected behaviour
}

void FileObserver::setContainer(IFileContainer *container)
{
    this->container = container;
}

void FileObserver::setLogger(ILog *logger)
{
    this->logger = logger;
}

void FileObserver::setUpdateDisappearInterval(unsigned int interval)
{
    fileUpdateDisappearInterval = interval;
}

void FileObserver::start()
{
    if (container == 0)
    {
        return;
    }
    // infinite cycle (only way to exit is to close console ot Ctrl + X (ot etc.)
    while (1)
    {
        emit onCycleEnd(); // call the signal
        // looking into all elements in container
        for (int i = 0; i < this->container->length(); ++i)
        {
            // for comfort usage writing data into separate variable
            QFileInfo file;
            file = this->container->operator[](i);
            file.refresh(); // !!! updated file existance, size, other data

            // check for existance and last modifications to the file
            if (file.exists() && QDateTime::currentDateTime().toMSecsSinceEpoch() - file.lastModified().toMSecsSinceEpoch() <= fileUpdateDisappearInterval * 1000) // only updated in specified time range will show up (default = 1000 sec)
            {
                emit onFileUpdate(this->container, i); // call the signal
            }
            // check for file existance (case where file exists and was not modified)
            else if (file.exists())
            {
                emit onFileExistance(this->container, i); // call the signal
            }
            // check for file not existance
            else if (!file.exists())
            {
                emit onFileRemoval(this->container, i); // call the signal
            }
        }
        refresher->refresh();
    }
}
