#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

#include <functional>
#include <map>

namespace alba
{

namespace algebra
{

using FunctionCondition = std::function<bool(Function const&)>;
using VariableToValueMap = std::map<std::string, AlbaNumber>;

AlbaNumber getCoefficientOfMonomialWithNoVariables(
        Polynomial const& polynomial);
AlbaNumber getCoefficientOfMonomialWithVariableOnly(
        Polynomial const& polynomial,
        std::string const& variableName);
VariableToValueMap getCoefficientsForVariablesOnly(
        Polynomial const& polynomial);

}

}
