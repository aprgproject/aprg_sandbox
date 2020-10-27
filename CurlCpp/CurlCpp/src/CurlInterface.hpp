#pragma once

#include <DownloadType.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>

#include <string>

namespace curl
{

namespace CurlInterface
{

extern int lowSpeedLimit;
extern int lowSpeedTime;

template <DownloadType configType> bool download(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType configType> bool downloadUntilSuccessful(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType configType> bool downloadBinaryFile(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType configType> bool downloadBinaryFileUntilSuccessful(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType configType> bool downloadBinaryFileWithFiniteNumberOfTries(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath, int const totalNumberOfTries);

}


}
