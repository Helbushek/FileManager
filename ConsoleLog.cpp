#include "ILog.h"

ConsoleLog::ConsoleLog(bool logTime)
{
    this->logTime = logTime;
}

void ConsoleLog::Log(std::string data)
{
    if (logTime)
    {
        std::cout << time.currentTime().toString().toStdString() << " ";
    }
    std::cout << "[LOG] " << data << "\n";
}

void ConsoleLog::Error(std::string error)
{
    std::cerr << error << "\n";
}
void ConsoleLog::Message(std::string message)
{
    std::cout << message << "\n";
}

void ConsoleLog::cls() {
    system("cls");
}


std::string ConsoleLog::qint64_to_string(qint64 value)
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

void ConsoleLog::onFileExistance(IFileContainer *container, const int index)
{
    QFileInfo file = container->operator[](index);
    this->Log(std::to_string(index) + ": " + file.absoluteFilePath().toStdString() + " | " +qint64_to_string(file.size()));
}

void ConsoleLog::onFileUpdate(IFileContainer *container, const int index)
{
    QFileInfo file = container->operator[](index);
    this->Log(std::to_string(index) + ": [UPDATED " +
              file.lastModified().time().toString().toStdString() +
              "] " + file.absoluteFilePath().toStdString() +
              " | " + qint64_to_string(file.size()));
}

void ConsoleLog::onFileRemoval(IFileContainer *container, const int index)
{
    QFileInfo file = container->operator[](index);
    this->Log(std::to_string(index) + ": [NOT EXISTS] " +
              file.absoluteFilePath().toStdString());
}
