#include "CurlInterface.hpp"

#include "CurlInterfaceHelpers.hpp"

using namespace alba;
using namespace std;

namespace curl
{

namespace CurlInterface
{

template<DownloadType configType>
bool download(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadFile(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Default, [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template<DownloadType configType>
bool downloadUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadFileUntilSuccessful(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Default, [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template<DownloadType configType>
bool downloadBinaryFile(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadFile(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Binary, [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template<DownloadType configType>
bool downloadBinaryFileUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath)
{
    return downloadFileUntilSuccessful(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Binary, [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template<DownloadType configType>
bool downloadBinaryFileWithFiniteNumberOfTries(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath, int const totalNumberOfTries)
{
    return downloadFileWithFiniteNumberOfTries(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Binary, totalNumberOfTries, [](curl_easy& easy)
    {
        addToCurlEasy<configType>(easy);
    });
}

template bool download<DownloadType::LowSpeedLimitAndMozillaFireFox> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool download<DownloadType::MozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool downloadUntilSuccessful<DownloadType::LowSpeedLimitAndMozillaFireFox> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool downloadBinaryFile<DownloadType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool downloadBinaryFileUntilSuccessful<DownloadType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template bool downloadBinaryFileWithFiniteNumberOfTries<DownloadType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath, int const totalNumberOfTries);

}

}
