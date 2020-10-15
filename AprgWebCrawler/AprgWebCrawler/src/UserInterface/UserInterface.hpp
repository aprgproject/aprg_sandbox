#pragma once

#include <string>
#include <vector>
#include <WebCrawler/CrawlMode.hpp>
#include <WebCrawler/CrawlState.hpp>

namespace aprgWebCrawler
{

struct DownloadDirectoryDetails
{
    std::string downloadDirectory;
    CrawlMode mode;
    CrawlState state;
    std::string modeString;
    std::string stateString;
};

class UserInterface
{
public:
    void startUi();

private:
    void inputTask();
    void inputWorkingDirectory();
    void inputDownloadDirectory();
    void inputDownloadSchedule();
    void inputDownloadDirectoryTask();

    void showWorkingDirectories() const;
    void showDownloadDirectories() const;
    void showDownloadSchedule() const;
    void showNotDownloadDirectories() const;
    void showDownloadDirectoryDetails() const;

    void addExistingDownloadAndNonDownloadDirectories();
    void addExistingDownloadDirectories();
    void addExistingNotDownloadDirectories();
    void addNewDownloadDirectory();

    std::string getUserInput() const;

    void writeConfigurationFile() const;
    void readConfigurationFile();
    void startDownload();
    void renameImmediateDirectoryToTitle(std::string const& downloadDirectory) const;
    void createBatchFile() const;
    DownloadDirectoryDetails createDownloadDirectoryDetails(std::string const& downloadDirectory) const;
    DownloadDirectoryDetails createDownloadDirectoryDetails(std::string const& workingDirectory, std::string const& webLink) const;


    std::vector<std::string> m_workingDirectories;
    std::vector<DownloadDirectoryDetails> m_downloadDirectories;
    std::vector<std::string> m_notDownloadDirectories;
    std::vector<DownloadDirectoryDetails> m_downloadSchedule;
    std::string m_workingDirectory;
    DownloadDirectoryDetails m_downloadDirectoryDetails;
};

}
