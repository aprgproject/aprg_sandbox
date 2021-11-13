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
bool doesCoefficientsHaveSameSign(Monomial const& monomial1, Monomial const& monomial2);
bool hasNegativeExponents(Monomial const& monomial);
bool isConstantOnly(Monomial const& monomial);
bool isVariableOnly(Monomial const& monomial);
bool hasASingleVariable(Monomial const& monomial);

std::string getFirstVariableName(Monomial const& monomial);

AlbaNumber getDegree(Monomial const& monomial);
AlbaNumber getMaxExponent(Monomial const& monomial);
AlbaNumber getGcfOfExponentsInMonomial(Monomial const& monomial);
AlbaNumber getGcfOfCoefficientsInMonomials(Monomials const& monomials);
AlbaNumber getLcmOfCoefficientsInMonomials(Monomials const& monomials);
AlbaNumber getCommonSignInMonomials(Monomials const& monomials);

Monomial getGcfMonomialInMonomials(Monomials const& monomials);
Monomial getLcmMonomialInMonomials(Monomials const& monomials);
Monomial compareMonomialsAndSaveMinimumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial);
Monomial compareMonomialsAndSaveMaximumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial);
Monomial getMonomialWithMinimumExponentsInMonomials(Monomials const& monomials);
Monomial getMonomialWithMaximumExponentsInMonomials(Monomials const& monomials);

}

}
