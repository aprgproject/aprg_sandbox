#include "AccumulateOperations.hpp"

#include <BooleanAlgebra/Operations/PerformOperations.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;
namespace alba
{

namespace booleanAlgebra
{

void accumulateTerms(
        Term & combinedTerm,
        Terms const& termsToCombine,
        OperatorLevel const operatorLevel)
{
    if(OperatorLevel::And == operatorLevel)
    {
        accumulateTermsWithAndOperation(combinedTerm, termsToCombine);
    }
    else if(OperatorLevel::Or == operatorLevel)
    {
        accumulateTermsWithOrOperation(combinedTerm, termsToCombine);
    }
}

void accumulateTermsWithAndOperation(
        Term & combinedTerm,
        Terms const& termsToCombine)
{
    bool isFirst(willHaveNoEffectOnAndOperation(combinedTerm));
    if(isTheValue(combinedTerm, false))    {
        combinedTerm = false;
    }
    else
    {
        for(Term const& term : termsToCombine)
        {
            if(isTheValue(term, false))
            {
                combinedTerm = false;                break;
            }
            else if(willHaveNoEffectOnAndOperation(term))
            {                continue;
            }
            else if(isFirst)
            {
                combinedTerm = term;
                isFirst=false;
            }
            else
            {
                combinedTerm = performAnd(combinedTerm, term);
            }
        }
        if(combinedTerm.isEmpty())        {
            combinedTerm = true;
        }
    }}

void accumulateTermsWithOrOperation(
        Term & combinedTerm,
        Terms const& termsToCombine)
{
    bool isFirst(willHaveNoEffectOnOrOperation(combinedTerm));
    if(isTheValue(combinedTerm, true))    {
        combinedTerm = true;
    }
    else
    {
        for(Term const& term : termsToCombine)
        {
            if(isTheValue(term, true))
            {
                combinedTerm = true;                break;
            }
            else if(willHaveNoEffectOnOrOperation(term))
            {                continue;
            }
            else if(isFirst)
            {
                combinedTerm = term;
                isFirst=false;
            }
            else
            {
                combinedTerm = performOr(combinedTerm, term);
            }
        }
        if(combinedTerm.isEmpty())        {
            combinedTerm = false;
        }
    }}

}

}
