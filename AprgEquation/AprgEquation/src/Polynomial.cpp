#include "Polynomial.hpp"

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

Monomials const& Polynomial::getMonomialsConstReference() const
{
    return m_monomials;
}

}

}
