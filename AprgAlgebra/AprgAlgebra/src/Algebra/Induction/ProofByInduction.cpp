#include "ProofByInduction.hpp"

#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

ProofByInduction::ProofByInduction(
        string const& variableNameInExpression,
        Term const& algebraicExpressionToCheck,
        ProofByInduction::FunctionToCheck const& functionToCheck)
    : m_variableNameInExpression(variableNameInExpression)
    , m_algebraicExpressionToCheck(algebraicExpressionToCheck)
    , m_functionToCheck(functionToCheck)
{}

bool ProofByInduction::isVerificationOnASpecificValueSuccessful(
        AlbaNumber const& value) const
{
    AlbaNumber valueFromFunction(m_functionToCheck(value));
    AlbaNumber valueFromExpression;
    SubstitutionOfVariablesToValues substitution{{m_variableNameInExpression, value}};
    Term termFromExpression(substitution.performSubstitutionTo(m_algebraicExpressionToCheck));
    if(termFromExpression.isConstant())
    {
        valueFromExpression=termFromExpression.getConstantValueConstReference();
    }
    return valueFromFunction==valueFromExpression;
}

bool ProofByInduction::isVerificationOnInductionStepSuccessful(
        Term const& firstTerm,
        Term const& secondTerm,
        Term const& expectedDifferenceOfSecondAndFirstTerm) const
{
    SubstitutionOfVariablesToTerms substitutionOfFirstTerm{{m_variableNameInExpression, firstTerm}};
    SubstitutionOfVariablesToTerms substitutionOfSecondTerm{{m_variableNameInExpression, secondTerm}};
    Term termFromExpression(
                substitutionOfSecondTerm.performSubstitutionTo(m_algebraicExpressionToCheck) -
                substitutionOfFirstTerm.performSubstitutionTo(m_algebraicExpressionToCheck));
    termFromExpression.simplify();
    return expectedDifferenceOfSecondAndFirstTerm==termFromExpression;
}

}

}
