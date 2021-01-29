#include <UserInterface/UserInterface.hpp>
#include <WebCrawler/WebCrawler.hpp>

#include <iostream>

using namespace aprgWebCrawler;
using namespace std;

int main(int , char** )
{
    //UI
    //UserInterface userInterface;
    //userInterface.startUi();

    //test
    cout<<"test"<<endl;
    WebCrawler crawler(APRG_CRAWLER_TEST_DIRECTORY, R"(https://www.youtube.com/watch?v=d6D4FgTpS9o&list=PL8NWNRmPSvBYvo8QOui8N14ZOK1pGkFA4&index=1)", APRG_CRAWLER_TEST_TEMPORARY_FILE_PATH);
    crawler.printStatus();
    crawler.crawl();

    return 0;
}
