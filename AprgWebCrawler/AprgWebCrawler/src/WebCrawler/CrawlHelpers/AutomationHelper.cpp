//make this FirefoxAutomationHelper
//this should be singleton
//firefox should start when this class is created
//-new window should be used in the console
//ctrl-w to close window
#include "AutomationHelper.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <windows.h>

#include <fstream>
#include <iostream>

//include this on cmake
#define APRG_WEB_CRAWLER_AUTOMATION_CONFIGURATION_FILE APRG_DIR R"(AprgWebCrawler\Configuration\firefoxConfiguration.txt)"

using namespace alba;
using namespace std;using namespace stringHelper;

namespace aprgWebCrawler
{
AutomationHelper::AutomationHelper()
{
    readConfigurationFile();
}

void AutomationHelper::readConfigurationFile()
{
    ifstream configurationFile(APRG_WEB_CRAWLER_AUTOMATION_CONFIGURATION_FILE);
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
            else if("FirefoxExecutablePath:" == lineFromConfigurationFile)
            {
                m_firefoxExecutablePath = configurationFileReader.getLineAndIgnoreWhiteSpaces();
            }
            else if("FirefoxFilePosition:" == lineFromConfigurationFile)
            {
                strings listOfStrings;
                splitToStrings<SplitStringType::WithoutDelimeters>(listOfStrings, configurationFileReader.getLineAndIgnoreWhiteSpaces(), ",");
                m_firefoxFilePosition.setX(convertStringToNumber<int>(listOfStrings[0]));
                m_firefoxFilePosition.setY(convertStringToNumber<int>(listOfStrings[1]));
            }
            else if("FirefoxSavePagePosition:" == lineFromConfigurationFile)
            {
                strings listOfStrings;
                splitToStrings<SplitStringType::WithoutDelimeters>(listOfStrings, configurationFileReader.getLineAndIgnoreWhiteSpaces(), ",");
                m_firefoxSavePagePosition.setX(convertStringToNumber<int>(listOfStrings[0]));
                m_firefoxSavePagePosition.setY(convertStringToNumber<int>(listOfStrings[1]));
            }
            else if("FirefoxCloseButtonPosition:" == lineFromConfigurationFile)
            {
                strings listOfStrings;
                splitToStrings<SplitStringType::WithoutDelimeters>(listOfStrings, configurationFileReader.getLineAndIgnoreWhiteSpaces(), ",");
                m_firefoxCloseButtonPosition.setX(convertStringToNumber<int>(listOfStrings[0]));
                m_firefoxCloseButtonPosition.setY(convertStringToNumber<int>(listOfStrings[1]));
            }
            else if("FirefoxCloseSecondTabButtonPosition:" == lineFromConfigurationFile)
            {
                strings listOfStrings;
                splitToStrings<SplitStringType::WithoutDelimeters>(listOfStrings, configurationFileReader.getLineAndIgnoreWhiteSpaces(), ",");
                m_firefoxCloseSecondTabButtonPosition.setX(convertStringToNumber<int>(listOfStrings[0]));
                m_firefoxCloseSecondTabButtonPosition.setY(convertStringToNumber<int>(listOfStrings[1]));
            }
            else if("FdmUrlBarPosition:" == lineFromConfigurationFile)
            {
                strings listOfStrings;
                splitToStrings<SplitStringType::WithoutDelimeters>(listOfStrings, configurationFileReader.getLineAndIgnoreWhiteSpaces(), ",");
                m_fdmUrlBarPosition.setX(convertStringToNumber<int>(listOfStrings[0]));
                m_fdmUrlBarPosition.setY(convertStringToNumber<int>(listOfStrings[1]));
            }
            else if("FdmUrlCopyPosition:" == lineFromConfigurationFile)
            {
                strings listOfStrings;
                splitToStrings<SplitStringType::WithoutDelimeters>(listOfStrings, configurationFileReader.getLineAndIgnoreWhiteSpaces(), ",");
                m_fdmUrlCopyPosition.setX(convertStringToNumber<int>(listOfStrings[0]));
                m_fdmUrlCopyPosition.setY(convertStringToNumber<int>(listOfStrings[1]));
            }
            else if("FdmCloseDownloadWindowPosition:" == lineFromConfigurationFile)
            {
                strings listOfStrings;
                splitToStrings<SplitStringType::WithoutDelimeters>(listOfStrings, configurationFileReader.getLineAndIgnoreWhiteSpaces(), ",");
                m_fdmCloseDownloadWindowPosition.setX(convertStringToNumber<int>(listOfStrings[0]));
                m_fdmCloseDownloadWindowPosition.setY(convertStringToNumber<int>(listOfStrings[1]));
            }
            else if("TimeoutForOpeningFirefox:" == lineFromConfigurationFile)
            {
                m_timeoutForOpeningFirefox = convertStringToNumber<int>(configurationFileReader.getLineAndIgnoreWhiteSpaces());
            }
            else if("TimeoutForLoadingFirefox:" == lineFromConfigurationFile)
            {
                m_timeoutForLoadingFirefox = convertStringToNumber<int>(configurationFileReader.getLineAndIgnoreWhiteSpaces());
            }
            else if("TimeoutForWaitingResponseFromFirefox:" == lineFromConfigurationFile)
            {
                m_timeoutForWaitingResponseFromFirefox = convertStringToNumber<int>(configurationFileReader.getLineAndIgnoreWhiteSpaces());
            }
        }
    }
}

void AutomationHelper::openMozillaFirefoxExecutableManually(string const& webPath)
{
    AlbaWebPathHandler webPathHandler(webPath);
    string firefoxCommand(string("start ")+m_firefoxExecutablePath+R"( ")"+webPathHandler.getFullPath()+R"(")");
    cout << firefoxCommand << endl;
    system(firefoxCommand.c_str());
}

//use tabs instead of clicks
void AutomationHelper::saveWebPageManuallyUsingMozillaFirefox(string const& webPath)
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

string AutomationHelper::getRedirectedLinkUsingMozillaFirefoxAndFdm(string const& webPath)
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

void AutomationHelper::downloadLinkUsingMozillaFirefoxAndFdm(string const& webPath)
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
