#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <set>
#include <string>

#define PATH_OF_7Z_EXECUTABLE R"(C:\APRG\AprgFileExtractor\7z\7z.exe)"
#define PATH_OF_7Z_TEMP_FILE R"(C:\APRG\AprgFileExtractor\7z\TempFile.txt)"

using std::set;

namespace alba
{

class AprgFileExtractor
{
public:
    AprgFileExtractor();
    AprgFileExtractor(string const& condition);
    void extractAllRelevantFilesInThisDirectory(string const& directoryPath) const;
    void extractAllRelevantFilesInThisCompressedFile(string const& filePathOfCompressedFile) const;
    void copyRelativeFilePathsFromCompressedFile(string const& filePathOfCompressedFile, set<string>& files) const;
    string extractAll(string const& filePathOfCompressedFile) const;
    string extractOneFile(string const& filePathOfCompressedFile, string const& relativePathOfFile) const;
private:
    void extractAllFilesRecursively(string const& filePathOfCompressedFile) const;
    void extractAllRelevantFilesRecursively(string const& filePathOfCompressedFile) const;
    bool isCompressedFile(string const& extension) const;
    bool isTheExtensionXz(string const& extension) const;
    AlbaGrepStringEvaluator m_grepEvaluator;
};

}
