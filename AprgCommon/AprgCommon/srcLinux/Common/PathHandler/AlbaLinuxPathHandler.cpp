#include "AlbaLinuxPathHandler.hpp"

#include <Common/Linux/AlbaLinuxHelper.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLinuxTimeHelper.hpp>
#include <sys/sendfile.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>

using namespace alba::AlbaLinuxHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaLinuxPathHandler::AlbaLinuxPathHandler(string_view path)
    : AlbaPathHandler(R"(/)"), m_foundInLocalSystem(false), m_relativePath(false) {
    save(path);
}

AlbaLinuxPathHandler AlbaLinuxPathHandler::createPathHandlerForDetectedPath() {
    return AlbaLinuxPathHandler(getCurrentDetectedPath());
}

void AlbaLinuxPathHandler::clear() {
    AlbaPathHandler::clear();
    m_foundInLocalSystem = false;
    m_relativePath = false;
}

bool AlbaLinuxPathHandler::isFoundInLocalSystem() const { return m_foundInLocalSystem; }

bool AlbaLinuxPathHandler::isRelativePath() const { return m_relativePath; }

double AlbaLinuxPathHandler::getFileSizeEstimate() const {
    struct stat fileStatus {};
    double fileSize(0);
    if (0 == stat(getFullPath().c_str(), &fileStatus)) {
        fileSize = fileStatus.st_size;
    } else {
        cout << "Error in AlbaLinuxPathHandler::getFileSizeEstimate() path:[" << getFullPath()
             << "] 'stat' errno value:[" << errno << "] error message:[" << getErrorMessage(errno) << "]\n";
    }
    return fileSize;
}

AlbaDateTime AlbaLinuxPathHandler::getFileCreationTime() const {
    struct stat fileStatus {};
    AlbaDateTime fileCreationTime;
    if (0 == stat(getFullPath().c_str(), &fileStatus)) {
        timespec timeSpec{};
        clock_gettime(CLOCK_REALTIME, &timeSpec);
        fileCreationTime = convertSystemTimeToAlbaDateTime(timeSpec);
    } else {
        cout << "Error in AlbaLinuxPathHandler::getFileCreationTime() path:[" << getFullPath()
             << "] 'stat' errno value:[" << errno << "] error message:[" << getErrorMessage(errno) << "]\n";
    }
    return fileCreationTime;
}

