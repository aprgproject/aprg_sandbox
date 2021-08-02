#include "MultipleVariableSolutionSet.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

MultipleVariableSolutionSet::MultipleVariableSolutionSet()
{}

unsigned int MultipleVariableSolutionSet::getNumberOfVariablesWithSolutions() const
{
    return m_variableNameToSolutionSetMap.size();
}

VariableNamesSet MultipleVariableSolutionSet::getVariableNames() const
{
    VariableNamesSet result;
    for(VariableNameToSolutionSetPair const& pair : m_variableNameToSolutionSetMap)
    {
        result.emplace(pair.first);
    }
    return result;
}

SolutionSet MultipleVariableSolutionSet::getSolutionSetForVariable(
        string const& variableName) const
{
    SolutionSet result;
    auto it = m_variableNameToSolutionSetMap.find(variableName);
    if(it != m_variableNameToSolutionSetMap.cend())
    {
        result = it->second;
    }
    return result;
}

MultipleVariableSolutionSet::VariableNameToSolutionSetMap const& MultipleVariableSolutionSet::getVariableNameToSolutionSetMap() const
{
    return m_variableNameToSolutionSetMap;
}

void MultipleVariableSolutionSet::addSolutionSetForVariable(
        string const& variableName,
        SolutionSet const& solutionSet)
{
    m_variableNameToSolutionSetMap.emplace(variableName, solutionSet);
}

}

}
