#include <fstream>
#include <iostream>
#include "IFileContainer.h"

// clears information about files it stores and reads it again from fileContainer file
void DynamicFileContainer::refresh()
{
    // opens file for reading
    std::ifstream mFile(fileContainerPath);
    // prepare variable for storing path of file
    std::string path;
    // check for errors
    if (mFile.is_open())
    {
        // clear stored files
        this->clear();
        // guarantees to get to closest error or EOF
        while (getline(mFile, path))
        {
            if (path.empty())
            {
                continue;
            }
            this->append(QFile(QString::fromStdString(path)));
        }
    }
}

DynamicFileContainer::DynamicFileContainer(std::string path)
{
    // initiate path
    this->fileContainerPath = path;
    // read from file
    this->refresh();
}

void DynamicFileContainer::setPath(std::string path)
{
    // change path
    this->fileContainerPath = path;
    // read from file
    this->refresh();
}

QFileInfo DynamicFileContainer::operator[](int index)
{
    // reads files
    this->refresh();
    // returns actual file on index
    return this->container[index];
}

void DynamicFileContainer::append(QFileInfo file)
{
    if (std::find(begin(filePathesContainer), end(filePathesContainer), file.absoluteFilePath().toStdString()) == end(filePathesContainer))
    {
        container.push_back(file);
        filePathesContainer.push_back(file.absoluteFilePath().toStdString());
    }
}

void DynamicFileContainer::clear()
{
    // clears container
    this->container.clear();
    filePathesContainer.clear();
}

int DynamicFileContainer::length()
{
    // reads from file
    this->refresh();
    // returns actual size
    return this->container.size();
}
