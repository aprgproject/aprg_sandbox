#include "FirefoxHandler.hpp"

#include <AlbaUserAutomation.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <iostream>
#include <windows.h>

#define FIREFOX_EXECUTABLE_PATH R"(C:\"Program Files"\"Mozilla Firefox"\firefox.exe)"
#define FIREFOX_RESTART_FIREFOX_POSITION 677, 541
#define FIREFOX_FILE_POSITION 15,9
#define FIREFOX_SAVE_PAGE_AS_POSITION 116, 127
#define FIREFOX_CLOSE_BUTTON_POSITION 1338, 7
#define FIREFOX_OPEN_TIMEOUT 60000
#define FIREFOX_LOADING_TIMEOUT 60000
#define FIREFOX_WAIT_FOR_RESPONSE 10000

using namespace alba;
using namespace std;

namespace aprgWebCrawler
{

void FirefoxHandler::saveWebPageManuallyUsingMozillaFirefox(string const& webPath)
{
    AlbaWebPathHandler webPathHandler(webPath);
    AlbaUserAutomation userAutomation;
    cout<<"Open Firefox"<<endl;
    openMozillaFirefoxExecutableManually(webPathHandler.getFullPath());

    cout<<"Wait"<<endl;
    Sleep(FIREFOX_OPEN_TIMEOUT);

    cout<<"Click restart firefox"<<endl;
    userAutomation.setMousePosition(MousePosition{FIREFOX_RESTART_FIREFOX_POSITION});
    userAutomation.doLeftClick();

    cout<<"Wait"<<endl;
    Sleep(FIREFOX_LOADING_TIMEOUT);

    cout<<"Click file"<<endl;
    userAutomation.setMousePosition(MousePosition{FIREFOX_FILE_POSITION});
    userAutomation.doLeftClick();
    cout<<"Click save page as"<<endl;
    userAutomation.setMousePosition(MousePosition{FIREFOX_SAVE_PAGE_AS_POSITION});
    userAutomation.doLeftClick();

    cout<<"Wait"<<endl;
    Sleep(FIREFOX_WAIT_FOR_RESPONSE);

    cout<<"Type name"<<endl;
    userAutomation.typeString(R"(temphtml)");
    cout<<"Enter"<<endl;
    userAutomation.typeCharacter(0x0D);

    cout<<"Wait"<<endl;
    Sleep(FIREFOX_WAIT_FOR_RESPONSE);

    cout<<"Close firefox"<<endl;
    userAutomation.setMousePosition(MousePosition{FIREFOX_CLOSE_BUTTON_POSITION});
    userAutomation.doLeftClick();
}

void FirefoxHandler::openMozillaFirefoxExecutableManually(string const& webPath)
{
    AlbaWebPathHandler webPathHandler(webPath);
    string firefoxCommand(string("start ")+FIREFOX_EXECUTABLE_PATH+R"( ")"+webPathHandler.getFullPath()+R"(")");
    cout << firefoxCommand << endl;
    system(firefoxCommand.c_str());
}

}
