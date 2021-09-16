#include "SimplificationUtilities.hpp"

#include <Algebra/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>


using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

bool simplifyToACommonDenominatorForExpressionAndReturnIfChanged(Expression & expression)
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
                isChanged = isChanged || simplifyToACommonDenominatorForExpressionAndReturnIfChanged(subExpression);
            }
        }
        if(isChanged)
        {
            expression.simplify();
        }
    }
}

}

}

}
