#pragma once

#include <User/AlbaWindowsUserAutomation.hpp>
#include <string>

namespace aprgWebCrawler
{

class AutomationHelper
{
public:
    AutomationHelper();
    void openMozillaFirefoxExecutableManually(std::string const& webPath);
    void saveWebPageManuallyUsingMozillaFirefox(std::string const& webPath);
    std::string getRedirectedLinkUsingMozillaFirefoxAndFdm(std::string const& webPath);
    void downloadLinkUsingMozillaFirefoxAndFdm(std::string const& webPath);
private:
    void readConfigurationFile();
    std::string m_firefoxExecutablePath;
    alba::MousePosition m_firefoxFilePosition;
    alba::MousePosition m_firefoxSavePagePosition;
    alba::MousePosition m_firefoxCloseButtonPosition;
    alba::MousePosition m_firefoxCloseSecondTabButtonPosition;
    alba::MousePosition m_fdmUrlBarPosition;
    alba::MousePosition m_fdmUrlCopyPosition;
    alba::MousePosition m_fdmCloseDownloadWindowPosition;
    int m_timeoutForOpeningFirefox;
    int m_timeoutForLoadingFirefox;
    int m_timeoutForWaitingResponseFromFirefox;
};

}
