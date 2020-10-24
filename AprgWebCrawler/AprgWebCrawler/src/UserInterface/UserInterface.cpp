#include "UserInterface.hpp"

#include <File/AlbaFileReader.hpp>
#include <String/AlbaStringHelper.hpp>
#include <User/AlbaUserInterface.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <set>
#include <windows.h>
#include <WebCrawler.hpp>

#define APRG_WEB_CRAWLER_CONFIGURATION_FILE R"(C:\APRG\AprgWebCrawler\configuration.txt)"
#define APRG_WEB_CRAWLER_FIX_BATCH_FILE R"(C:\APRG\AprgWebCrawler\fixDirectoryNames.bat)"

using namespace alba;
using namespace alba::stringHelper;
using namespace alba::AlbaUserInterface;
using namespace std;

namespace aprgWebCrawler
{

void UserInterface::startUi()
{
    readConfigurationFile();
    addExistingDownloadAndNonDownloadDirectories();
    while(1)
    {
        inputTask();
    }
}

void UserInterface::inputTask()
{
    cout << endl;
    cout << "Working directory: [" << m_workingDirectory << "]" << endl;
    cout << "Please select a task" << endl;
    cout << "[WD]  : Select a working directory" << endl;
    cout << "[DD]  : Select a download directory for download" << endl;
    cout << "[A]   : Add a new download" << endl;
    cout << "[DN]  : Show directories not for download" << endl;
    cout << "[DS]  : Check download schedule" << endl;
    cout << "[ST]  : Start download" << endl;
    cout << "Input your choice: ";
    string choice(getStringWithCapitalLetters(getUserInput()));


    if("A" == choice)
    {
        addNewDownloadDirectory();
    }
    else if("WD" == choice)
    {
        inputWorkingDirectory();
    }
    else if("DD" == choice)
    {
        inputDownloadDirectory();
    }
    else if("DN" == choice)
    {
        showNotDownloadDirectories();
    }
    else if("DS" == choice)
    {
        inputDownloadSchedule();
    }
    else if("ST" == choice)
    {
        startDownload();
    }
    writeConfigurationFile();
}

void UserInterface::inputWorkingDirectory()
{
    cout << endl;
    cout << "Please select working directory" << endl;
    showWorkingDirectories();
    cout << "[A]   : Add a new working directory" << endl;
    cout << "[C]   : Create batch script to fix all directory names" << endl;
    cout << "[B]   : Go back" << endl;

    cout << "Input your choice: ";
    string choice(getStringWithCapitalLetters(getUserInput()));
    unsigned int index = convertStringToNumber<unsigned int>(choice);
    bool isNumberFound(isNumber(choice));

    if("A" == choice)
    {
        cout << "Input new directory path: ";
        m_workingDirectories.push_back(getUserInput());
        inputWorkingDirectory();
    }
    else if("C" == choice)
    {
        createBatchFile();
    }
    else if("B" == choice)
    {
        //nothing here
    }
    else if (index < m_workingDirectories.size() && isNumberFound)
    {
        m_workingDirectory = m_workingDirectories[index];
        addExistingDownloadAndNonDownloadDirectories();
    }
    else
    {
        cout << "Input invalid: " << choice << endl;
    }

}

void UserInterface::inputDownloadDirectory()
{
    cout << endl;
    cout << "Please select download directory" << endl;
    showDownloadDirectories();
    cout << "[A]   : Add a new download" << endl;
    cout << "[R]   : Refresh download directory" << endl;
    cout << "[B]   : Go back" << endl;

    cout << "Input your choice: ";
    string choice(getStringWithCapitalLetters(getUserInput()));
    unsigned int index = convertStringToNumber<unsigned int>(choice);
    bool isNumberFound(isNumber(choice));

    if("A" == choice)
    {
        addNewDownloadDirectory();
    }
    else if("R" == choice)
    {
        addExistingDownloadAndNonDownloadDirectories();
    }
    else if("B" == choice)
    {
        //nothing here
    }
    else if (index < m_downloadDirectories.size() && isNumberFound)
    {
        m_downloadDirectoryDetails = m_downloadDirectories[index];
        inputDownloadDirectoryTask();
    }
    else
    {
        cout << "Input invalid: " << choice << endl;
    }
}

void UserInterface::inputDownloadSchedule()
{
    cout << endl;
    showDownloadSchedule();
}

void UserInterface::inputDownloadDirectoryTask()
{
    cout << endl;
    cout << "Please select download directory task" << endl;
    showDownloadDirectoryDetails();
    cout << "[DS]  : Add to download schedule" << endl;
    cout << "[F]   : Fix directory name and memory card" << endl;
    cout << "[B]   : Go back" << endl;

    cout << "Input your choice: ";
    string choice(getStringWithCapitalLetters(getUserInput()));

    if("DS" == choice)
    {
        m_downloadSchedule.emplace(m_downloadSchedule.begin(), m_downloadDirectoryDetails);
    }
    else if("F" == choice)
    {
        renameImmediateDirectoryToTitle(m_downloadDirectoryDetails.downloadDirectory);
    }
    else if("B" == choice)
    {
        //nothing here
    }
    else
    {
        cout << "Input invalid: " << choice << endl;
    }
}


void UserInterface::showWorkingDirectories() const
{
    cout << "Working Directories:" << endl;
    int index(0);
    for(string const& workingDirectories : m_workingDirectories)
    {
        cout << "[" << std::setfill(' ') << std::setw(3) << index++ << "] : " << workingDirectories << endl;
    }

}

void UserInterface::showDownloadDirectories() const
{
    cout << "Download Directories:" << endl;
    int index(0);
    for(DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadDirectories)
    {
        cout << "[" << std::setfill(' ') << std::setw(3) << index++ << "] : "
             << downloadDirectoryDetails.downloadDirectory << " "
             << downloadDirectoryDetails.modeString << " "
             << downloadDirectoryDetails.stateString << endl;
    }
}

void UserInterface::showDownloadSchedule() const
{
    cout << "Download Schedule:" << endl;
    int index(0);
    for(DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadSchedule)
    {
        cout << "[" << std::setfill(' ') << std::setw(3) << index++ << "] : " << downloadDirectoryDetails.downloadDirectory << endl;
    }
}

void UserInterface::showNotDownloadDirectories() const
{
    cout << "Download Directories:" << endl;
    int index(0);
    for(string const& notDownloadDirectory : m_notDownloadDirectories)
    {
        cout << "[" << std::setfill(' ') << std::setw(3) << index++ << "] : " << notDownloadDirectory << endl;
    }
}

void UserInterface::showDownloadDirectoryDetails() const
{
    cout << "Download Directories Details:" << endl;
    cout << "Download directory: " << m_downloadDirectoryDetails.downloadDirectory << endl;
    cout << "Mode: " << m_downloadDirectoryDetails.modeString << endl;
    cout << "State: " << m_downloadDirectoryDetails.stateString << endl;
}

void UserInterface::addExistingDownloadAndNonDownloadDirectories()
{
    addExistingDownloadDirectories();
    addExistingNotDownloadDirectories();
}

void UserInterface::addExistingDownloadDirectories()
{
    cout << "Finding download directories" << endl;
    m_downloadDirectories.clear();
    AlbaWindowsPathHandler workingDirectoryPathHandler(m_workingDirectory);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    workingDirectoryPathHandler.findFilesAndDirectoriesMultipleDepth("*.*", listOfFiles, listOfDirectories, 2);
    for(string const& file : listOfFiles)
    {
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(file, "MemoryCard.txt"))
        {
            AlbaWindowsPathHandler memoryCardPathHandler(file);
            m_downloadDirectories.push_back(createDownloadDirectoryDetails(memoryCardPathHandler.getDirectory()));
        }
    }
}

