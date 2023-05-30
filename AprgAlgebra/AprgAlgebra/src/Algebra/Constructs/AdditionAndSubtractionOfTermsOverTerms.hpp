#pragma once

#include <Algebra/Constructs/TermsOverTerms.hpp>

namespace alba {

namespace algebra {

class AdditionAndSubtractionOfTermsOverTerms {
public:
    AdditionAndSubtractionOfTermsOverTerms();

    VectorOfTermsOverTerms const& getItems() const;
    TermAssociationTypes const& getAssociations() const;
    Expression getCombinedExpression() const;
    Terms getLcmOfDenominatorTerms() const;
    Terms getRevisedNumeratorTermsBasedOnLcmOnIndex(int itemIndex, Terms const& lcmOfDenominatorTerms) const;

    void putAsAddition(TermsOverTerms const& addend);
    void putAsSubtraction(TermsOverTerms const& subtrahend);
    void putAsAddOrSubtraction(TermsOverTerms const& item, TermAssociationType const association);

private:
    void eraseCommonFactorOrAddDistinctFactor(
        Term const& termToCheck, Terms& commonFactors, Terms& outputFactors) const;
    Monomial getCombinedMonomialMultiplier(Terms const& monomialMultiplierTerms) const;
    void updateMonomialAndNonMonomialMultipliersBasedOnDenominatorOnIndex(
        int itemIndex, Monomial& monomialMultiplier, Terms& nonMonomialMultiplierTerms) const;
    void emplaceExistingNumeratorTerms(Terms& numeratorTerms, int itemIndex) const;
    void emplaceMonomialMultiplierIfNeeded(Terms& numeratorTerms, Monomial const& monomialMultiplier) const;
    void emplaceNonMonomialMultipliers(Terms& numeratorTerms, Terms const& nonMonomialMultiplierTerms) const;
    Expression getCombinedNumeratorExpression(Terms const& lcmDenominatorTerms) const;
    Expression getCombinedDenominatorExpression(Terms const& lcmDenominatorTerms) const;
    Expression getCombinedExpressionForNumeratorOnIndex(int numeratorIndex, Terms const& lcmDenominatorTerms) const;
    void combineExpressionAsAddOrSubtract(
        Expression& combinedExpression, Expression const& expression, TermAssociationType const association) const;
    TermsOverTerms getSimplifiedTermsOverTerms(TermsOverTerms const& termsOverTerms);
    void putItem(TermsOverTerms const& item, TermAssociationType const association);
    VectorOfTermsOverTerms m_items;
    TermAssociationTypes m_associations;
};

}  // namespace algebra

}  // namespace alba
