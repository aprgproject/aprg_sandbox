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

    bool isEmpty() const;
    bool isRadical() const;

    Term getCombinedTerm() const;
    Term const& getBase() const;
    AlbaNumber const& getExponent() const;

    Term & getBaseReference();

    void setBase(Term const& base);
    void setExponent(AlbaNumber const& exponent);

private:
    Term m_base;
    AlbaNumber m_exponent;
};

using ListOfTermRaiseToANumber = std::vector<TermRaiseToANumber>;

}

}
