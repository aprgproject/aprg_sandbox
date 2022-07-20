#include "AccumulateOperations.hpp"

#include <BooleanAlgebra/Operations/PerformOperations.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/TermUtilities.hpp>
#include <BooleanAlgebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

void accumulateAndDoOperationOnWrappedTerm(
        Term & combinedTerm,
        OperatorType const operatorType,
        WrappedTerm const& wrappedTerm)
{
    Term const& term(getTermConstReferenceFromSharedPointer(wrappedTerm.baseTermSharedPointer));
    switch(operatorType)
    {
    case OperatorType::And:
    {
        combinedTerm = performAnd(combinedTerm, term);
        break;
    }
    case OperatorType::Or:
    {
        combinedTerm = performOr(combinedTerm, term);
        break;
    }
    default:
        break;
    }
}

void accumulateTermsWithAndOperation(
        Term & combinedTerm,
        WrappedTerms const& termsToCombine)
{
    bool isFirst(willHaveNoEffectOnAndOperation(combinedTerm));
    if(isTheValue(combinedTerm, false))
    {
        combinedTerm = false;
    }
    else
    {
        for(WrappedTerm const& wrappedTerm : termsToCombine)
        {
            Term const& term(getTermConstReferenceFromSharedPointer(wrappedTerm.baseTermSharedPointer));
            if(isTheValue(term, false))
            {
                combinedTerm = false;
                break;
            }
            else if(willHaveNoEffectOnAndOperation(term))
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
                accumulateAndDoOperationOnWrappedTerm(combinedTerm, OperatorType::And, wrappedTerm);
            }
        }
        if(combinedTerm.isEmpty())
        {
            combinedTerm = true;
        }
    }
}

void accumulateTermsWithOrOperation(
        Term & combinedTerm,
        WrappedTerms const& termsToCombine)
{
    bool isFirst(willHaveNoEffectOnOrOperation(combinedTerm));
    if(isTheValue(combinedTerm, true))
    {
        combinedTerm = true;
    }
    else
    {
        for(WrappedTerm const& wrappedTerm : termsToCombine)
        {
            Term const& term(getTermConstReferenceFromSharedPointer(wrappedTerm.baseTermSharedPointer));
            if(isTheValue(term, true))
            {
                combinedTerm = true;
                break;
            }
            else if(willHaveNoEffectOnOrOperation(term))
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
                accumulateAndDoOperationOnWrappedTerm(combinedTerm, OperatorType::Or, wrappedTerm);
            }
        }
        if(combinedTerm.isEmpty())
        {
            combinedTerm = false;
        }
    }
}

}

}
