#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace alba {

namespace algebra {

using TermPair = std::pair<Term, Term>;
using VariableNames = std::vector<std::string>;
using VariableNamesSet = std::set<std::string>;
using FunctionsSet = std::set<Function>;
using TermSet = std::set<Term>;

}  // namespace algebra

}  // namespace alba
