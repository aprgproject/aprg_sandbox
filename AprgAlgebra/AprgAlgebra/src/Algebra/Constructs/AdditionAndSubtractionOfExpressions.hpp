#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

class AdditionAndSubtractionOfExpressions {
public:
    AdditionAndSubtractionOfExpressions();
    AdditionAndSubtractionOfExpressions(TermsWithDetails const& termsWithDetails);

    Expressions const& getExpressions() const;
    TermAssociationTypes const& getAssociations() const;
    int getSize() const;
    TermsWithDetails getAsTermsWithDetails() const;

    Term getCombinedTerm();

    void putAsAddition(Expression const& expression);
    void putAsSubtraction(Expression const& expression);
    void putAsAddOrSubtraction(Expression const& expression, TermAssociationType const association);
    void putTermsWithDetails(TermsWithDetails const& termsWithDetails);

    void combineExpressionsIfPossible();

private:
    void mergeExpressionsByCheckingTwoTermsAtATime(Terms& mergeParts, Terms& commonParts);
    Term mergeTerms(
        Term const& mergePart1, Term const& mergePart2, TermAssociationType const association1,
        TermAssociationType const association2);
    void prepareCommonParts(Terms& commonParts);
    void retrieveMergeParts(Terms& mergeParts);
    void retrieveCommonParts(Terms& commonParts);
    void retrieveMergePart(Term& mergePart, Expression const& expression);
    void retrieveCommonPart(Term& commonPart, Expression const& expression);
    bool doAllSizesMatch(Terms const& mergeParts, Terms const& commonParts) const;
    bool canBeMerged(Term const& mergePart1, Term const& mergePart2, Term const& commonPart1, Term const& commonPart2);
    void putItem(Expression const& expression, TermAssociationType const association);
    Expressions m_expressions;
    TermAssociationTypes m_associations;
};

}  // namespace algebra

}  // namespace alba
