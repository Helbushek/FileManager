#include <QDateTime>
#include <QTime>
#include <chrono>
#include <time.h>
#include <cstdlib>
#include "IFileObserver.h"

FileObserver::FileObserver(IFileContainer *container, ILog *logger, int refreshRate)
{
    this->container = container;
    this->logger = logger;
    this->_refershRate = refreshRate;

    connect(this, &FileObserver::onFileExistance, this->logger, &ILog::onFileExistance);
    connect(this, &FileObserver::onFileUpdate, this->logger, &ILog::onFileUpdate);
    connect(this, &FileObserver::onFileRemoval, this->logger, &ILog::onFileRemoval);
}

void FileObserver::setRefreshRate(int refreshRate)
{
    this->_refershRate = refreshRate;
}

int FileObserver::refreshRate()
{
    return this->_refershRate;
}

void FileObserver::start()
{
    logger->Log("Length: " + std::to_string(this->container->length()));
    this->logger->cls();
    while (1)
    {
        for (int i = 0; i < this->container->length(); ++i)
        {
            QFileInfo file;
            file = this->container->operator[](i);
            file.refresh();
            if (file.exists() &&
                file.lastModified().time().secsTo(QTime().currentTime()) < FileObserver::fileUpdateDisappearInterval)
            {
                emit onFileUpdate(this->container, i);
            }
            else if (file.exists())
            {
                emit onFileExistance(this->container, i);
            }
            else if (!file.exists())
            {
                emit onFileRemoval(this->container, i);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / this->_refershRate));
        this->logger->cls();
    }

}
