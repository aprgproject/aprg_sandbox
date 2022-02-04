#pragma once

#include <Optional/AlbaOptional.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <fstream>
#include <string>

namespace alba
{

namespace algorithm
{

template <typename ObjectToSort>
class DataBlockFileHandler
{
public:
    ~DataBlockFileHandler()
    {
        m_fileOptional.clear();
        AlbaLocalPathHandler(m_path).deleteFile();
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
    void openFileIfNeeded(std::string const& path)
    {
        if(!m_fileOptional)
        {
            AlbaLocalPathHandler filePathHandler(path);
            //filePathHandler.createDirectoriesForNonExisitingDirectories(); //is this needed?
            m_path = filePathHandler.getFullPath();
            m_fileOptional.createObjectUsingDefaultConstructor();
            std::ofstream & fileStream (m_fileOptional.getReference());
            fileStream.open(m_path, std::ios::ate|std::ios::app);
            assert(!fileStream.fail());
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

}

}//namespace alba
