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

template <DownloadType... configTypes> bool download(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType... configTypes> bool downloadUntilSuccessful(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType... configTypes> bool downloadBinaryFile(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType... configTypes> bool downloadBinaryFileUntilSuccessful(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType... configTypes> bool downloadBinaryFileWithFiniteNumberOfTries(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath, int const totalNumberOfTries);

}

}