#include "IFileContainer.h"

QFileInfo StaticFileContainer::operator[](int index)
{
    // return element on index
    return container[index];
}

void StaticFileContainer::append(QFileInfo file)
{
    // put element in vector
    container.push_back(file);
}

void StaticFileContainer::clear()
{
    // fully clear the vector
    container.clear();
}

int StaticFileContainer::length()
{
    // return size of the vector
    return container.size();
}
