#pragma once

#include <string>

namespace aprgWebCrawler
{

namespace AutomationHelper
{
    void saveWebPageManuallyUsingMozillaFirefox(std::string const& webPath);
    void openMozillaFirefoxExecutableManually(std::string const& webPath);
    std::string getRedirectedLinkUsingMozillaFirefoxAndFdm(std::string const& webPath);
    void downloadLinkUsingMozillaFirefoxAndFdm(std::string const& webPath);
}

}
