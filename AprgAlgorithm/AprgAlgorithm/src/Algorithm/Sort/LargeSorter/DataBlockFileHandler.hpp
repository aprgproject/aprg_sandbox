#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <cassert>
#include <fstream>
#include <optional>
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
        releaseFileStream();
        AlbaLocalPathHandler(m_path).deleteFile();
    }

    std::ofstream & getFileDumpStreamReference()
    {
        return m_fileOptional.value();
    }

    bool isFileStreamOpened()
    {
        if(m_fileOptional)
        {
            return m_fileOptional->is_open();
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
            m_fileOptional.emplace();
            std::ofstream & fileStream (m_fileOptional.value());
            fileStream.open(m_path, std::ios::ate|std::ios::app);
            assert(!fileStream.fail());
        }
    }

    void add(ObjectToSort const& objectToSort)
    {
        m_fileOptional.value()<<objectToSort<<std::endl;
    }

    void releaseFileStream()
    {
        //m_fileOptional->close(); // close does not work why?
        m_fileOptional.reset();
    }

private:
    std::string m_path;
    std::optional<std::ofstream> m_fileOptional;
};

}

}//namespace alba
