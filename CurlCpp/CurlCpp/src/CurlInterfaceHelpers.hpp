#pragma once

#include <curl_easy.h>
#include <DownloadType.hpp>
#include <fstream>
#include <functional>
#include <OutputFileType.hpp>
#include <string>

namespace curl
{

namespace CurlInterface
{

extern int lowSpeedLimit;
extern int lowSpeedTime;

typedef std::function<void(curl_easy&)> ConfigurationFunction;
void addLowSpeedLimitToCurlEasy(curl_easy& easy, LONG const lowSpeedLimit, LONG const duration);
template<DownloadType downloadType> void addToCurlEasy(curl_easy&);
template <> void addToCurlEasy<DownloadType::LowSpeedLimit>(curl_easy& easy);
template <> void addToCurlEasy<DownloadType::MozillaFireFox>(curl_easy& easy);
template <> void addToCurlEasy<DownloadType::PrintDownloadProgress>(curl_easy& easy);
template <> void addToCurlEasy<DownloadType::LowSpeedLimitAndMozillaFireFox>(curl_easy& easy);
template <> void addToCurlEasy<DownloadType::MozillaFireFoxAndPrintDownloadProgress>(curl_easy& easy);
template <> void addToCurlEasy<DownloadType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(curl_easy& easy);

void createOutputStream(std::unique_ptr<std::ofstream> & outputStream,OutputFileType outputFileType, std::string const& fileLocation);

bool download(std::string url, std::ofstream & outputFile, ConfigurationFunction additionalConfig);
bool downloadFile(std::string const& url, std::string const& fileLocation, OutputFileType outputFileType, ConfigurationFunction additionalConfig);bool downloadFileUntilSuccessful(std::string const& url, std::string const& fileLocation, OutputFileType outputFileType, ConfigurationFunction additionalConfig);
bool downloadFileWithFiniteNumberOfTries(
        std::string const& url,
        std::string const& fileLocation,        OutputFileType outputFileType,
        int const totalNumberOfTries,
        ConfigurationFunction additionalConfig);
inline void printDownloadErrorMessage(std::string const& errorMessage);

}


}
