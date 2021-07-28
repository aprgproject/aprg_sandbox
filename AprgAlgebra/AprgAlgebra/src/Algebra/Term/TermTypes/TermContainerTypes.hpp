#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/AlbaNumber.hpp>

#include <set>
#include <string>

namespace alba
{

namespace algebra
{

using AlbaNumbersSet = std::set<AlbaNumber>;
using VariableNamesSet = std::set<std::string>;
using FunctionsSet = std::set<Function>;

}

}
