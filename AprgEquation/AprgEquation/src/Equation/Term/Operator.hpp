#pragma once

#include <Equation/Term/BaseTermData.hpp>
#include <Equation/Term/OperatorLevel.hpp>
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
    bool operator!=(Operator const& second) const;
    bool operator<(Operator const& second) const;
    bool isAddition() const;
    bool isSubtraction() const;
    bool isMultiplication() const;
    bool isDivision() const;
    bool isRaiseToPower() const;
    bool isAnOperatorThatCanPerformed() const;
    bool isOpeningGroupOperator() const;
    bool isClosingGroupOperator() const;

    OperatorLevel getOperatorLevel() const;
    std::string getOperatorString() const;
    std::string getDisplayableString() const;

    void setOperatorString(std::string const& operatingString);

private:
    std::string m_operatingString;
};

}

}
