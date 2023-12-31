#include "AlbaWindowsPathHandler.hpp"

#include <Common/Macros/AlbaMacros.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaWindowsTimeHelper.hpp>
#include <Common/Windows/AlbaWindowsHelper.hpp>

#include <winbase.h>
#include <windows.h>

#include <functional>
#include <iostream>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaWindowsPathHandler::AlbaWindowsPathHandler(string_view path) : AlbaPathHandler(R"(\)") { setPath(path); }

AlbaWindowsPathHandler AlbaWindowsPathHandler::createPathHandlerForDetectedPath() {
    return AlbaWindowsPathHandler(getCurrentDetectedPath());
}

void AlbaWindowsPathHandler::clear() {
    AlbaPathHandler::clear();
    m_driveOrRoot.clear();
    m_foundInLocalSystem = false;
    m_relativePath = false;
}

string AlbaWindowsPathHandler::getDriveOrRoot() const { return m_driveOrRoot; }

double AlbaWindowsPathHandler::getFileSizeEstimate() {
    double fileSizeEstimate(0);
    WIN32_FILE_ATTRIBUTE_DATA attributeData;
    if (GetFileAttributesExW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(), GetFileExInfoStandard,
            &attributeData)) {
        fileSizeEstimate = (double)attributeData.nFileSizeHigh * 0x100'000'000 + attributeData.nFileSizeLow;
    } else {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << "Path:" << getFullPath() << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }
    return fileSizeEstimate;
}

AlbaDateTime AlbaWindowsPathHandler::getFileCreationTime() {
    AlbaDateTime fileCreationTime;
    WIN32_FILE_ATTRIBUTE_DATA attributeData;
    if (GetFileAttributesExW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(), GetFileExInfoStandard,
            &attributeData)) {
        SYSTEMTIME fileCreationTimeInSystemTime;
        FileTimeToSystemTime(&(attributeData.ftCreationTime), &fileCreationTimeInSystemTime);
        fileCreationTime = convertSystemTimeToAlbaDateTime(fileCreationTimeInSystemTime);
    } else {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << "Path:" << getFullPath() << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }
    return fileCreationTime;
}

bool AlbaWindowsPathHandler::isFoundInLocalSystem() const { return m_foundInLocalSystem; }

bool AlbaWindowsPathHandler::isRelativePath() const { return m_relativePath; }

void AlbaWindowsPathHandler::createDirectoriesForNonExisitingDirectories() const {
    string fullPath(getFullPath());
    int index = 0, length = fullPath.length();
    while (index < length) {
        int indexWithSlashCharacter = fullPath.find_first_of(m_slashCharacterString, index);
        if (isNpos(indexWithSlashCharacter)) {
            break;
        }
        string partialDirectory(fullPath.substr(0, indexWithSlashCharacter + 1));
        AlbaWindowsPathHandler partialDirectoryPathHandler(partialDirectory);
        if (!partialDirectoryPathHandler.isFoundInLocalSystem()) {
            if (!CreateDirectoryW(
                    convertToAnotherBasicStringVariant<string, wstring>(partialDirectoryPathHandler.getFullPath())
                        .c_str(),
                    NULL)) {
                cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
                cout << "Path: [" << partialDirectoryPathHandler.getFullPath() << "]\n";
                cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
            }
        }
        index = indexWithSlashCharacter + 1;
    }
}

