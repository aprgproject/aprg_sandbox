#include "FileDirectoryDatabase.hpp"

#include <AlbaStringHelper.hpp>
#include <AlbaWindowsPathHandler.hpp>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace codeReview;
using namespace std;

void FileDirectoryDatabase::printFilesAndDirectories(ostream& outputStream) const
{
    for (auto& directory :  m_directories)
    {
        outputStream << "FileDirectoryDatabase | Directory: [" << directory << "]" << endl;
    }
    for (auto& file :  m_files)
    {
        outputStream << "FileDirectoryDatabase | File: [" << file << "]" << endl;
    }
}

bool FileDirectoryDatabase::isFileIncluded(string const& baseDirectory, string const& fileName) const
{
    string whereItShouldBePath(
                getCorrectPathWithoutDoublePeriod<'\\'>(
                    getCorrectPathWithReplacedSlashCharacters<'\\'>(baseDirectory+fileName)));
    for(auto fullPathOfFileFromDatabase : m_files)
    {
        if(whereItShouldBePath == fullPathOfFileFromDatabase)
        {
            return true;
        }
        else if(isFileInFullPath(fullPathOfFileFromDatabase, fileName))
        {
            return true;
        }
    }
    return false;
}

bool FileDirectoryDatabase::isFileInFullPath(string const& fullPathFromDatabase, string const& fileName) const
{
    string correctFileName(
                getStringBeforeDoublePeriod<'\\'>(
                    getCorrectPathWithReplacedSlashCharacters<'\\'>(string("\\")+fileName)));
    int correctFileNameLength = correctFileName.length();
    int fullPathFromDatabaseLength = fullPathFromDatabase.length();
    if(correctFileNameLength < fullPathFromDatabaseLength)
    {
        string lastCharacters = fullPathFromDatabase.substr(fullPathFromDatabaseLength-correctFileNameLength);
        if(lastCharacters == correctFileName)
        {
            return true;
        }
    }
    return false;
}

string FileDirectoryDatabase::getFullPathOfFile(string const& baseDirectory, string const& fileName) const
{
    int count = 0;
    unsigned int levenshteinDistance = 0;
    int score = 0;
    string fullPathOfFirstFileFound;
    string whereItShouldBePath(
                getCorrectPathWithoutDoublePeriod<'\\'>(
                    getCorrectPathWithReplacedSlashCharacters<'\\'>(baseDirectory+fileName)));
    for(string fullPathOfFileFromDatabase: m_files)
    {
        if(whereItShouldBePath == fullPathOfFileFromDatabase)
        {
            return whereItShouldBePath;
        }
        else if(isFileInFullPath(fullPathOfFileFromDatabase, fileName))
        {
            unsigned int currentLevenshteinDistance = getLevenshteinDistance(whereItShouldBePath, fullPathOfFileFromDatabase);
            int lengthDifference = abs((int)(whereItShouldBePath.length() - fullPathOfFileFromDatabase.length()));
            int currentScore = currentLevenshteinDistance - lengthDifference;
            if(fullPathOfFirstFileFound.empty() || score > currentScore || (score == currentScore && levenshteinDistance > currentLevenshteinDistance))
            {
                fullPathOfFirstFileFound = fullPathOfFileFromDatabase;
                levenshteinDistance = currentLevenshteinDistance;
                score = currentLevenshteinDistance - lengthDifference;
            }
            count++;
        }
    }
    if(count > 1)
    {
        cout<<"FileDirectoryDatabase::getFullPathOfFile| Warning: multiple files found for file: "<<fileName<<endl;
        cout<<"WhereItShouldBe:"<<whereItShouldBePath<<endl;
        cout<<"WhereItIs: "<<fullPathOfFirstFileFound<<endl;
    }
    return fullPathOfFirstFileFound;
}

SetOfFiles& FileDirectoryDatabase::getSetOfFilesReference()
{
    return m_files;
}

SetOfDirectories& FileDirectoryDatabase::getSetOfDirectoriesReference()
{
    return m_directories;
}

void FileDirectoryDatabase::allowNonExistentDirectories()
{
    m_isNonExistentDirectoriesAllowed = true;
}

void FileDirectoryDatabase::addFileOrDirectory(string const& fileOrDirectory)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(fileOrDirectory);
    if(m_isNonExistentDirectoriesAllowed || pathHandler.isFoundInLocalSystem())
    {
        if(pathHandler.isFile())
        {
            m_files.emplace(pathHandler.getFullPath());
        }
        else if(pathHandler.isDirectory())
        {
            m_directories.emplace(pathHandler.getFullPath());
            pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", m_files, m_directories);
        }
    }
    else
    {
        cout << "FileDirectoryDatabase::addFileOrDirectory| InvalidFileAndDirectory: [" << fileOrDirectory << "]" << endl;
    }
}

