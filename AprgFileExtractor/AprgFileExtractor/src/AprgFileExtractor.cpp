#include "AprgFileExtractor.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <windows.h>

#include <fstream>
#include <iostream>

#ifndef PATH_OF_7Z_EXECUTABLE
    static_assert(false, "PATH_OF_7Z_EXECUTABLE is not set in cmake");
#endif

#ifndef PATH_OF_7Z_TEMP_FILE
    static_assert(false, "PATH_OF_7Z_TEMP_FILE is not set in cmake");
#endif

using namespace std;

namespace alba
{

namespace ProgressCounters
{
extern int numberOfFilesToBeAnalyzedForExtraction;
extern int numberOfFilesAnalyzedForExtraction;
}

AprgFileExtractor::AprgFileExtractor()
    : m_grepEvaluator("")
    , m_pathOf7zExecutable(AlbaLocalPathHandler(PATH_OF_7Z_EXECUTABLE).getFullPath())
    , m_pathOf7zTempFile(AlbaLocalPathHandler(PATH_OF_7Z_TEMP_FILE).getFullPath())
{}

AprgFileExtractor::AprgFileExtractor(string const& condition)
    : m_grepEvaluator(condition)
    , m_pathOf7zExecutable(AlbaLocalPathHandler(PATH_OF_7Z_EXECUTABLE).getFullPath())
    , m_pathOf7zTempFile(AlbaLocalPathHandler(PATH_OF_7Z_TEMP_FILE).getFullPath())
{}

AprgFileExtractor::AprgFileExtractor(string const& condition, string const& pathOf7zExecutable, string const& pathOf7zTempFile)
    : m_grepEvaluator(condition)
    , m_pathOf7zExecutable(pathOf7zExecutable)
    , m_pathOf7zTempFile(pathOf7zTempFile)
{}

void AprgFileExtractor::extractAllRelevantFiles(string const& pathOfFileOrDirectory)
{
    AlbaLocalPathHandler fileOrDirectoryPathHandler(pathOfFileOrDirectory);
    if(!fileOrDirectoryPathHandler.isFoundInLocalSystem())
    {
        cout << "extractAllRelevantFiles: File or directory not found in local system." << endl;
    }
    if(fileOrDirectoryPathHandler.isDirectory())
    {
        extractAllRelevantFilesInThisDirectory(fileOrDirectoryPathHandler.getFullPath());
    }
    else
    {
        extractAllRelevantFilesInThisCompressedFile(fileOrDirectoryPathHandler.getFullPath());
    }
}

void AprgFileExtractor::copyRelativeFilePathsFromCompressedFile(string const& filePathOfCompressedFile, SetOfFilePaths& files) const
{
    AlbaLocalPathHandler filePathHandler(filePathOfCompressedFile);
    string command = string(R"(cmd /S /C "")") + m_pathOf7zExecutable + R"(" l -slt ")"
            + filePathHandler.getFullPath() + R"(" > ")"
            + m_pathOf7zTempFile + R"("")";
    system(command.c_str());

    ifstream tempFile(m_pathOf7zTempFile);
    string path;
    AlbaFileReader fileReader(tempFile);
    while(fileReader.isNotFinished())
    {
        string lineInFile(fileReader.getLine());
        if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "Path = "))
        {
            path = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(stringHelper::getStringAfterThisString(lineInFile, "Path = "));
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "Attributes = "))
        {
            if(!stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(stringHelper::getStringAfterThisString(lineInFile, "Attributes = "), "D"))
            {
                files.emplace(path);
            }
        }
    }
}

string AprgFileExtractor::extractOnceForAllFiles(string const& filePathOfCompressedFile) const
{
    AlbaLocalPathHandler compressedFilePathHandler(filePathOfCompressedFile);
    AlbaLocalPathHandler outputPathHandler(compressedFilePathHandler.getDirectory() + R"(\)" + compressedFilePathHandler.getFilenameOnly() + R"(\)");
    string command = string(R"(cmd /S /C "")") + m_pathOf7zExecutable + R"(" e -y -o")"
            + outputPathHandler.getDirectory() + R"(" ")"
            + compressedFilePathHandler.getFullPath() + R"(" > nul ")";
    system(command.c_str());
    cout<<"extractAll: "<<outputPathHandler.getImmediateDirectoryName()<<R"(\)"<<endl;
    return outputPathHandler.getFullPath();
}

