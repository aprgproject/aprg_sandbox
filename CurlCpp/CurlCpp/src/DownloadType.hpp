#pragma once

namespace curl
{

namespace CurlInterface
{

enum class DownloadType
{
    LowSpeedLimit,
    MozillaFireFox,
    PrintDownloadProgress,
    LowSpeedLimitAndMozillaFireFox,
    MozillaFireFoxAndPrintDownloadProgress,
    LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress
};

}

}
