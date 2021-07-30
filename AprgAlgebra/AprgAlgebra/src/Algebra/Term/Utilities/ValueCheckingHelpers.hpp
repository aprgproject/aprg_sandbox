#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term);
bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term);
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
bool isAFiniteConstant(Term const& term);

}
}