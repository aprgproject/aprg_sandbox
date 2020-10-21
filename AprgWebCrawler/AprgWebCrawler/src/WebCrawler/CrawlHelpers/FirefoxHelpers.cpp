#include "WebCrawler.hpp"

#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <iostream>
#include <windows.h>

using namespace alba;
using namespace std;

#define FIREFOX_EXECUTABLE_PATH R"(C:\"Program Files"\"Mozilla Firefox"\firefox.exe)"

namespace aprgWebCrawler
{

string WebCrawler::getUserInputAfterManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const
{
    constexpr int bufferSize = 1000;
    char buffer[bufferSize];
    gotoLinkManuallyUsingMozillaFirefox(webPathHandler);
    cout<<"Enter user input:"<<endl;
    cin.getline(buffer, bufferSize);
    return string(buffer);
}

void WebCrawler::gotoLinkManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const
{
    string firefoxCommand(string(FIREFOX_EXECUTABLE_PATH)+R"( ")"+webPathHandler.getFullPath()+R"(")");
    cout << firefoxCommand << endl;
    system(firefoxCommand.c_str());
}

}
