#pragma once

#include <AlbaWebPathHandler.hpp>
#include <AlbaWindowsPathHandler.hpp>
#include <CurlInterfaceConfigType.hpp>
#include <string>

using alba::AlbaWebPathHandler;
using alba::AlbaWindowsPathHandler;
using curl::CurlInterface::ConfigType;
using std::string;

namespace curl
{

namespace CurlInterface
{

template <ConfigType configType> bool download(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template <ConfigType configType> bool downloadUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template <ConfigType configType> bool downloadBinaryFile(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template <ConfigType configType> bool downloadBinaryFileUntilSuccessful(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath);
template <ConfigType configType> bool downloadBinaryFileWithFiniteNumberOfTries(AlbaWebPathHandler const& webPath, AlbaWindowsPathHandler const& windowsPath, int const totalNumberOfTries);

}


}
