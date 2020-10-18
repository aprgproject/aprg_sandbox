#pragma once

#include <CurlInterfaceConfigType.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>

namespace curl
{

namespace CurlInterface
{

extern int lowSpeedLimit;
extern int lowSpeedTime;

template <ConfigType configType> bool download(alba::AlbaWebPathHandler const& webPath, alba::AlbaWindowsPathHandler const& windowsPath);
template <ConfigType configType> bool downloadUntilSuccessful(alba::AlbaWebPathHandler const& webPath, alba::AlbaWindowsPathHandler const& windowsPath);
template <ConfigType configType> bool downloadBinaryFile(alba::AlbaWebPathHandler const& webPath, alba::AlbaWindowsPathHandler const& windowsPath);
template <ConfigType configType> bool downloadBinaryFileUntilSuccessful(alba::AlbaWebPathHandler const& webPath, alba::AlbaWindowsPathHandler const& windowsPath);
template <ConfigType configType> bool downloadBinaryFileWithFiniteNumberOfTries(alba::AlbaWebPathHandler const& webPath, alba::AlbaWindowsPathHandler const& windowsPath, int const totalNumberOfTries);

}


}
