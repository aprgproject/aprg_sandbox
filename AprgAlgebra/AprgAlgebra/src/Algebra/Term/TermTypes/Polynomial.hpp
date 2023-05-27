#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/Monomial.hpp>

#include <string>
#include <vector>

namespace alba {

namespace algebra {

class Polynomial : public BaseTermData {
public:
    Polynomial();
    Polynomial(Monomials const& monomials);
    Polynomial(std::initializer_list<Monomial> const& monomials);

    // rule of zero

    bool operator==(Polynomial const& second) const;
    bool operator!=(Polynomial const& second) const;
    bool operator<(Polynomial const& second) const;
    bool isEmpty() const;
    bool isSimplified() const;
    Monomials const& getMonomialsConstReference() const;

    Monomials& getMonomialsReference();
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
    void raiseToUnsignedInteger(int const exponent);
    void setAsSimplified();
    void clearSimplifiedFlag();
private:
    bool isFurtherSimplificationNeeded(Polynomial const& beforeSimplify, Polynomial const& afterSimplify) const;
    void setNan();    void simplifyContinuouslyIfChanged();
    void simplifyMonomialsAndReAdd();

    friend std::ostream& operator<<(std::ostream& out, Polynomial const& polynomial);

    Monomials m_monomials;
    bool m_isSimplified;
};

using Polynomials = std::vector<Polynomial>;

}  // namespace algebra

}  // namespace alba
