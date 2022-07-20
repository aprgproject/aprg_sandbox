#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

bool isNonEmptyOrNonOperatorType(Term const& term);
bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term);

bool getNoEffectValueInOperation(OperatorLevel const operatorLevel);
bool getShortCircuitValueEffectInOperation(OperatorLevel const operatorLevel);

}

}