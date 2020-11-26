#include "CurlInterface.hpp"
#include "CurlInterfaceHelpers.hpp"

using namespace alba;
using namespace std;

namespace curl
{

namespace CurlInterface
{

template<DownloadType... configTypes>
bool download(AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath)
{
    return downloadFile(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Default, [](curl_easy& easy)
    {
        addToCurlEasy<configTypes...>(easy);
    });
}

template<DownloadType... configTypes>
bool downloadUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath)
{
    return downloadFileUntilSuccessful(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Default, [](curl_easy& easy)
    {
        addToCurlEasy<configTypes...>(easy);
    });
}

template<DownloadType... configTypes>
bool downloadBinaryFile(AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath)
{
    return downloadFile(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Binary, [](curl_easy& easy)
    {
        addToCurlEasy<configTypes...>(easy);
    });
}

template<DownloadType... configTypes>
bool downloadBinaryFileUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath)
{
    return downloadFileUntilSuccessful(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Binary, [](curl_easy& easy)
    {
        addToCurlEasy<configTypes...>(easy);
    });
}

template<DownloadType... configTypes>
bool downloadBinaryFileWithFiniteNumberOfTries(AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath, int const totalNumberOfTries)
{
    return downloadFileWithFiniteNumberOfTries(webPath.getFullPath(), windowsPath.getFullPath(), OutputFileType::Binary, totalNumberOfTries, [](curl_easy& easy)
    {
        addToCurlEasy<configTypes...>(easy);
    });
}

template bool download<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox> (AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath);
template bool download<DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath);
template bool downloadUntilSuccessful<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox> (AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath);
template bool downloadBinaryFile<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath);
template bool downloadBinaryFileUntilSuccessful<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath);
template bool downloadBinaryFileWithFiniteNumberOfTries<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress> (AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath, int const totalNumberOfTries);
template bool downloadBinaryFile<DownloadType::LowSpeedLimit> (AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath);
template bool downloadBinaryFileUntilSuccessful<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress, DownloadType::Ssl> (AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath);
template bool downloadBinaryFileWithFiniteNumberOfTries<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress, DownloadType::Ssl> (AlbaWebPathHandler const& webPath, AlbaLocalPathHandler const& windowsPath, int const totalNumberOfTries);

}

}
