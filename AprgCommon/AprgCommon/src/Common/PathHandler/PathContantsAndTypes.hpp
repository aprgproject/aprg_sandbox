#pragma once

#include <set>
#include <string>

namespace alba
{

enum class PathInitialValue
{
    CurrentDetectedPath,
    TemporaryLocalPath,
};

using ListOfPaths = std::set<std::string>;
}//namespace alba