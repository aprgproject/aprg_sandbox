#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <set>
#include <string>

#define PATH_OF_7Z_EXECUTABLE R"(C:\APRG\AprgFileExtractor\7z32\7z.exe)"
#define PATH_OF_7Z_TEMP_FILE R"(C:\APRG\AprgFileExtractor\7z32\TempFile.txt)"

namespace alba
{

class AprgFileExtractor
{
    typedef std::set<std::string> SetOfFilePaths;
public:
    AprgFileExtractor();
    AprgFileExtractor(std::string const& condition);
    void extractAllRelevantFiles(std::string const& pathOfFileOrDirectory) const;
    void copyRelativeFilePathsFromCompressedFile(std::string const& filePathOfCompressedFile, SetOfFilePaths& files) const;
    std::string extractAll(std::string const& filePathOfCompressedFile) const;
    std::string extractOneFile(std::string const& filePathOfCompressedFile, std::string const& relativePathOfFile) const;
    bool isRecognizedCompressedFile(std::string const& extension) const;
private:
    void extractAllRelevantFilesInThisDirectory(std::string const& directoryPath) const;
    void extractAllRelevantFilesInThisCompressedFile(std::string const& filePathOfCompressedFile) const;
    void extractAllFilesRecursively(std::string const& filePathOfCompressedFile) const;
    void extractAllRelevantFilesRecursively(std::string const& filePathOfCompressedFile) const;
    bool isTheExtensionXz(std::string const& extension) const;
    AlbaGrepStringEvaluator m_grepEvaluator;
};
}