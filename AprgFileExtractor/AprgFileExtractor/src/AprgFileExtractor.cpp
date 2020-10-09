#include "AprgFileExtractor.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <AlbaWindowsPathHandler.hpp>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

namespace alba
{

AprgFileExtractor::AprgFileExtractor()
    : m_grepEvaluator("")
{}

AprgFileExtractor::AprgFileExtractor(string const& condition)
    : m_grepEvaluator(condition)
{}

void AprgFileExtractor::extractAllRelevantFiles(string const& pathOfFileOrDirectory) const
{
    AlbaWindowsPathHandler fileOrDirectoryPathHandler;
    fileOrDirectoryPathHandler.inputPath(pathOfFileOrDirectory);
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

void AprgFileExtractor::copyRelativeFilePathsFromCompressedFile(string const& filePathOfCompressedFile, set<string>& files) const
{
    AlbaWindowsPathHandler filePathHandler;
    filePathHandler.inputPath(filePathOfCompressedFile);
    string command = string("") + PATH_OF_7Z_EXECUTABLE + R"( l -slt ")"
            + filePathHandler.getFullPath() + R"(" > ")"
            + PATH_OF_7Z_TEMP_FILE + R"(")";
    system(command.c_str());

    ifstream tempFile(PATH_OF_7Z_TEMP_FILE);
    string path;
    AlbaFileReader fileReader(tempFile);
    while(fileReader.isNotFinished())
    {
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "Path = "))
        {
            path = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(stringHelper::getStringAfterThisString(lineInFile, "Path = "));
        }
        else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "Attributes = "))
        {
            if(!stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(
                        stringHelper::getStringAfterThisString(lineInFile, "Attributes = "),
                        "D"))
            {
                files.emplace(path);
            }
        }
    }
}

string AprgFileExtractor::extractAll(string const& filePathOfCompressedFile) const
{
    AlbaWindowsPathHandler compressedFilePathHandler;
    compressedFilePathHandler.inputPath(filePathOfCompressedFile);
    AlbaWindowsPathHandler outputPathHandler;
    outputPathHandler.inputPath(compressedFilePathHandler.getDirectory() + R"(\)" + compressedFilePathHandler.getFilenameOnly() + R"(\)");
    string command = string("") + PATH_OF_7Z_EXECUTABLE + R"( e -y -o")"
            + outputPathHandler.getDirectory() + R"(" ")"
            + compressedFilePathHandler.getFullPath() + R"(" > nul)";
    system(command.c_str());
    cout<<"extractAll: "<<outputPathHandler.getImmediateDirectoryName()<<R"(\)"<<endl;
    return outputPathHandler.getFullPath();
}

string AprgFileExtractor::extractOneFile(string const& filePathOfCompressedFile, string const& relativePathOfFile) const
{
    AlbaWindowsPathHandler compressedFilePathHandler;
    compressedFilePathHandler.inputPath(filePathOfCompressedFile);
    AlbaWindowsPathHandler outputPathHandler;
    outputPathHandler.inputPath(compressedFilePathHandler.getDirectory() + R"(\)" + compressedFilePathHandler.getFilenameOnly() + R"(\)" + relativePathOfFile);
    string command = string("") + PATH_OF_7Z_EXECUTABLE + R"( e -y -o")"
            + outputPathHandler.getDirectory() + R"(" ")"
            + compressedFilePathHandler.getFullPath() + R"(" ")"
            + relativePathOfFile + R"(" > nul)";
    system(command.c_str());
    cout<<"extractOneFile: "<<outputPathHandler.getFile()<<endl;
    return outputPathHandler.getFullPath();
}

void AprgFileExtractor::extractAllRelevantFilesInThisDirectory(string const& directoryPath) const
{
    AlbaWindowsPathHandler directoryPathHandler;
    directoryPathHandler.inputPath(directoryPath);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& filePath: listOfFiles)
    {
        AlbaWindowsPathHandler extractedPathHandler;
        extractedPathHandler.inputPath(filePath);
        if(isCompressedFile(extractedPathHandler.getExtension()))
        {
            extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getFullPath());
        }
    }
}

void AprgFileExtractor::extractAllRelevantFilesInThisCompressedFile(string const& filePathOfCompressedFile) const
{
    AlbaWindowsPathHandler compressedFilePathHandler;
    compressedFilePathHandler.inputPath(filePathOfCompressedFile);
    if(isTheExtensionXz(compressedFilePathHandler.getExtension()))
    {
        extractAllFilesRecursively(filePathOfCompressedFile);
    }
    else
    {
        extractAllRelevantFilesRecursively(filePathOfCompressedFile);
    }
}

void AprgFileExtractor::extractAllFilesRecursively(string const& filePathOfCompressedFile) const
{
    AlbaWindowsPathHandler extractedPathHandler;
    extractedPathHandler.inputPath(extractAll(filePathOfCompressedFile));
    if(isCompressedFile(extractedPathHandler.getExtension()))
    {
        extractAllRelevantFilesInThisDirectory(extractedPathHandler.getFullPath());
        extractedPathHandler.deleteFile();
    }
}

void AprgFileExtractor::extractAllRelevantFilesRecursively(string const& filePathOfCompressedFile) const
{
    set<string> filePaths;
    copyRelativeFilePathsFromCompressedFile(filePathOfCompressedFile, filePaths);
    for(string const filePath : filePaths)
    {
        AlbaWindowsPathHandler filePathHandler;
        filePathHandler.inputPath(filePath);
        if(m_grepEvaluator.evaluate(filePathHandler.getFile()))
        {
            AlbaWindowsPathHandler extractedPathHandler;
            extractedPathHandler.inputPath(extractOneFile(filePathOfCompressedFile, filePath));
            if(isCompressedFile(extractedPathHandler.getExtension()))
            {
                extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getFullPath());
                extractedPathHandler.deleteFile();
            }
        }
    }
}

bool AprgFileExtractor::isCompressedFile(string const& extension) const
{
    return stringHelper::isEqualNotCaseSensitive("zip", extension) ||
            stringHelper::isEqualNotCaseSensitive("tar", extension) ||
            stringHelper::isEqualNotCaseSensitive("7z", extension) ||
            stringHelper::isEqualNotCaseSensitive("xz", extension);
}

bool AprgFileExtractor::isTheExtensionXz(string const& extension) const
{
    return stringHelper::isEqualNotCaseSensitive("xz", extension);
}

}
