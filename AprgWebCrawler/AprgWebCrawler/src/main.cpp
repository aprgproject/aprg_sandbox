#include <CrawlHelpers/AutomationHelper.hpp>
#include <iostream>
#include <UserInterface.hpp>
#include <WebCrawler.hpp>

#define APRG_CRAWLER_TEMPORARY_FILE_PATH R"(C:\APRG\AprgWebCrawler\TemporaryFile)"

using namespace aprgWebCrawler;
using namespace std;
int main(int argc, char** argv)
{
    if(argc < 2)    {
        UserInterface userInterface;
        userInterface.startUi();
    }
    else
    {
        string path(argv[1]);
        WebCrawler crawler(path, APRG_CRAWLER_TEMPORARY_FILE_PATH);
        crawler.printStatus();
        crawler.crawl();
    }    return 0;
}
