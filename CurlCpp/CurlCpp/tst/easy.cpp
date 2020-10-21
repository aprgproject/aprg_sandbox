#include "CurlInterface.hpp"

using namespace curl::CurlInterface;
using namespace alba;

int main()
{
    AlbaWebPathHandler webPathHandler(R"(http://static.doujin-moe.us/r-xw2jdte8.jpg?st=I3ab-_KKAWFeoAMw0MzDIg&e=1462041117)");
    AlbaWindowsPathHandler windowPathHandler(R"(C:\APRG\CurlCpp\CurlCpp\tst\home.jpg)");
    //download<DownloadType::MozillaFireFoxAndPrintDownloadProgress>(webPathHandler, windowPathHandler);
    downloadBinaryFile<DownloadType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(webPathHandler, windowPathHandler);
}