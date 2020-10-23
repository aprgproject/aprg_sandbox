#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <fstream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>

namespace alba
{

class AlbaCombineAndGrepFiles
{
public:
    AlbaCombineAndGrepFiles(std::string const& outputFilePath, std::string const& fileCondition, std::string const& lineCondition);
    void processDirectory(std::string const& path);
    void processFile(std::string const& path);

private:
    AlbaWindowsPathHandler m_pathHandler;
    std::ofstream m_outputFileStream;
    AlbaGrepStringEvaluator m_fileEvaluator;
    AlbaGrepStringEvaluator m_lineEvaluator;
};

}
