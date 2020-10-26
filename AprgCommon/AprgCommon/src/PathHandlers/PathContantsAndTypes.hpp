#pragma once

#include <set>
#include <string>

namespace alba
{

enum class PathInitialValueSource
{
    DetectedLocalPath
};

typedef std::set<std::string> ListOfPaths;

}//namespace alba
