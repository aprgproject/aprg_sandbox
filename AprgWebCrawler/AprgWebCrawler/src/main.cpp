#include <AprgWebCrawler.hpp>
#include <iostream>

using namespace alba;
using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "There should be at least 1 argument." << endl;
        return 1;
    }
    string path(argv[1]);
    AprgWebCrawler crawler(path);
    crawler.printStatus();
    crawler.crawl();

    return 0;
}
