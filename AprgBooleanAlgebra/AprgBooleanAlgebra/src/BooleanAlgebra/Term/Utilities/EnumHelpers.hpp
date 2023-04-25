#pragma once

#include <BooleanAlgebra/Term/TermTypes/OperatorLevel.hpp>
#include <BooleanAlgebra/Term/TermTypes/OperatorType.hpp>
#include <BooleanAlgebra/Term/TermTypes/TermType.hpp>

#include <string>

namespace alba {

namespace booleanAlgebra {

unsigned int getOperatorTypeInversePriority(OperatorType const operatorType);
unsigned int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
unsigned int getTermTypePriorityValue(TermType const termType);

OperatorLevel getDualOperatorLevel(OperatorLevel const operatorLevel);

std::string getEnumShortString(TermType const termType);
std::string getEnumShortString(OperatorType const operatorType);
std::string getEnumShortString(OperatorLevel const operatorLevel);

}  // namespace booleanAlgebra

}  // namespace alba
