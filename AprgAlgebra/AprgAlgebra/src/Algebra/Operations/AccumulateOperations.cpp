#include "AccumulateOperations.hpp"

#include <Algebra/Operations/PerformOperations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

void accumulateAndDoOperationOnTermDetails(
        Term & combinedTerm,
        OperatorLevel const operatorLevel,
        TermWithDetails const& termWithDetails)
{
    Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
    switch(operatorLevel)
    {
    case OperatorLevel::AdditionAndSubtraction:
    {
        if(termWithDetails.hasPositiveAssociation())
        {
            combinedTerm = performAddition(combinedTerm, term);
        }
        else if(termWithDetails.hasNegativeAssociation())
        {
            combinedTerm = performSubtraction(combinedTerm, term);
        }
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    {
        if(termWithDetails.hasPositiveAssociation())
        {
            combinedTerm = performMultiplication(combinedTerm, term);
        }
        else if(termWithDetails.hasNegativeAssociation())
        {
            combinedTerm = performDivision(combinedTerm, term);
        }
        break;
    }
    case OperatorLevel::RaiseToPower:
    {
        if(termWithDetails.hasPositiveAssociation())
        {
            combinedTerm = performRaiseToPower(combinedTerm, term);
        }
        break;
    }
    default:
        break;
    }
}

void accumulateTermsForAdditionAndSubtraction(
        Term & combinedTerm,
        TermsWithDetails const& termsToCombine)
{
    bool isFirst(willHaveNoEffectOnAdditionOrSubtraction(combinedTerm));
    for(TermWithDetails const& termWithDetails : termsToCombine)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(willHaveNoEffectOnAdditionOrSubtraction(term))
        {
            continue;
        }
        else if(isFirst)
        {
            if(termWithDetails.hasPositiveAssociation())
            {
                combinedTerm = term;
            }
            else if(termWithDetails.hasNegativeAssociation())
            {
                combinedTerm = -term;
            }
            isFirst=false;
        }
        else
        {
            accumulateAndDoOperationOnTermDetails(combinedTerm, OperatorLevel::AdditionAndSubtraction, termWithDetails);
        }
    }
}

void accumulateTermsForMultiplicationAndDivision(
        Term & combinedTerm,
        TermsWithDetails const& termsToCombine)
{
    bool isFirst(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(combinedTerm));
    if(combinedTerm.isTheValueZero())
    {
        combinedTerm = Term(Constant(0));
    }
    else
    {
        for(TermWithDetails const& termWithDetails : termsToCombine)
        {
            Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
            if(term.isTheValueZero() && termWithDetails.hasPositiveAssociation())
            {
                combinedTerm = Term(Constant(0));
                break;
            }
            if(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
            {
                continue;
            }
            else if(isFirst)
            {
                if(termWithDetails.hasPositiveAssociation())
                {
                    combinedTerm = term;
                }
                else if(termWithDetails.hasNegativeAssociation())
                {
                    combinedTerm = Term(Constant(1))/term;
                }
                isFirst=false;
            }
            else
            {
                accumulateAndDoOperationOnTermDetails(combinedTerm, OperatorLevel::MultiplicationAndDivision, termWithDetails);
            }
        }
    }
}

void accumulateTermsForRaiseToPower(
        Term & combinedTerm,
        TermsWithDetails const& termsToCombine)
{
    bool isFirst(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(combinedTerm));
    for(TermWithDetails const& termWithDetails : termsToCombine)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
        {
            continue;
        }
        else if(isFirst)
        {
            combinedTerm = term;
            isFirst=false;
        }
        else
        {
            accumulateAndDoOperationOnTermDetails(combinedTerm, OperatorLevel::RaiseToPower, termWithDetails);
        }
    }
}

}

}
