#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

using NumberCheckingCondition = std::function<bool(AlbaNumber const& number)>;

bool isValueSatisfyTheCondition(Term const& term, NumberCheckingCondition const& condition);
bool isValueSatisfyTheCondition(Constant const& constant, NumberCheckingCondition const& condition);
bool isValueSatisfyTheCondition(Monomial const& monomial, NumberCheckingCondition const& condition);
bool isValueSatisfyTheCondition(Polynomial const& polynomial, NumberCheckingCondition const& condition);
bool isValueSatisfyTheCondition(Expression const& expression, NumberCheckingCondition const& condition);
bool doAnyNumbersSatisfyTheCondition(Term const& term, NumberCheckingCondition const& condition);
bool doAnyNumbersSatisfyTheCondition(Monomial const& monomial, NumberCheckingCondition const& condition);
bool doAnyNumbersSatisfyTheCondition(Polynomial const& polynomial, NumberCheckingCondition const& condition);
bool doAnyNumbersSatisfyTheCondition(Expression const& expression, NumberCheckingCondition const& condition);
bool doAnyNumbersSatisfyTheCondition(Function const& function, NumberCheckingCondition const& condition);
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
bool isPositiveOrNegativeInfinity(Term const& term);
bool isPositiveOrNegativeInfinity(Constant const& constant);
bool isPositiveOrNegativeInfinity(Monomial const& monomial);
bool isPositiveOrNegativeInfinity(Polynomial const& polynomial);
bool isPositiveOrNegativeInfinity(Expression const& expression);
bool hasNotANumber(Term const& term);
bool hasNotANumber(Monomial const& monomial);
bool hasNotANumber(Polynomial const& polynomial);
bool hasNotANumber(Expression const& expression);
bool hasNotANumber(Function const& function);
bool hasNonFiniteNumbers(Term const& term);
bool hasNonFiniteNumbers(Monomial const& monomial);
bool hasNonFiniteNumbers(Polynomial const& polynomial);
bool hasNonFiniteNumbers(Expression const& expression);
bool hasNonFiniteNumbers(Function const& function);
bool hasZero(Terms const& terms);

bool isPositiveIntegerConstant(Term const& term);
bool isAFiniteConstant(Term const& term);bool hasNegativeExponentsWithVariable(Polynomial const& polynomial, std::string const& variableName);

}
}
