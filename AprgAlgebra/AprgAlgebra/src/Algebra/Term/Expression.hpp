#pragma once

#include <Algebra/Term/BaseTermData.hpp>
#include <Algebra/Term/OperatorLevel.hpp>
#include <Algebra/Term/Polynomial.hpp>
#include <Algebra/Term/TermsWithAssociation.hpp>

#include <functional>
#include <string>
#include <vector>

namespace alba
{

namespace algebra
{

class Expression : public BaseTermData
{
    friend std::ostream & operator<<(std::ostream & out, Expression const& expression);
public:
    using ConditionFunctionForTermsWithDetails = std::function<bool(TermsWithAssociation::TermWithDetails const&)>;

    Expression();
    Expression(BaseTerm const& baseTerm);
    ~Expression();

    bool operator==(Expression const& second) const;
    bool operator!=(Expression const& second) const;
    bool operator<(Expression const& second) const;
    bool isEmpty() const;
    bool containsOnlyOneTerm() const;

    OperatorLevel getCommonOperatorLevel() const;
    BaseTerm const& getFirstTermConstReference() const;
    TermsWithAssociation const& getTermsWithAssociation() const;
    TermsWithAssociation & getTermsWithAssociationReference();
    TermsWithAssociation getTermsWithDetailsThatSatisfiesCondition(
            ConditionFunctionForTermsWithDetails const& conditionFunction) const;
    std::string getDisplayableString() const;
    std::string getDebugString() const;

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
    void putTermsWithDetails(TermsWithAssociation::TermsWithDetails const& termsToSave);

    void reverseTheAssociationOfTheTerms();
    void set(OperatorLevel const operatorLevel, TermsWithAssociation const& termsWithPriorityAndAssociation);
    void setTerm(BaseTerm const& baseTerm);
    void setCommonOperatorLevel(OperatorLevel const operatorLevel);
    void setCommonOperatorLevelIfStillUnknown(OperatorLevel const operatorLevel);

    void simplify();
    void sort();

private:

    //put functions
    void putTermWithAddition(BaseTerm const& baseTerm);
    void putTermWithSubtraction(BaseTerm const& baseTerm);
    void putTermWithMultiplication(BaseTerm const& baseTerm);
    void putTermWithDivision(BaseTerm const& baseTerm);
    void putTermWithRaiseToPower(BaseTerm const& baseTerm);
    void putTermForExpressionAndNonExpressions(
            BaseTerm const& baseTerm,
            TermAssociationType const overallAssociation);
    void putTerm(
            BaseTerm const& baseTerm,
            TermAssociationType const overallAssociation);
    void putTermsWithAssociation(
            TermsWithAssociation const& termsWithAssociation,
            TermAssociationType const overallAssociation);

    // functions for multiply then add or subtract
    void multiplyThenAddOrSubtract(Polynomial const& polynomial, Expression const& expression);
    void multiplyThenAddOrSubtract(Expression const& expression, Polynomial const& polynomial);
    void multiplyThenAddOrSubtract(Polynomial const& polynomial, TermsWithAssociation::TermsWithDetails const& termsWithDetails);
    void multiplyThenAddOrSubtract(TermsWithAssociation::TermsWithDetails const& termsWithDetails, Polynomial const& polynomial);
    void multiplyThenAddOrSubtract(BaseTerm const& baseTerm, TermsWithAssociation::TermsWithDetails const& termsWithDetails);
    void multiplyThenAddOrSubtract(TermsWithAssociation::TermsWithDetails const& termsWithDetails, BaseTerm const& baseTerm);
    void multiplyThenAddOrSubtract(
            TermsWithAssociation::TermsWithDetails const& termsWithDetails1,
            TermsWithAssociation::TermsWithDetails const& termsWithDetails2);
    void multiplyThenAddOrSubtract(Expression const& multiplicand, BaseTerm const& multiplier, bool const isAdd);

    OperatorLevel m_commonOperatorLevel;
    TermsWithAssociation m_termsWithAssociation;
};

using Expressions=std::vector<Expression>;

std::ostream & operator<<(std::ostream & out, Expression const& expression);

}

}
