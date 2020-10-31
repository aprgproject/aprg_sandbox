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
    Ssl,
    LowSpeedLimitAndMozillaFireFox,
    MozillaFireFoxAndPrintDownloadProgress,
    LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress,
    LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgressWithSsl
};

}

}
