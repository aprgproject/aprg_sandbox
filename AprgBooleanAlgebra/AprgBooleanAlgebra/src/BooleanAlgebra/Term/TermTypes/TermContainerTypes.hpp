#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <set>
#include <string>
#include <vector>

namespace alba
{

namespace booleanAlgebra
{

using TermPair = std::pair<Term, Term>;
using VariableNames = std::vector<std::string>;
using VariableNamesSet = std::set<std::string>;
using TermSet = std::set<Term>;

}
}