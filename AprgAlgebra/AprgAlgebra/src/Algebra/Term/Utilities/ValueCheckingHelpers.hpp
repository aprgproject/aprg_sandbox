#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term);
bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term);
bool isTheValue(Term const& term, AlbaNumber const& number);
bool isTheValue(Constant const& constant, AlbaNumber const& number);
bool isTheValue(Monomial const& monomial, AlbaNumber const& number);
bool isTheValue(Polynomial const& polynomial, AlbaNumber const& number);
bool isTheValue(Expression const& expression, AlbaNumber const& number);
bool isNotANumber(Term const& term);
bool isNotANumber(Constant const& constant);
bool isNotANumber(Monomial const& monomial);
bool isNotANumber(Polynomial const& polynomial);
bool isNotANumber(Expression const& expression);
bool hasNotANumber(Term const& term);
bool hasNotANumber(Monomial const& monomial);
bool hasNotANumber(Polynomial const& polynomial);
bool hasNotANumber(Expression const& expression);
bool hasNotANumber(Function const& function);
bool hasNumbersNotFinite(Term const& term);
bool hasNumbersNotFinite(Monomial const& monomial);
bool hasNumbersNotFinite(Polynomial const& polynomial);
bool hasNumbersNotFinite(Expression const& expression);
bool hasNumbersNotFinite(Function const& function);
bool isAFiniteConstant(Term const& term);

}

}
