#include "AlbaWindowsPathHandler.hpp"

#include <String/AlbaStringHelper.hpp>

#include <windows.h>

#include <functional>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace alba
{

AlbaWindowsPathHandler::AlbaWindowsPathHandler(PathInitialValueSource const initialValueSource)
    : AlbaPathHandler(R"(\)")
{
    if(PathInitialValueSource::DetectedLocalPath == initialValueSource)
    {
        setPathToDetectedLocalPath();
    }
}

AlbaWindowsPathHandler::AlbaWindowsPathHandler(string const& path)
    : AlbaPathHandler(R"(\)")
{
    save(path);
}

void AlbaWindowsPathHandler::clear()
{
    AlbaPathHandler::clear();
    m_driveOrRoot.clear();
    m_foundInLocalSystem = false;
    m_relativePath = false;
}

string AlbaWindowsPathHandler::getDriveOrRoot() const
{
    return m_driveOrRoot;
}

double AlbaWindowsPathHandler::getFileSizeEstimate()
{
    double fileSizeEstimate(0);
    WIN32_FILE_ATTRIBUTE_DATA attributeData;
    if (GetFileAttributesEx(getFullPath().c_str(), GetFileExInfoStandard, &attributeData))
    {
        fileSizeEstimate = (double)attributeData.nFileSizeHigh * 0x100000000 + attributeData.nFileSizeLow;
    }
    else
    {
        cout<<"Error in AlbaWindowsPathHandler::getFileSizeEstimate() path:"<<getFullPath()<<endl;
        cout<<getLastFormattedErrorMessage()<<endl;
    }
    return fileSizeEstimate;
}

bool AlbaWindowsPathHandler::isFoundInLocalSystem() const
{
    return m_foundInLocalSystem;
}

bool AlbaWindowsPathHandler::isRelativePath() const
{
    return m_relativePath;
}

void AlbaWindowsPathHandler::setPathToDetectedLocalPath()
{
    char currentPathFromWindows[MAX_PATH] = "";
    if (GetModuleFileName(NULL, currentPathFromWindows, MAX_PATH))
    {
        input(string(currentPathFromWindows));
    }
    else
    {
        cout<<"Error in AlbaWindowsPathHandler::setPathToDetectedLocalPath() path:"<<getFullPath()<<endl;
        cout<<getLastFormattedErrorMessage()<<endl;
    }
}

void AlbaWindowsPathHandler::createDirectoriesForNonExisitingDirectories() const
{
    string fullPath(getFullPath());
    int index = 0, length = fullPath.length();
    while(index < length)
    {
        int indexWithSlashCharacter = fullPath.find_first_of(m_slashCharacterString, index);
        if(stringHelper::isNpos(indexWithSlashCharacter)){break;}
        string partialDirectory(fullPath.substr(0, indexWithSlashCharacter+1));
        AlbaWindowsPathHandler partialDirectoryPathHandler(partialDirectory);
        if(!partialDirectoryPathHandler.isFoundInLocalSystem())
        {
            CreateDirectory(partialDirectoryPathHandler.getFullPath().c_str(), NULL);
        }
        index = indexWithSlashCharacter+1;
    }
}

bool AlbaWindowsPathHandler::deleteFile()
{
    bool isSuccessful(false);
    if(isFile())
    {
        isSuccessful = (bool)DeleteFile(getFullPath().c_str());
        if(!isSuccessful)
        {
            cout<<"Error in AlbaWindowsPathHandler::deleteFile() path:"<<getFullPath()<<endl;
            cout<<getLastFormattedErrorMessage()<<endl;
        }
        reInput();
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::copyToNewFile(string const& newFilePath)
{
    bool isSuccessful(false);
    if(isFile())
    {
        isSuccessful = (bool)CopyFile(getFullPath().c_str(), newFilePath.c_str(), 0);
        if(!isSuccessful)
        {
            cout<<"Error in AlbaWindowsPathHandler::CopyFile() path:["<<getFullPath()<<"] newFilePath:["<<newFilePath<<"]"<<endl;
            cout<<getLastFormattedErrorMessage()<<endl;
        }
        reInput();
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::renameFile(string const& newFileName)
{
    bool isSuccessful(false);
    if(isFile())
    {
        string newPath(m_directory+newFileName);
        isSuccessful = (bool)MoveFile(getFullPath().c_str(), newPath.c_str());
        if(!isSuccessful)
        {
            cout<<"Error in AlbaWindowsPathHandler::renameFile() path:"<<getFullPath()<<" newFileName:"<<newFileName<<endl;
            cout<<getLastFormattedErrorMessage()<<endl;
        }
        input(newPath);
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::renameImmediateDirectory(string const& newDirectoryName)
{
    bool isSuccessful(false);
    if(isDirectory())
    {
        AlbaWindowsPathHandler newPathHandler(getFullPath());
        newPathHandler.goUp();
        newPathHandler.input(newPathHandler.getDirectory()+m_slashCharacterString+newDirectoryName);
        isSuccessful = (bool)MoveFile(getFullPath().c_str(), newPathHandler.getFullPath().c_str());
        if(!isSuccessful)
        {
            cout<<"Error in AlbaWindowsPathHandler::renameImmediateDirectory() path:"<<getFullPath()<<" newDirectoryName:"<<newDirectoryName<<endl;
            cout<<getLastFormattedErrorMessage()<<endl;
        }
        input(newPathHandler.getFullPath());
    }
    return isSuccessful;
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesOneDepth(
        string const& wildCardSearch,
        set<string>& listOfFiles,
        set<string>& listOfDirectories) const
{
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, 1);
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesMultipleDepth(
        string const& wildCardSearch,
        set<string>& listOfFiles,
        set<string>& listOfDirectories,
        int depth) const
{
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, depth);
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesUnlimitedDepth(
        string const& wildCardSearch,
        set<string>& listOfFiles,
        set<string>& listOfDirectories) const
{
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, -1);
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesWithDepth(
        string const& currentDirectory,
        string const& wildCardSearch,
        set<string>& listOfFiles,
        set<string>& listOfDirectories,
        int depth) const
{
    HANDLE hFind;
    WIN32_FIND_DATA data;

    if(depth==0) {return;}
    depth -= (depth>0) ? 1 : 0;

    hFind = FindFirstFile(string(currentDirectory+wildCardSearch).c_str(), &data);
    bool bContinue(hFind != INVALID_HANDLE_VALUE);
    while (bContinue)
    {
        string fileOrDirectoryName(data.cFileName);
        if(!stringHelper::isPeriodOrDoublePeriod(fileOrDirectoryName))
        {
            if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                string newDirectory(currentDirectory+fileOrDirectoryName+'\\');
                listOfDirectories.emplace(newDirectory);
                findFilesAndDirectoriesWithDepth(newDirectory, wildCardSearch, listOfFiles, listOfDirectories, depth);
            }
            else
            {
                listOfFiles.emplace(currentDirectory+fileOrDirectoryName);
            }
        }
        bContinue = FindNextFile(hFind, &data);
    }
}

void AlbaWindowsPathHandler::save(string const& path)
{
    string correctPath(stringHelper::getCorrectPathWithoutDoublePeriod(
                           stringHelper::getCorrectPathWithReplacedSlashCharacters(
                               path, m_slashCharacterString), m_slashCharacterString));
    DWORD attributes = GetFileAttributes(correctPath.c_str());
    bool isDirectoryInWindows(attributes == FILE_ATTRIBUTE_DIRECTORY);
    bool isLastCharacterNotSlash(correctPath[correctPath.length()-1] != m_slashCharacterString[0]);
    if(isDirectoryInWindows && isLastCharacterNotSlash)
    {
        correctPath = stringHelper::getCorrectPathWithoutDoublePeriod(correctPath + m_slashCharacterString, m_slashCharacterString);
    }
    setExtensionFromPath(correctPath);
    setDirectoryAndFileFromPath(correctPath);
    setDriveOrRoot();
    setFileType();
    m_foundInLocalSystem = INVALID_FILE_ATTRIBUTES != attributes;
}

void AlbaWindowsPathHandler::setDriveOrRoot()
{
    int index = m_directory.find_first_of(m_slashCharacterString + ":");
    if (stringHelper::isNotNpos(index) && m_directory[index]==':')
    {
        m_driveOrRoot = stringHelper::getStringWithCapitalLetters(m_directory.substr(0,index));
    }
    m_relativePath = m_driveOrRoot.empty();
}

string AlbaWindowsPathHandler::getLastFormattedErrorMessage() const
{
    stringstream lastError("No message from windows");
    unsigned int errorCode = GetLastError();
    if (errorCode)
    {
        LPVOID lpMessageBuffer;
        DWORD bufferLength = FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    errorCode,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPTSTR) &lpMessageBuffer,
                    0, NULL );
        if(bufferLength)
        {
            LPCSTR lpMessageString = (LPCSTR)lpMessageBuffer;
            std::string errorMessageFromWindows(lpMessageString, lpMessageString+bufferLength);
            LocalFree(lpMessageBuffer);
            lastError<<"Error from windows: ["<<errorMessageFromWindows<<"] ErrorCode:["<<errorCode<<"]"<<endl;
        }
    }
    return lastError.str();
}

}//namespace alba
