#include "Polynomial.hpp"

#include <Utilities.hpp>

using namespace std;

namespace alba{

namespace equation
{
Polynomial::Polynomial()
{}

Polynomial::Polynomial(Monomials const& monomials)
    : m_monomials(monomials)
{}

Polynomial::Polynomial(initializer_list<Monomial> const& monomials)
{
    copy(monomials.begin(), monomials.end(), back_inserter(m_monomials));
}

Monomials & Polynomial::getMonomialsReference()
{
    return m_monomials;
}

Monomials const& Polynomial::getMonomialsConstReference() const
{
    return m_monomials;
}

void Polynomial::addMonomial(Monomial const& monomial)
{
    bool isFoundInPolynomial(false);
    for(Monomial & monomialInternal : m_monomials)
    {
        if(canBeAddedOrSubtracted(monomialInternal, monomial))
        {
            isFoundInPolynomial=true;
            monomialInternal.setConstant(monomialInternal.getConstantConstReference() + monomial.getConstantConstReference());
        }
    }
    if(!isFoundInPolynomial)
    {
        m_monomials.emplace_back(monomial);
    }
}

void Polynomial::addPolynomial(Polynomial const& polynomial)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        addMonomial(monomial);
    }
}

void Polynomial::multiplyByNumber(AlbaNumber const& number)
{
    for(Monomial & monomial : m_monomials)
    {
        monomial.setConstant(monomial.getConstantConstReference()*number);
    }
}

}

}