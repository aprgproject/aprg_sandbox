#include "OneEquationOneUnknownEqualitySolver.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Solution/SolutionUtilities.hpp>
#include <Algebra/Solution/Solver/NewtonMethod.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

OneEquationOneUnknownEqualitySolver::OneEquationOneUnknownEqualitySolver(Equation const& equation)
    : m_isSolved(false)
    , m_isACompleteSolution(false)
    , m_equation(equation)
{}

bool OneEquationOneUnknownEqualitySolver::isSolved() const
{
    return m_isSolved;
}

bool OneEquationOneUnknownEqualitySolver::isACompleteSolution() const
{
    return m_isACompleteSolution;
}

SolutionSet OneEquationOneUnknownEqualitySolver::calculateSolutionAndReturnSolutionSet()
{
    SolutionSet result;    if(m_equation.getEquationOperator().isEqual())
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

void OneEquationOneUnknownEqualitySolver::setAsCompleteSolution()
{
    m_isSolved = true;
    m_isACompleteSolution = true;
}

void OneEquationOneUnknownEqualitySolver::setAsIncompleteSolution()
{
    m_isSolved = true;
    m_isACompleteSolution = false;
}

void OneEquationOneUnknownEqualitySolver::processWhenEquationIsAlwaysSatisfied(SolutionSet & result)
{
    result.addAcceptedInterval(createAllRealValuesInterval());
    setAsCompleteSolution();
}

void OneEquationOneUnknownEqualitySolver::calculateWhenEquationIsSometimesSatisfied(SolutionSet & result)
{
    Term const& nonZeroLeftHandTerm(m_equation.getLeftHandTerm());    VariableNamesSet variableNames(getVariableNames(nonZeroLeftHandTerm));
    if(variableNames.size() == 1)
    {
        string variableName = *variableNames.cbegin();        PolynomialOverPolynomialOptional popOptional(
                    createPolynomialOverPolynomialFromTermIfPossible(nonZeroLeftHandTerm));
        if(popOptional.hasContent())
        {
            PolynomialOverPolynomial const& pop(popOptional.getConstReference());
            result.addAcceptedValues(getRoots(pop.getNumerator()));
            result.addRejectedValues(getRoots(pop.getDenominator()));
            setAsCompleteSolution();
        }
        else
        {            performNewtonMethodToFindSolution(result, nonZeroLeftHandTerm, variableName);
        }
    }
}
void OneEquationOneUnknownEqualitySolver::performNewtonMethodToFindSolution(
        SolutionSet & result,
        Term const& termToCheck,
        string const& variableNameForSubstitution)
{
    SubstitutionOfVariablesToValues substitution;
    NewtonMethod newtonMethod(
                getInitialValueForNewtonMethod(termToCheck),
                [&](AlbaNumber const& value)
    {
        substitution.putVariableWithValue(variableNameForSubstitution, value);
        Term result(substitution.performSubstitutionTo(termToCheck));
        AlbaNumber resultValue;
        if(result.isConstant())
        {
            resultValue = result.getConstantConstReference().getNumberConstReference();
        }
        return resultValue;
    });

    newtonMethod.runMaxNumberOfIterationsOrUntilFinished(1000);

    if(newtonMethod.isSolved())
    {
        result.addAcceptedValue(newtonMethod.getCurrentComputedValue());
        setAsIncompleteSolution();
    }
}
}

}