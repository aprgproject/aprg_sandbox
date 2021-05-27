#pragma once

#include <BaseTermData.hpp>

#include <string>

namespace alba
{

namespace equation
{

class Variable : public BaseTermData
{
public:
    Variable();
    Variable(std::string const& variableName);

    std::string getVariableName() const;

    void setVariableName(std::string const& variableName);

private:
    std::string m_variableName;
};

}

}
