#include "TermsAggregator.hpp"

#include <Algebra/Operations/PerformOperations.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace std;

namespace alba {

namespace algebra {

TermsAggregator::TermsAggregator(Terms const& terms) : m_startIndex(0), m_endIndex(0), m_terms(terms) {}

Terms const& TermsAggregator::getTermsConstReference() const { return m_terms; }

void TermsAggregator::buildExpressionFromTerms() { traverse(AggregatorTraverseSteps::BuildExpression); }

void TermsAggregator::simplifyTerms() { traverse(AggregatorTraverseSteps::Simplify); }

void TermsAggregator::traverse(AggregatorTraverseSteps const traverseSteps) {
    bool continueToCombine(true);
    while (continueToCombine) {
        updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
        bool continueToTraverse(true);
        while (continueToTraverse) {
            continueToTraverse =
                traverseOnOperatorIndexesAndReturnIfContinue(traverseSteps, OperatorInputType::UnaryOperation);
            if (!continueToTraverse) {
                continueToTraverse =
                    traverseOnOperatorIndexesAndReturnIfContinue(traverseSteps, OperatorInputType::BinaryOperation);
            }
        }
        continueToCombine = combineOpeningClosingOperatorsAtStartEndIndexesAndReturnIfCombined();
    }
}

void TermsAggregator::updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators() {
    m_startIndex = 0;
    m_endIndex = 0;
    if (!m_terms.empty()) {
        m_endIndex = m_terms.size() - 1;
    }
    for (int i = 0; i < static_cast<int>(m_terms.size()); i++) {
        Term const& term(m_terms[i]);
        if (term.isOperator()) {
            Operator const& operatorTerm(term.getAsOperator());
            if (operatorTerm.isOpeningGroupOperator()) {
                m_startIndex = i;
                m_endIndex = i;
            } else if (operatorTerm.isClosingGroupOperator()) {
                m_endIndex = i;
                break;
            }
        }
    }
}

bool TermsAggregator::combineOpeningClosingOperatorsAtStartEndIndexesAndReturnIfCombined() {
    bool isCombined(false);
    if (m_startIndex + 2 == m_endIndex && m_endIndex < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[m_startIndex]);
        Term const& term2(m_terms[m_startIndex + 1]);
        Term const& term3(m_terms[m_endIndex]);
        if (term1.isOperator() && term1.getAsOperator().isOpeningGroupOperator() &&
            isNonEmptyOrNonOperatorType(term2) && term3.isOperator() &&
            term3.getAsOperator().isClosingGroupOperator()) {
            Term termBeforeStart;
            if (m_startIndex >= 1) {
                termBeforeStart = m_terms[m_startIndex - 1];
            }
            if (m_startIndex >= 1 && termBeforeStart.isFunction()) {
                Function newFunction(termBeforeStart.getAsFunction());
                getTermReferenceFromBaseTerm(newFunction.getInputTermReference()) = term2;
                eraseAndThenInsert(m_startIndex - 1, m_endIndex, newFunction);
                isCombined = true;
            } else {
                eraseAndThenInsert(m_startIndex, m_endIndex, term2);
                isCombined = true;
            }
        }
    }
    return isCombined;
}

bool TermsAggregator::traverseOnOperatorIndexesAndReturnIfContinue(
    AggregatorTraverseSteps const traverseSteps, OperatorInputType const operatorInputType) {
    bool continueToTraverse(false);
    Indexes nextOperatorIndexes(getNextOperatorIndexes(operatorInputType));
    for (int const nextOperatorIndex : nextOperatorIndexes) {
        continueToTraverse =
            performTraverseStepsAndReturnIfContinue(traverseSteps, nextOperatorIndex, operatorInputType);
        if (continueToTraverse) {
            break;
        }
    }
    return continueToTraverse;
}

bool TermsAggregator::performTraverseStepsAndReturnIfContinue(
    AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex,
    OperatorInputType const operatorInputType) {
    bool continueToTraverse(false);
    if (OperatorInputType::UnaryOperation == operatorInputType) {
        continueToTraverse =
            performTraverseStepsWithUnaryOperationAndReturnIfContinue(traverseSteps, nextOperatorIndex);
    } else if (OperatorInputType::BinaryOperation == operatorInputType) {
        continueToTraverse =
            performTraverseStepsWithBinaryOperationAndReturnIfContinue(traverseSteps, nextOperatorIndex);
    }
    return continueToTraverse;
}

bool TermsAggregator::performTraverseStepsWithBinaryOperationAndReturnIfContinue(
    AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex) {
    bool continueToTraverse(true);
    if (AggregatorTraverseSteps::BuildExpression == traverseSteps) {
        continueToTraverse = buildExpressionWithBinaryOperationAndReturnIfBuilt(nextOperatorIndex);
    } else if (AggregatorTraverseSteps::Simplify == traverseSteps) {
        continueToTraverse = simplifyBinaryOperationAndReturnIfSimplified(nextOperatorIndex);
    }
    return continueToTraverse;
}

bool TermsAggregator::performTraverseStepsWithUnaryOperationAndReturnIfContinue(
    AggregatorTraverseSteps const traverseSteps, int const nextOperatorIndex) {
    bool continueToTraverse(true);
    if (AggregatorTraverseSteps::BuildExpression == traverseSteps) {
        continueToTraverse = buildExpressionWithUnaryOperationAndReturnIfBuilt(nextOperatorIndex);
    } else if (AggregatorTraverseSteps::Simplify == traverseSteps) {
        continueToTraverse = simplifyUnaryOperationAndReturnIfSimplified(nextOperatorIndex);
    }
    return continueToTraverse;
}

TermsAggregator::Indexes TermsAggregator::getNextOperatorIndexes(OperatorInputType const operatorInputType) const {
    Indexes operatorIndexes;
    multimap<int, int> operatorLevelToIndexMap;
    for (int i = m_startIndex; i < m_endIndex; i++) {
        Term const& term(m_terms[i]);
        if (term.isOperator()) {
            Operator const& operatorTerm(term.getAsOperator());
            if (operatorTerm.isSameOperatorInputType(operatorInputType)) {
                operatorLevelToIndexMap.emplace(getOperatorLevelInversePriority(operatorTerm.getOperatorLevel()), i);
            }
        }
    }
    for (auto const& [operatorLevel, index] : operatorLevelToIndexMap) {
        operatorIndexes.emplace_back(index);
    }
    return operatorIndexes;
}

bool TermsAggregator::buildExpressionWithBinaryOperationAndReturnIfBuilt(int const index) {
    bool isBuilt(false);
    if (index > 0 && index + 1 < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[index - 1]);
        Term const& term2(m_terms[index]);
        Term const& term3(m_terms[index + 1]);
        if (isNonEmptyOrNonOperatorType(term1) && term2.isOperator() && isNonEmptyOrNonOperatorType(term3)) {
            Expression newExpression(createOrCopyExpressionFromATerm(term1));
            Operator const& operatorTerm(term2.getAsOperator());
            if (operatorTerm.isAddition()) {
                newExpression.putTermWithAdditionIfNeeded(term3);
            } else if (operatorTerm.isSubtraction()) {
                newExpression.putTermWithSubtractionIfNeeded(term3);
            } else if (operatorTerm.isMultiplication()) {
                newExpression.putTermWithMultiplicationIfNeeded(term3);
            } else if (operatorTerm.isDivision()) {
                newExpression.putTermWithDivisionIfNeeded(term3);
            } else if (operatorTerm.isRaiseToPower()) {
                newExpression.putTermWithRaiseToPowerIfNeeded(term3);
            }
            eraseAndThenInsert(index - 1, index + 1, newExpression);
            isBuilt = true;
        }
    }
    return isBuilt;
}

