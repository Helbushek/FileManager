#include "IFileContainer.h"

QFileInfo StaticFileContainer::operator[](int index)
{
    return container[index];
}

void StaticFileContainer::append(QFileInfo file)
{
    container.push_back(file);
}

void StaticFileContainer::clear()
{
    container.clear();
}

int StaticFileContainer::length()
{
    return container.size();
}
