#include "AlbaLinuxPathHandler.hpp"

#include <Linux/AlbaLinuxHelper.hpp>
#include <String/AlbaStringHelper.hpp>
#include <Time/AlbaLinuxTimeHelper.hpp>

#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>

using namespace alba::AlbaLinuxHelper;
using namespace std;

namespace alba
{

AlbaLinuxPathHandler::AlbaLinuxPathHandler(PathInitialValueSource const initialValueSource)
    : AlbaPathHandler(R"(/)")
{
    if(PathInitialValueSource::DetectedLocalPath == initialValueSource)
    {
        setPathToDetectedLocalPath();
    }
}

AlbaLinuxPathHandler::AlbaLinuxPathHandler(string const& path)
    : AlbaPathHandler(R"(/)")
{
    save(path);
}

AlbaLinuxPathHandler::~AlbaLinuxPathHandler()
{}

void AlbaLinuxPathHandler::clear()
{
    AlbaPathHandler::clear();
    m_foundInLocalSystem = false;
    m_relativePath = false;
}

double AlbaLinuxPathHandler::getFileSizeEstimate()
{
    struct stat fileStatus;
    double fileSize(0);
    if(0 == stat(getFullPath().c_str(), &fileStatus))
    {
        fileSize = fileStatus.st_size;
    }
    else
    {
        cout<<"Error in AlbaLinuxPathHandler::getFileSizeEstimate() path:["<<getFullPath()
           <<"] 'stat' errno value:["<<errno<<"] error message:["<<getErrorMessage(errno)<<"]"<<endl;
    }
    return fileSize;
}

AlbaDateTime AlbaLinuxPathHandler::getFileCreationTime()
{
    struct stat fileStatus;
    AlbaDateTime fileCreationTime;
    if(0 == stat(getFullPath().c_str(), &fileStatus))
    {
        struct timespec timeSpec;
        clock_gettime(CLOCK_REALTIME, &timeSpec);
        fileCreationTime = convertSystemTimeToAlbaDateTime(timeSpec);
    }
    else
    {
        cout<<"Error in AlbaLinuxPathHandler::getFileCreationTime() path:["<<getFullPath()
           <<"] 'stat' errno value:["<<errno<<"] error message:["<<getErrorMessage(errno)<<"]"<<endl;
    }
    return fileCreationTime;
}

bool AlbaLinuxPathHandler::isFoundInLocalSystem() const
{
    return m_foundInLocalSystem;
}

bool AlbaLinuxPathHandler::isRelativePath() const
{
    return m_relativePath;
}

void AlbaLinuxPathHandler::setPathToDetectedLocalPath()
{
    constexpr unsigned int MAX_ARGUMENT_LENGTH = 50;
    constexpr unsigned int MAX_PATH = 1000;
    char argument[MAX_ARGUMENT_LENGTH];
    char detectedLocalPath[MAX_PATH];

    snprintf(argument, MAX_ARGUMENT_LENGTH, "/proc/%d/exe", getpid());
    unsigned int length = static_cast<unsigned int>(readlink(argument, detectedLocalPath, MAX_PATH));
    if(length<=0)
    {
        length=1;
    }
    detectedLocalPath[length] = '\0';
    input(string(detectedLocalPath));
}

void AlbaLinuxPathHandler::createDirectoriesForNonExisitingDirectories() const
{
    string fullPath(getFullPath());
    unsigned int index = 0, length = static_cast<unsigned int>(fullPath.length());
    while(index < length)
    {
        unsigned int indexWithSlashCharacter = static_cast<unsigned int>(fullPath.find_first_of(m_slashCharacterString, index));
        if(stringHelper::isNpos(static_cast<int>(indexWithSlashCharacter))){break;}
        string partialDirectory(fullPath.substr(0, indexWithSlashCharacter+1));
        AlbaLinuxPathHandler partialDirectoryPathHandler(partialDirectory);
        if(!partialDirectoryPathHandler.isFoundInLocalSystem())
        {
            mkdir(partialDirectoryPathHandler.getFullPath().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        index = indexWithSlashCharacter+1;
    }
}

bool AlbaLinuxPathHandler::deleteFile()
{
    bool isSuccessful(false);
    if(isFile())
    {
        int errorReturnValue = unlink(getFullPath().c_str());
        isSuccessful = errorReturnValue==0;
        if(!isSuccessful)
        {
            cout<<"Error in AlbaLinuxPathHandler::deleteFile() path:["<<getFullPath()<<"] 'unlink' error value:["<<errorReturnValue<<"]"<<endl;
        }
        else
        {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaLinuxPathHandler::deleteDirectoryWithoutFilesAndDirectories()
{
    bool isSuccessful(false);
    if(isDirectory())
    {
        int errorReturnValue = rmdir(getFullPath().c_str());
        isSuccessful = errorReturnValue==0;
        if(!isSuccessful)
        {
            cout<<"Error in AlbaLinuxPathHandler::deleteDirectoryWithoutFilesAndDirectories() path:["<<getFullPath()<<"] 'rmdir' error value:["<<errorReturnValue<<"]"<<endl;
        }
        else
        {
            reInput();
        }
    }
    return isSuccessful;
}

void AlbaLinuxPathHandler::deleteFilesInDirectory()
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& file: listOfFiles)
    {
        AlbaLinuxPathHandler(file).deleteFile();
    }
    reInput();
}

void AlbaLinuxPathHandler::deleteDirectoryWithFilesAndDirectories()
{
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& file: listOfFiles)
    {
        AlbaLinuxPathHandler(file).deleteFile();
    }
    set<string>::reverse_iterator reverseIterator;
    for (reverseIterator=listOfDirectories.rbegin(); reverseIterator != listOfDirectories.rend(); ++reverseIterator)
    {
        AlbaLinuxPathHandler(*reverseIterator).deleteDirectoryWithoutFilesAndDirectories();
    }
    deleteDirectoryWithoutFilesAndDirectories();
    reInput();
}

bool AlbaLinuxPathHandler::copyToNewFile(string const& newFilePath)
{
    int readFileDescriptor;
    int writeFileDescriptor;
    struct stat statBuffer;
    off_t offset = 0;
    bool isSuccessful(false);

    readFileDescriptor = open(getFullPath().c_str(), O_RDONLY);
    if(0 == stat(getFullPath().c_str(), &statBuffer))
    {
        writeFileDescriptor = open(newFilePath.c_str(), O_WRONLY | O_CREAT, statBuffer.st_mode);
        if(isFile())
        {
            int errorReturnValue = static_cast<int>(sendfile(writeFileDescriptor, readFileDescriptor, &offset, static_cast<unsigned long>(statBuffer.st_size)));
            isSuccessful = errorReturnValue!=-1;
            if(!isSuccessful)
            {
                cout<<"Error in AlbaLinuxPathHandler::copyToNewFile() path:["<<getFullPath()<<"] newFilePath:["<<newFilePath<<"] 'sendfile' error value:["<<errorReturnValue<<"]"<<endl;
            }
            else
            {
                reInput();
            }
        }
        close (writeFileDescriptor);
    }
    else
    {
        cout<<"Error in AlbaLinuxPathHandler::copyToNewFile() path:["<<getFullPath()
           <<"] 'stat' errno value:["<<errno<<"] error message:["<<getErrorMessage(errno)<<"]"<<endl;
    }
    close (readFileDescriptor);
    return isSuccessful;
}

bool AlbaLinuxPathHandler::renameFile(string const& newFileName)
{
    bool isSuccessful(false);
    if(isFile())
    {
        string newPath(m_directory+newFileName);
        int errorReturnValue = rename(getFullPath().c_str(), newPath.c_str());
        isSuccessful = errorReturnValue==0;
        if(!isSuccessful)
        {
            cout<<"Error in AlbaLinuxPathHandler::renameFile() path:["<<getFullPath()<<"] newFileName:["<<newFileName<<"] 'rename' error value:["<<errorReturnValue<<"]"<<endl;
        }
        else
        {
            input(newPath);
        }
    }
    return isSuccessful;
}

bool AlbaLinuxPathHandler::renameImmediateDirectory(string const& newDirectoryName)
{
    bool isSuccessful(false);
    if(isDirectory())
    {
        AlbaLinuxPathHandler newPathHandler(getFullPath());
        newPathHandler.goUp();
        newPathHandler.input(newPathHandler.getDirectory()+m_slashCharacterString+newDirectoryName);
        int errorReturnValue = rename(getFullPath().c_str(), newPathHandler.getFullPath().c_str());
        isSuccessful = errorReturnValue==0;
        if(!isSuccessful)
        {
            cout<<"Error in AlbaLinuxPathHandler::renameImmediateDirectory() path:["<<getFullPath()<<"] newDirectoryName:["<<newDirectoryName<<"] 'rename' error value:["<<errorReturnValue<<"]"<<endl;
        }
        else
        {
            input(newPathHandler.getFullPath());
        }
    }
    return isSuccessful;
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesOneDepth(
        string const& wildCardSearch,
        set<string>& listOfFiles,
        set<string>& listOfDirectories) const
{
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, 1);
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesMultipleDepth(
        string const& wildCardSearch,
        set<string>& listOfFiles,
        set<string>& listOfDirectories,
        int depth) const
{
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, depth);
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesUnlimitedDepth(
        string const& wildCardSearch,
        set<string>& listOfFiles,
        set<string>& listOfDirectories) const
{
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, -1);
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesWithDepth(
        string const& currentDirectory,
        string const& wildCardSearch,
        set<string>& listOfFiles,
        set<string>& listOfDirectories,
        int depth) const
{
    if(depth==0) {return;}
    depth -= (depth>0) ? 1 : 0;

    DIR *directoryStream;

    directoryStream  = opendir(currentDirectory.c_str());
    if(directoryStream != nullptr)
    {
        loopAllFilesAndDirectoriesInDirectoryStream(directoryStream, currentDirectory, wildCardSearch, listOfFiles, listOfDirectories, depth);
    }
    else
    {
        cout<<"Error in AlbaLinuxPathHandler::findFilesAndDirectoriesWithDepth() currentDirectory:["<<currentDirectory
           <<"] 'opendir' errno value:["<<errno<<"] error message:["<<getErrorMessage(errno)<<"]"<<endl;
    }
    closedir(directoryStream);
}

void AlbaLinuxPathHandler::loopAllFilesAndDirectoriesInDirectoryStream(
        DIR *directoryStream,
        string const& currentDirectory,
        string const& wildCardSearch,
        set<string>& listOfFiles,
        set<string>& listOfDirectories,
        int depth) const
{
    struct dirent *directoryPointer;
    do
    {
        directoryPointer = readdir(directoryStream);
        if(directoryPointer != nullptr)
        {
            string immediateFileOrDirectoryName(directoryPointer->d_name);
            bool canProceedBasedOnWildcard = wildCardSearch.empty() || "*.*" == wildCardSearch || stringHelper::isWildcardMatch(immediateFileOrDirectoryName, wildCardSearch);
            bool isTheNameNotComposedOfPeriods = "." != immediateFileOrDirectoryName && ".." != immediateFileOrDirectoryName;
            if(isTheNameNotComposedOfPeriods && canProceedBasedOnWildcard)
            {
                string fullFileOrDirectoryName(currentDirectory+immediateFileOrDirectoryName);
                if(isPathADirectory(fullFileOrDirectoryName))
                {
                    string fullFileOrDirectoryNameWithSlash(fullFileOrDirectoryName+"/");
                    listOfDirectories.emplace(fullFileOrDirectoryNameWithSlash);
                    findFilesAndDirectoriesWithDepth(fullFileOrDirectoryNameWithSlash, wildCardSearch, listOfFiles, listOfDirectories, depth);
                }
                else
                {
                    listOfFiles.emplace(fullFileOrDirectoryName);
                }
            }
        }
        else
        {
            cout<<"Error in AlbaLinuxPathHandler::findFilesAndDirectoriesWithDepth() currentDirectory:["<<currentDirectory
               <<"] 'readdir' errno value:["<<errno<<"] error message:["<<getErrorMessage(errno)<<"]"<<endl;
        }
    }
    while(directoryPointer != nullptr);
}

void AlbaLinuxPathHandler::save(string const& path)
{
    string correctPath(stringHelper::getCorrectPathWithoutDoublePeriod(
                           stringHelper::getStringWithoutCharAtTheEnd(
                               stringHelper::getCorrectPathWithReplacedSlashCharacters(
                                   path , m_slashCharacterString)
                               , m_slashCharacterString[0])
                       , m_slashCharacterString));
    if(isSlashNeededAtTheEnd(correctPath, path))
    {
        correctPath = stringHelper::getCorrectPathWithoutDoublePeriod(correctPath + m_slashCharacterString, m_slashCharacterString);
    }
    setExtensionFromPath(correctPath);
    setDirectoryAndFileFromPath(correctPath);
    setFileType();
    m_foundInLocalSystem = canBeLocated(correctPath);
}

bool AlbaLinuxPathHandler::isPathADirectory(string const& fileOrDirectoryName) const
{
    bool result(false);
    if(canBeLocated(fileOrDirectoryName))
    {
        struct stat statBuffer;
        if(0 == stat(fileOrDirectoryName.c_str(), &statBuffer))
        {
            result = S_ISDIR(statBuffer.st_mode);
        }
        else
        {
            cout<<"Error in AlbaLinuxPathHandler::isPathADirectory() path:["<<getFullPath()
               <<"] 'stat' errno value:["<<errno<<"] error message:["<<getErrorMessage(errno)<<"]"<<endl;
        }
    }
    return result;
}

bool AlbaLinuxPathHandler::canBeLocated(string const& fullPath) const
{
    struct stat statBuffer;
    return stat(fullPath.c_str(), &statBuffer)==0;
}

bool AlbaLinuxPathHandler::isSlashNeededAtTheEnd(string const& correctPath, string const& path) const
{
    bool result = false;
    if(canBeLocated(correctPath))
    {
        if(isPathADirectory(correctPath))
        {
            result=true;
        }
    }
    else
    {
        bool isLastCharacterSlash(path[path.length()-1] == m_slashCharacterString[0]);
        if(isLastCharacterSlash)
        {
            result=true;
        }
    }
    return result;
}

}//namespace alba
