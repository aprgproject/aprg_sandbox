#include "FileDestructor.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace std;

namespace alba
{

FileDestructor::FileDestructor()
    : m_pathToDestroy(PathInitialValueSource::DetectedLocalPath)
{}

void FileDestructor::destroy() const
{
    destroy(m_pathToDestroy.getFullPath());
}

void FileDestructor::destroy(string const& path) const
{
    renameDirectoriesUnderneath(path);
    destroyFilesAndDirectories(path);
}

void FileDestructor::renameDirectoriesUnderneath(string const& directoryPath) const
{
    AlbaLocalPathHandler pathHandler(directoryPath);
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;
    pathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& directoryFromList : listOfDirectories)
    {
        renameDirectory(directoryFromList);
    }
    listOfFiles.clear();
    listOfDirectories.clear();
    pathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& directoryFromList : listOfDirectories)
    {
        renameDirectoriesUnderneath(directoryFromList);
    }
}

void FileDestructor::destroyFilesAndDirectories(string const& path) const
{
    cout<<"Destroying files in: ["<<path<<"]\n";
    AlbaLocalPathHandler pathHandler(path);
    ListOfPaths listOfFiles;
    ListOfPaths listOfDirectories;    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    listOfFiles.erase(pathHandler.getFullPath());
    for(string const& filePath : listOfFiles)
    {        destroyFile(filePath);
    }
    for(string const& directoryPath : listOfDirectories)
    {
        cout<<"Destroying directories: ["<<path<<"]\n";
        AlbaLocalPathHandler (directoryPath).deleteDirectoryWithFilesAndDirectories();
    }
}

void FileDestructor::renameDirectory(string const& directoryPath) const
{
    cout<<"Renaming directory: ["<<directoryPath<<"]\n";
    AlbaLocalPathHandler directoryPathHandler(directoryPath);
    unsigned int retries=10;
    bool isNotSuccessful = true;    while(retries>0 && isNotSuccessful)
    {
        isNotSuccessful = !directoryPathHandler.renameImmediateDirectory(stringHelper::getRandomAlphaNumericString(10));
        if(!isNotSuccessful)
        {
            cout<<"Renamed directory: ["<<directoryPathHandler.getFullPath()<<"]\n";
        }
        retries--;
    }}

void FileDestructor::destroyFile(string const& filePath) const
{
    constexpr unsigned int MAX_CHARACTERS_ON_PATH=100;
    cout<<"Destroying File: ["<<filePath<<"]\n";
    AlbaLocalPathHandler filePathHandler(filePath);
    unsigned int retries=10;
    bool isNotSuccessful = true;    while(retries>0 && isNotSuccessful)
    {
        if(filePathHandler.getFullPath().length() > MAX_CHARACTERS_ON_PATH)
        {
            isNotSuccessful = !filePathHandler.renameFile(stringHelper::getRandomAlphaNumericString(10));
            if(!isNotSuccessful)
            {
                cout<<"Renamed File: ["<<filePathHandler.getFullPath()<<"]\n";
            }
        }
        isNotSuccessful = !filePathHandler.deleteFile();
        if(!isNotSuccessful)
        {
            cout<<"Destroyed File: ["<<filePathHandler.getFullPath()<<"]\n";
        }
        retries--;
    }}


}