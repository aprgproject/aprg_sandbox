#include "RetrieveHelpers.hpp"

#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Retrieval/ExpressionAndFunctionsRetriever.hpp>
#include <Algebra/Retrieval/FunctionsRetriever.hpp>
#include <Algebra/Retrieval/SubTermsRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>

#include <algorithm>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba {

namespace algebra {

bool hasAnyFunctions(Term const& term) {
    FunctionsRetriever functionsRetriever([](Function const&) { return true; });
    functionsRetriever.retrieveFromTerm(term);
    return !functionsRetriever.getFunctions().empty();
}

bool hasAnyTrigonometricFunctions(Term const& term) {
    FunctionsRetriever functionsRetriever(
        [](Function const& functionObject) { return isTrigonometricFunction(functionObject); });
    functionsRetriever.retrieveFromTerm(term);
    return !functionsRetriever.getFunctions().empty();
}

bool isVariableFoundInTerm(Term const& term, string const& variableName) {
    VariableNamesRetriever retriever;
    retriever.retrieveFromTerm(term);
    VariableNamesSet const& variableNames(retriever.getVariableNames());
    return variableNames.find(variableName) != variableNames.cend();
}

AlbaNumber getCoefficientOfMonomialWithNoVariables(Polynomial const& polynomial) {
    AlbaNumber coefficientValue;
    for (Monomial const& monomial : polynomial.getMonomials()) {
        Monomial::VariablesToExponentsMap const& variableToExponentMap(monomial.getVariablesToExponentsMap());
        if (variableToExponentMap.empty()) {
            coefficientValue = monomial.getCoefficient();
            break;
        }
    }
    return coefficientValue;
}

AlbaNumber getCoefficientOfMonomialWithVariableOnly(Polynomial const& polynomial, string const& variableName) {
    AlbaNumber coefficientValue;
    for (Monomial const& monomial : polynomial.getMonomials()) {
        Monomial::VariablesToExponentsMap const& variableToExponentMap(monomial.getVariablesToExponentsMap());
        if (variableToExponentMap.size() == 1) {
            auto const& [variableNameFromMap, exponentFromMap] = *(variableToExponentMap.cbegin());
            if (variableNameFromMap == variableName) {
                coefficientValue = monomial.getCoefficient();
                break;
            }
        }
    }
    return coefficientValue;
}

VariableToValueMap getCoefficientsForVariablesOnly(Polynomial const& polynomial) {
    VariableToValueMap result;
    for (Monomial const& monomial : polynomial.getMonomials()) {
        Monomial::VariablesToExponentsMap const& variableToExponentMap(monomial.getVariablesToExponentsMap());
        if (variableToExponentMap.size() == 1) {
            auto const& [variableNameFromMap, exponentFromMap] = *(variableToExponentMap.cbegin());
            result.emplace(variableNameFromMap, monomial.getCoefficient());
        }
    }
    return result;
}

void retrieveTermsFromTermsWithDetails(Terms& terms, TermsWithDetails const& termsWithDetails) {
    terms.reserve(terms.size() + termsWithDetails.size());
    transform(
        termsWithDetails.cbegin(), termsWithDetails.cend(), back_inserter(terms),
        [](TermWithDetails const& termWithDetails) {
            return getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer);
        });
}

Terms retrieveSubExpressionsAndSubFunctions(Term const& term) {
    ExpressionAndFunctionsRetriever retriever;
    retriever.retrieveFromTerm(term);
    Terms result;
    for (Term const& retrievedTerm : retriever.getExpressionsAndFunctions()) {
        if ((retrievedTerm.isFunction() || retrievedTerm.isExpression()) && term != retrievedTerm) {
            result.emplace_back(retrievedTerm);
        }
    }
    return result;
}

Terms retrieveSubTerms(Term const& term) {
    SubTermsRetriever retriever;
    retriever.retrieveFromTerm(term);
    Terms result;
    for (Term const& retrievedTerm : retriever.getSubTerms()) {
        if (term != retrievedTerm) {
            result.emplace_back(retrievedTerm);
        }
    }
    return result;
}

TermsWithDetails retrieveTermsWithDetailsThatSatisfiesCondition(
    TermsWithDetails const& termsWithDetails, ConditionFunctionForTermsWithDetails const& conditionFunction) {
    TermsWithDetails result;
    for (TermWithDetails const& termWithDetails : termsWithDetails) {
        if (conditionFunction(termWithDetails)) {
            result.emplace_back(termWithDetails);
        }
    }
    return result;
}

}  // namespace algebra

}  // namespace alba
