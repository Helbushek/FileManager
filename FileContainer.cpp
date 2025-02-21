#include <iostream>
#include <sstream>
#include <FileContainer.h>

unsigned int FileContainer::fill(const std::vector<std::string> &list)
{
    if (list.empty())
    {
        return 0;
    }
    foreach (std::string path, list)
    {
        m_list.push_back(path);
    }
    return m_list.size();
}

FileContainer::FileContainer(const std::vector<std::string> &list) : FileContainer()
{
    fill(list);
}

FileContainer::FileContainer(const std::string &list) : FileContainer()
{
    std::vector<std::string> container;
    std::istringstream s(list);
    std::string path;
    while (s >> path)
    {
        if (!path.empty())
        {
            container.push_back(path);
        }
    }

    if (!container.empty())
    {
        fill(container);
    }
}

bool FileContainer::addFile(const std::string &path)
{
    if (path.empty())
    {
        return false;
    }
    m_list.push_back(path);
    return true;
}

unsigned int FileContainer::addFiles(const std::vector<std::string> &list)
{
    unsigned int count = 0;
    foreach (std::string path, list)
    {
        count += addFile(path);
    }
    return count;
}

bool FileContainer::removeFile(const std::string &path)
{
    auto res = std::find(m_list.begin(), m_list.end(), path);

    if (m_list[distance(m_list.begin(), res)].empty())
    {
        return false;
    }
    m_list.erase(res);
    return true;
}

unsigned int FileContainer::removeAll()
{
    if (m_list.empty())
    {
        return 0;
    }
    unsigned int count = m_list.size();
    m_list.clear();
    return count;
}

unsigned int FileContainer::removeSome(const std::vector<std::string> &list)
{
    if (list.empty())
    {
        return 0;
    }
    unsigned int count = 0;
    foreach (std::string path, list)
    {
        count += removeFile(path);
    }
    return count;
}

int FileContainer::count() const
{
    return m_list.size();
}

std::vector<std::string> FileContainer::list() const
{
    return std::vector<std::string>(m_list);
}
