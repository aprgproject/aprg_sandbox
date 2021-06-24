#pragma once

#include <Equation/Term/Term.hpp>
#include <Optional/AlbaOptional.hpp>

namespace alba
{

namespace equation
{

class TermsAggregator
{
public:
    enum class AggregatorTraverseSteps
    {
        BuildExpression,
        Simplify
    };
    using Indexes=std::vector<unsigned int>;

    TermsAggregator(Terms const& terms);

    Terms const& getTermsConstReference() const;

    void buildExpressionFromTerms();
    void simplifyTerms();


private:
    void updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
    bool combineOpeningClosingOperatorsAtStartEndIndexesAndReturnIfCombined();
    void traverse(AggregatorTraverseSteps const traverseOperation);
    bool traverseOnOperatorIndexesAndReturnIfContinue(
            AggregatorTraverseSteps const traverseSteps,
            OperatorInputType const operatorInputType);
    bool performTraverseStepsAndReturnIfContinue(
            AggregatorTraverseSteps const traverseSteps,
            unsigned int const nextOperatorIndex,
            OperatorInputType const operatorInputType);
    bool performTraverseStepsWithBinaryOperationAndReturnIfContinue(
            AggregatorTraverseSteps const traverseSteps,
            unsigned int const nextOperatorIndex);
    bool performTraverseStepsWithUnaryOperationAndReturnIfContinue(
            AggregatorTraverseSteps const traverseSteps,
            unsigned int const nextOperatorIndex);
    Indexes getNextOperatorIndexes(OperatorInputType const operatorInputType) const;

    bool buildExpressionWithBinaryOperationAndReturnIfBuilt(unsigned int const index);
    bool buildExpressionWithUnaryOperationAndReturnIfBuilt(unsigned int const index);
    bool simplifyBinaryOperationAndReturnIfSimplified(unsigned int const index);
    bool simplifyUnaryOperationAndReturnIfSimplified(unsigned int const index);
    bool hasNoValueBeforeThisIndex(unsigned int const index);

    void eraseAndThenInsert(
            unsigned int const firstIndex,
            unsigned int const secondIndex,
            Term const newTerm);
    void eraseTermsInclusive(
            unsigned int const firstIndex,
            unsigned int const secondIndex);
    void insertTerm(
            unsigned int const index,
            Term const& term);

    unsigned int m_startIndex;
    unsigned int m_endIndex;
    Terms m_terms;
};

}

}
