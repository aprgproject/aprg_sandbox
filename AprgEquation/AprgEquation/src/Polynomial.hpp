#pragma once

#include <BaseTermData.hpp>
#include <Monomial.hpp>

#include <string>

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

    bool operator==(Polynomial const& second) const;
    bool isZero() const;
    bool isOneMonomial() const;

    Monomial getFirstMonomial() const;
    Monomials const& getMonomialsConstReference() const;
    std::string getDisplayableString() const;

    void simplify();
    void addMonomial(Monomial const& monomial);
    void addPolynomial(Polynomial const& polynomial);
    void multiplyNumber(AlbaNumber const& number);
    void multiplyMonomial(Monomial const& monomial);
    void multiplyPolynomial(Polynomial const& polynomial);
    void divideMonomial(Monomial const& monomial);

private:
    Monomials m_monomials;
};

}

}