bool TermsAggregator::buildExpressionWithUnaryOperationAndReturnIfBuilt(int const index) {
    bool isBuilt(false);
    if (index + 1 < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index + 1]);
        bool haveNoFirstValue(hasNoValueBeforeThisIndex(index));
        if (haveNoFirstValue && term1.isOperator() && isNonEmptyOrNonOperatorType(term2) &&
            OperatorLevel::AdditionAndSubtraction == term1.getAsOperator().getOperatorLevel()) {
            Expression newExpression;
            Operator const& operatorTerm(term1.getAsOperator());
            if (operatorTerm.isAddition()) {
                newExpression.putTermWithAdditionIfNeeded(term2);
            } else if (operatorTerm.isSubtraction()) {
                newExpression.putTermWithSubtractionIfNeeded(term2);
            }
            eraseAndThenInsert(index, index + 1, newExpression);
            isBuilt = true;
        }
    }
    return isBuilt;
}

bool TermsAggregator::simplifyBinaryOperationAndReturnIfSimplified(int const index) {
    bool isSimplified(false);
    if (index > 0 && index + 1 < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[index - 1]);
        Term const& term2(m_terms[index]);
        Term const& term3(m_terms[index + 1]);
        if (isNonEmptyOrNonOperatorType(term1) && term2.isOperator() && isNonEmptyOrNonOperatorType(term3)) {
            Term newTerm(performOperation(term2.getAsOperator(), term1, term3));
            eraseAndThenInsert(index - 1, index + 1, newTerm);
            isSimplified = true;
        }
    }
    return isSimplified;
}

