#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

class RationalizeTermOverTerm
{
public:
    RationalizeTermOverTerm();
    RationalizeTermOverTerm(Term const& numerator, Term const& denominator);

    Term const& getNumerator() const;
    Term const& getDenominator() const;
    Term getCombinedTerm() const;

    void rationalizeNumerator();
    void rationalizeDenominator();

private:
    void rationalize(Term & termToRationalize, Term & otherTerm);
    void simplifyForRationalize(Term & term);
    Term getMultiplierToRationalize(Term const& term) const;
    Polynomial getMultiplierToRationalizeForPolynomial(Polynomial const& polynomial) const;
    Polynomial getMultiplierToRationalizeForPolynomial(
            Monomial const& firstMonomial,
            Monomial const& secondMonomial) const;
    Polynomial getMultiplierToRationalizeForPolynomialWhenExponentIsDivisibleByTwo(
            Monomial const& firstMonomial,
            Monomial const& secondMonomial) const;
    Polynomial getMultiplierToRationalizeForPolynomialWhenExponentIsDivisibleByThree(
            Monomial const& firstMonomial,
            Monomial const& secondMonomial) const;
    Expression getMultiplierToRationalizeForExpression(
            Expression const& expression) const;
    Expression getMultiplierToRationalizeForExpression(
            TermsWithAssociation::TermWithDetails const& firstTermWithDetails,
            TermsWithAssociation::TermWithDetails const& secondTermWithDetails) const;
    Expression getMultiplierToRationalizeForExpressionWhenExponentIsDivisibleByTwo(
            TermsWithAssociation::TermWithDetails const& firstTermWithDetails,
            TermsWithAssociation::TermWithDetails const& secondTermWithDetails) const;
    Expression getMultiplierToRationalizeForExpressionWhenExponentIsDivisibleByThree(
            TermsWithAssociation::TermWithDetails const& firstTermWithDetails,
            TermsWithAssociation::TermWithDetails const& secondTermWithDetails) const;
    Term m_numerator;
    Term m_denominator;
};

}

}
