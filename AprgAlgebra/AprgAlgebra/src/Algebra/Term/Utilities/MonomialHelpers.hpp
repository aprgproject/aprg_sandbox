#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

bool canBeMergedInAMonomialByAdditionOrSubtraction(Term const& term1, Term const& term2);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial1, Monomial const& monomial2);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial, Variable const& variable);
bool canBeMergedInAMonomialByAdditionOrSubtraction(Variable const& variable1, Variable const& variable2);
bool hasNegativeExponents(Monomial const& monomial);

AlbaNumber getGcfCoefficientInMonomials(Monomials const& monomials);
AlbaNumber getLcmCoefficientInMonomials(Monomials const& monomials);AlbaNumber getCommonSignInMonomials(Monomials const& monomials);
Monomial getGcfMonomialInMonomials(Monomials const& monomials);
Monomial getLcmMonomialInMonomials(Monomials const& monomials);
Monomial compareMonomialsAndSaveMinimumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial);Monomial compareMonomialsAndSaveMaximumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial);
Monomial getMonomialWithMinimumExponentsInMonomials(Monomials const& monomials);
Monomial getMonomialWithMaximumExponentsInMonomials(Monomials const& monomials);

}

}
