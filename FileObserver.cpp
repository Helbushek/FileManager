#include <QDateTime>
#include <QTime>
#include <chrono>
#include <time.h>
#include <cstdlib>
#include "FileObserver.h"

void FileObserver::setRefreshRate(int refreshRate)
{
    this->_refershRate = refreshRate;
}

int FileObserver::refreshRate()
{
    return this->_refershRate;
}

std::string FileObserver::qint64_to_string(qint64 value)
{
    std::string result;
    result.reserve(20); // max. 20 digits possible
    qint64 q = value;
    do
    {
        result += "0123456789"[q % 10];
        q /= 10;
    } while (q);
    std::reverse(result.begin(), result.end());
    return result;
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
                logger->Log(std::to_string(i) + ": [UPDATED " + file.lastModified().time().toString().toStdString() +
                                "] " + file.absoluteFilePath().toStdString() +
                            " | " + qint64_to_string(file.size()));
            }
            else if (file.exists())
            {
                logger->Log(std::to_string(i) + ": " + file.absoluteFilePath().toStdString() + " | " + qint64_to_string(file.size()));
            }
            else if (!file.exists())
            {
                logger->Log(std::to_string(i) + ": [NOT EXISTS] " + file.absoluteFilePath().toStdString());
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / this->_refershRate));
        this->logger->cls();
    }

}
