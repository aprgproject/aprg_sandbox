#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

class TermRaiseToANumber
{
public:
    TermRaiseToANumber();
    TermRaiseToANumber(Term const& base, AlbaNumber const& exponent);

    bool isRadical() const;

    Term getBase() const;
    AlbaNumber getExponent() const;

private:
    Term m_base;
    AlbaNumber m_exponent;
};

}

}