bool TermsAggregator::simplifyUnaryOperationAndReturnIfSimplified(int const index) {
    bool isSimplified(false);
    if (index + 1 < static_cast<int>(m_terms.size())) {
        Term const& term1(m_terms[index]);
        Term const& term2(m_terms[index + 1]);
        bool haveNoFirstValue(hasNoValueBeforeThisIndex(index));
        if (haveNoFirstValue && term1.isOperator() && isNonEmptyOrNonOperatorType(term2) &&
            OperatorLevel::AdditionAndSubtraction == term1.getAsOperator().getOperatorLevel()) {
            Term newTerm(performOperation(term1.getAsOperator(), term2));
            eraseAndThenInsert(index, index + 1, newTerm);
            isSimplified = true;
        }
    }
    return isSimplified;
}

bool TermsAggregator::hasNoValueBeforeThisIndex(int const index) const {
    bool result(false);
    if (index == 0) {
        result = true;
    } else if (index - 1 < static_cast<int>(m_terms.size())) {
        result = !isNonEmptyOrNonOperatorType(m_terms[index - 1]);
    }
    return result;
}

void TermsAggregator::eraseAndThenInsert(int const firstIndex, int const secondIndex, Term const& term) {
    Term newTerm(term);
    eraseTermsInclusive(firstIndex, secondIndex);
    insertTerm(firstIndex, newTerm);
}

void TermsAggregator::eraseTermsInclusive(int const firstIndex, int const secondIndex) {
    bool isOutsideStartAndEndIndex(m_startIndex > firstIndex || m_endIndex < secondIndex);
    m_terms.erase(m_terms.cbegin() + firstIndex, m_terms.cbegin() + secondIndex + 1);
    if (isOutsideStartAndEndIndex) {
        updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
    } else {
        m_endIndex = m_endIndex - (secondIndex - firstIndex + 1);
    }
}

void TermsAggregator::insertTerm(int const index, Term const& term) {
    bool isOutsideStartAndEndIndex(m_startIndex > index || m_endIndex < index);
    m_terms.emplace(m_terms.cbegin() + index, term);
    if (isOutsideStartAndEndIndex) {
        updateStartIndexAndEndIndexAndCheckOpeningAndClosingOperators();
    } else {
        m_endIndex++;
    }
}

}  // namespace algebra

}  // namespace alba
