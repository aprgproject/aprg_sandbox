#include <CurlInterfaceHelpers.hpp>

#include <fstream>
#include <iostream>
#include <windows.h>

using curl::CurlInterface::ConfigType;
using curl::curl_easy;

using namespace std;

namespace curl
{

static int xferinfo(void *, curl_off_t dlTotal, curl_off_t dlNow, curl_off_t ulTotal, curl_off_t ulNow)
{
    curl_off_t currentBytesTransferred(dlNow+ulNow);
    curl_off_t totalBytes(dlTotal+ulTotal);
    double percentProgress = (totalBytes == 0) ? 0 : (double)100*currentBytesTransferred/totalBytes;
    if((int)percentProgress == 100)
    {
        cout<< "\rProgress: " << percentProgress << "% (DownLink: " << dlNow << " of " << dlTotal << "   UpLink: " << ulNow << " of " << ulTotal  << ")" << endl;
    }
    else
    {
        cout<< "\rProgress: " << percentProgress << "% (DownLink: " << dlNow << " of " << dlTotal << "   UpLink: " << ulNow << " of " << ulTotal  << ")" << std::flush;
    }
    return 0;
}

void CurlInterface::addLowSpeedLimitToCurlEasy(curl_easy& easy, LONG const lowSpeedLimit, LONG const duration)
{
    easy.add<CURLOPT_LOW_SPEED_LIMIT>(lowSpeedLimit);
    easy.add<CURLOPT_LOW_SPEED_TIME>(duration);
}

template <ConfigType configType>
void CurlInterface::addToCurlEasy(curl_easy&)
{}

template <>
void CurlInterface::addToCurlEasy<ConfigType::LowSpeedLimit>(curl_easy& easy)
{
    addLowSpeedLimitToCurlEasy(easy, 1000, 60);
}

template <>
void CurlInterface::addToCurlEasy<ConfigType::MozillaFireFox>(curl_easy& easy)
{
    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:39.0) Gecko/20100101 Firefox/39.0");
    chunk = curl_slist_append(chunk, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    chunk = curl_slist_append(chunk, "Accept-Language: en-US,en;q=0.5");
    easy.add<CURLOPT_HTTPHEADER>(chunk);

    easy.add<CURLOPT_ACCEPT_ENCODING>("identity");
}

template <>
void CurlInterface::addToCurlEasy<ConfigType::PrintDownloadProgress>(curl_easy& easy)
{
    easy.add<CURLOPT_XFERINFOFUNCTION>(xferinfo);
    easy.add<CURLOPT_XFERINFODATA>(nullptr);
    easy.add<CURLOPT_NOPROGRESS>(0);
}

template <>
void CurlInterface::addToCurlEasy<ConfigType::MozillaFireFoxAndPrintDownloadProgress>(curl_easy& easy)
{
    addToCurlEasy<ConfigType::MozillaFireFox>(easy);
    addToCurlEasy<ConfigType::PrintDownloadProgress>(easy);
}

template <>
void CurlInterface::addToCurlEasy<ConfigType::LowSpeedLimitAndMozillaFireFox>(curl_easy& easy)
{
    addToCurlEasy<ConfigType::LowSpeedLimit>(easy);    addToCurlEasy<ConfigType::MozillaFireFox>(easy);
}

template <>void CurlInterface::addToCurlEasy<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(curl_easy& easy)
{
    addToCurlEasy<ConfigType::LowSpeedLimit>(easy);
    addToCurlEasy<ConfigType::MozillaFireFox>(easy);
    addToCurlEasy<ConfigType::PrintDownloadProgress>(easy);
}

bool CurlInterface::downloadForOutputFileStream(string url, ofstream& outputFile, function<void(curl_easy&)> additionalConfig)
{
    if(!outputFile.is_open())
    {
        printDownloadErrorMessage("Cannot open output file");
        return false;
    }

    curl_writer writer(outputFile);
    curl_easy easy(writer);
    easy.add(curl_pair<CURLoption,string>(CURLOPT_URL, url));
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    additionalConfig(easy);
    try
    {
        easy.perform();
        return true;
    }
    catch (curl_easy_exception error)
    {
        auto errors = error.what();
        printDownloadErrorMessage(string(errors));
        error.print_traceback();
    }
    return false;
}

bool CurlInterface::downloadWithAdditionalConfig(string const& url, string const& fileLocation, function<void(curl_easy&)> additionalConfig)
{
    cout<<"   --> Downloading file. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
    ofstream outputFile(fileLocation);
    bool isSuccessful (downloadForOutputFileStream(url, outputFile, additionalConfig));
    if(!isSuccessful)
    {
        cout<<"   --> Download failed. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
    }
    return isSuccessful;
}

bool CurlInterface::downloadWithAdditionalConfigUntilSuccessful(string const& url, string const& fileLocation, function<void(curl_easy&)> additionalConfig)
{
    bool isSuccessful(false);
    while(!isSuccessful)
    {
        cout<<"   --> Downloading file until successful. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
        ofstream outputFile(fileLocation);
        isSuccessful = downloadForOutputFileStream(url, outputFile, additionalConfig);
        if(!isSuccessful)
        {
            cout<<"   --> Download failed and retrying in a few seconds. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
            Sleep(5000);
        }
    }
    return isSuccessful;
}


bool CurlInterface::downloadAsBinaryWithAdditionalConfig(string const& url, string const& fileLocation, function<void(curl_easy&)> additionalConfig)
{
    cout<<"   --> Downloading binary file. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
    ofstream outputFile(fileLocation, ofstream::binary);
    bool isSuccessful (downloadForOutputFileStream(url, outputFile, additionalConfig));
    if(!isSuccessful)
    {
        cout<<"   --> Download failed. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
    }
    return isSuccessful;
}

bool CurlInterface::downloadAsBinaryWithAdditionalConfigUntilSuccessful(string const& url, string const& fileLocation, function<void(curl_easy&)> additionalConfig)
{
    bool isSuccessful(false);
    while(!isSuccessful)
    {
        cout<<"   --> Downloading binary file until successful. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
        ofstream outputFile(fileLocation, ofstream::binary);
        isSuccessful = downloadForOutputFileStream(url, outputFile, additionalConfig);
        if(!isSuccessful)
        {
            cout<<"   --> Download failed and retrying in a few seconds. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
            Sleep(5000);
        }
    }
    return isSuccessful;
}

bool CurlInterface::downloadAsBinaryWithAdditionalConfigWithFiniteNumberOfTries(
        string const& url,
        string const& fileLocation,
        int const totalNumberOfTries,
        function<void(curl_easy&)> additionalConfig)
{
    bool isSuccessful(false);
    for(int numberOfTries = 1; (!isSuccessful)&&(numberOfTries <= totalNumberOfTries); numberOfTries++)
    {
        cout<<"   --> Downloading binary file. Number of tries=" << numberOfTries << " \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
        ofstream outputFile(fileLocation, ofstream::binary);
        isSuccessful = downloadForOutputFileStream(url, outputFile, [numberOfTries, additionalConfig](curl_easy& easy)
        {
                additionalConfig(easy);
                addLowSpeedLimitToCurlEasy(easy, 1000, 10*numberOfTries);
        });
        if(!isSuccessful)
        {
            cout<<"   --> Download failed and retrying in a few seconds. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
            Sleep(5000);
        }
    }
    return isSuccessful;
}

void CurlInterface::printDownloadErrorMessage(string const& errorMessage)
{
    cout << "CurlInterface::download function failed. Error: " << errorMessage << endl;
}

}
