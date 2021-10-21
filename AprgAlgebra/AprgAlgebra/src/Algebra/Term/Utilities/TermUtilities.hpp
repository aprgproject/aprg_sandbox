#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{

bool isTermSimpler(Term const& supposeToBeComplicatedTerm, Term const& supposeToBeSimpleTerm);
bool isNegatedTermSimpler(Term const& term, Term const& negatedTerm);
bool isNonEmptyOrNonOperatorType(Term const& term);
bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term);
bool isARadicalTerm(Term const& term);

bool isANegativeTerm(Term const& term);
bool isANegativeConstant(Constant const& constant);
bool isANegativeMonomial(Monomial const& monomial);
bool isANegativePolynomial(Polynomial const& polynomial);
bool isANegativeExpression(Expression const& expression);

AlbaNumber getConstantFactor(Term const& term);

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        std::string const& variableName,
        Term const& term);

Term getPiAsTerm();
Term getEAsTerm();
Term convertPositiveTermIfNegative(Term const& term);
Term negateTerm(Term const& term);
Term invertTerm(Term const& term, std::string const& variableName);
Expression negateExpression(Expression const& expression);

}

}
