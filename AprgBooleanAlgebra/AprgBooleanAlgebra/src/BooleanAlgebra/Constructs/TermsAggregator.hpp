#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace booleanAlgebra {

class TermsAggregator {
public:
    enum class AggregatorTraverseSteps { BuildExpression, Simplify };
    using Indexes = std::vector<int>;

    TermsAggregator(Terms const& terms);

    Terms const& getTermsConstReference() const;

    void buildExpressionFromTerms();
    void simplifyTerms();

private:
    void updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
    bool combineOpeningClosingOperatorsAtStartEndIndexesAndReturnIfCombined();
    void traverse(AggregatorTraverseSteps const traverseSteps);
    bool traverseOnOperatorIndexesAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps, OperatorInputType const operatorInputType);
    bool performTraverseStepsAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex,
        OperatorInputType const operatorInputType);
    bool performTraverseStepsWithBinaryOperationAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex);
    bool performTraverseStepsWithUnaryOperationAndReturnIfContinue(
        AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex);
    Indexes getNextOperatorIndexes(OperatorInputType const operatorInputType) const;

    bool buildExpressionWithBinaryOperationAndReturnIfBuilt(int const index);
    bool buildExpressionWithUnaryOperationAndReturnIfBuilt(int const index);
    bool simplifyBinaryOperationAndReturnIfSimplified(int const index);
    bool simplifyUnaryOperationAndReturnIfSimplified(int const index);
    bool hasNoValueBeforeThisIndex(int const index) const;

    void eraseAndThenInsert(int const firstIndex, int const secondIndex, Term const& term);
    void eraseTermsInclusive(int const firstIndex, int const secondIndex);
    void insertTerm(int const index, Term const& term);

    int m_startIndex;
    int m_endIndex;
    Terms m_terms;
};

}  // namespace booleanAlgebra

}  // namespace alba
