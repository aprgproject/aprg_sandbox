#include "CurlInterface.hpp"
#include <string>

using namespace alba;
using namespace curl::CurlInterface;
using namespace std;

int main(int argc, char** argv)
{
    if(argc >= 2)
    {
        string webPath(argv[1]);
        AlbaWebPathHandler webPathHandler(webPath);
        AlbaWindowsPathHandler windowPathHandler(R"(C:\APRG\CurlCpp\CurlCpp\tst\test.html)");
        download<DownloadType::MozillaFireFoxAndPrintDownloadProgress>(webPathHandler, windowPathHandler);
        //downloadBinaryFile<DownloadType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(webPathHandler, windowPathHandler);
    }
}