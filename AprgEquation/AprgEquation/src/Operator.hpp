#pragma once

#include <BaseTermData.hpp>

#include <string>

namespace alba
{

namespace equation
{

class Operator : public BaseTermData
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
