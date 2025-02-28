//#include <QCoreApplication>
#include "FileObserver.h"

int main(int argc, char *argv[])
{
    //    QCoreApplication a(argc, argv);

    DynamicFileContainer container("C:/projects/TRPO/FileManager/fileContainer.txt");
//    QFileInfo file(QString("C:/projects/TRPO/FileManager/hi.txt"));
//    container.append(file);
    ConsoleLog logger(true);

    FileObserver observer(&container, &logger, 1);
    observer.start();
    //    return a.exec();
    return 0;
}
