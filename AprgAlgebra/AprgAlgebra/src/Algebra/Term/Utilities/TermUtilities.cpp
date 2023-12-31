#include "TermUtilities.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Mutation/NegationMutator.hpp>
#include <Algebra/Retrieval/FirstCoefficientRetriever.hpp>
#include <Algebra/Retrieval/NumberOfTermsRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Factorization;
using namespace std;

namespace alba {

namespace algebra {

bool isTermSimpler(Term const& supposeToBeComplicatedTerm, Term const& supposeToBeSimpleTerm) {
    return getNumberOfTerms(supposeToBeComplicatedTerm) > getNumberOfTerms(supposeToBeSimpleTerm);
}

bool isNegatedTermSimpler(Term const& term, Term const& negatedTerm) {
    FirstCoefficientRetriever firstCoefficientRetrieverForTerm;
    firstCoefficientRetrieverForTerm.retrieveFromTerm(term);

    return isTermSimpler(term, negatedTerm) || firstCoefficientRetrieverForTerm.getFirstCoefficient() < 0;
}

bool isNonEmptyOrNonOperatorType(Term const& term) {
    TermType termType(term.getTermType());
    return TermType::Empty != termType && TermType::Operator != termType;
}

bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term) {
    TermType termType(term.getTermType());
    return TermType::Empty != termType && TermType::Operator != termType && TermType::Expression != termType;
}

bool isARadicalTerm(Term const& term) {
    TermRaiseToANumber termRaiseToANumber(createTermRaiseToANumberFromTerm(term));
    return termRaiseToANumber.isRadical();
}

int getNumberOfTerms(Term const& term) {
    NumberOfTermsRetriever retriever;
    retriever.retrieveFromTerm(term);
    return retriever.getNumberOfTerms();
}

AlbaNumber getConstantFactor(Term const& term) {
    AlbaNumber result(1);
    if (term.isConstant()) {
        result = term.getAsNumber();
    } else if (term.isMonomial()) {
        result = term.getAsMonomial().getCoefficient();
    } else if (term.isPolynomial()) {
        Polynomials factors(factorizeCommonMonomial(term.getAsPolynomial()));
        for (Polynomial const& factor : factors) {
            if (isOneMonomial(factor)) {
                result *= getFirstMonomial(factor).getCoefficient();
            }
        }
    }
    return result;
}

AlbaNumber getDegree(Term const& term) {
    AlbaNumber result;
    if (term.isConstant()) {
        result = 0;
    }
    if (term.isVariable()) {
        result = 1;
    } else if (term.isMonomial()) {
        result = getDegree(term.getAsMonomial());
    } else if (term.isPolynomial()) {
        result = getMaxDegree(term.getAsPolynomial());
    } else if (term.isExpression()) {
        Expression const& expression(term.getAsExpression());
        TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
        if (OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel()) {
            AlbaNumber maxDegree(0);
            for (TermWithDetails const& termWithDetails : termsWithDetails) {
                Term const& term(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
                maxDegree = max(maxDegree, getDegree(term));
            }
            result = maxDegree;
        } else if (OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel()) {
            AlbaNumber sumDegree(0);
            for (TermWithDetails const& termWithDetails : termsWithDetails) {
                Term const& term(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
                sumDegree += getDegree(term);
            }
            result = sumDegree;
        } else if (OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel()) {
            result = ALBA_NUMBER_POSITIVE_INFINITY;
        }
    } else if (term.isFunction()) {
        if ("ln" == term.getAsFunction().getFunctionName()) {
            result = ALBA_NUMBER_NEGATIVE_INFINITY;
        } else {
            result = 0;
        }
    }
    return result;
}

AlbaNumberPairs evaluateAndGetInputOutputPair(
    AlbaNumbers const& numbers, string const& variableName, Term const& term) {
    AlbaNumberPairs result;
    SubstitutionOfVariablesToValues substitution;
    for (AlbaNumber const& number : numbers) {
        substitution.putVariableWithValue(variableName, number);
        Term substituteTerm(substitution.performSubstitutionTo(term));
        if (substituteTerm.isConstant()) {
            result.emplace_back(number, substituteTerm.getAsNumber());
        }
    }
    return result;
}

Term getPiAsATerm() { return ALBA_NUMBER_PI; }

Term getEAsATerm() { return ALBA_NUMBER_E; }

Term getPositiveInfinityAsATerm() { return ALBA_NUMBER_POSITIVE_INFINITY; }

Term getNegativeInfinityAsATerm() { return ALBA_NUMBER_NEGATIVE_INFINITY; }

Term convertPositiveTermIfNegative(Term const& term) {
    Term result;
    if (isANegativeTerm(term)) {
        result = negateTerm(term);
    } else {
        result = term;
    }
    return result;
}

Term negateTerm(Term const& term) {
    NegationMutator negationMutator;
    Term negatedTerm(term);
    negationMutator.mutateTerm(negatedTerm);
    return negatedTerm;
}

Term flipTerm(Term const& term) { return 1 / term; }

Term negateTermIfHasNegativeAssociation(TermWithDetails const& termWithDetails) {
    Term result(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
    if (termWithDetails.hasNegativeAssociation()) {
        result = negateTerm(result);
    }
    return result;
}

Term flipTermIfHasNegativeAssociation(TermWithDetails const& termWithDetails) {
    Term result(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
    if (termWithDetails.hasNegativeAssociation()) {
        result = 1 / result;
    }
    return result;
}

Term invertTerm(Term const& term, string const& variableName) {
    string newVariableName(createVariableNameForSubstitution(term));
    Equation equationToIsolate(newVariableName, "=", term);
    IsolationOfOneVariableOnEqualityEquation isolation(equationToIsolate);
    SubstitutionOfVariablesToTerms substitution{{newVariableName, variableName}};
    return substitution.performSubstitutionTo(isolation.getEquivalentTermByIsolatingAVariable(variableName));
}

Expression negateExpression(Expression const& expression) {
    NegationMutator negationMutator;
    Expression negatedExpression(expression);
    negationMutator.mutateExpression(negatedExpression);
    return negatedExpression;
}

}  // namespace algebra

}  // namespace alba
