#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba {

namespace algebra {

bool isTermSimpler(Term const& supposeToBeComplicatedTerm, Term const& supposeToBeSimpleTerm);
bool isNegatedTermSimpler(Term const& term, Term const& negatedTerm);
bool isNonEmptyOrNonOperatorType(Term const& term);
bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term);
bool isARadicalTerm(Term const& term);

unsigned int getNumberOfTerms(Term const& term);

AlbaNumber getConstantFactor(Term const& term);
AlbaNumber getDegree(Term const& term);

AlbaNumberPairs evaluateAndGetInputOutputPair(
    AlbaNumbers const& numbers, std::string const& variableName, Term const& term);

Term getPiAsATerm();
Term getEAsATerm();
Term getPositiveInfinityAsATerm();
Term getNegativeInfinityAsATerm();
Term convertPositiveTermIfNegative(Term const& term);
Term negateTerm(Term const& term);
Term flipTerm(Term const& term);
Term negateTermIfHasNegativeAssociation(TermWithDetails const& termWithDetails);
Term flipTermIfHasNegativeAssociation(TermWithDetails const& termWithDetails);
Term invertTerm(Term const& term, std::string const& variableName);
Expression negateExpression(Expression const& expression);

}  // namespace algebra

}  // namespace alba
