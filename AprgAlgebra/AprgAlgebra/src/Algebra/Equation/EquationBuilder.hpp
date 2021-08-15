#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <String/AlbaStringHelper.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class EquationBuilder
{
public:
    EquationBuilder(std::string const& equationInString);
    Equation getEquation() const;
    stringHelper::strings const& getTermStrings() const;
    stringHelper::strings const& getEquationOperatorStrings() const;
private:
    void splitAndSaveOperatorAndTermStrings(std::string const& equationInString);
    stringHelper::strings m_termStrings;
    stringHelper::strings m_equationOperatorStrings;
};

}

}
