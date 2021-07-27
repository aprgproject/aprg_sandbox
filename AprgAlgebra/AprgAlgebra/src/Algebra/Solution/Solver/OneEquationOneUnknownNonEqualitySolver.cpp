#include "OneEquationOneUnknownNonEqualitySolver.hpp"

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

OneEquationOneUnknownNonEqualitySolver::OneEquationOneUnknownNonEqualitySolver(Equation const& equation)
    : m_equation(equation)
{}

SolutionSet OneEquationOneUnknownNonEqualitySolver::calculateSolutionAndReturnSolutionSet()
{
    SolutionSet result;
    if(!m_equation.getEquationOperator().isEqual())
    {
        m_equation.simplify();
        if(m_equation.isEquationSatisfied())
        {
            addIntervalWhenEquationIsAlwaysSatisfied(result);
        }
        else
        {
            calculateWhenEquationIsSometimesSatisfied(result);
        }
    }
    return result;
}

void OneEquationOneUnknownNonEqualitySolver::addIntervalWhenEquationIsAlwaysSatisfied(SolutionSet & result)
{
    result.addAcceptedInterval(
                AlbaNumberInterval(
                    createOpenEndpoint(AlbaNumber::Value::NegativeInfinity),
                    createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)));
}

void OneEquationOneUnknownNonEqualitySolver::calculateWhenEquationIsSometimesSatisfied(SolutionSet & result)
{
    Term const& nonZeroLeftHandTerm(m_equation.getLeftHandTerm());
    VariableNamesSet variableNames(getVariableNames(nonZeroLeftHandTerm));
    if(variableNames.size() == 1)
    {
        string variableName = *variableNames.cbegin();
        PolynomialOverPolynomialOptional popOptional(
                    createPolynomialOverPolynomialFromTermIfPossible(nonZeroLeftHandTerm));
        if(popOptional.hasContent())
        {
            PolynomialOverPolynomial const& pop(popOptional.getConstReference());
            result.addAcceptedValues(getRoots(pop.getNumerator()));
            result.addRejectedValues(getRoots(pop.getDenominator()));
        }
        else
        {
            performNewtonMethodToFindSolution(result, nonZeroLeftHandTerm, variableName);
        }
    }
}

void OneEquationOneUnknownNonEqualitySolver::performNewtonMethodToFindSolution(
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
    }
}

}

}
