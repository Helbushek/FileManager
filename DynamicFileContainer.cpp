#include <fstream>
#include "IFileContainer.h"

void DynamicFileContainer::refresh()
{
    std::ifstream mFile(_path);
    std::string path;
    if (mFile.is_open())
    {
        this->clear();
        while (getline(mFile, path))
        {
            QFileInfo newFile(QString::fromStdString(path));
            this->append(newFile);
        }
    }
}

DynamicFileContainer::DynamicFileContainer(std::string path)
{
    this->_path = path;
    this->refresh();
}

void DynamicFileContainer::setPath(std::string path)
{
    this->_path = path;
    this->refresh();
}

QFileInfo DynamicFileContainer::operator[](int index)
{
    this->refresh();
    return this->container[index];
}

void DynamicFileContainer::append(QFileInfo file)
{
    container.push_back(file);
}

void DynamicFileContainer::clear()
{
    this->container.clear();
}

int DynamicFileContainer::length()
{
    this->refresh();
    return this->container.size();
}
