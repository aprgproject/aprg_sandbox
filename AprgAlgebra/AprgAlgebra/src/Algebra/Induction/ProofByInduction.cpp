#include "ProofByInduction.hpp"

#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba {

namespace algebra {

ProofByInduction::ProofByInduction(
    std::string const& variableName, Term const& expressionForEachStep, Operator const& accumulateOperator,
    Term const& guessExpression, ManualCalculationFunction const& manualCalculation)
    : m_variableName(variableName),
      m_expressionForEachStep(expressionForEachStep),
      m_accumulateOperator(accumulateOperator),
      m_guessExpression(guessExpression),
      m_manualCalculation(manualCalculation) {}

bool ProofByInduction::isCorrectOnASpecificValue(AlbaNumber const& value) const {
    AlbaNumber valueFromManual(m_manualCalculation(value));
    AlbaNumber valueFromGuess;
    SubstitutionOfVariablesToValues substitution{{m_variableName, value}};
    Term guessTerm(substitution.performSubstitutionTo(m_guessExpression));
    if (guessTerm.isConstant()) {
        valueFromGuess = guessTerm.getConstantValueConstReference();
    }
    return valueFromManual == valueFromGuess;
}

bool ProofByInduction::isCorrectOnInductionStep() const {
    SubstitutionOfVariablesToTerms substitutionForNextStep{
        {m_variableName, Polynomial{Monomial(1, {{m_variableName, 1}}), Monomial(1, {})}}};
    Term expectedDelta = substitutionForNextStep.performSubstitutionTo(m_expressionForEachStep);
    expectedDelta.simplify();

    Term initialValue(Monomial(1, {{m_variableName, 1}}));
    Term nextValue(Polynomial{Monomial(1, {{m_variableName, 1}}), Monomial(1, {})});
    SubstitutionOfVariablesToTerms substitutionOfInitialValue{{m_variableName, initialValue}};
    SubstitutionOfVariablesToTerms substitutionOfNextValue{{m_variableName, nextValue}};
    Term deltaFromGuess(createExpressionIfPossible(
        {substitutionOfNextValue.performSubstitutionTo(m_guessExpression), reverse(m_accumulateOperator),
         substitutionOfInitialValue.performSubstitutionTo(m_guessExpression)}));
    deltaFromGuess.simplify();

    return expectedDelta == deltaFromGuess;
}

}  // namespace algebra

}  // namespace alba
