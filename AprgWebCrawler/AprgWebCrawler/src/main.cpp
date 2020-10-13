#include <WebCrawler.hpp>
#include <iostream>

using namespace alba;using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "Something user interface" << endl;
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