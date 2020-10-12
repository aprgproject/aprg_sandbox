#include "AlbaWindowsPathHandler.hpp"

#include <AlbaStringHelper.hpp>
#include <functional>
#include <string>
#include <windows.h>

namespace alba
{

AlbaWindowsPathHandler::AlbaWindowsPathHandler(string const& path)
    : AlbaPathHandler(R"(\)")
{
    save(path);
}

void AlbaWindowsPathHandler::clear()
{
    AlbaPathHandler::clear();
    m_drive.clear();
    m_foundInLocalSystem = false;
    m_relativePath = false;
}

string AlbaWindowsPathHandler::getDrive() const
{
    return m_drive;
}

double AlbaWindowsPathHandler::getFileSizeEstimate()
{
    double fileSizeEstimate;
    WIN32_FILE_ATTRIBUTE_DATA attributeData;
    if (!GetFileAttributesEx(getFullPath().c_str(), GetFileExInfoStandard, &attributeData))
    {
        return 0; // error condition, could call GetLastError to find out more
    }
    fileSizeEstimate = (double)attributeData.nFileSizeHigh * 0x100000000 + attributeData.nFileSizeLow;
    return fileSizeEstimate;
}

bool AlbaWindowsPathHandler::isFoundInLocalSystem() const
{
    return m_foundInLocalSystem;
}

void AlbaWindowsPathHandler::createDirectoriesIfItDoesNotExist() const
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

void AlbaWindowsPathHandler::deleteFile()
{
    if(isFile())
    {
        DeleteFile(getFullPath().c_str());
    }
}

void AlbaWindowsPathHandler::renameFile(string const& newFileName)
{
    if(isFile())
    {
        string newPath(m_directory+newFileName);
        if(MoveFile(getFullPath().c_str(), newPath.c_str()))
        {
            input(newPath);
        }
    }
}

bool AlbaWindowsPathHandler::isRelativePath() const
{
    return m_relativePath;
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
    setDrive();
    setFileType();
    m_foundInLocalSystem = INVALID_FILE_ATTRIBUTES != attributes;
}

void AlbaWindowsPathHandler::setDrive()
{
    int index = m_directory.find_first_of(m_slashCharacterString + ":");
    if (stringHelper::isNotNpos(index) && m_directory[index]==':')
    {
        m_drive = stringHelper::getStringWithCapitalLetters(m_directory.substr(0,index));
    }
    m_relativePath = m_drive.empty();
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

}//namespace alba
