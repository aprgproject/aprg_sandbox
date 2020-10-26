#include <CurlInterfaceHelpers.hpp>

#include <windows.h>

#include <fstream>
#include <iostream>

using curl::CurlInterface::DownloadType;
using curl::CurlInterface::OutputFileType;
using curl::curl_easy;

using namespace std;

namespace curl
{

namespace CurlInterface
{
int lowSpeedLimit=1000;
int lowSpeedTime=60;
}

static int xferinfo(void *, curl_off_t dlTotal, curl_off_t dlNow, curl_off_t ulTotal, curl_off_t ulNow)
{
    curl_off_t currentBytesTransferred(dlNow+ulNow);
    curl_off_t totalBytes(dlTotal+ulTotal);
    double percentProgress = (totalBytes == 0) ? 0 : (double)100*currentBytesTransferred/totalBytes;
    cout<< "\rProgress: " << percentProgress << "% (DownLink: " << dlNow << " of " << dlTotal << "   UpLink: " << ulNow << " of " << ulTotal  << ")" << std::flush;
    return 0;
}

void CurlInterface::addLowSpeedLimitToCurlEasy(curl_easy& easy, LONG const lowSpeedLimit, LONG const duration)
{
    easy.add<CURLOPT_LOW_SPEED_LIMIT>(lowSpeedLimit);
    easy.add<CURLOPT_LOW_SPEED_TIME>(duration);
}

template <DownloadType downloadType>
void CurlInterface::addToCurlEasy(curl_easy&)
{}

template <>
void CurlInterface::addToCurlEasy<DownloadType::LowSpeedLimit>(curl_easy& easy)
{
    addLowSpeedLimitToCurlEasy(easy, lowSpeedLimit, lowSpeedTime);
}

template <>
void CurlInterface::addToCurlEasy<DownloadType::MozillaFireFox>(curl_easy& easy)
{
    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:39.0) Gecko/20100101 Firefox/39.0");
    chunk = curl_slist_append(chunk, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    chunk = curl_slist_append(chunk, "Accept-Language: en-US,en;q=0.5");
    easy.add<CURLOPT_HTTPHEADER>(chunk);

    easy.add<CURLOPT_ACCEPT_ENCODING>("identity");
}

template <>
void CurlInterface::addToCurlEasy<DownloadType::PrintDownloadProgress>(curl_easy& easy)
{
    easy.add<CURLOPT_XFERINFOFUNCTION>(xferinfo);
    easy.add<CURLOPT_XFERINFODATA>(nullptr);
    easy.add<CURLOPT_NOPROGRESS>(0);
}

template <>
void CurlInterface::addToCurlEasy<DownloadType::MozillaFireFoxAndPrintDownloadProgress>(curl_easy& easy)
{
    addToCurlEasy<DownloadType::MozillaFireFox>(easy);
    addToCurlEasy<DownloadType::PrintDownloadProgress>(easy);
}

template <>
void CurlInterface::addToCurlEasy<DownloadType::LowSpeedLimitAndMozillaFireFox>(curl_easy& easy)
{
    addToCurlEasy<DownloadType::LowSpeedLimit>(easy);
    addToCurlEasy<DownloadType::MozillaFireFox>(easy);
}

template <>
void CurlInterface::addToCurlEasy<DownloadType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(curl_easy& easy)
{
    addToCurlEasy<DownloadType::LowSpeedLimit>(easy);
    addToCurlEasy<DownloadType::MozillaFireFox>(easy);
    addToCurlEasy<DownloadType::PrintDownloadProgress>(easy);
}

void CurlInterface::createOutputStream(unique_ptr<ofstream> & outputStream, OutputFileType outputFileType, string const& fileLocation)
{
    switch (outputFileType)
    {
    case OutputFileType::Binary:
        outputStream.reset(new ofstream(fileLocation, ofstream::binary));
        break;
    default:
        outputStream.reset(new ofstream(fileLocation));
        break;
    }
}

bool CurlInterface::download(string url, ofstream& outputFile, function<void(curl_easy&)> additionalConfig)
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

    bool status(false);
    additionalConfig(easy);
    try
    {
        easy.perform();
        status = true;
    }
    catch (curl_easy_exception error)
    {
        auto errors = error.what();
        printDownloadErrorMessage(string(errors));
        error.print_traceback();
    }
    cout << endl;
    return status;
}

bool CurlInterface::downloadFile(string const& url, string const& fileLocation, OutputFileType outputFileType, CurlInterface::ConfigurationFunction additionalConfig)
{
    cout<<"   --> Downloading file. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
    unique_ptr<ofstream> outputFile;
    createOutputStream(outputFile, outputFileType, fileLocation);
    bool isSuccessful (download(url, *(outputFile.get()), additionalConfig));
    if(!isSuccessful)
    {
        cout<<"   --> Download failed. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
    }
    return isSuccessful;
}

bool CurlInterface::downloadFileUntilSuccessful(string const& url, string const& fileLocation, OutputFileType outputFileType, CurlInterface::ConfigurationFunction additionalConfig)
{
    bool isSuccessful(false);
    while(!isSuccessful)
    {
        cout<<"   --> Downloading file until successful. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
        unique_ptr<ofstream> outputFile;
        createOutputStream(outputFile, outputFileType, fileLocation);
        isSuccessful = download(url, *(outputFile.get()), additionalConfig);
        if(!isSuccessful)
        {
            cout<<"   --> Download failed and retrying in a few seconds. \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
            Sleep(5000);
        }
    }
    return isSuccessful;
}

bool CurlInterface::downloadFileWithFiniteNumberOfTries(
        string const& url,
        string const& fileLocation,
        OutputFileType outputFileType,
        int const totalNumberOfTries,
        CurlInterface::ConfigurationFunction additionalConfig)
{
    bool isSuccessful(false);
    for(int numberOfTries = 1; (!isSuccessful)&&(numberOfTries <= totalNumberOfTries); numberOfTries++)
    {
        cout<<"   --> Downloading binary file. Number of tries=" << numberOfTries << " \nFile: ["<<fileLocation<<"] \nFrom: ["<<url<<"]"<<endl;
        unique_ptr<ofstream> outputFile;
        createOutputStream(outputFile, outputFileType, fileLocation);
        isSuccessful = download(url, *(outputFile.get()), [numberOfTries, additionalConfig](curl_easy& easy)
        {
                additionalConfig(easy);
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


