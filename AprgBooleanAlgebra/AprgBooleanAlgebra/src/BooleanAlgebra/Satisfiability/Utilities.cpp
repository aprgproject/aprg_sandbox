#include "Utilities.hpp"

#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

using SatisfiabilityTerm = VariableTerms;
using SatisfiabilityTerms = std::vector<VariableTerms>;

unsigned int getSatisfiabilityLevel(
        SatisfiabilityTerms const& satTerms)
{
    unsigned int result(0);
    for(SatisfiabilityTerm const& satTerm : satTerms)
    {
        result = max(result, static_cast<unsigned int>(satTerm.size()));
    }
    return result;
}

SatisfiabilityTerms getSatisfiabilityTerms(
        Term const& term)
{
    SatisfiabilityTerms result;
    if(term.isVariableTerm())
    {
        result.emplace_back(SatisfiabilityTerm{term.getVariableTermConstReference()});
    }
    else if(term.isExpression())
    {
        result = getSatisfiabilityTerms(term.getExpressionConstReference());
    }
    return result;
}

SatisfiabilityTerms getSatisfiabilityTerms(
        Expression const& expression)
{
    // The form should be "outer AND expression" with "inner OR expression"
    // example: (x1'|x2|x3')&(x4')&(x5'|x6) ...
    // This is called conjunctive normal form (CNF) or clausal normal form. It is a product of sums or an AND of ORs.
    // Note in the algo that constants are considered invalid
    SatisfiabilityTerms result;
    if(OperatorLevel::And == expression.getCommonOperatorLevel())
    {
        for(WrappedTerm const& subWrappedTerm : expression.getWrappedTerms())
        {
            bool isInvalid(false);
            Term const& termInAnd(getTermConstReferenceFromUniquePointer(subWrappedTerm.baseTermPointer));
            if(termInAnd.isVariableTerm())
            {
                result.emplace_back(SatisfiabilityTerm{termInAnd.getVariableTermConstReference()});            }
            else if(termInAnd.isExpression() && OperatorLevel::Or == termInAnd.getExpressionConstReference().getCommonOperatorLevel())
            {
                SatisfiabilityTerm satisfiabilityTerm;
                for(WrappedTerm const& subSubWrappedTerm : termInAnd.getExpressionConstReference().getWrappedTerms())
                {
                    Term const& termInOr(getTermConstReferenceFromUniquePointer(subSubWrappedTerm.baseTermPointer));
                    if(termInOr.isVariableTerm())
                    {
                        satisfiabilityTerm.emplace_back(termInOr.getVariableTermConstReference());                    }
                    else
                    {
                        isInvalid = true;                        break;
                    }
                }
                result.emplace_back(satisfiabilityTerm);
            }
            else
            {
                isInvalid = true;
            }
            if(isInvalid)
            {
                result.clear();
                break;
            }
        }
    }
    return result;
}

}

}
