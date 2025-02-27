#include <QDateTime>
#include <QTime>
#include <chrono>
#include <time.h>
#include <cstdlib>
#include "FileObserver.h"

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
    logger->Log("Length: " + std::to_string(this->container.size()));
    system("cls");
    while (1)
    {
        int i = 0;
        foreach (QFileInfo file, this->container)
        {
            file.refresh();
            if (file.exists() &&
                file.lastModified().time().secsTo(QTime().currentTime()) < FileObserver::fileChangeDisappearInterval)
            {
                logger->Log(std::to_string(i) + ": " + file.absoluteFilePath().toStdString() + " U: " + file.lastModified().time().toString().toStdString() +
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
    }

}
