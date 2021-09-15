#pragma once

#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermAssociationType.hpp>

namespace alba
{

namespace algebra
{

class AdditionAndSubtractionOfExpressions
{
public:
    AdditionAndSubtractionOfExpressions();

    Expressions const& getExpressions() const;
    TermAssociationTypes const& getAssociations() const;
    unsigned int getSize() const;
    TermsWithDetails getAsTermsWithDetails() const;

    void putAsAddition(Expression const& expression);
    void putAsSubtraction(Expression const& expression);
    void putAsAddOrSubtraction(Expression const& expression, TermAssociationType const association);
    void putTermsWithDetails(TermsWithDetails const& termsWithDetails);
    void combineExpressionsIfPossible();

private:
    bool mergeForAdditionAndSubtractionAndReturnIfMerged(
            unsigned int const index1,
            unsigned int const index2);
    void retrieveUniqueExpressionsAndMergeTerms(
            Expression & uniqueExpression1,
            Expression & uniqueExpression2,
            Term & mergeTerm1,
            Term & mergeTerm2,
            Expression const& expression1,
            Expression const& expression2);
    Expression getUniqueExpressionForAdditionOrSubtractionMergeChecking(Expression const& expression);
    void accumulateMergeTermForAdditionOrSubtractionMergeChecking(Term & combinedTerm, Expression const& expression);
    bool canBeMergedForAdditionAndSubtraction(
            Expression const& uniqueExpression1,
            Expression const& uniqueExpression2,
            Term const& mergeTerm1,
            Term const& mergeTerm2);
    void putItem(Expression const& expression, TermAssociationType const association);
    Expressions m_expressions;
    TermAssociationTypes m_associations;
};

}

}
