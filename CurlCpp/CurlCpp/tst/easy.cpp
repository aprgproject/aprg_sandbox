#include "curl_easy.h"
#include "curl_option.h"
#include "CurlInterface.hpp"
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

using curl::curl_easy;
using curl::make_option;

using namespace curl::CurlInterface;
using namespace alba;

int main()
{
    AlbaWebPathHandler webPathHandler(R"(http://pronto.inside.nsn.com/pronto/home.html)");
    AlbaWindowsPathHandler windowPathHandler(R"(C:\APRG\CurlCpp\CurlCpp\tst\home.html)");
    download<ConfigType::MozillaFireFoxAndPrintDownloadProgress>(webPathHandler, windowPathHandler);
    //downloadBinaryFile<ConfigType::PrintDownloadProgress>(webPathHandler, windowPathHandler);
}

int main_curl_easy()
{
    curl_easy easy;

    easy.add<CURLOPT_URL>("http://mangafox.me/manga/kateikyoushi_hitman_reborn/v02/c014/4.html");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();
    }
    catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        //auto errors = error.what();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }

    return 0;
}
