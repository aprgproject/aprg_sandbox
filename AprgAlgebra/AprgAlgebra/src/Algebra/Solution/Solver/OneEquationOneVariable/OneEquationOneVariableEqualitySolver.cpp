#include "OneEquationOneVariableEqualitySolver.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Solution/SolutionUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace algebra {

namespace {
constexpr int NUMBER_OF_ITERATIONS_IN_NEWTON_METHOD = 1000;
constexpr double DIFFERENCE_TOLERANCE_FOR_ACCEPTED_VALUE = 1E-11;
}  // namespace

OneEquationOneVariableEqualitySolver::OneEquationOneVariableEqualitySolver() : BaseOneEquationOneVariableSolver() {}

void OneEquationOneVariableEqualitySolver::calculateSolution(SolutionSet& solutionSet, Equation const& equation) {
    if (equation.getEquationOperator().isEqual()) {
        Equation simplifiedEquation(equation);
        simplifiedEquation.simplify();
        if (simplifiedEquation.isEquationSatisfied()) {
            processWhenEquationIsAlwaysSatisfied(solutionSet);
        } else {
            calculateWhenEquationIsSometimesSatisfied(solutionSet, simplifiedEquation);
        }
    }
}

void OneEquationOneVariableEqualitySolver::calculateForEquation(SolutionSet& solutionSet, Equation const& equation) {
    Term const& nonZeroLeftHandTerm(equation.getLeftHandTerm());
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromTerm(nonZeroLeftHandTerm);
    VariableNamesSet const& variableNames(variableNamesRetriever.getSavedData());
    if (variableNames.size() == 1) {
        string variableName = *variableNames.cbegin();
        calculateForTermAndCheckAbsoluteValueFunctions(nonZeroLeftHandTerm, variableName);
        sortAndRemoveDuplicateCalculatedValues();
        addValuesToSolutionSetIfNeeded(solutionSet, nonZeroLeftHandTerm, variableName);
    }
}

void OneEquationOneVariableEqualitySolver::calculateForTermAndVariable(Term const& term, string const& variableName) {
    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(term));
    if (popOptional) {
        PolynomialOverPolynomial const& pop(popOptional.value());
        AlbaNumbers numeratorRoots(getRoots(RootType::RealAndImaginaryRoots, pop.getNumerator()));
        AlbaNumbers denominatorRoots(getRoots(RootType::RealAndImaginaryRoots, pop.getDenominator()));
        m_calculatedValues.reserve(numeratorRoots.size() + denominatorRoots.size());
        copy(numeratorRoots.cbegin(), numeratorRoots.cend(), back_inserter(m_calculatedValues));
        copy(denominatorRoots.cbegin(), denominatorRoots.cend(), back_inserter(m_calculatedValues));
        setAsCompleteSolution();
    } else {
        TermsOverTerms termsOverTerms(createTermsOverTermsFromTerm(term));
        if (!termsOverTerms.getDenominators().empty()) {
            performNewtonMethodToFindSolution(termsOverTerms.getCombinedNumerator(), variableName);
            performNewtonMethodToFindSolution(termsOverTerms.getCombinedDenominator(), variableName);
        } else {
            performNewtonMethodToFindSolution(term, variableName);
        }
    }
}

void OneEquationOneVariableEqualitySolver::addValuesToSolutionSetIfNeeded(
    SolutionSet& solutionSet, Term const& term, string const& variableName) {
    if (!m_calculatedValues.empty()) {
        SubstitutionOfVariablesToValues substitution;
        for (AlbaNumber const& value : m_calculatedValues) {
            substitution.putVariableWithValue(variableName, value);
            Term substitutedResult(substitution.performSubstitutionTo(term));
            if (substitutedResult.isConstant()) {
                AlbaNumber const& computedValue(substitutedResult.getConstantValueConstReference());
                if (!computedValue.isAFiniteValue()) {
                    solutionSet.addRejectedValue(value);
                } else if (isAlmostEqual(computedValue.getDouble(), 0.0, DIFFERENCE_TOLERANCE_FOR_ACCEPTED_VALUE)) {
                    solutionSet.addAcceptedValue(value);
                }
            }
        }
    }
}

void OneEquationOneVariableEqualitySolver::performNewtonMethodToFindSolution(
    Term const& termToCheck, string const& variableNameForSubstitution) {
    NewtonMethod::Function functionToIterate(getFunctionToIterate(termToCheck, variableNameForSubstitution));
    AlbaNumbers initialValues(getInitialValuesForIteratingMethods(termToCheck));
    for (AlbaNumber const& initialValue : initialValues) {
        NewtonMethod newtonMethod(initialValue, functionToIterate);
        newtonMethod.runMaxNumberOfIterationsOrUntilFinished(NUMBER_OF_ITERATIONS_IN_NEWTON_METHOD);
        if (newtonMethod.isSolved()) {
            m_calculatedValues.emplace_back(newtonMethod.getCurrentValue());
            setAsIncompleteSolution();
            break;
        }
    }
}

NewtonMethod::Function OneEquationOneVariableEqualitySolver::getFunctionToIterate(
    Term const& termToCheck, string const& variableNameForSubstitution) {
    NewtonMethod::Function result = [&](AlbaNumber const& value) {
        SubstitutionOfVariablesToValues substitution;
        substitution.putVariableWithValue(variableNameForSubstitution, value);
        Term substitutedTerm(substitution.performSubstitutionTo(termToCheck));
        AlbaNumber computedValue;
        if (substitutedTerm.isConstant()) {
            computedValue = substitutedTerm.getConstantValueConstReference();
        }
        return computedValue;
    };
    return result;
}

AlbaNumber OneEquationOneVariableEqualitySolver::getMoreAccurateValueFromNewtonMethod(
    Term const& termToCheck, string const& variableNameForSubstitution, AlbaNumber const& value) {
    AlbaNumber result(value);
    NewtonMethod::Function functionToIterate(getFunctionToIterate(termToCheck, variableNameForSubstitution));
    NewtonMethod newtonMethod(value, functionToIterate);
    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(NUMBER_OF_ITERATIONS_IN_NEWTON_METHOD);
    if (newtonMethod.isSolved()) {
        result = newtonMethod.getCurrentValue();
    }
    return result;
}

}  // namespace algebra

}  // namespace alba
