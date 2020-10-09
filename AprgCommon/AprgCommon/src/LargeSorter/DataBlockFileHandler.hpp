#pragma once

#include <AlbaOptional.hpp>
#include <AlbaWindowsPathHandler.hpp>
#include <fstream>
#include <string>

using std::string;
namespace alba
{
template <typename ObjectToSort>
class DataBlockFileHandler
{
public:
    ~DataBlockFileHandler()
    {
        AlbaWindowsPathHandler filePathToDelete;
        filePathToDelete.inputPath(m_path);
        filePathToDelete.deleteFile();
    }
    std::ofstream & getFileDumpStreamReference()
    {
        return m_fileOptional.getReference();
    }
    bool isFileStreamOpened()
    {
        if(m_fileOptional)
        {
            return m_fileOptional.getReference().is_open();
        }
        return false;
    }
    void openFileIfNeeded(string const& path)
    {
        if(!m_fileOptional)
        {
            AlbaWindowsPathHandler filePath;
            filePath.inputPath(path);
            m_path = filePath.getFullPath();
            m_fileOptional.createObjectUsingDefaultConstructor();
            std::ofstream & fileStream (m_fileOptional.getReference());
            fileStream.open(m_path, std::ios::ate|std::ios::app);
        }
    }
    void add(ObjectToSort const& objectToSort)
    {
        m_fileOptional.getReference()<<objectToSort<<std::endl;
    }
    void releaseFileStream()
    {
        m_fileOptional.clear();
    }

private:
    string m_path;
    AlbaOptional<std::ofstream> m_fileOptional;
};

}//namespace alba
