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
    AlbaNumber getExponentOfIsolatedVariable(std::string const& variableName) const;

    Equation isolate(std::string const& variableName);

private:
    AlbaNumber getSameVariableExponentIfPossible(
            Polynomial const& polynomial,
            std::string const& variableName) const;
    bool canBeIsolated(AlbaNumber const& variableExponent) const;
    AlbaNumber getExponentOfIsolatedVariable(
            Polynomial const& polynomial,
            std::string const& variableName) const;    Term m_simplifiedLeftSideTerm;
};

}
}
