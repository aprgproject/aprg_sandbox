#include "CMakeDatabase.hpp"

#include <String/AlbaStringHelper.hpp>
#include <AlbaLocalPathHandler.hpp>

#include <iostream>

using namespace std;
using namespace alba;

namespace codeReview
{

CMakeDatabase::CMakeDatabase()
    : m_cMakeFileDirectoryPath()
    , m_isNonExistentDirectoriesAllowed(false)
    , m_parentCMake(*this)
    , m_hasCMakeParent(false)
{}

CMakeDatabase::CMakeDatabase(CMakeDatabase& parentCMake)
    : m_cMakeFileDirectoryPath()
    , m_isNonExistentDirectoriesAllowed(false)
    , m_parentCMake(parentCMake)
    , m_hasCMakeParent(true)
{}

SetOfFiles& CMakeDatabase::getSetOfFilesReference()
{
    return m_setOfFiles;
}

SetOfDirectories& CMakeDatabase::getSetOfDirectoriesReference()
{
    return m_setOfDirectories;
}

SubCMakeDatabases& CMakeDatabase::getSubCMakeDatabasesReference()
{
    return m_subCMakeDatabases;
}

void CMakeDatabase::printFilesAndDirectories() const
{
        //use output iterator here
    cout << "CMakeDatabase::printFilesAndDirectories| CMakeFile [" << m_cMakeFileDirectoryPath << "] contains:" << endl;
    for (auto& directory :  m_setOfDirectories)
    {
        cout << "CMakeDatabase::printFilesAndDirectories| Directory: [" << directory << "]" << endl;
    }
    for (auto& file :  m_setOfFiles)
    {
        cout << "CMakeDatabase::printFilesAndDirectories| File: [" << file << "]" << endl;
    }
    for (auto& subCMakeDatabase :  m_subCMakeDatabases)
    {
        subCMakeDatabase.printFilesAndDirectories();
    }
}

void CMakeDatabase::addFileOrDirectory(string const& fileOrDirectory)
{
    AlbaLocalPathHandler pathHandler;
    pathHandler.inputPath(fileOrDirectory);
    if(m_isNonExistentDirectoriesAllowed || pathHandler.isFoundInLocalSystem())
    {
        if(pathHandler.isFile())
        {
            m_setOfFiles.emplace(pathHandler.getFullPath());
        }
        else if(pathHandler.isDirectory())
        {
            m_setOfDirectories.emplace(pathHandler.getFullPath());
        }

    }
    else
    {
        cout << "CMakeDatabase::addFileOrDirectory| InvalidFileAndDirectory: [" << fileOrDirectory << "]" << endl;
    }
}

void CMakeDatabase::setCMakeFileDirectoryPath(string const& cMakeFileDirectoryPath)
{
    m_cMakeFileDirectoryPath = cMakeFileDirectoryPath;
}

void CMakeDatabase::allowNonExistentDirectories()
{
    m_isNonExistentDirectoriesAllowed = true;
}

CMakeDatabase& CMakeDatabase::addCMakeSubDirectory()
{
    m_subCMakeDatabases.emplace_back(*this);
    CMakeDatabase& subCMakeDatabaseReference = m_subCMakeDatabases.back();
    if(m_isNonExistentDirectoriesAllowed)
    {
        subCMakeDatabaseReference.allowNonExistentDirectories();
    }
    return subCMakeDatabaseReference;
}

CMakeDatabase& CMakeDatabase::find_InnerDirection(
        string const& stringPathIn,
        bool& isFoundResult,
        string& stringFullPathOut)
{
    isFoundResult = false;
    AlbaLocalPathHandler pathHandler;
    pathHandler.inputPath(stringPathIn);
    if(pathHandler.isFile())
    {
        return findFile<RecursionDirectionType::Inner>(pathHandler.getFullPath(), pathHandler.getWildCardSearch(), isFoundResult, stringFullPathOut);
    }
    else if(pathHandler.isDirectory())
    {
        return findDirectory<RecursionDirectionType::Inner>(pathHandler.getFullPath(), isFoundResult, stringFullPathOut);
    }
    return (*this);
}

CMakeDatabase& CMakeDatabase::find_OuterDirection(
        string const& stringPathIn,
        bool& isFoundResult,
        string& stringFullPathOut)
{
    isFoundResult = false;
    AlbaLocalPathHandler pathHandler;
    pathHandler.inputPath(stringPathIn);
    if(pathHandler.isFile())
    {
        return findFile<RecursionDirectionType::Outer>(pathHandler.getFullPath(), pathHandler.getWildCardSearch(), isFoundResult, stringFullPathOut);
    }
    else if(pathHandler.isDirectory())
    {
        return findDirectory<RecursionDirectionType::Outer>(pathHandler.getFullPath(), isFoundResult, stringFullPathOut);
    }
    return (*this);
}

void CMakeDatabase::clear()
{
    m_setOfFiles.clear();
    m_setOfDirectories.clear();
    m_subCMakeDatabases.clear();
    m_cMakeFileDirectoryPath.clear();
    m_isNonExistentDirectoriesAllowed = false;
    //m_parentCMake = *this;
    m_hasCMakeParent=false;
}

template <RecursionDirectionType direction> CMakeDatabase& CMakeDatabase::findFile(
        string const& stringPathIn,
        string const& wildCardSearch,
        bool& isFoundResult,
        string& stringFullPathOut)
{
    //stl algorithm
    for (auto& file :  m_setOfFiles)
    {
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(file, stringPathIn))
        {
            stringFullPathOut = file;
            isFoundResult = true;
            return (*this);
        }
    }
    for (auto& directory :  m_setOfDirectories)
    {
        AlbaLocalPathHandler pathHandler;
        pathHandler.inputPath(directory);
        set<string> temporaryListOfFiles;
        set<string> temporaryListOfDirectories;
        pathHandler.findFilesAndDirectoriesOneDepth(wildCardSearch, temporaryListOfFiles, temporaryListOfDirectories);
        if(temporaryListOfFiles.size()>0)
        {
            stringFullPathOut = *(temporaryListOfFiles.begin());
            isFoundResult = true;
            return (*this);
        }
    }
    return proceedToNextFile<direction>(stringPathIn, wildCardSearch, isFoundResult, stringFullPathOut);
}

