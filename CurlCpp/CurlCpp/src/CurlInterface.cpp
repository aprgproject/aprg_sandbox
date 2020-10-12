#include "CurlInterface.hpp"

#include "CurlInterfaceHelpers.hpp"

using namespace alba;
using namespace std;

namespace curl
{

namespace CurlInterface
{

template<ConfigType configType>
bool download(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadWithAdditionalConfig(webPath.getFullPath(), windowsPath.getFullPath(), [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);    });
}

template<ConfigType configType>
bool downloadUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadWithAdditionalConfigUntilSuccessful(webPath.getFullPath(), windowsPath.getFullPath(), [](curl_easy& easy)
    {        addToCurlEasy<configType>(easy);
    });
}

template<ConfigType configType>
bool downloadBinaryFile(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadAsBinaryWithAdditionalConfig(webPath.getFullPath(), windowsPath.getFullPath(), [](curl_easy& easy)
    {        addToCurlEasy<configType>(easy);
    });
}

template<ConfigType configType>
bool downloadBinaryFileUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadAsBinaryWithAdditionalConfigUntilSuccessful(webPath.getFullPath(), windowsPath.getFullPath(), [](curl_easy& easy)
    {        addToCurlEasy<configType>(easy);
    });
}

template<ConfigType configType>
bool downloadBinaryFileWithFiniteNumberOfTries(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath, int const totalNumberOfTries)
{
    return downloadAsBinaryWithAdditionalConfigWithFiniteNumberOfTries(webPath.getFullPath(), windowsPath.getFullPath(), totalNumberOfTries, [](curl_easy& easy)
    {        addToCurlEasy<configType>(easy);
    });
}

template bool download<ConfigType::LowSpeedLimitAndMozillaFireFox> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool download<ConfigType::MozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool downloadUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFox> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool downloadBinaryFile<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool downloadBinaryFileUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool downloadBinaryFileWithFiniteNumberOfTries<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath, int const totalNumberOfTries);

}
}