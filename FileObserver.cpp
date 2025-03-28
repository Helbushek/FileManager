#include <QDateTime>
#include <QTime>
#include <cstdlib>
#include <math.h>
#include "FileObserver.h"

FileObserver &FileObserver::Instance(IFileContainer *container, ILog *logger, IRefresher *refresher)
{
    static FileObserver object(container, logger, refresher);
    return object;
}

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
    if (container == nullptr)
    {
        return;
    }
    bool hasChanges = false;
    bool forceEmit = true;

    std::vector<QFileInfo> previousStates;

           // infinite cycle (only way to exit is to close console ot Ctrl + X (ot etc.)
    while (1)
    {
        hasChanges = false;

        // если контейнер изменился
        if (previousStates.size() != this->container->length())
        {
            previousStates.clear();
            for (int i = 0; i < container->length(); ++i)
            {
                previousStates.push_back(container->operator[](i));
                previousStates[i].refresh(); // Получаем начальное состояние
            }
            hasChanges = true;
        }

        for (int i = 0; i < this->container->length(); ++i)
        {

            QFileInfo file = this->container->operator[](i);
            QFileInfo &oldFile = previousStates[i];

                   // Если файл изменился
            if (file.lastModified() != oldFile.lastModified() ||
                file.size() != oldFile.size() ||
                file.exists() != oldFile.exists())
            {
                hasChanges = true;
                break; // Достаточно знать, что хотя бы один файл изменился
            }
        }

        if (hasChanges || forceEmit)
        {
            emit onCycleEnd(); // Отправляем сигнал о конце цикла

                   // Обновляем состояние всех файлов
            for (int i = 0; i < this->container->length(); ++i)
            {
                QFileInfo file = this->container->operator[](i);
                file.refresh(); // Обновляем данные файла

                if (file.exists() &&
                    QDateTime::currentDateTime().toMSecsSinceEpoch() - file.lastModified().toMSecsSinceEpoch() <=
                        fileUpdateDisappearInterval * 1000)
                {
                    emit onFileUpdate(this->container, i); // Сигнал об обновлении файла
                }
                else if (file.exists())
                {
                    emit onFileExistance(this->container, i); // Сигнал о существовании файла
                }
                else
                {
                    emit onFileRemoval(this->container, i); // Сигнал об удалении файла
                }

                previousStates[i] = file;
            }

                   // Сбрасываем флаги после обработки
            hasChanges = false;
            if (forceEmit)
            {
                forceEmit = false; // Отключаем после первого запуска
            }
        }

        refresher->refresh();
    }
}
