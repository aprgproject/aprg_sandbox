#include "CurlInterface.hpp"

#include "CurlInterfaceHelpers.hpp"

using namespace std;

namespace curl
{

template<CurlInterface::ConfigType configType>
bool CurlInterface::download(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadWithAdditionalConfig(webPath.getFullPath(), windowsPath.getFullPath(), [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template<CurlInterface::ConfigType configType>
bool CurlInterface::downloadUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadWithAdditionalConfigUntilSuccessful(webPath.getFullPath(), windowsPath.getFullPath(), [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template<CurlInterface::ConfigType configType>
bool CurlInterface::downloadBinaryFile(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadAsBinaryWithAdditionalConfig(webPath.getFullPath(), windowsPath.getFullPath(), [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template<CurlInterface::ConfigType configType>
bool CurlInterface::downloadBinaryFileUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadAsBinaryWithAdditionalConfigUntilSuccessful(webPath.getFullPath(), windowsPath.getFullPath(), [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template<CurlInterface::ConfigType configType>
bool CurlInterface::downloadBinaryFileWithFiniteNumberOfTries(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath, int const totalNumberOfTries)
{
    return downloadAsBinaryWithAdditionalConfigWithFiniteNumberOfTries(webPath.getFullPath(), windowsPath.getFullPath(), totalNumberOfTries, [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template bool CurlInterface::download<ConfigType::LowSpeedLimitAndMozillaFireFox> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool CurlInterface::download<ConfigType::MozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool CurlInterface::downloadUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFox> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool CurlInterface::downloadBinaryFile<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool CurlInterface::downloadBinaryFileUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);template bool CurlInterface::downloadBinaryFileWithFiniteNumberOfTries<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath, int const totalNumberOfTries);


}