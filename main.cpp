#include <QCoreApplication>
#include "FileObserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DynamicFileContainer container("C:/projects/TRPO/FileManager/fileContainer.txt"); // create container for observer
    ConsoleLog logger(true); // create logger for observer
    TimeRefresher refresher(0.5f);

    FileObserver observer(&container, &logger, &refresher); // put container and logger into observer with refreshRate parameter
    observer.start(); // run cycle
    return a.exec();
}
