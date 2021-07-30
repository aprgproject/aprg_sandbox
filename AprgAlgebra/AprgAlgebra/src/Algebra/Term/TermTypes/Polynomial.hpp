#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/Monomial.hpp>

#include <string>
#include <vector>

namespace alba
{

namespace algebra
{

class Polynomial : public BaseTermData
{
public:
    Polynomial();
    Polynomial(Monomials const& monomials);
    Polynomial(std::initializer_list<Monomial> const& monomials);

    bool operator==(Polynomial const& second) const;
    bool operator!=(Polynomial const& second) const;
    bool operator<(Polynomial const& second) const;
    bool isEmpty() const;
    bool isOne() const;
    bool isZero() const;
    bool isOneMonomial() const;
    bool isVariableExponentInMonomialFound(Monomial const& monomial) const;
    bool hasNegativeExponents() const;

    AlbaNumber getCoefficientOfVariableExponent(Monomial const& monomial) const;
    Monomial getFirstMonomial() const;
    Monomials const& getMonomialsConstReference() const;
    AlbaNumber getMaxDegree() const;
    std::string getDisplayableString() const;

    void clear();
    void simplify();
    void sortMonomialsWithInversePriority();
    void addMonomial(Monomial const& monomial);
    void addPolynomial(Polynomial const& polynomial);
    void multiplyNumber(AlbaNumber const& number);
    void divideNumber(AlbaNumber const& number);
    void multiplyMonomial(Monomial const& monomial);
    void multiplyPolynomial(Polynomial const& polynomial);
    void divideMonomial(Monomial const& monomial);

private:
    bool isFurtherSimplificationNeeded(Polynomial const& beforeSimplify, Polynomial const& afterSimplify) const;
    void simplifyMonomialsAndReAdd();
    Monomials m_monomials;
};
using Polynomials=std::vector<Polynomial>;

std::ostream & operator<<(std::ostream & out, Polynomial const& polynomial);
}

}
