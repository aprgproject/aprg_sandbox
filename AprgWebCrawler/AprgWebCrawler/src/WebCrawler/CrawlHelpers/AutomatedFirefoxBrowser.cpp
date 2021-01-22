//make this FirefoxAutomatedFirefoxBrowser
//this should be singleton
//firefox should start when this class is created
//-new window should be used in the console
//ctrl-w to close window
#include "AutomatedFirefoxBrowser.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <windows.h>

#include <fstream>
#include <iostream>


#include <Debug/AlbaDebug.hpp>

#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_RETURN 0x0D

using namespace alba;
using namespace std;
using namespace stringHelper;

namespace aprgWebCrawler
{

AutomatedFirefoxBrowser& AutomatedFirefoxBrowser::getInstance()
{
    static AutomatedFirefoxBrowser instance;
    return instance;
}

void AutomatedFirefoxBrowser::downloadFileWithDefaultSettings(string const& webPath, string const& downloadLocalPath) const
{
    ALBA_PRINT2(webPath, downloadLocalPath);
    createNewTab();
    openWebPathOnCurrentTab(webPath);
    saveCurrentTab(downloadLocalPath);
    closeTab();
}

void AutomatedFirefoxBrowser::createNewTab() const
{
    pressControlAndLetter('T');
}

void AutomatedFirefoxBrowser::closeTab() const
{
    pressControlAndLetter('W');
}

void AutomatedFirefoxBrowser::openWebPathOnCurrentTab(string const& webPath) const
{
    focusOnLocationBar();
    m_userAutomation.setStringToClipboard(webPath);
    triggerPaste();
    m_userAutomation.typeCharacter(VK_RETURN);
    m_userAutomation.sleep(30000);
}

void AutomatedFirefoxBrowser::saveCurrentTab(string const& downloadLocalPath) const
{
    AlbaLocalPathHandler downloadLocalPathHandler(downloadLocalPath);
    triggerSave();
    m_userAutomation.setStringToClipboard(downloadLocalPathHandler.getFile());
    triggerPaste();
    focusOnLocationBar();
    m_userAutomation.setStringToClipboard(downloadLocalPathHandler.getDirectory());
    triggerPaste();
    m_userAutomation.typeCharacter(VK_RETURN);
    pressAltAndLetter('S');
    m_userAutomation.typeCharacter('Y');
}

void AutomatedFirefoxBrowser::saveBinaryFile(string const& downloadLocalPath) const
{
    AlbaLocalPathHandler downloadLocalPathHandler(downloadLocalPath);
    m_userAutomation.typeCharacter(VK_RETURN);
    focusOnLocationBar();
    m_userAutomation.setStringToClipboard(downloadLocalPathHandler.getDirectory());
    triggerPaste();
    m_userAutomation.typeCharacter(VK_RETURN);
    pressAltAndLetter('S');
    m_userAutomation.typeCharacter('Y');
}

void AutomatedFirefoxBrowser::doLeftClickAt(MousePosition const& position) const
{
    m_userAutomation.setMousePosition(position);
    m_userAutomation.doLeftClick();
}

void AutomatedFirefoxBrowser::sleep(unsigned int const milliseconds) const
{
    m_userAutomation.sleep(milliseconds);
}

AutomatedFirefoxBrowser::AutomatedFirefoxBrowser()
{
    readConfigurationFile();
    openFirefox();
}

void AutomatedFirefoxBrowser::openFirefox() const
{
    string firefoxCommand(string("start ")+m_firefoxExecutablePath);
    cout << firefoxCommand << endl;
    system(firefoxCommand.c_str());
    m_userAutomation.sleep(10000);
}

void AutomatedFirefoxBrowser::readConfigurationFile()
{
    ifstream configurationFile(APRG_WEB_CRAWLER_AUTOMATION_CONFIGURATION_FILE);
    if(configurationFile.is_open())
    {
        AlbaFileReader configurationFileReader(configurationFile);
        if(configurationFileReader.isNotFinished())
        {
            m_firefoxExecutablePath = configurationFileReader.getLineAndIgnoreWhiteSpaces();
        }
    }
}

void AutomatedFirefoxBrowser::pressControlAndLetter(unsigned int const letter) const
{
    m_userAutomation.pressDownKey(VK_CONTROL);
    m_userAutomation.pressDownKey(letter);
    m_userAutomation.sleepWithRealisticDelay();
    m_userAutomation.pressUpKey(letter);
    m_userAutomation.pressUpKey(VK_CONTROL);
}

void AutomatedFirefoxBrowser::pressAltAndLetter(unsigned int const letter) const
{
    m_userAutomation.pressDownKey(VK_MENU);
    m_userAutomation.pressDownKey(letter);
    m_userAutomation.sleepWithRealisticDelay();
    m_userAutomation.pressUpKey(letter);
    m_userAutomation.pressUpKey(VK_MENU);
}

void AutomatedFirefoxBrowser::focusOnLocationBar() const
{
    pressControlAndLetter('L');
}

void AutomatedFirefoxBrowser::triggerSave() const
{
    pressControlAndLetter('S');
}

void AutomatedFirefoxBrowser::triggerPaste() const
{
    pressControlAndLetter('V');
}

}
