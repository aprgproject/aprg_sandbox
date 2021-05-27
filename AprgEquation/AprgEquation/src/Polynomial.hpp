#pragma once

#include <BaseTermData.hpp>
#include <Monomial.hpp>

namespace alba
{

namespace equation
{

class Polynomial : public BaseTermData
{
public:
    Polynomial();
    Polynomial(Monomials const& monomials);
    Polynomial(std::initializer_list<Monomial> const& monomials);

    Monomials const& getMonomialsConstReference() const;

private:
    Monomials m_monomials;
};

}

}
