#include <UserInterface.hpp>
#include <iostream>
#include <WebCrawler.hpp>

using namespace aprgWebCrawler;
using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        UserInterface userInterface;
        userInterface.startUi();
    }
    else
    {
        string path(argv[1]);
        WebCrawler crawler(path);
        crawler.printStatus();
        crawler.crawl();
    }
    return 0;
}
