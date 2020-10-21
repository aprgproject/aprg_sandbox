#include "WebCrawler.hpp"

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <CurlInterface.hpp>
#include <string>
#include <iostream>
#include <windows.h>

using namespace alba;
using namespace curl::CurlInterface;
using namespace std;

#define PHANTOM_BIN_PATH R"(C:\APRG\PhantomJs\PhantomJs\bin\)"

namespace aprgWebCrawler
{

bool WebCrawler::downloadBinaryFile(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler) const
{
    bool isSuccessful(false);
    CrawlConfiguration configuration(m_mode);
    DownloadLowSpeedLimitConfigurationOptional downloadLowSpeedLimitConfigurationOptional(configuration.getDownloadLowSpeedLimitConfigurationOptional());
    if(downloadLowSpeedLimitConfigurationOptional)
    {
        curl::CurlInterface::lowSpeedLimit = downloadLowSpeedLimitConfigurationOptional.getReference().m_lowSpeedLimit;
        curl::CurlInterface::lowSpeedTime = downloadLowSpeedLimitConfigurationOptional.getReference().m_lowSpeedTime;
    }
    if(configuration.isFileToBeDownloadUntilSuccessful())
    {
        isSuccessful = downloadBinaryFileUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler);
    }
    else
    {
        isSuccessful = downloadBinaryFileWithFiniteNumberOfTries<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler, configuration.getNumberOfRetries());
    }
    return isSuccessful;
}

bool WebCrawler::downloadFileAsText(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler) const
{
    return downloadUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFox>(fileToDownloadWebPathHandler, downloadPathHandler);
}

void WebCrawler::downloadFileUsingPhantomJs(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler) const
{
    AlbaWindowsPathHandler const phantomJsFolder(PHANTOM_BIN_PATH);
    string const command(phantomJsFolder.getFullPath()+"phantomjs.exe "+phantomJsFolder.getFullPath()+R"(loadPage.js ")"+fileToDownloadWebPathHandler.getFullPath()+R"(" ")"+downloadPathHandler.getFullPath()+R"(")");
    cout<<command<<endl;
    system(command.c_str());
}

}
