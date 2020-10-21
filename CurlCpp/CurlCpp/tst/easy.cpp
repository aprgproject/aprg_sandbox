#include "CurlInterface.hpp"

using namespace curl::CurlInterface;
using namespace alba;

int main()
{
    AlbaWebPathHandler webPathHandler(R"(http://www.doujin-moe.us/6xp3sqqm)");
    AlbaWindowsPathHandler windowPathHandler(R"(C:\APRG\CurlCpp\CurlCpp\tst\home.html)");
    download<DownloadType::MozillaFireFoxAndPrintDownloadProgress>(webPathHandler, windowPathHandler);
    //downloadBinaryFile<ConfigType::MozillaFireFoxAndPrintDownloadProgress>(webPathHandler, windowPathHandler);
}
