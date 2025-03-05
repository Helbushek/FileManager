#include "ILog.h"

ConsoleLog::ConsoleLog(bool logTime)
{
    // sets whether logger will be logging timestamps or not
    this->logTime = logTime;
}

void ConsoleLog::cls()
{
    // clears console
    system("cls");
}

void ConsoleLog::Log(std::string data)
{
    // logs given data to console
    if (logTime)
    {
        std::cout << time.currentTime().toString().toStdString() << " ";
    }
    std::cout << "[LOG] " << data << "\n";
}

// converts file size to string
std::string ConsoleLog::qint64_to_string(qint64 value)
{
    std::string result;
    result.reserve(20); // max. 20 digits possible
    qint64 q = value;
    do
    {
        result += "0123456789"[q % 10]; // q = "14", q % 10 = 4, 4-th index is string "4"  ---> Simple!
        q /= 10; // "remove" last digit
    } while (q); // while q contains any digits
    std::reverse(result.begin(), result.end()); // as we went tail-to-head, we need to reverse string
    return result;
}

// case for when file exists and was NOT modified
void ConsoleLog::onFileExistance(IFileContainer *container, const int index)
{
    QFileInfo file = container->operator[](index);
    this->Log(std::to_string(index) + ": " + file.absoluteFilePath().toStdString() + " | " +qint64_to_string(file.size()));
}

// case for when file exists and was modified
void ConsoleLog::onFileUpdate(IFileContainer *container, const int index)
{
    QFileInfo file = container->operator[](index);
    this->Log(std::to_string(index) + ": [UPDATED " +
              file.lastModified().time().toString().toStdString() +
              "] " + file.absoluteFilePath().toStdString() +
              " | " + qint64_to_string(file.size()));
}

// case for when file DOES NOT exists
void ConsoleLog::onFileRemoval(IFileContainer *container, const int index)
{
    QFileInfo file = container->operator[](index);
    this->Log(std::to_string(index) + ": [NOT EXISTS] " +
              file.absoluteFilePath().toStdString());
}

// end of cycle => clear console
void ConsoleLog::onCycleEnd()
{
    this->cls();
}
