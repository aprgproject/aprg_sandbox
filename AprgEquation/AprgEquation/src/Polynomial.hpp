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

    Monomials & getMonomialsReference();
    Monomials const& getMonomialsConstReference() const;

    void addMonomial(Monomial const& monomial);
    void addPolynomial(Polynomial const& polynomial);
    void multiplyByNumber(AlbaNumber const& number);
    void multiplyByMonomial(Monomial const& monomial);
    void multiplyByPolynomial(Polynomial const& polynomial);
    void divideByMonomial(Monomial const& monomial);

private:
    Monomials m_monomials;
};

}

}
