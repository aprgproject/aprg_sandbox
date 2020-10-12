#pragma once

namespace curl
{

namespace CurlInterface
{

enum class ConfigType
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