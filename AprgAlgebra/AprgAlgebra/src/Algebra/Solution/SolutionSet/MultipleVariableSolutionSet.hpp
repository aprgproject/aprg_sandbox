#pragma once

#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

#include <map>
#include <vector>

namespace alba
{

namespace algebra
{

class MultipleVariableSolutionSet
{
public:
    using VariableNameToSolutionSetMap = std::map<std::string, SolutionSet>;
    using VariableNameToSolutionSetPair = std::pair<std::string, SolutionSet>;

    MultipleVariableSolutionSet();

    bool isValueAcceptedForVariable(std::string const& variableName, AlbaNumber const& value) const;
    unsigned int getNumberOfVariablesWithSolutions() const;
    std::string getDisplayableString() const;

    VariableNamesSet getVariableNames() const;
    SolutionSet getSolutionSetForVariable(std::string const& variableName) const;
    VariableNameToSolutionSetMap const& getVariableNameToSolutionSetMap() const;

    void addSolutionSetForVariable(std::string const& variableName, SolutionSet const& solutionSet);

private:
    VariableNameToSolutionSetMap m_variableNameToSolutionSetMap;
};

using MultipleVariableSolutionSets = std::vector<MultipleVariableSolutionSet>;

}

}