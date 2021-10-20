#pragma once

#include <Algebra/Equation/Equation.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class IsolationOfOneVariableOnEqualityEquation
{
public:
    IsolationOfOneVariableOnEqualityEquation(Equation const& equation);

    bool canBeIsolated(std::string const& variableName) const;
    AlbaNumber getIdenticalExponentForVariableIfPossible(std::string const& variableName) const;

    Equation isolateTermWithVariableOnLeftSideOfEquation(std::string const& variableName) const;
    Equation isolateTermWithVariableOnRightSideOfEquation(std::string const& variableName) const;

    Term getTermByIsolatingVariable(std::string const& variableName) const;

    void isolateTermWithVariable(
            std::string const& variableName,
            Term & termWithVariable,
            Term & termWithWithoutVariable) const;

private:
    bool canBeIsolated(AlbaNumber const& identicalExponentForVariable) const;
    AlbaNumber getIdenticalExponentForVariableIfPossible(
            std::string const& variableName,
            Polynomial const& polynomial) const;
    Term m_simplifiedLeftSideTerm;
};
}

}