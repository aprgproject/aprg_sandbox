#include "BaseOneEquationOneVariableSolver.hpp"

#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

BaseOneEquationOneVariableSolver::BaseOneEquationOneVariableSolver()
    : BaseSolver()
    , m_calculatedValues()
{}

SolutionSet BaseOneEquationOneVariableSolver::calculateSolutionAndReturnSolutionSet(
        Equation const& equation)
{
    SolutionSet solutionSet;
    calculateSolution(solutionSet, equation);
    return solutionSet;
}

void BaseOneEquationOneVariableSolver::processWhenEquationIsAlwaysSatisfied(
        SolutionSet & solutionSet)
{
    solutionSet.addAcceptedInterval(createAllRealValuesInterval());
    setAsCompleteSolution();
}

void BaseOneEquationOneVariableSolver::calculateWhenEquationIsSometimesSatisfied(
        SolutionSet & solutionSet,
        Equation const& equation)
{
    calculateForEquation(solutionSet, equation);
}

void BaseOneEquationOneVariableSolver::calculateForTermAndCheckAbsoluteValueFunctions(
        Term const& term,
        string const& variableName)
{
    FunctionsSet absFunctions(
                retrieveAndReturnFunctionsWithCondition(
                    term, [](Function const& functionObject)
    {
                    return functionObject.getFunctionName() == "abs";                }));
    if(absFunctions.empty())
    {
        calculateForTermAndVariable(term, variableName);
    }
    else
    {
        calculateAndSubstituteAbsoluteValueFunctions(absFunctions, term, variableName);
    }
}

void BaseOneEquationOneVariableSolver::sortCalculatedValues()
{
    sort(m_calculatedValues.begin(), m_calculatedValues.end());
}

void BaseOneEquationOneVariableSolver::calculateAndSubstituteAbsoluteValueFunctions(
        FunctionsSet const& absFunctions,
        Term const& term,
        string const& variableName)
{
    for(Function const& absFunction : absFunctions)
    {
        Term absFunctionTerm(absFunction);
        SubstitutionOfTermsToTerms substitutionForPositive;
        Term positiveTerm(absFunction.getInputExpressionConstReference());
        substitutionForPositive.putTermToTermMapping(absFunctionTerm, positiveTerm);
        Term substitutedPositiveTerm(substitutionForPositive.performSubstitutionTo(term));
        substitutedPositiveTerm.simplify();
        calculateForTermAndVariable(substitutedPositiveTerm, variableName);

        SubstitutionOfTermsToTerms substitutionForNegative;
        Term negativeTerm(
                    createExpressionIfPossible({
                                                   Term(-1),
                                                   Term("*"),
                                                   Term(absFunction.getInputExpressionConstReference())}));
        substitutionForNegative.putTermToTermMapping(absFunctionTerm, negativeTerm);
        Term substitutedNegativeTerm(substitutionForNegative.performSubstitutionTo(term));
        substitutedNegativeTerm.simplify();
        calculateForTermAndVariable(substitutedNegativeTerm, variableName);
    }
}

void BaseOneEquationOneVariableSolver::addValuesToSolutionSetIfNeeded(
        SolutionSet& solutionSet,
        Term const& term,
        string const& variableName)
{
    if(!m_calculatedValues.empty() && isACompleteSolution())
    {
        SubstitutionOfVariablesToValues substitution;
        for(AlbaNumber const& value : m_calculatedValues)
        {
            substitution.putVariableWithValue(variableName, value);
            Term substitutedResult(substitution.performSubstitutionTo(term));
            if(substitutedResult.isConstant())
            {
                AlbaNumber const& computedValue(
                            substitutedResult.getConstantConstReference().getNumberConstReference());
                if(!computedValue.isAFiniteValue())
                {
                    solutionSet.addRejectedValue(value);
                }
                else if(computedValue == 0)
                {
                    solutionSet.addAcceptedValue(value);
                }
            }
        }
    }
}

}

}
