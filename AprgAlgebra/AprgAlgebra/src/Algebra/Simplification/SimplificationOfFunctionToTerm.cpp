#include "SimplificationOfFunctionToTerm.hpp"

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba {

namespace algebra {

namespace Simplification {

SimplificationOfFunctionToTerm::SimplificationOfFunctionToTerm() {}

bool SimplificationOfFunctionToTerm::shouldSimplifyTrigonometricFunctionsToSinAndCos() {
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyTrigonometricFunctionsToSinAndCos;
}

bool SimplificationOfFunctionToTerm::shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel() {
    return Configuration::getInstance()
        .getConfigurationDetails()
        .shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel;
}

Term SimplificationOfFunctionToTerm::simplifyToTerm(Function const& functionObject) {
    Term result;
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
    if (inputTerm.isConstant()) {
        result = Term(functionObject.performFunctionAndReturnResultIfPossible());
    } else if (isTrigonometricFunction(functionObject)) {
        result = simplifyTrigometricFunctionToExpression(functionObject);
        result.simplify();
    } else if (isLogarithmicFunction(functionObject)) {
        result = simplifyLogarithmicFunctionToExpression(functionObject);
        result.simplify();
    }

    if (result.isEmpty()) {
        result = Term(functionObject);
    }
    return result;
}

Term SimplificationOfFunctionToTerm::simplifyTrigometricFunctionToExpression(Function const& functionObject) {
    Term result;
    string functionName(functionObject.getFunctionName());
    if (shouldSimplifyTrigonometricFunctionsToSinAndCos()) {
        Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
        if ("tan" == functionName) {
            result = Term(createExpressionIfPossible({sin(inputTerm), "/", cos(inputTerm)}));
        } else if ("csc" == functionName) {
            result = Term(createExpressionIfPossible({1, "/", sin(inputTerm)}));
        } else if ("sec" == functionName) {
            result = Term(createExpressionIfPossible({1, "/", cos(inputTerm)}));
        } else if ("cot" == functionName) {
            result = Term(createExpressionIfPossible({cos(inputTerm), "/", sin(inputTerm)}));
        }
    }
    return result;
}

Term SimplificationOfFunctionToTerm::simplifyLogarithmicFunctionToExpression(Function const& functionObject) {
    Term result;
    if (!shouldNotSimplifyLogarithmicFunctionsByReducingTheOperatorLevel()) {
        Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTerm()));
        if (inputTerm.isExpression()) {
            Expression resultExpression;
            Expression const& inputExpression(inputTerm.getAsExpression());
            if (OperatorLevel::MultiplicationAndDivision == inputExpression.getCommonOperatorLevel()) {
                TermsWithDetails newTermsWithDetails(inputExpression.getTermsWithAssociation().getTermsWithDetails());
                for (TermWithDetails& newTermWithDetails : newTermsWithDetails) {
                    Term& newTerm(getTermReferenceFromUniquePointer(newTermWithDetails.baseTermPointer));
                    newTerm = getLogarithmicOfTermBasedFromName(newTerm, functionObject.getFunctionName());
                }
                resultExpression.set(OperatorLevel::AdditionAndSubtraction, newTermsWithDetails);
            } else if (OperatorLevel::RaiseToPower == inputExpression.getCommonOperatorLevel()) {
                TermRaiseToTerms termRaiseToTerms(inputExpression.getTermsWithAssociation().getTermsWithDetails());
                TermsWithDetails newTermsWithDetails(termRaiseToTerms.getExponents());
                Term logarithmicBase(
                    getLogarithmicOfTermBasedFromName(termRaiseToTerms.getBase(), functionObject.getFunctionName()));
                newTermsWithDetails.emplace_back(logarithmicBase, TermAssociationType::Positive);
                resultExpression.set(OperatorLevel::MultiplicationAndDivision, newTermsWithDetails);
            }
            result = Term(resultExpression);
        }
    }
    return result;
}

Term SimplificationOfFunctionToTerm::getLogarithmicOfTermBasedFromName(
    Term const& term, string const& functionName) const {
    Term result;
    if ("ln" == functionName) {
        result = ln(term);
    } else if ("log" == functionName) {
        result = log(term);
    }
    return result;
}

}  // namespace Simplification

}  // namespace algebra

template <>
algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails
getDefaultConfigurationDetails<alba::algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails>() {
    return algebra::Simplification::SimplificationOfFunctionToTerm::ConfigurationDetails{false, false};
}

}  // namespace alba
