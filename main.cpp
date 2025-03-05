#include <QCoreApplication>
#include "IFileObserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DynamicFileContainer container("C:/projects/TRPO/FileManager/fileContainer.txt"); // create container for observer
    ConsoleLog logger(true); // create logger for observer

    FileObserver observer(&container, &logger, 0.5f); // put container and logger into observer with refreshRate parameter
    observer.start(); // run cycle
    return a.exec();
}
