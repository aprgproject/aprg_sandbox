#include "UserInterface.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/WebCrawler.hpp>

#include <windows.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler {

void UserInterface::startUi() {
    readConfigurationFile();
    addExistingDownloadAndNonDownloadDirectories();
    while (1) {
        inputTask();
    }
}

void UserInterface::inputTask() {
    cout << "\n";
    cout << "Working directory: [" << m_workingDirectory << "]\n";

    AlbaUserInterface::Choices<string> choices;
    choices.emplace("WD", "Select a working directory");
    choices.emplace("DD", "Select a download directory for download");
    choices.emplace("A", "Add a new download");
    choices.emplace("DN", "Show directories not for download");
    choices.emplace("DS", "Check download schedule");
    choices.emplace("ST", "Start download");

    string choice(
        m_userInterface.displayQuestionAndChoicesAndGetStringAnswerInAllCapitals("Please select a task.", choices));

    if ("A" == choice) {
        addNewDownloadDirectory();
    } else if ("WD" == choice) {
        inputWorkingDirectory();
    } else if ("DD" == choice) {
        inputDownloadDirectory();
    } else if ("DN" == choice) {
        showNotDownloadDirectories();
    } else if ("DS" == choice) {
        inputDownloadSchedule();
    } else if ("ST" == choice) {
        startDownload();
    }
    writeConfigurationFile();
}

void UserInterface::inputWorkingDirectory() {
    cout << "\n";
    AlbaUserInterface::Choices<string> choices;
    copyWorkingDirectoriesToChoices(choices);
    choices.emplace("A", "Add a new working directory");
    choices.emplace("C", "Create batch script to fix all directory names");
    choices.emplace("B", "Go back");

    string choice(m_userInterface.displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(
        "Please select working directory.", choices));
    unsigned int index = convertStringToNumber<unsigned int>(choice);
    bool isNumberFound(isNumber(choice));

    if ("A" == choice) {
        cout << "Input new directory path: ";
        m_workingDirectories.push_back(m_userInterface.getUserInput());
        inputWorkingDirectory();
    } else if ("C" == choice) {
        createBatchFile();
    } else if ("B" == choice) {
        // nothing here
    } else if (index < m_workingDirectories.size() && isNumberFound) {
        m_workingDirectory = m_workingDirectories[index];
        addExistingDownloadAndNonDownloadDirectories();
    } else {
        cout << "Input invalid: " << choice << "\n";
    }
}

void UserInterface::inputDownloadDirectory() {
    cout << "\n";
    AlbaUserInterface::Choices<string> choices;
    copyDownloadDirectoriesToChoices(choices);
    choices.emplace("A", "Add a new download");
    choices.emplace("R", "Refresh download directory");
    choices.emplace("B", "Go back");

    cout << "Input your choice: ";
    string choice(m_userInterface.displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(
        "Please select download directory.", choices));
    unsigned int index = convertStringToNumber<unsigned int>(choice);
    bool isNumberFound(isNumber(choice));

    if ("A" == choice) {
        addNewDownloadDirectory();
    } else if ("R" == choice) {
        addExistingDownloadAndNonDownloadDirectories();
    } else if ("B" == choice) {
        // nothing here
    } else if (index < m_downloadDirectories.size() && isNumberFound) {
        m_downloadDirectoryDetails = m_downloadDirectories[index];
        inputDownloadDirectoryTask();
    } else {
        cout << "Input invalid: " << choice << "\n";
    }
}

void UserInterface::inputDownloadSchedule() {
    cout << "\n";
    showDownloadSchedule();
}

void UserInterface::inputDownloadDirectoryTask() {
    cout << "\n";
    showDownloadDirectoryDetails();
    AlbaUserInterface::Choices<string> choices;
    choices.emplace("DS", "Add to download schedule");
    choices.emplace("F", "Fix directory name and memory card");
    choices.emplace("B", "Go back");

    string choice(m_userInterface.displayQuestionAndChoicesAndGetStringAnswerInAllCapitals(
        "Please select download directory task.", choices));

    if ("DS" == choice) {
        m_downloadSchedule.emplace(m_downloadSchedule.begin(), m_downloadDirectoryDetails);
    } else if ("F" == choice) {
        renameImmediateDirectoryToTitle(m_downloadDirectoryDetails.downloadDirectory);
    } else if ("B" == choice) {
        // nothing here
    } else {
        cout << "Input invalid: " << choice << "\n";
    }
}

void UserInterface::copyWorkingDirectoriesToChoices(AlbaUserInterface::Choices<string>& choices) {
    unsigned int displayedIndex(0);
    for (string const& workingDirectory : m_workingDirectories) {
        choices.emplace(convertToString(displayedIndex++), workingDirectory);
    }
}

