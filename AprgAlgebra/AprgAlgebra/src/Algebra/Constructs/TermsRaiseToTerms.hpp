#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <map>

namespace alba
{

namespace algebra
{

class TermsRaiseToTerms
{
public:
    using BaseToExponentMap = std::map<Term, Term>;
    using BaseExponentPair = std::pair<Term, Term>;

    TermsRaiseToTerms();
    TermsRaiseToTerms(BaseToExponentMap const& baseToExponentMap);

    BaseToExponentMap const& getBaseToExponentMap() const;
    Term getExponentOfBase(Term const& base) const;
    Terms getTermsInMultiplicationOperation() const;
    TermsWithDetails getTermWithDetailsInMultiplicationAndDivisionOperation() const;
    Term getCombinedTerm() const;

    void addExponents(TermsRaiseToTerms const& termsRaiseToNumbers);
    void subtractExponents(TermsRaiseToTerms const& termsRaiseToNumbers);
    void multiplyToExponents(Term const& term);
    void putTerm(Term const& term, TermAssociationType const association);
    void putTerms(Terms const& terms, TermAssociationType const association);

    void setBaseAndExponent(Term const& base, Term const& exponent);
    void removeItemWithBase(Term const& base);

    void simplify();

private:

    void removeItemsWithExponentsZero();
    Term convertToTerm(Term const& base, Term const& exponent) const;

    BaseToExponentMap m_baseToExponentMap;
};

}

}
