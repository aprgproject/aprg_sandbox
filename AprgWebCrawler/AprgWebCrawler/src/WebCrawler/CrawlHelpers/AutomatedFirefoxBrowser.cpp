//make this FirefoxAutomatedFirefoxBrowser
//this should be singleton
//firefox should start when this class is created
//-new window should be used in the console
//ctrl-w to close window
#include "AutomatedFirefoxBrowser.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <windows.h>

#include <fstream>
#include <iostream>

//include this on cmake

using namespace alba;
using namespace std;
using namespace stringHelper;

namespace aprgWebCrawler
{

AutomatedFirefoxBrowser::AutomatedFirefoxBrowser()
{
    readConfigurationFile();
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

void AutomatedFirefoxBrowser::openMozillaFirefoxExecutableManually(string const& webPath)
{
    AlbaWebPathHandler webPathHandler(webPath);
    string firefoxCommand(string("start ")+m_firefoxExecutablePath+R"( ")"+webPathHandler.getFullPath()+R"(")");
    cout << firefoxCommand << endl;
    system(firefoxCommand.c_str());
}

//use tabs instead of clicks
void AutomatedFirefoxBrowser::saveWebPageManuallyUsingMozillaFirefox(string const& webPath)
{
    AlbaWebPathHandler webPathHandler(webPath);
    AlbaWindowsUserAutomation userAutomation;
    cout<<"Open Firefox"<<endl;
    openMozillaFirefoxExecutableManually(webPathHandler.getFullPath());

    cout<<"Wait"<<endl;
    Sleep(m_timeoutForLoadingFirefox);

    cout<<"Click file"<<endl;
    userAutomation.setMousePosition(m_firefoxFilePosition);
    userAutomation.doLeftClick();
    cout<<"Click save page as"<<endl;
    userAutomation.setMousePosition(m_firefoxSavePagePosition);
    userAutomation.doLeftClick();

    cout<<"Wait"<<endl;
    Sleep(m_timeoutForWaitingResponseFromFirefox);

    cout<<"Type name"<<endl;
    userAutomation.typeString(R"(temp.html)");
    cout<<"Enter"<<endl;
    userAutomation.typeCharacter(0x0D);

    cout<<"Wait"<<endl;
    Sleep(m_timeoutForWaitingResponseFromFirefox);

    cout<<"Close firefox"<<endl;
    userAutomation.setMousePosition(m_firefoxCloseSecondTabButtonPosition);
    userAutomation.doLeftClick();
}

string AutomatedFirefoxBrowser::getRedirectedLinkUsingMozillaFirefoxAndFdm(string const& webPath)
{
    AlbaWebPathHandler webPathHandler(webPath);
    AlbaWindowsUserAutomation userAutomation;
    cout<<"Open Firefox"<<endl;
    openMozillaFirefoxExecutableManually(webPathHandler.getFullPath());

    cout<<"Wait"<<endl;
    Sleep(m_timeoutForLoadingFirefox);

    cout<<"Right click address bar"<<endl;
    userAutomation.setMousePosition(m_fdmUrlBarPosition);
    userAutomation.doRightClick();
    cout<<"Copy"<<endl;
    userAutomation.setMousePosition(m_fdmUrlCopyPosition);
    userAutomation.doLeftClick();
    cout<<"Close FDM"<<endl;
    userAutomation.setMousePosition(m_fdmCloseDownloadWindowPosition);
    userAutomation.doLeftClick();

    cout<<"Wait"<<endl;
    Sleep(m_timeoutForWaitingResponseFromFirefox);

    cout<<"Close firefox"<<endl;
    userAutomation.setMousePosition(m_firefoxCloseSecondTabButtonPosition);
    userAutomation.doLeftClick();

    return userAutomation.getStringFromClipboard();
}

void AutomatedFirefoxBrowser::downloadLinkUsingMozillaFirefoxAndFdm(string const& webPath)
{
    AlbaWebPathHandler webPathHandler(webPath);
    AlbaWindowsUserAutomation userAutomation;
    cout<<"Open Firefox"<<endl;
    openMozillaFirefoxExecutableManually(webPathHandler.getFullPath());

    cout<<"Wait"<<endl;
    Sleep(m_timeoutForLoadingFirefox);

    cout<<"Enter"<<endl;
    userAutomation.typeCharacter(0x0D);

    cout<<"Wait"<<endl;
    Sleep(m_timeoutForWaitingResponseFromFirefox);

    cout<<"Close firefox"<<endl;
    userAutomation.setMousePosition(m_firefoxCloseSecondTabButtonPosition);
    userAutomation.doLeftClick();
}

}
