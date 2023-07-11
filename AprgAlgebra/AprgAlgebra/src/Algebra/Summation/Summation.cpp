#include "Summation.hpp"

#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba {

namespace algebra {

Summation::Summation(Term const& termToSum, string const& variableName)
    : m_termToSum(termToSum), m_variableName(variableName), m_summationModel(getSummationModel()) {}

Term Summation::getSummationModelWithKnownConstant(AlbaNumber const& startNumber) const {
    SubstitutionOfVariablesToValues substitution({{m_variableName, startNumber}});
    Term firstTerm(substitution.performSubstitutionTo(m_termToSum));
    substitution.putVariableWithValue(m_variableName, startNumber);
    Term summationValueFromModel(substitution.performSubstitutionTo(m_summationModel));
    Term difference = firstTerm - summationValueFromModel;
    Term result(m_summationModel + difference);
    return result;
}

Term Summation::getSummationModelWithUnknownConstant() const { return m_summationModel + Term(C); }

Term Summation::getSum(Term const& start, Term const& end) const {
    Term result;
    bool isStartAFiniteConstant = start.isConstant() && start.getAsNumber().isAFiniteValue();
    bool isEndAFiniteConstant = end.isConstant() && end.getAsNumber().isAFiniteValue();
    if (isStartAFiniteConstant && isEndAFiniteConstant) {
        calculateSumFromANumberToANumber(
            result, start.getAsNumber(), end.getAsNumber());
    } else if (isStartAFiniteConstant) {
        calculateSumStartingFromANumber(result, start.getAsNumber(), end);
    } else {
        result = ALBA_NUMBER_NOT_A_NUMBER;
    }
    return result;
}

void Summation::calculateSumFromANumberToANumber(
    Term& result, AlbaNumber const& startNumber, AlbaNumber const& endNumber) const {
    if (startNumber.isIntegerType() && endNumber.isIntegerType() && startNumber <= endNumber) {
        if (isNan(m_summationModel)) {
            calculateSumUsingEachTerm(result, startNumber, endNumber);
        } else {
            calculateSumUsingModel(result, startNumber, endNumber);
        }
    } else {
        result = ALBA_NUMBER_NOT_A_NUMBER;
    }
}

void Summation::calculateSumStartingFromANumber(Term& result, AlbaNumber const& startNumber, Term const& end) const {
    if (startNumber.isIntegerType()) {
        Term summationModelWithConstant(getSummationModelWithKnownConstant(startNumber));

        if (end.isConstant() && end.getAsNumber().isPositiveInfinity()) {
            result = getLimit(summationModelWithConstant, m_variableName, ALBA_NUMBER_POSITIVE_INFINITY);
        } else {
            SubstitutionOfVariablesToTerms substitution({{m_variableName, end}});
            result = substitution.performSubstitutionTo(summationModelWithConstant);
        }
    } else {
        result = ALBA_NUMBER_NOT_A_NUMBER;
    }
}

void Summation::calculateSumUsingEachTerm(
    Term& result, AlbaNumber const& startNumber, AlbaNumber const& endNumber) const {
    long long start(startNumber.getInteger());
    long long end(endNumber.getInteger());
    Term sum;
    if (start <= end) {
        SubstitutionOfVariablesToValues substitution;
        substitution.putVariableWithValue(m_variableName, start);
        sum = substitution.performSubstitutionTo(m_termToSum);
        for (long long value = start + 1; value <= end; value++) {
            substitution.putVariableWithValue(m_variableName, value);
            sum += substitution.performSubstitutionTo(m_termToSum);
        }
    }
    result = sum;
}

void Summation::calculateSumUsingModel(Term& result, AlbaNumber const& startNumber, AlbaNumber const& endNumber) const {
    Term summationModelWithConstant(getSummationModelWithKnownConstant(startNumber));
    SubstitutionOfVariablesToValues substitution({{m_variableName, endNumber}});
    result = substitution.performSubstitutionTo(summationModelWithConstant);
}

Term Summation::getSummationModel() const {
    IntegrationForFiniteCalculus integration(m_variableName);
    // Put plus one because finite calculus terms are summation up to n-1.
    Term variablePlusOne(Polynomial{Monomial(1, {{m_variableName, 1}}), Monomial(1, {})});
    SubstitutionOfVariablesToTerms substitution({{m_variableName, variablePlusOne}});
    return substitution.performSubstitutionTo(integration.integrate(m_termToSum));
}

}  // namespace algebra

}  // namespace alba
