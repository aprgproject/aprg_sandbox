#pragma once

#include <AlbaOptional.hpp>
#include <fstream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>

namespace alba
{

template <typename ObjectToSort>
class DataBlockFileHandler
{
public:
    ~DataBlockFileHandler()
    {
        m_fileOptional.clear();
        AlbaWindowsPathHandler(m_path).deleteFile();
    }
    std::ofstream & getFileDumpStreamReference()    {
        return m_fileOptional.getReference();
    }
    bool isFileStreamOpened()    {
        if(m_fileOptional)
        {
            return m_fileOptional.getReference().is_open();
        }
        return false;
    }
    void openFileIfNeeded(std::string const& path)
    {
        if(!m_fileOptional)
        {
            m_path = AlbaWindowsPathHandler(path).getFullPath();
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
    std::string m_path;
    AlbaOptional<std::ofstream> m_fileOptional;
};

}//namespace alba
