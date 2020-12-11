#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>

#include <set>
#include <string>

namespace alba
{

class AprgFileExtractor
{
    typedef std::set<std::string> SetOfFilePaths;
public:
    AprgFileExtractor();
    AprgFileExtractor(std::string const& condition);
    void extractAllRelevantFiles(std::string const& pathOfFileOrDirectory);
    void copyRelativeFilePathsFromCompressedFile(std::string const& filePathOfCompressedFile, SetOfFilePaths& files) const;
    std::string extractAll(std::string const& filePathOfCompressedFile) const;
    std::string extractOneFile(std::string const& filePathOfCompressedFile, std::string const& relativePathOfFile) const;
    bool isRecognizedCompressedFile(std::string const& extension) const;
private:
    void extractAllRelevantFilesInThisDirectory(std::string const& directoryPath);
    void extractAllRelevantFilesInThisCompressedFile(std::string const& filePathOfCompressedFile);
    void extractAllFilesRecursively(std::string const& filePathOfCompressedFile);
    void extractAllRelevantFilesRecursively(std::string const& filePathOfCompressedFile);
    bool isTheExtensionXz(std::string const& extension) const;
    AlbaGrepStringEvaluator m_grepEvaluator;
    std::string m_pathOf7zExecutable;
    std::string m_pathOf7zTempFile;
};

}
