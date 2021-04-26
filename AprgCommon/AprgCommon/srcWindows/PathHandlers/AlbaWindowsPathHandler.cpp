#include "AlbaWindowsPathHandler.hpp"

#include <String/AlbaStringHelper.hpp>
#include <Time/AlbaWindowsTimeHelper.hpp>
#include <Windows/AlbaWindowsHelper.hpp>

#include <winbase.h>
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

AlbaWindowsPathHandler::~AlbaWindowsPathHandler()
{}

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
    if (GetFileAttributesExW(stringHelper::convertStringToWideString(getFullPath()).c_str(), GetFileExInfoStandard, &attributeData))
    {
        fileSizeEstimate = (double)attributeData.nFileSizeHigh * 0x100000000 + attributeData.nFileSizeLow;
    }
    else
    {
        cout<<"Error in AlbaWindowsPathHandler::getFileSizeEstimate() path:"<<getFullPath()<<endl;
        cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
    }
    return fileSizeEstimate;
}

AlbaDateTime AlbaWindowsPathHandler::getFileCreationTime()
{
    AlbaDateTime fileCreationTime;
    WIN32_FILE_ATTRIBUTE_DATA attributeData;
    if (GetFileAttributesExW(stringHelper::convertStringToWideString(getFullPath()).c_str(), GetFileExInfoStandard, &attributeData))
    {
        SYSTEMTIME fileCreationTimeInSystemTime;
        FileTimeToSystemTime(&(attributeData.ftCreationTime), &fileCreationTimeInSystemTime);
        fileCreationTime = convertSystemTimeToAlbaDateTime(fileCreationTimeInSystemTime);
    }
    else
    {
        cout<<"Error in AlbaWindowsPathHandler::getFileCreationTime() path:"<<getFullPath()<<endl;
        cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
    }
    return fileCreationTime;
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
    constexpr unsigned int MAXIMUM_CHARACTERS_PATH = 1000;
    WCHAR currentPathFromWindowsWideCharArray[MAXIMUM_CHARACTERS_PATH];
    if (GetModuleFileNameW(NULL, currentPathFromWindowsWideCharArray, MAX_PATH))
    {
        string currentPathFromWindows(stringHelper::convertWideStringToString(wstring(currentPathFromWindowsWideCharArray)));
        input(currentPathFromWindows);
    }
    else
    {
        cout<<"Error in AlbaWindowsPathHandler::setPathToDetectedLocalPath() path:"<<getFullPath()<<endl;
        cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
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
            if (!CreateDirectoryW(stringHelper::convertStringToWideString(partialDirectoryPathHandler.getFullPath()).c_str(), NULL))
            {
                cout<<"Error in AlbaWindowsPathHandler::createDirectoriesForNonExisitingDirectories() path:"<<partialDirectoryPathHandler.getFullPath()<<endl;
                cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
            }
        }
        index = indexWithSlashCharacter+1;
    }
}

bool AlbaWindowsPathHandler::deleteFile()
{
    bool isSuccessful(false);
    if(isFile())
    {
        isSuccessful = (bool)DeleteFileW(stringHelper::convertStringToWideString(getFullPath()).c_str());
        if(!isSuccessful)
        {
            cout<<"Error in AlbaWindowsPathHandler::deleteFile() path:"<<getFullPath()<<endl;
            cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
        }
        else
        {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::deleteDirectoryWithoutFilesAndDirectories()
{
    bool isSuccessful(false);
    if(isDirectory())
    {
        isSuccessful = (bool)RemoveDirectoryW(stringHelper::convertStringToWideString(getFullPath()).c_str());
        if(!isSuccessful)
        {
            cout<<"Error in AlbaWindowsPathHandler::RemoveDirectory() path:"<<getFullPath()<<endl;
            cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
        }
        else
        {
            reInput();
        }
    }
    return isSuccessful;
}

void AlbaWindowsPathHandler::deleteFilesInDirectory()
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& file: listOfFiles)
    {
        AlbaWindowsPathHandler(file).deleteFile();
    }
    reInput();
}

void AlbaWindowsPathHandler::deleteInnerFilesAndDirectories()
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& file: listOfFiles)
    {
        AlbaWindowsPathHandler(file).deleteFile();
    }
    set<string>::reverse_iterator reverseIterator;
    for (reverseIterator=listOfDirectories.rbegin(); reverseIterator != listOfDirectories.rend(); ++reverseIterator)
    {
        AlbaWindowsPathHandler(*reverseIterator).deleteDirectoryWithoutFilesAndDirectories();
    }
    reInput();
}