string AprgFileExtractor::extractOneFile(string const& filePathOfCompressedFile, string const& relativePathOfFile) const
{
    AlbaLocalPathHandler compressedFilePathHandler(filePathOfCompressedFile);
    AlbaLocalPathHandler outputPathHandler(compressedFilePathHandler.getDirectory() + R"(\)" + compressedFilePathHandler.getFilenameOnly() + R"(\)" + relativePathOfFile);
    string command = string(R"(cmd /S /C "")") + m_pathOf7zExecutable + R"(" e -y -o")"
            + outputPathHandler.getDirectory() + R"(" ")"
            + compressedFilePathHandler.getFullPath() + R"(" ")"
            + relativePathOfFile + R"(" > nul ")";
    system(command.c_str());
    cout<<"extractOneFile: "<<outputPathHandler.getFile()<<endl;
    return outputPathHandler.getFullPath();
}

bool AprgFileExtractor::isRecognizedCompressedFile(string const& extension) const
{
    return stringHelper::isEqualNotCaseSensitive("zip", extension) ||
            stringHelper::isEqualNotCaseSensitive("tar", extension) ||
            stringHelper::isEqualNotCaseSensitive("7z", extension) ||
            stringHelper::isEqualNotCaseSensitive("xz", extension)||
            stringHelper::isEqualNotCaseSensitive("gz", extension);
}

void AprgFileExtractor::extractAllRelevantFilesInThisDirectory(string const& directoryPath)
{
    AlbaLocalPathHandler directoryPathHandler(directoryPath);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    ProgressCounters::numberOfFilesToBeAnalyzedForExtraction += listOfFiles.size();
    for(string const& filePath: listOfFiles)
    {
        AlbaLocalPathHandler extractedPathHandler(filePath);
        if(isRecognizedCompressedFile(extractedPathHandler.getExtension()))
        {
            extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getFullPath());
        }
        ProgressCounters::numberOfFilesAnalyzedForExtraction++;
    }
}

void AprgFileExtractor::extractAllRelevantFilesInThisCompressedFile(string const& filePathOfCompressedFile)
{
    AlbaLocalPathHandler compressedFilePathHandler(filePathOfCompressedFile);
    if(isTheExtensionXzOrGzOrTar(compressedFilePathHandler.getExtension()))
    {
        if(m_grepEvaluator.evaluate(compressedFilePathHandler.getFile()))
        {
            extractAllFilesRecursively(filePathOfCompressedFile);
        }
    }
    else
    {
        extractAllRelevantFilesRecursively(filePathOfCompressedFile);
    }
}

void AprgFileExtractor::extractAllFilesRecursively(string const& filePathOfCompressedFile)
{
    AlbaLocalPathHandler extractedPathHandler(extractOnceForAllFiles(filePathOfCompressedFile));
    extractAllRelevantFilesInThisDirectory(extractedPathHandler.getFullPath());
}

void AprgFileExtractor::extractAllRelevantFilesRecursively(string const& filePathOfCompressedFile)
{
    set<string> filePaths;
    copyRelativeFilePathsFromCompressedFile(filePathOfCompressedFile, filePaths);
    ProgressCounters::numberOfFilesToBeAnalyzedForExtraction += filePaths.size();
    for(string const filePath : filePaths)
    {
        AlbaLocalPathHandler filePathHandler(filePath);
        if(m_grepEvaluator.evaluate(filePathHandler.getFile()))
        {
            AlbaLocalPathHandler extractedPathHandler(extractOneFile(filePathOfCompressedFile, filePath));
            if(isRecognizedCompressedFile(extractedPathHandler.getExtension()))
            {
                extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getFullPath());
                extractedPathHandler.deleteFile();
            }
        }
        ProgressCounters::numberOfFilesAnalyzedForExtraction++;
    }
}

bool AprgFileExtractor::isTheExtensionXzOrGzOrTar(string const& extension) const
{
    return stringHelper::isEqualNotCaseSensitive("xz", extension) || stringHelper::isEqualNotCaseSensitive("gz", extension) || stringHelper::isEqualNotCaseSensitive("tar", extension);
}

}
