#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <set>
#include <string>
#include <utility>

namespace alba
{

namespace algebra
{

using TermPair = std::pair<Term, Term>;
using VariableNamesSet = std::set<std::string>;
using FunctionsSet = std::set<Function>;
using TermSet = std::set<Term>;

}

}
