#pragma once

#include <User/AlbaWindowsUserAutomation.hpp>

#include <string>

namespace aprgWebCrawler
{

class AutomatedFirefoxBrowser
{
public:
    static AutomatedFirefoxBrowser& getInstance();
    void downloadFileWithDefaultSettings(std::string const& webPath, std::string const& downloadLocalPath) const;
    void createNewTab() const;
    void closeTab() const;
    void openWebPathOnCurrentTab(std::string const& webPath) const;
    void saveCurrentTab(std::string const& downloadLocalPath) const;
    void saveBinaryFile(std::string const& downloadLocalPath) const;
    void doLeftClickAt(alba::MousePosition const& position) const;
    void sleep(unsigned int const milliseconds) const;
private:
    AutomatedFirefoxBrowser();
    void openFirefox() const;
    void readConfigurationFile();
    void pressControlAndLetter(unsigned int const letter) const;
    void pressAltAndLetter(unsigned int const letter) const;
    void focusOnLocationBar() const;
    void triggerSave() const;
    void triggerPaste() const;
    std::string m_firefoxExecutablePath;
    alba::AlbaWindowsUserAutomation m_userAutomation;
};

}