void UserInterface::copyDownloadDirectoriesToChoices(AlbaUserInterface::Choices<string>& choices) {
    unsigned int displayedIndex(0);
    for (DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadDirectories) {
        choices.emplace(
            convertToString(displayedIndex++), downloadDirectoryDetails.downloadDirectory + " " +
                                                   downloadDirectoryDetails.modeString + " " +
                                                   downloadDirectoryDetails.stateString);
    }
}

void UserInterface::showWorkingDirectories() const {
    cout << "Working Directories:\n";
    int index(0);
    for (string const& workingDirectories : m_workingDirectories) {
        cout << "[" << std::setfill(' ') << std::setw(3) << index++ << "] : " << workingDirectories << "\n";
    }
}

void UserInterface::showDownloadDirectories() const {
    cout << "Download Directories:\n";
    int index(0);
    for (DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadDirectories) {
        cout << "[" << std::setfill(' ') << std::setw(3) << index++
             << "] : " << downloadDirectoryDetails.downloadDirectory << " " << downloadDirectoryDetails.modeString
             << " " << downloadDirectoryDetails.stateString << "\n";
    }
}

void UserInterface::showDownloadSchedule() const {
    cout << "Download Schedule:\n";
    int index(0);
    for (DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadSchedule) {
        cout << "[" << std::setfill(' ') << std::setw(3) << index++
             << "] : " << downloadDirectoryDetails.downloadDirectory << "\n";
    }
}

void UserInterface::showNotDownloadDirectories() const {
    cout << "Download Directories:\n";
    int index(0);
    for (string const& notDownloadDirectory : m_notDownloadDirectories) {
        cout << "[" << std::setfill(' ') << std::setw(3) << index++ << "] : " << notDownloadDirectory << "\n";
    }
}

void UserInterface::showDownloadDirectoryDetails() const {
    cout << "Download Directories Details:\n";
    cout << "Download directory: " << m_downloadDirectoryDetails.downloadDirectory << "\n";
    cout << "Mode: " << m_downloadDirectoryDetails.modeString << "\n";
    cout << "State: " << m_downloadDirectoryDetails.stateString << "\n";
}

void UserInterface::addExistingDownloadAndNonDownloadDirectories() {
    addExistingDownloadDirectories();
    addExistingNotDownloadDirectories();
}

void UserInterface::addExistingDownloadDirectories() {
    cout << "Finding download directories\n";
    m_downloadDirectories.clear();
    AlbaLocalPathHandler workingDirectoryPathHandler(m_workingDirectory);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    workingDirectoryPathHandler.findFilesAndDirectoriesMultipleDepth("*.*", listOfFiles, listOfDirectories, 2);
    for (string const& file : listOfFiles) {
        if (isStringFoundInsideTheOtherStringNotCaseSensitive(file, "MemoryCard.txt")) {
            AlbaLocalPathHandler memoryCardPathHandler(file);
            m_downloadDirectories.push_back(createDownloadDirectoryDetails(memoryCardPathHandler.getDirectory()));
        }
    }
}

void UserInterface::addExistingNotDownloadDirectories() {
    cout << "Finding not download directories\n";
    m_notDownloadDirectories.clear();
    AlbaLocalPathHandler workingDirectoryPathHandler(m_workingDirectory);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    workingDirectoryPathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
    for (string const& directory : listOfDirectories) {
        bool isDownloadDirectory(false);
        for (DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadDirectories) {
            if (isStringFoundInsideTheOtherStringNotCaseSensitive(
                    downloadDirectoryDetails.downloadDirectory, directory)) {
                isDownloadDirectory = true;
                break;
            }
        }
        if (!isDownloadDirectory) {
            m_notDownloadDirectories.push_back(directory);
        }
    }
}

void UserInterface::addNewDownloadDirectory() {
    cout << "Input webLink: ";
    string webLink(m_userInterface.getUserInput());
    m_downloadSchedule.emplace(m_downloadSchedule.begin(), createDownloadDirectoryDetails(m_workingDirectory, webLink));
    addExistingDownloadAndNonDownloadDirectories();
}

void UserInterface::writeConfigurationFile() const {
    ofstream configurationFile(APRG_WEB_CRAWLER_CONFIGURATION_FILE);
    if (configurationFile.is_open()) {
        configurationFile << "WorkingDirectory:\n";
        configurationFile << m_workingDirectory << "\n";
        configurationFile << "WorkingDirectories:\n";
        for (string const& workingDirectories : m_workingDirectories) {
            configurationFile << workingDirectories << "\n";
        }
        configurationFile << "TemporaryFilePath:\n";
        configurationFile << m_temporaryFilePath << "\n";
        configurationFile << "DownloadSchedule:\n";
        for (DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadSchedule) {
            configurationFile << downloadDirectoryDetails.downloadDirectory << "\n";
        }
    }
}

