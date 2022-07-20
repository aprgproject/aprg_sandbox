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
using VariableTermNames = std::vector<std::string>;
using VariableTermNamesSet = std::set<std::string>;
using TermSet = std::set<Term>;

}

}
