#include "BaseOneEquationOneVariableSolver.hpp"

#include <Algebra/Retrieval/FunctionsRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Bit/AlbaBitManipulation.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

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
    FunctionsRetriever absFunctionsRetriever([](Function const& functionObject)
    {
        return functionObject.getFunctionName() == "abs";
    });
    absFunctionsRetriever.retrieveFromTerm(term);
    FunctionsSet const& absFunctions(absFunctionsRetriever.getSavedData());
    if(absFunctions.empty())
    {
        calculateForTermAndVariable(term, variableName);
    }
    else
    {
        calculateAndSubstituteAbsoluteValueFunctions(absFunctions, term, variableName);
    }
}

void BaseOneEquationOneVariableSolver::sortAndRemoveDuplicateCalculatedValues()
{
    sort(m_calculatedValues.begin(), m_calculatedValues.end());
    m_calculatedValues.erase(unique(m_calculatedValues.begin(), m_calculatedValues.end()), m_calculatedValues.end());
}

void BaseOneEquationOneVariableSolver::calculateAndSubstituteAbsoluteValueFunctions(
        FunctionsSet const& absFunctions,
        Term const& term,
        string const& variableName)
{
    using BitManipulation = AlbaBitManipulation<unsigned int>;
    unsigned int finalValue = BitManipulation::generateOnesWithNumberOfBits(absFunctions.size());
    for(unsigned int permutationValue=0; permutationValue<=finalValue; permutationValue++)
    {
        SubstitutionOfTermsToTerms substitution;
        auto itFunctionSet = absFunctions.cbegin();
        for(unsigned int i=0; i<absFunctions.size(); i++)
        {
            bool isBitAsserted(((permutationValue >> i) & 1) != 0);
            Term termToReplace;
            Term const& absFunctionTerm(*itFunctionSet);
            Term const& absFunctionInputTerm(getTermConstReferenceFromBaseTerm(itFunctionSet->getInputTermConstReference()));
            if(isBitAsserted)
            {
                termToReplace = absFunctionInputTerm;
            }
            else
            {
                termToReplace
                        = Term(createExpressionIfPossible({Term(-1), Term("*"), absFunctionInputTerm}));
            }
            substitution.putTermToTermMapping(absFunctionTerm, termToReplace);
            itFunctionSet++;
        }
        Term termAfterSubstitution(substitution.performSubstitutionTo(term));
        calculateForTermAndVariable(termAfterSubstitution, variableName);
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
