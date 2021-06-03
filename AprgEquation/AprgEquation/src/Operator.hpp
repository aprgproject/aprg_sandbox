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

    bool isAddition() const;
    bool isSubtraction() const;
    bool isMultiplication() const;
    bool isDivision() const;
    bool isRaiseToPower() const;
    std::string getOperatorString() const;
    AlbaNumber performOperation(AlbaNumber const& number1, AlbaNumber const& number2) const;

    void setOperatorString(std::string const& operatingString);

private:
    std::string m_operatingString;
};

}

}
