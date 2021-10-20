#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>
#include <String/AlbaStringHelper.hpp>
#include <string>

namespace alba
{

namespace algebra
{

namespace Functions
{

bool isFunctionContinuous(Function const& functionObject);
bool isTrigonometricFunction(Function const& functionObject);
bool isLogarithmicFunction(Function const& functionObject);
bool isFunctionNameFoundOnAList(
        Function const& functionObject,
        stringHelper::strings const& names);

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        std::string const& variableName,
        Function const& functionObject);

Term getNaturalLogarithmOfTheAbsoluteValueOfTerm(
        Term const& term);

}

}
}
