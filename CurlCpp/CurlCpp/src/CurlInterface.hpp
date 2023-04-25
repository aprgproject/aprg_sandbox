#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/PathHandler/AlbaWebPathHandler.hpp>
#include <DownloadType.hpp>

#include <string>

namespace curl {

namespace CurlInterface {

extern int lowSpeedLimit;
extern int lowSpeedTime;

template <DownloadType... configTypes>
bool download(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType... configTypes>
bool downloadUntilSuccessful(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType... configTypes>
bool downloadBinaryFile(alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType... configTypes>
bool downloadBinaryFileUntilSuccessful(
    alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath);
template <DownloadType... configTypes>
bool downloadBinaryFileWithFiniteNumberOfTries(
    alba::AlbaWebPathHandler const& webPath, alba::AlbaLocalPathHandler const& windowsPath,
    int const totalNumberOfTries);

}  // namespace CurlInterface

}  // namespace curl
