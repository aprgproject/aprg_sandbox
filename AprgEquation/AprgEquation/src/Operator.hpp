#pragma once

#include <BaseTerm.hpp>

#include <string>

namespace alba
{

namespace equation
{

class Operator : public BaseTerm
{
public:
    Operator();
    Operator(std::string const& operatingString);

    std::string getOperatorString() const;

    void setOperatorString(std::string const& operatingString);

private:
    std::string m_operatingString;
};

}

}
