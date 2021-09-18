#include "SimplificationUtilities.hpp"

#include <Algebra/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

bool simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(
        Expression & expression)
{
    bool isChanged(false);
    if(expression.getCommonOperatorLevel() == OperatorLevel::AdditionAndSubtraction)
    {
        isChanged = tryToAddSubtractTermsOverTermsAndReturnIfChanged(expression);
    }
    else
    {
        simplifyTermsWithDetailsInExpressionToACommonDenominator(expression);
    }
    return isChanged;
}

bool tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression & addSubtractExpression)
{
    AdditionAndSubtractionOfTermsOverTerms addSubtractTermsOverTerms;
    bool isAddSubtractExpressionUpdateNeeded(false);
    for(TermWithDetails const& addSubtractTermWithDetails : addSubtractExpression.getTermsWithAssociation().getTermsWithDetails())
    {
        Term const& addSubtractTerm(getTermConstReferenceFromSharedPointer(addSubtractTermWithDetails.baseTermSharedPointer));
        bool isTermAddedOrSubtracted(false);
        if(addSubtractTerm.isExpression())
        {
            Expression const& expression(addSubtractTerm.getExpressionConstReference());
            if(expression.getCommonOperatorLevel() == OperatorLevel::MultiplicationAndDivision)
            {
                TermsWithDetails numerators;
                TermsWithDetails denominators;
                segregateTermsWithPositiveAndNegativeAssociations(expression.getTermsWithAssociation().getTermsWithDetails(), numerators, denominators);
                if(!denominators.empty())
                {
                    isAddSubtractExpressionUpdateNeeded=true;
                }
                addSubtractTermsOverTerms.putAsAddOrSubtraction(TermsOverTerms(numerators, denominators), addSubtractTermWithDetails.association);
                isTermAddedOrSubtracted=true;
            }
        }
        if(!isTermAddedOrSubtracted)
        {
            addSubtractTermsOverTerms.putAsAddOrSubtraction(TermsOverTerms({addSubtractTerm}, {}), addSubtractTermWithDetails.association);
        }
    }
    if(isAddSubtractExpressionUpdateNeeded)
    {
        addSubtractExpression=addSubtractTermsOverTerms.getCombinedExpression();
        addSubtractExpression.simplify();
    }
    return isAddSubtractExpressionUpdateNeeded;
}

void simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression & expression)
{
    bool isChanged(true);
    while(isChanged)
    {
        isChanged=false;
        for(TermWithDetails & termWithDetails : expression.getTermsWithAssociationReference().getTermsWithDetailsReference())
        {
            Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
            if(term.isExpression())
            {
                Expression & subExpression(term.getExpressionReference());
                isChanged = isChanged || simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(subExpression);
            }
        }
        if(isChanged)
        {
            expression.simplify();
        }
    }
}

void simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
        TermsWithDetails & newTermsWithDetails,
        OperatorLevel & mainOperatorLevel,
        TermsWithDetails const& oldTermsWithDetails)
{
    for(TermWithDetails const& oldTermWithDetails : oldTermsWithDetails)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(oldTermWithDetails.baseTermSharedPointer));
        if(term.isExpression())
        {
            Expression subExpression(term.getExpressionConstReference());
            subExpression.simplify();
            TermAssociationType subExpressionAssociation(oldTermWithDetails.association);
            simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
                        newTermsWithDetails, mainOperatorLevel, subExpression, subExpressionAssociation);
        }
        else if(isNonEmptyOrNonOperatorType(term))
        {            Term newTerm(term);
            newTerm.simplify();
            newTermsWithDetails.emplace_back(newTerm, oldTermWithDetails.association);
        }    }
}

void simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
        TermsWithDetails & newTermsWithDetails,
        OperatorLevel & mainOperatorLevel,
        Expression const& subExpression,
        TermAssociationType const subExpressionAssociation)
{
    OperatorLevel subExpressionOperatorLevel(subExpression.getCommonOperatorLevel());
    if(subExpression.containsOnlyOnePositivelyAssociatedTerm()
            || OperatorLevel::Unknown == mainOperatorLevel
            || (subExpressionOperatorLevel == mainOperatorLevel
                && OperatorLevel::AdditionAndSubtraction == mainOperatorLevel
                && OperatorLevel::MultiplicationAndDivision == mainOperatorLevel))
    {
        if(OperatorLevel::Unknown == mainOperatorLevel)
        {
            mainOperatorLevel = subExpression.getCommonOperatorLevel();
        }
        TermsWithAssociation termsWithAssociation(getTermsWithAssociationAndReverseIfNeeded(subExpression, subExpressionAssociation));
        simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(newTermsWithDetails, mainOperatorLevel, termsWithAssociation.getTermsWithDetails());
    }
    else
    {
        newTermsWithDetails.emplace_back(Term(subExpression), subExpressionAssociation);
    }
}

TermsWithAssociation getTermsWithAssociationAndReverseIfNeeded(
        Expression const& expression,
        TermAssociationType const overallAssociation)
{
    TermsWithAssociation termsWithAssociation(expression.getTermsWithAssociation());
    if(TermAssociationType::Negative == overallAssociation)
    {
        termsWithAssociation.reverseTheAssociationOfTheTerms();
    }
    return termsWithAssociation;
}

}

}

}
