#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>
#include <BooleanAlgebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba
{

namespace booleanAlgebra
{

bool isNonEmptyOrNonOperatorType(Term const& term);
bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term);

bool getNoEffectValueInOperation(OperatorLevel const operatorLevel);
bool getShortCircuitValueEffectInOperation(OperatorLevel const operatorLevel);

VariableNamesSet getVariableNames(Term const& term);

Term getTermFromVariableAndPrimeValue(std::string const& variableName, char const primeValue);

}

}
