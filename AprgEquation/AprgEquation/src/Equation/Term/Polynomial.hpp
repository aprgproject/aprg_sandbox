#pragma once

#include <Equation/Constructs/VariablesToValuesTypes.hpp>
#include <Equation/Term/BaseTermData.hpp>
#include <Equation/Term/Monomial.hpp>

#include <string>
#include <vector>
namespace alba
{

namespace equation
{

class Polynomial : public BaseTermData
{
    friend std::ostream & operator<<(std::ostream & out, Polynomial const& polynomial);
public:
    Polynomial();
    Polynomial(Monomials const& monomials);    Polynomial(std::initializer_list<Monomial> const& monomials);

    bool operator==(Polynomial const& second) const;
    bool operator!=(Polynomial const& second) const;
    bool operator<(Polynomial const& second) const;
    bool isEmpty() const;
    bool isOne() const;
    bool isZero() const;
    bool isOneMonomial() const;
    bool isVariableExponentContentFound(Monomial const& monomial) const;

    AlbaNumber getCoefficientOfVariableExponent(Monomial const& monomial) const;
    Monomial getFirstMonomial() const;
    Monomials const& getMonomialsConstReference() const;
    std::string getDisplayableString() const;
    void clear();
    void simplify();
    void sortMonomialsWithInversePriority();
    void substituteVariablesToValues(VariablesToValuesMap const& variableValueMap);
    void addMonomial(Monomial const& monomial);
    void addPolynomial(Polynomial const& polynomial);
    void multiplyNumber(AlbaNumber const& number);
    void divideNumber(AlbaNumber const& number);
    void multiplyMonomial(Monomial const& monomial);
    void multiplyPolynomial(Polynomial const& polynomial);
    void divideMonomial(Monomial const& monomial);

private:
    void simplifyFurtherIfNeeded(Polynomial const& beforeSimplify, Polynomial const& afterSimplify);
    void simplifyMonomialsAndReAdd();    Monomials m_monomials;
};

using Polynomials=std::vector<Polynomial>;

std::ostream & operator<<(std::ostream & out, Polynomial const& polynomial);

}

}