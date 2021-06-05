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

    std::string getDisplayableString() const;
    Monomial getFirstMonomial() const;

    Monomials & getMonomialsReference();    Monomials const& getMonomialsConstReference() const;

    void addMonomial(Monomial const& monomial);
    void addPolynomial(Polynomial const& polynomial);    void multiplyByNumber(AlbaNumber const& number);
    void multiplyByMonomial(Monomial const& monomial);
    void multiplyByPolynomial(Polynomial const& polynomial);
    void divideByMonomial(Monomial const& monomial);

private:
    Monomials m_monomials;
};

}

}
