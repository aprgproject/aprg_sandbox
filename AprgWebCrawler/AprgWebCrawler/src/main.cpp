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

    /*AlbaWebPathHandler webPathHandler;
    webPathHandler.inputPath(R"(http://www.youtube.com/oembed?url=http://www.youtube.com/watch?v=7EFSPTEY1s0&index=1&list=PL3_NLXp9puXX1iFiBaRX1s8TMbsae8MD5&format=json)");
    AlbaWindowsPathHandler windowsPathHandler;
    windowsPathHandler.inputPath(R"(E:\CrawlerDownload\sample.txt)");
    curl::CurlInterface::downloadBinaryFileUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(webPathHandler, windowsPathHandler);
    */
    return 0;
}
