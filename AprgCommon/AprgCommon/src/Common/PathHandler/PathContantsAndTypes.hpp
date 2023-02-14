#pragma once

#include <set>
#include <string>

namespace alba
{

enum class PathInitialValueSource
{
    DetectedLocalPath
};

using ListOfPaths = std::set<std::string>;

}//namespace alba