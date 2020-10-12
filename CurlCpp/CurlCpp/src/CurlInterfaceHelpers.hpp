#pragma once

#include <CurlInterfaceConfigType.hpp>
#include <curl_easy.h>
#include <fstream>
#include <functional>
#include <string>

namespace curl
{

namespace CurlInterface
{
typedef std::function<void(curl_easy&)> ConfigurationFunction;
void addLowSpeedLimitToCurlEasy(curl_easy& easy, LONG const lowSpeedLimit, LONG const duration);
template<ConfigType configType> void addToCurlEasy(curl_easy&);
template <> void addToCurlEasy<ConfigType::LowSpeedLimit>(curl_easy& easy);
template <> void addToCurlEasy<ConfigType::MozillaFireFox>(curl_easy& easy);
template <> void addToCurlEasy<ConfigType::PrintDownloadProgress>(curl_easy& easy);
template <> void addToCurlEasy<ConfigType::LowSpeedLimitAndMozillaFireFox>(curl_easy& easy);
template <> void addToCurlEasy<ConfigType::MozillaFireFoxAndPrintDownloadProgress>(curl_easy& easy);
template <> void addToCurlEasy<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(curl_easy& easy);

bool downloadForOutputFileStream(std::string url, std::ofstream & outputFile, ConfigurationFunction additionalConfig);
bool downloadWithAdditionalConfig(std::string const& url, std::string const& fileLocation, ConfigurationFunction additionalConfig);
bool downloadWithAdditionalConfigUntilSuccessful(std::string const& url, std::string const& fileLocation, ConfigurationFunction additionalConfig);
bool downloadAsBinaryWithAdditionalConfig(std::string const& url, std::string const& fileLocation, ConfigurationFunction additionalConfig);
bool downloadAsBinaryWithAdditionalConfigUntilSuccessful(std::string const& url, std::string const& fileLocation, ConfigurationFunction additionalConfig);
bool downloadAsBinaryWithAdditionalConfigWithFiniteNumberOfTries(
        std::string const& url,
        std::string const& fileLocation,
        int const totalNumberOfTries,
        ConfigurationFunction additionalConfig);
inline void printDownloadErrorMessage(std::string const& errorMessage);

}


}
