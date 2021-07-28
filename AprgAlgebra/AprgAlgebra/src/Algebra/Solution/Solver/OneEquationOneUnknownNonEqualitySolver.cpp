#include "OneEquationOneUnknownNonEqualitySolver.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Solution/SolutionUtilities.hpp>
#include <Algebra/Solution/Solver/NewtonMethod.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <algorithm>

using namespace std;

namespace alba{

namespace algebra
{

OneEquationOneUnknownNonEqualitySolver::OneEquationOneUnknownNonEqualitySolver(Equation const& equation)
    : m_isSolved(false)
    , m_isACompleteSolution(false)
    , m_equation(equation)
{}

bool OneEquationOneUnknownNonEqualitySolver::isSolved() const
{
    return m_isSolved;
}

bool OneEquationOneUnknownNonEqualitySolver::isACompleteSolution() const
{
    return m_isACompleteSolution;
}

SolutionSet OneEquationOneUnknownNonEqualitySolver::calculateSolutionAndReturnSolutionSet()
{
    SolutionSet result;    if(!m_equation.getEquationOperator().isEqual())
    {
        m_equation.simplify();
        if(m_equation.isEquationSatisfied())
        {
            processWhenEquationIsAlwaysSatisfied(result);
        }
        else
        {            calculateWhenEquationIsSometimesSatisfied(result);
        }
    }
    return result;
}

void OneEquationOneUnknownNonEqualitySolver::setAsCompleteSolution()
{
    m_isSolved = true;
    m_isACompleteSolution = true;
}

void OneEquationOneUnknownNonEqualitySolver::setAsIncompleteSolution()
{
    m_isSolved = true;
    m_isACompleteSolution = false;
}

void OneEquationOneUnknownNonEqualitySolver::processWhenEquationIsAlwaysSatisfied(SolutionSet & result)
{
    result.addAcceptedInterval(createAllRealValuesInterval());
    setAsCompleteSolution();
}

void OneEquationOneUnknownNonEqualitySolver::calculateWhenEquationIsSometimesSatisfied(SolutionSet & result)
{
    SubstitutionOfVariablesToValues substitution;
    Term const& nonZeroLeftHandTerm(m_equation.getLeftHandTerm());
    VariableNamesSet variableNames(getVariableNames(nonZeroLeftHandTerm));
    if(variableNames.size() == 1)    {
        string variableName = *variableNames.cbegin();
        PolynomialOverPolynomialOptional popOptional(
                    createPolynomialOverPolynomialFromTermIfPossible(nonZeroLeftHandTerm));
        if(popOptional.hasContent())
        {
            PolynomialOverPolynomial const& pop(popOptional.getConstReference());
            AlbaNumbers valuesToCheck(getValuesToCheck(pop));
            result.determineAndAddAcceptedIntervals(valuesToCheck, [&](AlbaNumber const& value)
            {
                substitution.putVariableWithValue(variableName, value);
                Equation substitutedEquation(substitution.performSubstitutionTo(m_equation));
                return substitutedEquation.isEquationSatisfied()
                        && isAFiniteValue(substitutedEquation.getLeftHandTerm())
                        && isAFiniteValue(substitutedEquation.getRightHandTerm());
            });
            setAsCompleteSolution();
        }
    }
}

AlbaNumbers OneEquationOneUnknownNonEqualitySolver::getValuesToCheck(PolynomialOverPolynomial const& pop)
{
    AlbaNumbers valuesToCheck(getRoots(pop.getNumerator()));
    AlbaNumbers denominatorRoots(getRoots(pop.getDenominator()));
    valuesToCheck.reserve(valuesToCheck.size() + denominatorRoots.size());
    copy(denominatorRoots.cbegin(), denominatorRoots.cend(), back_inserter(valuesToCheck));
    return valuesToCheck;
}

}
}