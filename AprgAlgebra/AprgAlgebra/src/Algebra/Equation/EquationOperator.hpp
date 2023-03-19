#pragma once

#include <string>

namespace alba
{

namespace algebra
{

class EquationOperator
{
public:

    EquationOperator() = default;
    EquationOperator(std::string const& operatingString);

    // rule of zero

    bool operator==(EquationOperator const& second) const;
    bool operator!=(EquationOperator const& second) const;
    bool operator<(EquationOperator const& second) const;
    bool isEqual() const;
    bool isNotEqual() const;
    bool isLessThan() const;    bool isGreaterThan() const;
    bool isLessThanOrEqual() const;
    bool isGreaterThanOrEqual() const;
    bool isAnEqualityVariant() const;
    bool isALessThanVariant() const;
    bool isAGreaterThanVariant() const;
    std::string getOperatorString() const;

private:

    friend std::ostream & operator<<(std::ostream & out, EquationOperator const& equationOperator);

    std::string m_operatingString;
};

}

}