void AlbaWindowsPathHandler::deleteDirectoryWithFilesAndDirectories()
{
    deleteInnerFilesAndDirectories();
    deleteDirectoryWithoutFilesAndDirectories();
    reInput();
}

bool AlbaWindowsPathHandler::copyToNewFile(string const& newFilePath)
{
    bool isSuccessful(false);
    if(isFile())
    {
        isSuccessful = (bool)CopyFileW(stringHelper::convertStringToWideString(getFullPath()).c_str(), stringHelper::convertStringToWideString(newFilePath).c_str(), 0);
        if(!isSuccessful)
        {
            cout<<"Error in AlbaWindowsPathHandler::CopyFile() path:["<<getFullPath()<<"] newFilePath:["<<newFilePath<<"]"<<endl;
            cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
        }
        else
        {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::renameFile(string const& newFileName)
{
    bool isSuccessful(false);
    if(isFile())
    {
        string newPath(m_directory+newFileName);
        isSuccessful = (bool)MoveFileW(stringHelper::convertStringToWideString(getFullPath()).c_str(), stringHelper::convertStringToWideString(newPath).c_str());
        if(!isSuccessful)
        {
            cout<<"Error in AlbaWindowsPathHandler::renameFile() path:"<<getFullPath()<<" newFileName:"<<newFileName<<endl;
            cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
        }
        else
        {
            input(newPath);
        }
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
        isSuccessful = (bool)MoveFileW(stringHelper::convertStringToWideString(getFullPath()).c_str(), stringHelper::convertStringToWideString(newPathHandler.getFullPath()).c_str());
        if(!isSuccessful)
        {
            cout<<"Error in AlbaWindowsPathHandler::renameImmediateDirectory() path:"<<getFullPath()<<" newDirectoryName:"<<newDirectoryName<<endl;
            cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
        }
        else
        {
            input(newPathHandler.getFullPath());
        }
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
    WIN32_FIND_DATAW data;

    if(depth==0) {return;}
    depth -= (depth>0) ? 1 : 0;

    hFind = FindFirstFileW(stringHelper::convertStringToWideString(string(currentDirectory+wildCardSearch)).c_str(), &data);
    bool bContinue(hFind != INVALID_HANDLE_VALUE);
    while (bContinue)
    {
        string fileOrDirectoryName(stringHelper::convertWideStringToString(wstring(data.cFileName)));
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
        bContinue = FindNextFileW(hFind, &data);
    }
}

void AlbaWindowsPathHandler::save(string const& path)
{
    string correctPath(stringHelper::getCorrectPathWithoutDoublePeriod(
                           stringHelper::getCorrectPathWithReplacedSlashCharacters(
                               path, m_slashCharacterString), m_slashCharacterString));
    if(isSlashNeededAtTheEnd(correctPath, path))
    {
        correctPath = stringHelper::getCorrectPathWithoutDoublePeriod(correctPath + m_slashCharacterString, m_slashCharacterString);
    }

    setExtensionFromPath(correctPath);
    setDirectoryAndFileFromPath(correctPath);
    setDriveOrRoot();
    setFileType();
    m_foundInLocalSystem = canBeLocated(correctPath);
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

bool AlbaWindowsPathHandler::canBeLocated(string const& fullPath) const
{
    DWORD attributes = GetFileAttributesW(stringHelper::convertStringToWideString(fullPath).c_str());
    return INVALID_FILE_ATTRIBUTES != attributes;
}

bool AlbaWindowsPathHandler::isSlashNeededAtTheEnd(string const& correctedPath, string const& originalPath) const
{
    bool result(false);
    bool isCorrectPathLastCharacterIsNotSlash(correctedPath[correctedPath.length()-1] != m_slashCharacterString[0]);
    if(isCorrectPathLastCharacterIsNotSlash)
    {
        DWORD attributes = GetFileAttributesW(stringHelper::convertStringToWideString(correctedPath).c_str());
        bool isFoundInWindows(INVALID_FILE_ATTRIBUTES != attributes);
        if(isFoundInWindows)
        {
            bool isDirectoryInWindows(attributes & FILE_ATTRIBUTE_DIRECTORY);
            if(isDirectoryInWindows)
            {
                result=true;
            }
        }
        else
        {
            bool isPathLastCharacterIsSlash(originalPath[originalPath.length()-1] == m_slashCharacterString[0]);
            if(isPathLastCharacterIsSlash)
            {
                result=true;
            }
        }
    }
    return result;
}

}//namespace alba
