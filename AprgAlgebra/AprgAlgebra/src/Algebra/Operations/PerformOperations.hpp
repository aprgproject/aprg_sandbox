#pragma once

#include <Algebra/Term/TermTypes/Operator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermsWithAssociation.hpp>

namespace alba
{

namespace algebra
{

Term performOperation(
        Operator const& operatorTerm,
        Term const& term);
Term performOperation(
        Operator const& operatorTerm,
        Term const& term1,
        Term const& term2);
Term performUnaryPlus(Term const& term);
Term performUnaryMinus(Term const& term);
Term performAddition(Term const& term1, Term const& term2);
Term performSubtraction(Term const& term1, Term const& term2);
Term performMultiplication(Term const& term1, Term const& term2);
Term performDivision(Term const& term1, Term const& term2);
Term performRaiseToPower(Term const& term1, Term const& term2);

}

}
