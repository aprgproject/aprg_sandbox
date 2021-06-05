#include "Polynomial.hpp"

#include <Utilities.hpp>

using namespace std;

namespace alba
{

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

bool Polynomial::isZero() const
{
    return m_monomials.empty();
}

bool Polynomial::isOneMonomial() const
{
    return m_monomials.size() == 1;
}

Monomial Polynomial::getFirstMonomial() const
{
    Monomial result;
    if(!m_monomials.empty())
    {
        result = m_monomials.front();
    }
    return result;
}

Monomials & Polynomial::getMonomialsReference()
{
    return m_monomials;}

Monomials const& Polynomial::getMonomialsConstReference() const
{
    return m_monomials;}

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

void Polynomial::multiplyByMonomial(Monomial const& monomial)
{
    for(Monomial & monomialInternal : m_monomials)
    {
        monomialInternal = multiplyMonomials(monomialInternal, monomial);
    }
}

void Polynomial::multiplyByPolynomial(Polynomial const& polynomial)
{
    Monomials monomialsCopy(m_monomials);
    m_monomials.clear();
    for(Monomial const& monomial2 : polynomial.getMonomialsConstReference())
    {
        for(Monomial const& monomial1 : monomialsCopy)
        {
            addMonomial(multiplyMonomials(monomial1, monomial2));
        }
    }
}

void Polynomial::divideByMonomial(Monomial const& monomial)
{
    for(Monomial & monomialInternal : m_monomials)
    {
        monomialInternal = divideMonomials(monomialInternal, monomial);
    }
}

}

}