bool AlbaWindowsPathHandler::deleteFile() {
    bool isSuccessful(false);
    if (isFile()) {
        isSuccessful = (bool)DeleteFileW(convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str());
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::deleteDirectoryWithoutFilesAndDirectories() {
    bool isSuccessful(false);
    if (isDirectory()) {
        isSuccessful =
            (bool)RemoveDirectoryW(convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str());
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

void AlbaWindowsPathHandler::deleteFilesInDirectory() {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (auto&& file : listOfFiles) {
        AlbaWindowsPathHandler(file).deleteFile();
    }
    reInput();
}

void AlbaWindowsPathHandler::deleteInnerFilesAndDirectories() {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (auto&& file : listOfFiles) {
        AlbaWindowsPathHandler(file).deleteFile();
    }
    set<string>::reverse_iterator reverseIterator;
    for (reverseIterator = listOfDirectories.rbegin(); reverseIterator != listOfDirectories.rend(); ++reverseIterator) {
        AlbaWindowsPathHandler(*reverseIterator).deleteDirectoryWithoutFilesAndDirectories();
    }
    reInput();
}

void AlbaWindowsPathHandler::deleteDirectoryWithFilesAndDirectories() {
    deleteInnerFilesAndDirectories();
    deleteDirectoryWithoutFilesAndDirectories();
    reInput();
}

bool AlbaWindowsPathHandler::copyToNewFile(string_view newFilePath) {
    bool isSuccessful(false);
    if (isFile()) {
        isSuccessful = (bool)CopyFileW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(),
            convertToAnotherBasicStringVariant<string_view, wstring>(newFilePath).c_str(), 0);
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << "newFilePath: [" << newFilePath << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            reInput();
        }
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::renameFile(string_view newFileName) {
    bool isSuccessful(false);
    if (isFile()) {
        string newPath(m_directory + string(newFileName));
        isSuccessful = (bool)MoveFileW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(),
            convertToAnotherBasicStringVariant<string, wstring>(newPath).c_str());
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << "newFileName: [" << newFileName << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            input(newPath);
        }
    }
    return isSuccessful;
}

bool AlbaWindowsPathHandler::renameImmediateDirectory(string_view newDirectoryName) {
    bool isSuccessful(false);
    if (isDirectory()) {
        AlbaWindowsPathHandler newPathHandler(getFullPath());
        newPathHandler.goUp();
        newPathHandler.input(newPathHandler.getDirectory() + m_slashCharacterString + string(newDirectoryName));
        isSuccessful = (bool)MoveFileW(
            convertToAnotherBasicStringVariant<string, wstring>(getFullPath()).c_str(),
            convertToAnotherBasicStringVariant<string, wstring>(newPathHandler.getFullPath()).c_str());
        if (!isSuccessful) {
            cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
            cout << "Path: [" << getFullPath() << "]\n";
            cout << "newDirectoryName: [" << newDirectoryName << "]\n";
            cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
        } else {
            input(newPathHandler.getFullPath());
        }
    }
    return isSuccessful;
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesOneDepth(
    string_view wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, 1);
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesMultipleDepth(
    string_view wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories, int depth) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, depth);
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesUnlimitedDepth(
    string_view wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories) const {
    findFilesAndDirectoriesWithDepth(m_directory, wildCardSearch, listOfFiles, listOfDirectories, -1);
}

void AlbaWindowsPathHandler::findFilesAndDirectoriesWithDepth(
    string_view currentDirectory, string_view wildCardSearch, set<string>& listOfFiles, set<string>& listOfDirectories,
    int depth) const {
    HANDLE hFind;
    WIN32_FIND_DATAW data;

    if (depth == 0) {
        return;
    }
    depth -= (depth > 0) ? 1 : 0;

    string currentDirectoryString(currentDirectory);
    string searchString = currentDirectoryString + string(wildCardSearch);
    hFind = FindFirstFileW(convertToAnotherBasicStringVariant<string, wstring>(searchString).c_str(), &data);
    bool bContinue(hFind != INVALID_HANDLE_VALUE);
    while (bContinue) {
        string fileOrDirectoryName(convertToAnotherBasicStringVariant<wstring, string>(wstring(data.cFileName)));
        if (!isPeriodOrDoublePeriod(fileOrDirectoryName)) {
            if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                string newDirectory(currentDirectoryString + fileOrDirectoryName + '\\');
                listOfDirectories.emplace(newDirectory);
                findFilesAndDirectoriesWithDepth(newDirectory, wildCardSearch, listOfFiles, listOfDirectories, depth);
            } else {
                listOfFiles.emplace(currentDirectoryString + fileOrDirectoryName);
            }
        }
        bContinue = FindNextFileW(hFind, &data);
    }
}

string AlbaWindowsPathHandler::getCurrentDetectedPath() {
    string result;
    constexpr size_t MAXIMUM_CHARACTERS_PATH = 1000;
    WCHAR currentPathFromWindowsWideCharArray[MAXIMUM_CHARACTERS_PATH];
    if (GetModuleFileNameW(NULL, currentPathFromWindowsWideCharArray, MAX_PATH)) {
        result = convertToAnotherBasicStringVariant<wstring, string>(wstring(currentPathFromWindowsWideCharArray));
    } else {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }
    return result;
}

void AlbaWindowsPathHandler::save(string_view path) { setPath(path); }

void AlbaWindowsPathHandler::setPath(string_view path) {
    string correctPath(getCorrectPathWithoutDoublePeriod(
        getCorrectPathWithReplacedSlashCharacters(path, m_slashCharacterString), m_slashCharacterString));
    if (isSlashNeededAtTheEnd(correctPath, path)) {
        correctPath = getCorrectPathWithoutDoublePeriod(correctPath + m_slashCharacterString, m_slashCharacterString);
    }

    setExtensionFromPath(correctPath);
    setDirectoryAndFileFromPath(correctPath);
    setDriveOrRoot();
    setFileType();
    m_foundInLocalSystem = canBeLocated(correctPath);
}

void AlbaWindowsPathHandler::setDriveOrRoot() {
    int index = m_directory.find_first_of(m_slashCharacterString + ":");
    if (isNotNpos(index) && m_directory[index] == ':') {
        m_driveOrRoot = getStringWithCapitalLetters(m_directory.substr(0, index));
    }
    m_relativePath = m_driveOrRoot.empty();
}

bool AlbaWindowsPathHandler::canBeLocated(string_view fullPath) const {
    DWORD attributes = GetFileAttributesW(convertToAnotherBasicStringVariant<string_view, wstring>(fullPath).c_str());
    return INVALID_FILE_ATTRIBUTES != attributes;
}

bool AlbaWindowsPathHandler::isSlashNeededAtTheEnd(string_view correctedPath, string_view originalPath) const {
    bool result(false);
    if (!correctedPath.empty()) {
        bool isCorrectPathLastCharacterNotASlash(
            correctedPath[correctedPath.length() - 1] != m_slashCharacterString[0]);
        if (isCorrectPathLastCharacterNotASlash) {
            DWORD attributes =
                GetFileAttributesW(convertToAnotherBasicStringVariant<string_view, wstring>(correctedPath).c_str());
            bool isFoundInWindows(INVALID_FILE_ATTRIBUTES != attributes);
            if (isFoundInWindows) {
                bool isDirectoryInWindows(attributes & FILE_ATTRIBUTE_DIRECTORY);
                if (isDirectoryInWindows) {
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
    }
    return result;
}

}  // namespace alba
