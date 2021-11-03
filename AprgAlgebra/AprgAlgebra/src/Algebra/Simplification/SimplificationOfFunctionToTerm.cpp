#include "SimplificationOfFunctionToTerm.hpp"

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

SimplificationOfFunctionToTerm::SimplificationOfFunctionToTerm()
{}

bool SimplificationOfFunctionToTerm::shouldSimplifyTrigonometricFunctionsToSinAndCos()
{
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyTrigonometricFunctionsToSinAndCos;
}

bool SimplificationOfFunctionToTerm::shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel()
{
    return Configuration::getInstance().getConfigurationDetails().shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel;
}

Term SimplificationOfFunctionToTerm::simplifyToTerm(
        Function const& functionObject)
{
    Term result;
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    if(inputTerm.isConstant())
    {
        result = Term(functionObject.performFunctionAndReturnResultIfPossible());
    }
    else if(isTrigonometricFunction(functionObject))
    {
        result = simplifyTrigometricFunctionToExpression(functionObject);
        result.simplify();
    }
    else if(isLogarithmicFunction(functionObject))
    {
        result = simplifyLogarithmicFunctionToExpression(functionObject);
        result.simplify();
    }

    if(result.isEmpty())
    {
        result = Term(functionObject);
    }
    return result;
}

Term SimplificationOfFunctionToTerm::simplifyTrigometricFunctionToExpression(
        Function const& functionObject)
{
    Term result;
    string functionName(functionObject.getFunctionName());
    if(shouldSimplifyTrigonometricFunctionsToSinAndCos())
    {
        Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
        if("tan" == functionName)
        {
            result = Term(createExpressionIfPossible({Term(sin(inputTerm)), Term("/"), Term(cos(inputTerm))}));
        }
        else if("csc" == functionName)
        {
            result = Term(createExpressionIfPossible({Term(1), Term("/"), Term(sin(inputTerm))}));
        }
        else if("sec" == functionName)
        {
            result = Term(createExpressionIfPossible({Term(1), Term("/"), Term(cos(inputTerm))}));
        }
        else if("cot" == functionName)
        {
            result = Term(createExpressionIfPossible({Term(cos(inputTerm)), Term("/"), Term(sin(inputTerm))}));
        }
    }
    return result;
}

Term SimplificationOfFunctionToTerm::simplifyLogarithmicFunctionToExpression(
        Function const& functionObject)
{
    Term result;
    if(!shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel())
    {
        Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
        if(inputTerm.isExpression())
        {
            Expression resultExpression;
            Expression const& inputExpression(inputTerm.getExpressionConstReference());
            if(OperatorLevel::MultiplicationAndDivision == inputExpression.getCommonOperatorLevel())
            {
                TermsWithDetails newTermsWithDetails(inputExpression.getTermsWithAssociation().getTermsWithDetails());
                for(TermWithDetails & newTermWithDetails : newTermsWithDetails)
                {
                    Term & newTerm(getTermReferenceFromSharedPointer(newTermWithDetails.baseTermSharedPointer));
                    newTerm = getLogarithmicOfTermBasedFromName(newTerm, functionObject.getFunctionName());
                }
                resultExpression.set(OperatorLevel::AdditionAndSubtraction, newTermsWithDetails);
            }
            else if(OperatorLevel::RaiseToPower == inputExpression.getCommonOperatorLevel())
            {
                TermRaiseToTerms termRaiseToTerms(inputExpression.getTermsWithAssociation().getTermsWithDetails());
                TermsWithDetails newTermsWithDetails(termRaiseToTerms.getExponents());
                Term logarithmicBase(getLogarithmicOfTermBasedFromName(termRaiseToTerms.getBase(), functionObject.getFunctionName()));
                newTermsWithDetails.emplace_back(getBaseTermConstReferenceFromTerm(logarithmicBase), TermAssociationType::Positive);
                resultExpression.set(OperatorLevel::MultiplicationAndDivision, newTermsWithDetails);
            }
            result = Term(resultExpression);
        }
    }
    return result;
}

Term SimplificationOfFunctionToTerm::getLogarithmicOfTermBasedFromName(
        Term const& term,
        string const& functionName) const
{
    Term result;
    if("ln" == functionName)
    {
        result = Term(ln(term));
    }
    else if("log" == functionName)
    {
        result = Term(log(term));
    }
    return result;
}

}

}

template <>
algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails
getDefaultConfigurationDetails<alba::algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails>()
{
    return algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails
    {false, false};
}

}
