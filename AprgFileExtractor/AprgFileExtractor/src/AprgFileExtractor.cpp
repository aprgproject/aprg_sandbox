#include "AprgFileExtractor.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iostream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
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
    AlbaWindowsPathHandler fileOrDirectoryPathHandler(pathOfFileOrDirectory);
    if(!fileOrDirectoryPathHandler.isFoundInLocalSystem())
    {
        cout << "extractAllRelevantFiles: File or directory not found in local system." << endl;
    }
    if(fileOrDirectoryPathHandler.isDirectory())
    {
        extractAllRelevantFilesInThisDirectory(fileOrDirectoryPathHandler.getFullPath());    }
    else
    {
        extractAllRelevantFilesInThisCompressedFile(fileOrDirectoryPathHandler.getFullPath());
    }
}

void AprgFileExtractor::copyRelativeFilePathsFromCompressedFile(string const& filePathOfCompressedFile, set<string>& files) const
{
    AlbaWindowsPathHandler filePathHandler(filePathOfCompressedFile);
    string command = string("") + PATH_OF_7Z_EXECUTABLE + R"( l -slt ")"
            + filePathHandler.getFullPath() + R"(" > ")"
            + PATH_OF_7Z_TEMP_FILE + R"(")";
    system(command.c_str());

    ifstream tempFile(PATH_OF_7Z_TEMP_FILE);
    string path;    AlbaFileReader fileReader(tempFile);
    while(fileReader.isNotFinished())
    {
        string lineInFile(fileReader.simpleGetLine());
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
string AprgFileExtractor::extractAll(string const& filePathOfCompressedFile) const
{
    AlbaWindowsPathHandler compressedFilePathHandler(filePathOfCompressedFile);
    AlbaWindowsPathHandler outputPathHandler(compressedFilePathHandler.getDirectory() + R"(\)" + compressedFilePathHandler.getFilenameOnly() + R"(\)");
    string command = string("") + PATH_OF_7Z_EXECUTABLE + R"( e -y -o")"
            + outputPathHandler.getDirectory() + R"(" ")"
            + compressedFilePathHandler.getFullPath() + R"(" > nul)";
    system(command.c_str());
    cout<<"extractAll: "<<outputPathHandler.getImmediateDirectoryName()<<R"(\)"<<endl;
    return outputPathHandler.getFullPath();
}
string AprgFileExtractor::extractOneFile(string const& filePathOfCompressedFile, string const& relativePathOfFile) const
{
    AlbaWindowsPathHandler compressedFilePathHandler(filePathOfCompressedFile);
    AlbaWindowsPathHandler outputPathHandler(compressedFilePathHandler.getDirectory() + R"(\)" + compressedFilePathHandler.getFilenameOnly() + R"(\)" + relativePathOfFile);
    string command = string("") + PATH_OF_7Z_EXECUTABLE + R"( e -y -o")"
            + outputPathHandler.getDirectory() + R"(" ")"
            + compressedFilePathHandler.getFullPath() + R"(" ")"
            + relativePathOfFile + R"(" > nul)";
    system(command.c_str());
    cout<<"extractOneFile: "<<outputPathHandler.getFile()<<endl;
    return outputPathHandler.getFullPath();}

bool AprgFileExtractor::isRecognizedCompressedFile(string const& extension) const
{
    return stringHelper::isEqualNotCaseSensitive("zip", extension) ||
            stringHelper::isEqualNotCaseSensitive("tar", extension) ||
            stringHelper::isEqualNotCaseSensitive("7z", extension) ||
            stringHelper::isEqualNotCaseSensitive("xz", extension);
}

void AprgFileExtractor::extractAllRelevantFilesInThisDirectory(string const& directoryPath) const
{
    AlbaWindowsPathHandler directoryPathHandler(directoryPath);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& filePath: listOfFiles)
    {
        AlbaWindowsPathHandler extractedPathHandler(filePath);
        if(isRecognizedCompressedFile(extractedPathHandler.getExtension()))
        {
            extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getFullPath());
        }
    }
}
void AprgFileExtractor::extractAllRelevantFilesInThisCompressedFile(string const& filePathOfCompressedFile) const
{
    AlbaWindowsPathHandler compressedFilePathHandler(filePathOfCompressedFile);
    if(isTheExtensionXz(compressedFilePathHandler.getExtension()))
    {
        extractAllFilesRecursively(filePathOfCompressedFile);
    }
    else
    {
        extractAllRelevantFilesRecursively(filePathOfCompressedFile);    }
}

void AprgFileExtractor::extractAllFilesRecursively(string const& filePathOfCompressedFile) const
{
    AlbaWindowsPathHandler extractedPathHandler(extractAll(filePathOfCompressedFile));
    if(isRecognizedCompressedFile(extractedPathHandler.getExtension()))
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
        AlbaWindowsPathHandler filePathHandler(filePath);
        if(m_grepEvaluator.evaluate(filePathHandler.getFile()))
        {
            AlbaWindowsPathHandler extractedPathHandler(extractOneFile(filePathOfCompressedFile, filePath));
            if(isRecognizedCompressedFile(extractedPathHandler.getExtension()))
            {
                extractAllRelevantFilesInThisCompressedFile(extractedPathHandler.getFullPath());
                extractedPathHandler.deleteFile();
            }
        }
    }}

bool AprgFileExtractor::isTheExtensionXz(string const& extension) const
{
    return stringHelper::isEqualNotCaseSensitive("xz", extension);
}

}
