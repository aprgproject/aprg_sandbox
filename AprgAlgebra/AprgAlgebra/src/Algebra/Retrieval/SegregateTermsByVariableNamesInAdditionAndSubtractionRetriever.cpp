#include "SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever.hpp"

#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::
    SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever(strings const& variableNames)
    : m_variableNameToTermMap(), m_termWithMultipleVariableNames(), m_remainingTerm() {
    initializeWithVariableNames(variableNames);
}

SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::VariableNameToTermMap const&
SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::getVariableNameToTermMap() const {
    return m_variableNameToTermMap;
}

Term const& SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::getTermWithMultipleVariableNames() const {
    return m_termWithMultipleVariableNames;
}

Term const& SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::getRemainingTerm() const {
    return m_remainingTerm;
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromConstant(Constant const& constant) {
    m_remainingTerm += Term(constant);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromVariable(Variable const& variable) {
    int numberOfTimesFound(0);
    string lastVariableNameFound;
    for (auto& variableNameAndTermPair : m_variableNameToTermMap) {
        if (variableNameAndTermPair.first == variable.getVariableName()) {
            lastVariableNameFound = variableNameAndTermPair.first;
            numberOfTimesFound++;
        }
    }
    saveTerm(Term(variable), numberOfTimesFound, lastVariableNameFound);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromMonomial(Monomial const& monomial) {
    int numberOfTimesFound(0);
    string lastVariableNameFound;
    for (auto& variableNameAndTermPair : m_variableNameToTermMap) {
        if (monomial.getExponentForVariable(variableNameAndTermPair.first) != 0) {
            lastVariableNameFound = variableNameAndTermPair.first;
            numberOfTimesFound++;
        }
    }
    saveTerm(Term(monomial), numberOfTimesFound, lastVariableNameFound);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromPolynomial(
    Polynomial const& polynomial) {
    for (Monomial const& monomial : polynomial.getMonomialsConstReference()) {
        retrieveFromMonomial(monomial);
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromExpression(
    Expression const& expression) {
    if (OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel()) {
        for (TermWithDetails const& termWithDetails : expression.getTermsWithAssociation().getTermsWithDetails()) {
            if (termWithDetails.hasPositiveAssociation()) {
                retrieveFromTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
            } else {
                retrieveFromTerm(negateTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer)));
            }
        }
    } else {
        int numberOfTimesFound(0);
        string lastVariableNameFound;
        VariableNamesRetriever variableNamesRetriever;
        variableNamesRetriever.retrieveFromExpression(expression);
        VariableNamesSet const& namesInExpression(variableNamesRetriever.getSavedData());
        for (auto& variableNameAndTermPair : m_variableNameToTermMap) {
            if (namesInExpression.find(variableNameAndTermPair.first) != namesInExpression.cend()) {
                lastVariableNameFound = variableNameAndTermPair.first;
                numberOfTimesFound++;
            }
        }
        saveTerm(Term(expression), numberOfTimesFound, lastVariableNameFound);
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromFunction(
    Function const& functionObject) {
    int numberOfTimesFound(0);
    string lastVariableNameFound;
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromFunction(functionObject);
    VariableNamesSet const& namesInFunction(variableNamesRetriever.getSavedData());
    for (auto& variableNameAndTermPair : m_variableNameToTermMap) {
        if (namesInFunction.find(variableNameAndTermPair.first) != namesInFunction.cend()) {
            lastVariableNameFound = variableNameAndTermPair.first;
            numberOfTimesFound++;
        }
    }
    saveTerm(Term(functionObject), numberOfTimesFound, lastVariableNameFound);
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::retrieveFromTerm(Term const& term) {
    if (term.isConstant()) {
        retrieveFromConstant(term.getConstantConstReference());
    } else if (term.isVariable()) {
        retrieveFromVariable(term.getVariableConstReference());
    } else if (term.isMonomial()) {
        retrieveFromMonomial(term.getMonomialConstReference());
    } else if (term.isPolynomial()) {
        retrieveFromPolynomial(term.getPolynomialConstReference());
    } else if (term.isExpression()) {
        retrieveFromExpression(term.getExpressionConstReference());
    } else if (term.isFunction()) {
        retrieveFromFunction(term.getFunctionConstReference());
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::initializeWithVariableNames(
    strings const& namesInOrder) {
    for (string const& name : namesInOrder) {
        m_variableNameToTermMap.emplace(name, Term());
    }
}

void SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever::saveTerm(
    Term const& term, int numberOfTimesFound, string const& variableName) {
    if (numberOfTimesFound == 0) {
        m_remainingTerm += term;
    } else if (numberOfTimesFound == 1) {
        m_variableNameToTermMap[variableName] += term;
    } else {
        m_termWithMultipleVariableNames += term;
    }
}

}  // namespace algebra

}  // namespace alba