void UserInterface::readConfigurationFile() {
    int state = 0;
    ifstream configurationFile(APRG_WEB_CRAWLER_CONFIGURATION_FILE);
    if (configurationFile.is_open()) {
        AlbaFileReader configurationFileReader(configurationFile);
        while (configurationFileReader.isNotFinished()) {
            string lineFromConfigurationFile(configurationFileReader.getLineAndIgnoreWhiteSpaces());
            if (lineFromConfigurationFile.empty()) {
                continue;
            } else if ("WorkingDirectory:" == lineFromConfigurationFile) {
                state = 1;
            } else if ("WorkingDirectories:" == lineFromConfigurationFile) {
                state = 2;
            } else if ("TemporaryFilePath:" == lineFromConfigurationFile) {
                state = 3;
            } else if ("DownloadSchedule:" == lineFromConfigurationFile) {
                state = 4;
            } else if (1 == state) {
                m_workingDirectory = lineFromConfigurationFile;
            } else if (2 == state) {
                m_workingDirectories.push_back(lineFromConfigurationFile);
            } else if (3 == state) {
                m_temporaryFilePath = lineFromConfigurationFile;
            } else if (4 == state) {
                m_downloadSchedule.push_back(createDownloadDirectoryDetails(lineFromConfigurationFile));
            }
        }
    }
}

void UserInterface::startDownload() {
    for (DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadSchedule) {
        WebCrawler crawler(downloadDirectoryDetails.downloadDirectory, m_temporaryFilePath);
        crawler.crawl();
    }
}

void UserInterface::renameImmediateDirectoryToTitle(string const& downloadDirectory) const {
    string title;
    {
        WebCrawler crawler(downloadDirectory, m_temporaryFilePath);
        title = crawler.getNewDirectoryName();
    }
    cout << "WebCrawler::renameImmediateToTitle | downloadDirectory: " << downloadDirectory << " title: " << title
         << "\n";
    if (!title.empty()) {
        AlbaLocalPathHandler directoryPathHandler(downloadDirectory);
        cout << "Directory rename error code is " << directoryPathHandler.renameImmediateDirectory(title) << "\n";
    }
}

void UserInterface::createBatchFile() const {
    ofstream batchFile(APRG_WEB_CRAWLER_FIX_BATCH_FILE);
    if (batchFile.is_open()) {
        AlbaLocalPathHandler workingDirectoryPathHandler(m_workingDirectory);
        set<string> listOfFiles;
        set<string> listOfDirectories;
        workingDirectoryPathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
        for (DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadDirectories) {
            listOfDirectories.emplace(downloadDirectoryDetails.downloadDirectory);
        }
        for (string const& directory : listOfDirectories) {
            AlbaLocalPathHandler directoryPathHandler(directory);
            WebCrawler crawler(directory, m_temporaryFilePath);
            string newDirectoryName(crawler.getNewDirectoryName());
            if (newDirectoryName.empty()) {
                newDirectoryName = getStringWithoutStartingAndTrailingCharacters(
                    getStringAndReplaceNonAlphanumericCharactersToUnderScore(
                        directoryPathHandler.getImmediateDirectoryName()),
                    "_");
            }

            if (directoryPathHandler.getImmediateDirectoryName() != newDirectoryName && !newDirectoryName.empty()) {
                batchFile << R"(rename ")" << directory << R"(" ")" << newDirectoryName << R"(")"
                          << "\n";
            }
        }
    }
}

DownloadDirectoryDetails UserInterface::createDownloadDirectoryDetails(string const& downloadDirectory) const {
    WebCrawler crawler(downloadDirectory, m_temporaryFilePath);
    DownloadDirectoryDetails downloadDirectoryDetails = {
        downloadDirectory, crawler.getCrawlMode(), crawler.getCrawlState(), crawler.getCrawlModeString(),
        crawler.getCrawlStateString()};
    return downloadDirectoryDetails;
}

DownloadDirectoryDetails UserInterface::createDownloadDirectoryDetails(
    string const& workingDirectory, string const& webLink) const {
    WebCrawler crawler(workingDirectory, webLink, m_temporaryFilePath);
    DownloadDirectoryDetails downloadDirectoryDetails = {
        crawler.getDownloadDirectory(), crawler.getCrawlMode(), crawler.getCrawlState(), crawler.getCrawlModeString(),
        crawler.getCrawlStateString()};
    return downloadDirectoryDetails;
}

}  // namespace aprgWebCrawler
