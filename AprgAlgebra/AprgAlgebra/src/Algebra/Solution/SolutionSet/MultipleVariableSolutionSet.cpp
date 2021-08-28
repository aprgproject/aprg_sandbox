#include "MultipleVariableSolutionSet.hpp"

#include <algorithm>
#include <sstream>

using namespace std;

namespace alba
{

namespace algebra
{

MultipleVariableSolutionSet::MultipleVariableSolutionSet()
{}

bool MultipleVariableSolutionSet::isValueAcceptedForVariable(
        string const& variableName,
        AlbaNumber const& value) const
{
    SolutionSet solutionSet(getSolutionSetForVariable(variableName));
    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    return find(acceptedValues.cbegin(), acceptedValues.cend(), value) != acceptedValues.cend();
}

unsigned int MultipleVariableSolutionSet::getNumberOfVariablesWithSolutions() const
{
    return m_variableNameToSolutionSetMap.size();
}

string MultipleVariableSolutionSet::getDisplayableString() const
{
    stringstream result;
    for(VariableNameToSolutionSetPair const& pair : m_variableNameToSolutionSetMap)
    {
        result << "Variable:{" << pair.first << "} SolutionSet:{" << pair.second << "} ";
    }
    return result.str();
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
    m_variableNameToSolutionSetMap[variableName] = solutionSet;
}

ostream & operator<<(ostream & out, MultipleVariableSolutionSet const& solutionSet){
    out << solutionSet.getDisplayableString();
    return out;
}
}

}
