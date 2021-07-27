#pragma once

#include <Algebra/Equation/EquationOperator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

bool isEqual(Term const& leftTerm, Term const& rightTerm);
bool isNotEqual(Term const& leftTerm, Term const& rightTerm);
bool isLessThan(Term const& leftTerm, Term const& rightTerm);
bool isGreaterThan(Term const& leftTerm, Term const& rightTerm);
bool isLessThanOrEqual(Term const& leftTerm, Term const& rightTerm);
bool isGreaterThanOrEqual(Term const& leftTerm, Term const& rightTerm);
bool isEquationOperationSatisfied(
        EquationOperator const& operatorObject,
        Term const& leftTerm,
        Term const& rightTerm);

}

}
