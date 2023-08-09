#pragma once

#include <BaseTermData.hpp>
#include <Math/AlbaNumber.hpp>

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

    bool operator==(Operator const& second) const;

    bool isAddition() const;
    bool isSubtraction() const;
    bool isMultiplication() const;
    bool isDivision() const;
    bool isRaiseToPower() const;

    std::string getOperatorString() const;

    void setOperatorString(std::string const& operatingString);

private:
    std::string m_operatingString;
};

}

}
