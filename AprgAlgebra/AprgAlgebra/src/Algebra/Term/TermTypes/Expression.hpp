#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/OperatorLevel.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Algebra/Term/TermTypes/TermsWithAssociation.hpp>

#include <string>
#include <vector>

namespace alba
{

namespace algebra
{

class Expression : public BaseTermData
{
public:

    Expression();
    Expression(BaseTerm const& baseTerm);
    Expression(BaseTerm && baseTerm);
    Expression(OperatorLevel const operatorLevel, TermsWithDetails const& termsWithDetails);
    Expression(OperatorLevel const operatorLevel, TermsWithDetails && termsWithDetails);

    // rule of zero

    bool operator==(Expression const& second) const;
    bool operator!=(Expression const& second) const;
    bool operator<(Expression const& second) const;
    bool isEmpty() const;
    bool containsOnlyOnePositivelyAssociatedTerm() const;
    bool isSimplified() const;

    OperatorLevel getCommonOperatorLevel() const;
    BaseTerm const& getFirstTermConstReference() const;
    TermAssociationType getFirstAssociationType() const;
    TermsWithAssociation const& getTermsWithAssociation() const;
    std::string getDebugString() const;

    TermsWithAssociation & getTermsWithAssociationReference();

    void clear();
    void clearAndPutTermInTermsWithAssociation(BaseTerm const& baseTerm);

    void putTermWithAdditionIfNeeded(BaseTerm const& baseTerm);
    void putTermWithSubtractionIfNeeded(BaseTerm const& baseTerm);
    void putTermWithMultiplicationIfNeeded(BaseTerm const& baseTerm);
    void putTermWithDivisionIfNeeded(BaseTerm const& baseTerm);
    void putTermWithRaiseToPowerIfNeeded(BaseTerm const& baseTerm);
    void putPolynomialFirstWithMultiplication(Polynomial const& polynomial);
    void putPolynomialSecondWithMultiplication(Polynomial const& polynomial);
    void putExpressionWithMultiplication(Expression const& expression);
    void putTermWithDetails(TermWithDetails const& termToSave);
    void putTermsWithDetails(TermsWithDetails const& termsToSave);
    void putTerm(
            BaseTerm const& baseTerm,
            TermAssociationType const overallAssociation);

    void reverseTheAssociationOfTheTerms();
    void set(OperatorLevel const operatorLevel, TermsWithDetails const& termsWithDetails);
    void setTerm(BaseTerm const& baseTerm);
    void setCommonOperatorLevel(OperatorLevel const operatorLevel);
    void setCommonOperatorLevelIfStillUnknown(OperatorLevel const operatorLevel);

    void simplify();
    void sort();

    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();

private:

    //put functions
    void putTermWithAddition(BaseTerm const& baseTerm);
    void putTermWithSubtraction(BaseTerm const& baseTerm);
    void putOnlyTermWithMultiplicationIfNeeded(BaseTerm const& baseTerm);
    void putTermWithMultiplication(BaseTerm const& baseTerm);
    void putTermWithDivision(BaseTerm const& baseTerm);
    void putTermWithRaiseToPower(BaseTerm const& baseTerm);
    void putTermForExpressionAndNonExpressions(
            BaseTerm const& baseTerm,
            TermAssociationType const overallAssociation);
    void putTermWithRaiseToPowerForExpressionAndNonExpressions(
            BaseTerm const& baseTerm,
            TermAssociationType const overallAssociation);
    void putTermsWithAssociation(
            TermsWithAssociation const& termsWithAssociation,
            TermAssociationType const overallAssociation);

    // functions for multiply then add or subtract
    void distributeAndMultiply(Polynomial const& polynomial, Expression const& expression);
    void distributeAndMultiply(Expression const& expression, Polynomial const& polynomial);
    void distributeAndMultiply(Polynomial const& polynomial, TermsWithDetails const& termsWithDetails);
    void distributeAndMultiply(TermsWithDetails const& termsWithDetails, Polynomial const& polynomial);
    void distributeAndMultiply(BaseTerm const& baseTerm, TermsWithDetails const& termsWithDetails);
    void distributeAndMultiply(TermsWithDetails const& termsWithDetails, BaseTerm const& baseTerm);
    void distributeAndMultiply(
            TermsWithDetails const& termsWithDetails1,
            TermsWithDetails const& termsWithDetails2);
    void distributeAndMultiply(Expression const& multiplicand, BaseTerm const& multiplier, bool const isAdd);

    friend std::ostream & operator<<(std::ostream & out, Expression const& expression);

    OperatorLevel m_commonOperatorLevel;
    TermsWithAssociation m_termsWithAssociation;
    bool m_isSimplified;
};

using Expressions=std::vector<Expression>;

}

}
