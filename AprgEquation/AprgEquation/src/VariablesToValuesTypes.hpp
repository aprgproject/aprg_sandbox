#pragma once

#include <Math/AlbaNumber.hpp>

#include <map>
#include <string>

namespace alba
{

namespace equation
{

using VariablesToValuesMap = std::map<std::string, AlbaNumber>;
using VariableValuePair = std::pair<std::string, AlbaNumber>;

}

}
