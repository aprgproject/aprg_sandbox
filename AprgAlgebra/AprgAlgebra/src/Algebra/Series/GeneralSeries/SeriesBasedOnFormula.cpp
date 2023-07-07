#include "SeriesBasedOnFormula.hpp"

#include <Algebra/Differentiation/DifferentiationForFiniteCalculus.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Mutation/SignMutator.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <algorithm>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Simplification;
using namespace std;

namespace alba {

namespace algebra {

SeriesBasedOnFormula::SeriesBasedOnFormula(Term const& formulaForSeries, string const& variableName)
    : m_formulaForSeries(formulaForSeries), m_variableName(variableName) {}

bool SeriesBasedOnFormula::isConvergent() const { return isARealFiniteConstant(getValueAtInfinity()); }
bool SeriesBasedOnFormula::isIncreasing() const {
    Term sign(getSignDerivativeForFiniteCalculus());
    return isTheValue(sign, 1);}

bool SeriesBasedOnFormula::isDecreasing() const {
    Term sign(getSignDerivativeForFiniteCalculus());
    return isTheValue(sign, -1);
}

bool SeriesBasedOnFormula::isMonotonic() const {
    Term sign(getSignDerivativeForFiniteCalculus());
    return isTheValue(sign, 1) || isTheValue(sign, -1);
}

bool SeriesBasedOnFormula::isBounded() const {
    AlbaNumberOptional greatestLowerBound(getGreatestLowerBound());
    AlbaNumberOptional leastUpperBound(getLeastUpperBound());
    return greatestLowerBound && leastUpperBound;
}

Term SeriesBasedOnFormula::getFormulaForSeries() const { return m_formulaForSeries; }

Term SeriesBasedOnFormula::getValueAtIndex(int const index) const {
    SubstitutionOfVariablesToValues substitution{{m_variableName, index}};
    return substitution.performSubstitutionTo(m_formulaForSeries);
}

Term SeriesBasedOnFormula::getSum(int const startingIndex, int const endingIndex) const {
    Summation summation(m_formulaForSeries, m_variableName);
    return summation.getSum(startingIndex, endingIndex);
}

Term SeriesBasedOnFormula::getSumStartingAtIndexAndToInfinity(int const startingIndex) const {
    Summation summation(m_formulaForSeries, m_variableName);
    return summation.getSum(startingIndex, ALBA_NUMBER_POSITIVE_INFINITY);
}

Term SeriesBasedOnFormula::getValueAtInfinity() const {
    return getLimit(m_formulaForSeries, m_variableName, ALBA_NUMBER_POSITIVE_INFINITY);
}

Term SeriesBasedOnFormula::getRemainderAtIndex(int const index) const {    return getValueAtInfinity() - getValueAtIndex(index);
}

AlbaNumberOptional SeriesBasedOnFormula::getGreatestLowerBound() const {    AlbaNumberOptional result;
    AlbaNumbers boundValues(getBoundValues());

    if (boundValues.size() >= 2) {
        auto it = min_element(boundValues.cbegin(), boundValues.cend());
        if (it != boundValues.cend()) {
            result = *it;
        }
    } else if (boundValues.size() == 1) {
        if (isIncreasing()) {
            result = boundValues.back();
        }
    }
    return result;
}

AlbaNumberOptional SeriesBasedOnFormula::getLeastUpperBound() const {
    AlbaNumberOptional result;
    AlbaNumbers boundValues(getBoundValues());
    if (boundValues.size() >= 2) {
        auto it = max_element(boundValues.cbegin(), boundValues.cend());
        if (it != boundValues.cend()) {
            result = *it;
        }
    } else if (boundValues.size() == 1) {
        if (isDecreasing()) {
            result = boundValues.back();
        }
    }
    return result;
}

AlbaNumbers SeriesBasedOnFormula::getBoundValues() const {
    DifferentiationForFiniteCalculus differentiation(m_variableName);
    Term secondDerivative(differentiation.differentiateMultipleTimes(m_formulaForSeries, 2));

    AlbaNumbers boundValues;
    AlbaNumbers extremaIndexes(getExtremaIndexes());
    extremaIndexes.emplace_back(AlbaNumber(0));
    for (AlbaNumber const& extremumIndex : extremaIndexes) {
        SubstitutionOfVariablesToValues substitution{{m_variableName, extremumIndex}};
        Term secondDerivativeAtExtrema(substitution.performSubstitutionTo(secondDerivative));
        if (secondDerivativeAtExtrema.isConstant()) {
            boundValues.emplace_back(secondDerivativeAtExtrema.getConstantValueConstReference());        }
    }
    Term valueTermAtInfinity(getValueAtInfinity());
    if (isARealFiniteConstant(valueTermAtInfinity)) {        boundValues.emplace_back(valueTermAtInfinity.getConstantValueConstReference());
    }
    return boundValues;
}

AlbaNumbers SeriesBasedOnFormula::getExtremaIndexes() const {
    DifferentiationForFiniteCalculus differentiation(m_variableName);
    Term firstDerivative(differentiation.differentiate(m_formulaForSeries));
    OneEquationOneVariableEqualitySolver solver;
    simplifyTermToACommonDenominator(firstDerivative);    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(firstDerivative, "=", 0)));
    return solutionSet.getAcceptedValues();
}

Term SeriesBasedOnFormula::getSignDerivativeForFiniteCalculus() const {
    DifferentiationForFiniteCalculus differentiation(m_variableName);
    Term derivative(differentiation.differentiate(m_formulaForSeries));
    SignMutator signMutator;
    signMutator.putVariableWithSign(m_variableName, TermAssociationType::Positive);
    signMutator.mutateTerm(derivative);
    return derivative;
}

string SeriesBasedOnFormula::getNameForVariableInFormula() const { return m_variableName; }

}  // namespace algebra
}  // namespace alba