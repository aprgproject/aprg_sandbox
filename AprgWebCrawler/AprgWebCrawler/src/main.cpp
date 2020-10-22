#include <CrawlHelpers/FirefoxHandler.hpp>
#include <iostream>
#include <UserInterface.hpp>
#include <WebCrawler.hpp>

using namespace aprgWebCrawler;
using namespace std;

int main2(int argc, char** argv)
{
    if(argc < 2)
    {        UserInterface userInterface;
        userInterface.startUi();
    }
    else    {
        string path(argv[1]);
        WebCrawler crawler(path);
        crawler.printStatus();
        crawler.crawl();
    }
    return 0;
}

int main(int argc, char** argv)
{
    FirefoxHandler::saveWebPageManuallyUsingMozillaFirefox(R"(https://www.ssyoutube.com/watch?v=b436uUuf_VI&list=PLmKbqjSZR8TbfAMV9bLy4beDh4vrze5kc&index=54)");
}