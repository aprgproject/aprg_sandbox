#pragma once

#include <Equation/Term/Term.hpp>
#include <Equation/Term/TermsWithAssociation.hpp>

namespace alba
{
namespace equation
{

Term getResultOfAddingAndSubtractingOfTermsWithExpressions(
        TermsWithAssociation::TermsWithDetails const& termsWithExpressions);
bool mergeForAdditionAndSubtractionAndReturnIfMerged(
        TermsWithAssociation::TermWithDetails & termExpressionWithDetails1,
        TermsWithAssociation::TermWithDetails & termExpressionWithDetails2);
void retrieveUniqueExpressionsAndMergeTerms(
        Expression & uniqueExpression1,
        Expression & uniqueExpression2,
        Term & mergeTerm1,
        Term & mergeTerm2,
        TermsWithAssociation::TermWithDetails const& termExpressionWithDetails1,
        TermsWithAssociation::TermWithDetails const& termExpressionWithDetails2);
Expression getUniqueExpressionForAdditionOrSubtractionMergeChecking(Expression const& expression);
void accumulateMergeTermForAdditionOrSubtractionMergeChecking(Term & combinedTerm, Expression const& expression);
bool canBeMergedForAdditionAndSubtraction(
        Expression const& uniqueExpression1,
        Expression const& uniqueExpression2,
        Term const& mergeTerm1,
        Term const& mergeTerm2);

}

}
