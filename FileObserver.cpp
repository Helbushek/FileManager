#include <QDateTime>
#include <QTime>
#include <chrono>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "IFileObserver.h"

FileObserver::FileObserver(IFileContainer *container, ILog *logger, float refreshRate)
{
    // initiate variables
    this->container = container;
    this->logger = logger;
    this->_refershRate = refreshRate;

    //connect signal - slot relations with logger
    connect(this, &FileObserver::onFileExistance, this->logger, &ILog::onFileExistance);
    connect(this, &FileObserver::onFileUpdate, this->logger, &ILog::onFileUpdate);
    connect(this, &FileObserver::onFileRemoval, this->logger, &ILog::onFileRemoval);
    connect(this, &FileObserver::onCycleEnd, this->logger, &ILog::onCycleEnd);
}

FileObserver::~FileObserver()
{
    // delete pointers
    delete container;
    delete logger;
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

void FileObserver::setRefreshRate(unsigned int refreshRate)
{
    // setting refresh rate
    this->_refershRate = refreshRate;
}

unsigned int FileObserver::refreshRate() const
{
    // returning refresh rate
    return this->_refershRate;
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
            file.refresh(); // !!! updated file existance, size, metadata, ...

            // check for existance and last modifications to the file
            if (file.exists() &&
                (file.lastModified().date().daysTo(QDate().currentDate()) <= FileObserver::fileUpdateDisappearInterval / (60*60*24)) &&
                (file.lastModified().time().secsTo(QTime().currentTime()) <= FileObserver::fileUpdateDisappearInterval % (60*60*24))) // only updated in specified time range will show up (default = 1000 sec)
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
        std::this_thread::sleep_for(std::chrono::milliseconds(int(1000 / this->_refershRate))); // wait before next cycle. cycle repeats every 1/refreshRate seconds or one refreshRate amount at a second

    }
}