template <RecursionDirectionType direction> CMakeDatabase& CMakeDatabase::findDirectory(
        string const& stringPathIn,
        bool& isFoundResult,
        string& stringFullPathOut)
{
    //stl algorithm
    for (auto& directory :  m_setOfDirectories)
    {
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(directory, stringPathIn))
        {
            stringFullPathOut = directory;
            isFoundResult = true;
            return (*this);
        }
    }
    return proceedToNextDirectory<direction>(stringPathIn, isFoundResult, stringFullPathOut);
}

template <> CMakeDatabase& CMakeDatabase::proceedToNextFile<RecursionDirectionType::Outer>(
        string const& stringPathIn,
        string const& wildCardSearch,
        bool& isFoundResult,
        string& stringFullPathOut)
{
    if(m_hasCMakeParent)
    {
        return m_parentCMake.findFile<RecursionDirectionType::Outer>(stringPathIn, wildCardSearch, isFoundResult, stringFullPathOut);
    }
    return (*this);
}

template <> CMakeDatabase& CMakeDatabase::proceedToNextFile<RecursionDirectionType::Inner>(
        string const& stringPathIn,
        string const& wildCardSearch,
        bool& isFoundResult,
        string& stringFullPathOut)
{
    for (auto& subCMakeDatabase : m_subCMakeDatabases)
    {
        CMakeDatabase& cMakeFileDirectoryDatabaseReference
                = subCMakeDatabase.findFile<RecursionDirectionType::Inner>(stringPathIn, wildCardSearch, isFoundResult, stringFullPathOut);
        if(isFoundResult)
        {
            return cMakeFileDirectoryDatabaseReference;
        }
    }
    return (*this);
}


template <> CMakeDatabase& CMakeDatabase::proceedToNextDirectory<RecursionDirectionType::Inner>(
        string const& stringPathIn,
        bool& isFoundResult,
        string& stringFullPathOut)
{
    for (auto& subCMakeDatabase :  m_subCMakeDatabases)
    {
        CMakeDatabase& cMakeFileDirectoryDatabaseReference
                = subCMakeDatabase.findDirectory<RecursionDirectionType::Inner>(stringPathIn, isFoundResult, stringFullPathOut);
        if(isFoundResult)
        {
            return cMakeFileDirectoryDatabaseReference;
        }
    }
    return (*this);
}

template <> CMakeDatabase& CMakeDatabase::proceedToNextDirectory<RecursionDirectionType::Outer>(
        string const& stringPathIn,
        bool& isFoundResult,
        string& stringFullPathOut)
{
    if(m_hasCMakeParent)
    {
        return m_parentCMake.findDirectory<RecursionDirectionType::Outer>(stringPathIn, isFoundResult, stringFullPathOut);
    }
    return (*this);
}

}// namespace codeReview
