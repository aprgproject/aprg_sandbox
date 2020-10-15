#include "UserInterface.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <set>
#include <WebCrawler.hpp>

#define APRG_WEB_CRAWLER_CONFIGURATION_FILE R"(C:\APRG\AprgWebCrawler\configuration.txt)"

using namespace alba;
using namespace std;

namespace aprgWebCrawler
{

void UserInterface::startUi()
{
    readConfigurationFile();
    while(1)
    {
        inputTask();
    }
}

void UserInterface::inputTask()
{
    cout << "Working directory: [" << m_workingDirectory << "]" << endl;
    cout << "Please select a task" << endl;
    cout << "[WD]  : Select a working directory" << endl;
    cout << "[DD]  : Select a download directory for download" << endl;
    cout << "[DN]  : Show directories not for download" << endl;
    cout << "[DS]  : Check download schedule" << endl;
    cout << "[ST]  : Start download" << endl;
    cout << "[SV]  : Save configuration" << endl;
    cout << "Input your choice: ";
    string choice(stringHelper::getStringWithCapitalLetters(getUserInput()));

    if("WD" == choice)
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
        //nothing here
    }
    else if("SV" == choice)
    {
        writeConfigurationFile();
    }
}

void UserInterface::inputWorkingDirectory()
{
    cout << "Please select working directory" << endl;
    showWorkingDirectories();
    cout << "[A]   : Or add a new working directory" << endl;
    cout << "[F]   : Fix all directory names and memory cards" << endl;
    cout << "[B]   : Go back" << endl;

    cout << "Input your choice: ";
    string choice(stringHelper::getStringWithCapitalLetters(getUserInput()));
    unsigned int index = stringHelper::convertStringToNumber<unsigned int>(choice);

    if("A" == choice)
    {
        cout << "Input new directory path: ";
        m_workingDirectories.push_back(getUserInput());
        inputWorkingDirectory();
    }
    else if("F" == choice)
    {
        //what to do here
    }
    else if("B" == choice)
    {
        //nothing here
    }
    else if (index < m_workingDirectories.size())
    {
        m_workingDirectory = m_workingDirectories[index];
        findDownloadDirectories();
        findNotDownloadDirectories();
    }
    else
    {
        cout << "Input invalid: " << index << endl;
    }

}

void UserInterface::inputDownloadDirectory()
{
    cout << "Please select download directory" << endl;
    showDownloadDirectories();
    cout << "[A]   : Add new download" << endl;
    cout << "[R]   : Refresh download directory" << endl;
    cout << "[B]   : Go back" << endl;

    cout << "Input your choice: ";
    string choice(stringHelper::getStringWithCapitalLetters(getUserInput()));
    unsigned int index = stringHelper::convertStringToNumber<unsigned int>(choice);

    if("A" == choice)
    {
        //something here
    }
    else if("R" == choice)
    {
        //nothing here
    }
    else if("B" == choice)
    {
        //nothing here
    }
    else if (index < m_downloadDirectories.size())
    {
        m_downloadDirectoryDetails = m_downloadDirectories[index];
        inputDownloadDirectoryTask();
    }
    else
    {
        cout << "Input invalid: " << index << endl;
    }

}

void UserInterface::inputDownloadSchedule()
{
    showDownloadSchedule();
}

void UserInterface::inputDownloadDirectoryTask()
{
    cout << "Please select download directory" << endl;
    showDownloadDirectories();
    cout << "[DS]  : Add to download schedule" << endl;
    cout << "[F]   : Fix directory name and memory card" << endl;
    cout << "[B]   : Go back" << endl;

    cout << "Input your choice: ";
    string choice(stringHelper::getStringWithCapitalLetters(getUserInput()));

    if("DS" == choice)
    {
        //nothing here
    }
    else if("F" == choice)
    {
        //nothing here
    }
    else if("B" == choice)
    {
        //nothing here
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
    for(string const& downloadSchedule : m_downloadSchedule)
    {
        cout << "[" << std::setfill(' ') << std::setw(3) << index++ << "] : " << downloadSchedule << endl;
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

void UserInterface::findDownloadDirectories()
{
    cout << "Finding download directories" << endl;
    m_downloadDirectories.clear();
    AlbaWindowsPathHandler workingDirectoryPathHandler(m_workingDirectory);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    workingDirectoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& file : listOfFiles)
    {
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(file, "MemoryCard.txt"))
        {
            AlbaWindowsPathHandler memoryCardPathHandler(file);
            WebCrawler crawler(memoryCardPathHandler.getDirectory());
            DownloadDirectoryDetails downloadDirectoryDetails =
            {
                memoryCardPathHandler.getDirectory(),
                crawler.getCrawlMode(),
                crawler.getCrawlState(),
                crawler.getCrawlModeString(),
                crawler.getCrawlStateString()
            };
            m_downloadDirectories.push_back(downloadDirectoryDetails);
        }
    }
}

void UserInterface::findNotDownloadDirectories()
{
    cout << "Finding download directories" << endl;
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
            if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(downloadDirectoryDetails.downloadDirectory, directory))
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

string UserInterface::getUserInput() const
{
    constexpr int bufferSize = 1000;
    char buffer[bufferSize];
    cin.getline(buffer, bufferSize);
    return string(buffer);
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
        configurationFile<<"DownloadSchedule:"<<endl;
        for(string const& downloadSchedule : m_downloadSchedule)
        {
            configurationFile << downloadSchedule << endl;
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
            if("WorkingDirectory:" == lineFromConfigurationFile)
            {
                state=1;
            }
            else if("WorkingDirectories:" == lineFromConfigurationFile)
            {
                state=2;
            }
            else if("DownloadSchedule:" == lineFromConfigurationFile)
            {
                state=3;
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
                m_downloadSchedule.push_back(lineFromConfigurationFile);
            }
        }
    }
}

}