void AlbaLinuxPathHandler::createDirectoriesForNonExisitingDirectories() const {
    string fullPath(getFullPath());
    size_t index = 0, length = static_cast<size_t>(fullPath.length());
    while (index < length) {
        size_t indexWithSlashCharacter =
            static_cast<size_t>(fullPath.find_first_of(m_slashCharacterString, index));
        if (isNpos(static_cast<int>(indexWithSlashCharacter))) {
            break;
        }
        string partialDirectory(fullPath.substr(0, indexWithSlashCharacter + 1));
        AlbaLinuxPathHandler partialDirectoryPathHandler(partialDirectory);
        if (!partialDirectoryPathHandler.isFoundInLocalSystem()) {
            mkdir(partialDirectoryPathHandler.getFullPath().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        index = indexWithSlashCharacter + 1;
    }
}

bool AlbaLinuxPathHandler::deleteFile() {
    bool isSuccessful(false);
    if (isFile()) {
        int errorReturnValue = unlink(getFullPath().c_str());
        isSuccessful = errorReturnValue == 0;
        if (!isSuccessful) {
            cout << "Error in AlbaLinuxPathHandler::deleteFile() path:[" << getFullPath() << "] 'unlink' error value:["
                 << errorReturnValue << "]\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaLinuxPathHandler::deleteDirectoryWithoutFilesAndDirectories() {
    bool isSuccessful(false);
    if (isDirectory()) {
        int errorReturnValue = rmdir(getFullPath().c_str());
        isSuccessful = errorReturnValue == 0;
        if (!isSuccessful) {
            cout << "Error in AlbaLinuxPathHandler::deleteDirectoryWithoutFilesAndDirectories() path:[" << getFullPath()
                 << "] 'rmdir' error value:[" << errorReturnValue << "]\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

void AlbaLinuxPathHandler::deleteFilesInDirectory() {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (auto&& file : listOfFiles) {
        AlbaLinuxPathHandler(file).deleteFile();
    }
    reInput();
}

void AlbaLinuxPathHandler::deleteInnerFilesAndDirectories() {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (auto&& file : listOfFiles) {
        AlbaLinuxPathHandler(file).deleteFile();
    }
    set<string>::reverse_iterator reverseIterator;
    for (reverseIterator = listOfDirectories.rbegin(); reverseIterator != listOfDirectories.rend(); ++reverseIterator) {
        AlbaLinuxPathHandler(*reverseIterator).deleteDirectoryWithoutFilesAndDirectories();
    }
    reInput();
}

void AlbaLinuxPathHandler::deleteDirectoryWithFilesAndDirectories() {
    deleteInnerFilesAndDirectories();
    deleteDirectoryWithoutFilesAndDirectories();
    reInput();
}

bool AlbaLinuxPathHandler::copyToNewFile(string_view newFilePath) {
    int readFileDescriptor;
    int writeFileDescriptor;
    struct stat statBuffer {};
    off_t offset = 0;
    bool isSuccessful(false);

    readFileDescriptor = open(getFullPath().c_str(), O_RDONLY);
    if (0 == stat(getFullPath().c_str(), &statBuffer)) {
        writeFileDescriptor = open(newFilePath.data(), O_WRONLY | O_CREAT, statBuffer.st_mode);
        if (isFile()) {
            int errorReturnValue = static_cast<int>(sendfile(
                writeFileDescriptor, readFileDescriptor, &offset, static_cast<size_t>(statBuffer.st_size)));            isSuccessful = errorReturnValue != -1;
            if (!isSuccessful) {
                cout << "Error in AlbaLinuxPathHandler::copyToNewFile() path:[" << getFullPath() << "] newFilePath:["
                     << newFilePath << "] 'sendfile' error value:[" << errorReturnValue << "]\n";            } else {
                reInput();
            }
        }
        close(writeFileDescriptor);
    } else {
        cout << "Error in AlbaLinuxPathHandler::copyToNewFile() path:[" << getFullPath() << "] 'stat' errno value:["
             << errno << "] error message:[" << getErrorMessage(errno) << "]\n";
    }
    close(readFileDescriptor);
    return isSuccessful;
}

bool AlbaLinuxPathHandler::renameFile(string_view newFileName) {
    bool isSuccessful(false);
    if (isFile()) {
        string newPath(m_directory + string(newFileName));
        int errorReturnValue = rename(getFullPath().c_str(), newPath.c_str());
        isSuccessful = errorReturnValue == 0;
        if (!isSuccessful) {            cout << "Error in AlbaLinuxPathHandler::renameFile() path:[" << getFullPath() << "] newFileName:["
                 << newFileName << "] 'rename' error value:[" << errorReturnValue << "]\n";
        } else {
            input(newPath);        }
    }
    return isSuccessful;
}

bool AlbaLinuxPathHandler::renameImmediateDirectory(string_view newDirectoryName) {
    bool isSuccessful(false);
    if (isDirectory()) {
        AlbaLinuxPathHandler newPathHandler(getFullPath());
        newPathHandler.goUp();
        newPathHandler.input(newPathHandler.getDirectory() + m_slashCharacterString + string(newDirectoryName));
        int errorReturnValue = rename(getFullPath().c_str(), newPathHandler.getFullPath().c_str());
        isSuccessful = errorReturnValue == 0;
        if (!isSuccessful) {            cout << "Error in AlbaLinuxPathHandler::renameImmediateDirectory() path:[" << getFullPath()
                 << "] newDirectoryName:[" << newDirectoryName << "] 'rename' error value:[" << errorReturnValue
                 << "]\n";
        } else {            input(newPathHandler.getFullPath());
        }
    }
    return isSuccessful;
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesOneDepth(
    string_view wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, 1);
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesMultipleDepth(
    string_view wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories, int depth) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, depth);
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesUnlimitedDepth(
    string_view wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, -1);
}

string AlbaLinuxPathHandler::getCurrentDetectedPath() {
    constexpr size_t MAX_ARGUMENT_LENGTH = 50;
    constexpr size_t MAX_PATH = 1000;
    char argument[MAX_ARGUMENT_LENGTH];
    char detectedLocalPath[MAX_PATH];

    snprintf(argument, MAX_ARGUMENT_LENGTH, "/proc/%d/exe", getpid());
    size_t length = static_cast<size_t>(readlink(argument, detectedLocalPath, MAX_PATH));
    if (length <= 0) {
        length = 1;
    }
    detectedLocalPath[length] = '\0';
    return string(detectedLocalPath);
}

void AlbaLinuxPathHandler::save(string_view path) {
    string correctPath(getCorrectPathWithoutDoublePeriod(
        // getStringWithoutCharAtTheEnd(
        getCorrectPathWithReplacedSlashCharacters(path, m_slashCharacterString)
        //   , m_slashCharacterString[0])
        ,
        m_slashCharacterString));
    if (isSlashNeededAtTheEnd(correctPath, path)) {
        correctPath = getCorrectPathWithoutDoublePeriod(correctPath + m_slashCharacterString, m_slashCharacterString);
    }
    setExtensionFromPath(correctPath);
    setDirectoryAndFileFromPath(correctPath);
    setFileType();
    m_foundInLocalSystem = canBeLocated(correctPath);
}

void AlbaLinuxPathHandler::findFilesAndDirectoriesWithDepth(
    string_view currentDirectory, string_view wildCardSearch, ListOfPaths& listOfFiles,
    ListOfPaths& listOfDirectories, int depth) const {
    if (depth == 0) {
        return;
    }
    depth -= (depth > 0) ? 1 : 0;

    DIR* directoryStream;

    directoryStream = opendir(currentDirectory.data());
    if (directoryStream != nullptr) {
        loopAllFilesAndDirectoriesInDirectoryStream(
            directoryStream, currentDirectory, wildCardSearch, listOfFiles, listOfDirectories, depth);    } else {
        cout << "Error in AlbaLinuxPathHandler::findFilesAndDirectoriesWithDepth() currentDirectory:["
             << currentDirectory << "] 'opendir' errno value:[" << errno << "] error message:["
             << getErrorMessage(errno) << "]\n";    }
    closedir(directoryStream);
}

void AlbaLinuxPathHandler::loopAllFilesAndDirectoriesInDirectoryStream(
    DIR* directoryStream, string_view currentDirectory, string_view wildCardSearch, set<string>& listOfFiles,
    set<string>& listOfDirectories, int depth) const {
    struct dirent* directoryPointer;
    do {
        directoryPointer = readdir(directoryStream);
        if (directoryPointer != nullptr) {
            string immediateFileOrDirectoryName(directoryPointer->d_name);
            bool canProceedBasedOnWildcard = wildCardSearch.empty() || "*.*" == wildCardSearch ||
                                             isWildcardMatch(immediateFileOrDirectoryName, wildCardSearch);
            bool isTheNameNotComposedOfPeriods =
                "." != immediateFileOrDirectoryName && ".." != immediateFileOrDirectoryName;
            if (isTheNameNotComposedOfPeriods && canProceedBasedOnWildcard) {
                string fullFileOrDirectoryName(string(currentDirectory) + immediateFileOrDirectoryName);
                if (isPathADirectory(fullFileOrDirectoryName)) {
                    string fullFileOrDirectoryNameWithSlash(fullFileOrDirectoryName + "/");
                    listOfDirectories.emplace(fullFileOrDirectoryNameWithSlash);                    findFilesAndDirectoriesWithDepth(
                        fullFileOrDirectoryNameWithSlash, wildCardSearch, listOfFiles, listOfDirectories, depth);
                } else {
                    listOfFiles.emplace(fullFileOrDirectoryName);                }
            }
        } else {
            cout << "Error in AlbaLinuxPathHandler::findFilesAndDirectoriesWithDepth() currentDirectory:["
                 << currentDirectory << "] 'readdir' errno value:[" << errno << "] error message:["
                 << getErrorMessage(errno) << "]\n";
        }
    } while (directoryPointer != nullptr);
}

bool AlbaLinuxPathHandler::isPathADirectory(string_view fileOrDirectoryName) const {
    bool result(false);
    if (canBeLocated(fileOrDirectoryName)) {
        struct stat statBuffer {};
        if (0 == stat(fileOrDirectoryName.data(), &statBuffer)) {
            result = S_ISDIR(statBuffer.st_mode);
        } else {
            cout << "Error in AlbaLinuxPathHandler::isPathADirectory() path:[" << getFullPath()                 << "] 'stat' errno value:[" << errno << "] error message:[" << getErrorMessage(errno) << "]\n";
        }
    }
    return result;}

bool AlbaLinuxPathHandler::canBeLocated(string_view fullPath) const {
    struct stat statBuffer {};
    return stat(fullPath.data(), &statBuffer) == 0;
}

bool AlbaLinuxPathHandler::isSlashNeededAtTheEnd(string_view correctedPath, string_view originalPath) const {    bool result = false;
    bool isCorrectPathLastCharacterNotASlash(correctedPath[correctedPath.length() - 1] != m_slashCharacterString[0]);
    if (isCorrectPathLastCharacterNotASlash) {
        if (canBeLocated(correctedPath)) {            if (isPathADirectory(correctedPath)) {
                result = true;
            }
        } else {
            bool isOriginalPathLastCharacterASlash(
                originalPath[originalPath.length() - 1] == m_slashCharacterString[0]);
            if (isOriginalPathLastCharacterASlash) {
                result = true;
            }
        }
    }
    return result;
}

}  // namespace alba
