#pragma once

#include <CurlInterfaceConfigType.hpp>
#include <curl_easy.h>
#include <fstream>
#include <functional>
#include <string>

using std::string;
using std::function;
using std::ofstream;

namespace curl
{

namespace CurlInterface
{

void addLowSpeedLimitToCurlEasy(curl_easy& easy, LONG const lowSpeedLimit, LONG const duration);
template<ConfigType configType> void addToCurlEasy(curl_easy&);
template <> void addToCurlEasy<ConfigType::LowSpeedLimit>(curl_easy& easy);
template <> void addToCurlEasy<ConfigType::MozillaFireFox>(curl_easy& easy);
template <> void addToCurlEasy<ConfigType::PrintDownloadProgress>(curl_easy& easy);
template <> void addToCurlEasy<ConfigType::LowSpeedLimitAndMozillaFireFox>(curl_easy& easy);
template <> void addToCurlEasy<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(curl_easy& easy);

bool downloadForOutputFileStream(string url, ofstream& outputFile, function<void(curl_easy&)> additionalConfig);
bool downloadWithAdditionalConfig(string const& url, string const& fileLocation, function<void(curl_easy&)> additionalConfig);
bool downloadWithAdditionalConfigUntilSuccessful(string const& url, string const& fileLocation, function<void(curl_easy&)> additionalConfig);
bool downloadAsBinaryWithAdditionalConfig(string const& url, string const& fileLocation, function<void(curl_easy&)> additionalConfig);
bool downloadAsBinaryWithAdditionalConfigUntilSuccessful(string const& url, string const& fileLocation, function<void(curl_easy&)> additionalConfig);
bool downloadAsBinaryWithAdditionalConfigWithFiniteNumberOfTries(string const& url, string const& fileLocation, function<void(curl_easy&)> additionalConfig);
inline void printDownloadErrorMessage(string const& errorMessage);

}


}
