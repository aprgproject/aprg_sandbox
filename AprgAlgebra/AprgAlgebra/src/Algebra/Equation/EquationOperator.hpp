#pragma once

#include <string>

namespace alba
{

namespace algebra
{

class EquationOperator
{
    friend std::ostream & operator<<(std::ostream & out, EquationOperator const& equationOperator);
public:
    EquationOperator();
    EquationOperator(std::string const& operatingString);

    bool operator==(EquationOperator const& second) const;
    bool operator!=(EquationOperator const& second) const;
    bool operator<(EquationOperator const& second) const;

    bool isEqual() const;
    bool isNotEqual() const;
    bool isLessThan() const;
    bool isGreaterThan() const;
    bool isLessThanOrEqual() const;
    bool isGreaterThanOrEqual() const;
    bool isAnEqualityVariant() const;
    bool isALessThanVariant() const;
    bool isAGreaterThanVariant() const;

    std::string getOperatorString() const;
    std::string getDisplayableString() const;

private:
    std::string m_operatingString;
};

std::ostream & operator<<(std::ostream & out, EquationOperator const& equationOperator);

}

}