void UserInterface::addExistingNotDownloadDirectories()
{
    cout << "Finding not download directories" << endl;
    m_notDownloadDirectories.clear();
    AlbaWindowsPathHandler workingDirectoryPathHandler(m_workingDirectory);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    workingDirectoryPathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& directory : listOfDirectories)
    {
        bool isDownloadDirectory(false);
        for(DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadDirectories)
        {
            if(isStringFoundInsideTheOtherStringNotCaseSensitive(downloadDirectoryDetails.downloadDirectory, directory))
            {
                isDownloadDirectory = true;
                break;
            }
        }
        if(!isDownloadDirectory)
        {
            m_notDownloadDirectories.push_back(directory);
        }
    }
}

void UserInterface::addNewDownloadDirectory()
{
    cout << "Input webLink: ";
    string webLink(getUserInput());
    m_downloadSchedule.emplace(m_downloadSchedule.begin(), createDownloadDirectoryDetails(m_workingDirectory, webLink));
    addExistingDownloadAndNonDownloadDirectories();
}

void UserInterface::writeConfigurationFile() const
{
    ofstream configurationFile(APRG_WEB_CRAWLER_CONFIGURATION_FILE);
    if(configurationFile.is_open())
    {
        configurationFile<<"WorkingDirectory:"<<endl;
        configurationFile << m_workingDirectory << endl;
        configurationFile<<"WorkingDirectories:"<<endl;
        for(string const& workingDirectories : m_workingDirectories)
        {
            configurationFile << workingDirectories << endl;
        }
        configurationFile<<"TemporaryFilePath:"<<endl;
        configurationFile << m_temporaryFilePath << endl;
        configurationFile<<"DownloadSchedule:"<<endl;
        for(DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadSchedule)
        {
            configurationFile << downloadDirectoryDetails.downloadDirectory << endl;
        }
    }
}

