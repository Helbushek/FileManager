#include <QCoreApplication>
#include "FileObserver.h"

int main(int argc, char *argv[])
{
    //    QCoreApplication a(argc, argv);

    std::vector<QFileInfo> container;
    QFileInfo file(QString("C:/projects/TRPO/FileManager/hi.txt"));
    container.push_back(file);
    ConsoleLog logger(true);

    FileObserver observer(container, &logger);
    observer.start();
    //    return a.exec();
    return 0;
}
