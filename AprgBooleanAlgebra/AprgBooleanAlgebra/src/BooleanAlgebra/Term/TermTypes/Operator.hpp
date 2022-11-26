#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermData.hpp>
#include <BooleanAlgebra/Term/TermTypes/OperatorInputType.hpp>
#include <BooleanAlgebra/Term/TermTypes/OperatorType.hpp>

#include <string>

namespace alba
{

namespace booleanAlgebra
{

class Operator : public BaseTermData
{
public:
    Operator();
    Operator(std::string const& operatingString);

    bool operator==(Operator const& second) const;
    bool operator!=(Operator const& second) const;
    bool operator<(Operator const& second) const;

    bool isNot() const;
    bool isAnd() const;
    bool isOr() const;
    bool isAnOperatorThatCanPerformed() const;
    bool isOpeningGroupOperator() const;
    bool isClosingGroupOperator() const;
    bool isUnaryOperator() const;
    bool isBinaryOperator() const;
    bool isSameOperatorInputType(OperatorInputType const operatorInputType) const;
    OperatorType getOperatorType() const;
    std::string getOperatorString() const;

    void setOperatorString(std::string const& operatingString);

private:
    friend std::ostream & operator<<(std::ostream & out, Operator const& operatorObject);

    std::string m_operatingString;
};

}

}