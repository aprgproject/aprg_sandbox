#pragma once

#include <BaseTerm.hpp>

#include <string>

namespace alba
{

namespace equation
{

class Variable : public BaseTerm
{
public:
    Variable();
    Variable(std::string const& variableName);

    std::string getVariableName() const;
    void setVariableName(std::string const& variableName);

private:    std::string m_variableName;
};

}

}
