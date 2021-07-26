#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/OperatorLevel.hpp>
#include <Algebra/Term/TermTypes/OperatorInputType.hpp>
#include <Math/AlbaNumber.hpp>

#include <string>

namespace alba
{

namespace algebra
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
    bool isSameOperatorInputType(OperatorInputType const operatorInputType) const;

    OperatorLevel getOperatorLevel() const;
    std::string getOperatorString() const;
    std::string getDisplayableString() const;

    void setOperatorString(std::string const& operatingString);

private:
    std::string m_operatingString;
};

std::ostream & operator<<(std::ostream & out, Operator const& operatorTerm);

}

}