void UserInterface::readConfigurationFile()
{
    int state=0;
    ifstream configurationFile(APRG_WEB_CRAWLER_CONFIGURATION_FILE);
    if(configurationFile.is_open())
    {
        AlbaFileReader configurationFileReader(configurationFile);
        while(configurationFileReader.isNotFinished())
        {
            string lineFromConfigurationFile(configurationFileReader.getLineAndIgnoreWhiteSpaces());
            if(lineFromConfigurationFile.empty())
            {
                continue;
            }
            else if("WorkingDirectory:" == lineFromConfigurationFile)
            {
                state=1;
            }
            else if("WorkingDirectories:" == lineFromConfigurationFile)
            {
                state=2;
            }
            else if("TemporaryFilePath:" == lineFromConfigurationFile)
            {
                state=3;
            }
            else if("DownloadSchedule:" == lineFromConfigurationFile)
            {
                state=4;
            }
            else if(1==state)
            {
                m_workingDirectory = lineFromConfigurationFile;
            }
            else if(2==state)
            {
                m_workingDirectories.push_back(lineFromConfigurationFile);
            }
            else if(3==state)
            {
                m_temporaryFilePath = lineFromConfigurationFile;
            }
            else if(4==state)
            {
                m_downloadSchedule.push_back(createDownloadDirectoryDetails(lineFromConfigurationFile));
            }
        }
    }
}

void UserInterface::startDownload()
{
    for(DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadSchedule)
    {
        WebCrawler crawler(downloadDirectoryDetails.downloadDirectory, m_temporaryFilePath);
        crawler.crawl();
    }
}

void UserInterface::renameImmediateDirectoryToTitle(string const& downloadDirectory) const
{
    string title;
    {
        WebCrawler crawler(downloadDirectory, m_temporaryFilePath);
        title = crawler.getNewDirectoryName();
    }
    cout << "WebCrawler::renameImmediateToTitle | downloadDirectory: " << downloadDirectory << " title: " << title << endl;
    if(!title.empty())
    {
        AlbaWindowsPathHandler directoryPathHandler(downloadDirectory);
        cout<<"Directory rename error code is " << directoryPathHandler.renameImmediateDirectory(title) << endl;
    }
}

void UserInterface::createBatchFile() const
{
    ofstream batchFile(APRG_WEB_CRAWLER_FIX_BATCH_FILE);
    if(batchFile.is_open())
    {
        AlbaWindowsPathHandler workingDirectoryPathHandler(m_workingDirectory);
        set<string> listOfFiles;
        set<string> listOfDirectories;
        workingDirectoryPathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectories);
        for(DownloadDirectoryDetails const& downloadDirectoryDetails : m_downloadDirectories)
        {
            listOfDirectories.emplace(downloadDirectoryDetails.downloadDirectory);
        }
        for(string const& directory : listOfDirectories)
        {
            AlbaWindowsPathHandler directoryPathHandler(directory);
            WebCrawler crawler(directory, m_temporaryFilePath);
            string newDirectoryName(crawler.getNewDirectoryName());
            if(newDirectoryName.empty())
            {
                newDirectoryName = getStringWithoutStartingAndTrailingCharacters(
                            getStringAndReplaceNonAlphanumericCharactersToUnderScore(
                                directoryPathHandler.getImmediateDirectoryName()), "_");
            }

            if(directoryPathHandler.getImmediateDirectoryName() != newDirectoryName && !newDirectoryName.empty())
            {
                batchFile << R"(rename ")" << directory << R"(" ")" << newDirectoryName << R"(")" << endl;
            }
        }
    }
}

DownloadDirectoryDetails UserInterface::createDownloadDirectoryDetails(string const& downloadDirectory) const
{
    WebCrawler crawler(downloadDirectory, m_temporaryFilePath);
    DownloadDirectoryDetails downloadDirectoryDetails =
    {
        downloadDirectory,
        crawler.getCrawlMode(),
        crawler.getCrawlState(),
        crawler.getCrawlModeString(),
        crawler.getCrawlStateString()
    };
    return downloadDirectoryDetails;
}

DownloadDirectoryDetails UserInterface::createDownloadDirectoryDetails(string const& workingDirectory, string const& webLink) const
{
    WebCrawler crawler(workingDirectory, webLink, m_temporaryFilePath);
    DownloadDirectoryDetails downloadDirectoryDetails =
    {
        crawler.getDownloadDirectory(),
        crawler.getCrawlMode(),
        crawler.getCrawlState(),
        crawler.getCrawlModeString(),
        crawler.getCrawlStateString()
    };
    return downloadDirectoryDetails;
}

}
