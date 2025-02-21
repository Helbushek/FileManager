#pragma once

#include <QObject>
#include <string>
#include <vector>

class FileContainer : public QObject
{
    Q_OBJECT

    void init()
    {
        m_list = std::vector<std::string>();
    }

    unsigned int fill(const std::vector<std::string> &list);

  public:
    FileContainer()
    {
        init();
    }
    FileContainer(const std::vector<std::string> &file_list);
    FileContainer(const std::string &file_list);
    ~FileContainer() = default;

    bool addFile(const std::string &path);
    unsigned int addFiles(const std::vector<std::string> &list);

    bool removeFile(const std::string &path);
    unsigned int removeAll();
    unsigned int removeSome(const std::vector<std::string> &list);

    int count() const;
    std::vector<std::string> list() const;

  private:
    std::vector<std::string> m_list;
};
