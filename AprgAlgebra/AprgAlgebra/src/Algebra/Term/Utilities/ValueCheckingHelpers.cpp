#include "ValueCheckingHelpers.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba {

namespace algebra {

namespace {

NumberCheckingCondition IsDoubleCondition = [](AlbaNumber const& numberToCheck) -> bool {
    return numberToCheck.isDoubleType();
};

NumberCheckingCondition IsNanCondition = [](AlbaNumber const& numberToCheck) -> bool {
    return numberToCheck.isNotANumber();
};

NumberCheckingCondition IsNotARealFiniteNumberCondition = [](AlbaNumber const& numberToCheck) -> bool {
    return !numberToCheck.isARealFiniteValue();
};

NumberCheckingCondition IsPositiveOrNegativeInfinityCondition = [](AlbaNumber const& numberToCheck) -> bool {
    return numberToCheck.isPositiveOrNegativeInfinity();
};

}  // namespace

bool isValueSatisfyTheCondition(Term const& term, NumberCheckingCondition const& condition) {
    bool result(false);
    if (term.isConstant()) {
        result = isValueSatisfyTheCondition(term.getAsConstant(), condition);
    } else if (term.isMonomial()) {
        result = isValueSatisfyTheCondition(term.getAsMonomial(), condition);
    } else if (term.isPolynomial()) {
        result = isValueSatisfyTheCondition(term.getAsPolynomial(), condition);
    } else if (term.isExpression()) {
        result = isValueSatisfyTheCondition(term.getAsExpression(), condition);
    }
    return result;
}

bool isValueSatisfyTheCondition(Constant const& constant, NumberCheckingCondition const& condition) {
    return condition(constant.getNumber());
}

bool isValueSatisfyTheCondition(Monomial const& monomial, NumberCheckingCondition const& condition) {
    return isConstantOnly(monomial) && isValueSatisfyTheCondition(monomial.getCoefficient(), condition);
}

bool isValueSatisfyTheCondition(Polynomial const& polynomial, NumberCheckingCondition const& condition) {    return isOneMonomial(polynomial) && isValueSatisfyTheCondition(getFirstMonomial(polynomial), condition);
}

bool isValueSatisfyTheCondition(Expression const& expression, NumberCheckingCondition const& condition) {    bool result(false);
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    if (termsWithDetails.size() == 1) {
        result = isValueSatisfyTheCondition(
            getTermConstReferenceFromUniquePointer(termsWithDetails.front().baseTermPointer), condition);
    }
    return result;
}

bool doAnyNumbersSatisfyTheCondition(Term const& term, NumberCheckingCondition const& condition) {
    bool result(false);
    if (term.isConstant()) {
        result = condition(term.getAsNumber());
    } else if (term.isMonomial()) {
        result = doAnyNumbersSatisfyTheCondition(term.getAsMonomial(), condition);
    } else if (term.isPolynomial()) {
        result = doAnyNumbersSatisfyTheCondition(term.getAsPolynomial(), condition);
    } else if (term.isExpression()) {
        result = doAnyNumbersSatisfyTheCondition(term.getAsExpression(), condition);
    } else if (term.isFunction()) {
        result = doAnyNumbersSatisfyTheCondition(term.getAsFunction(), condition);
    }
    return result;
}

bool doAnyNumbersSatisfyTheCondition(Monomial const& monomial, NumberCheckingCondition const& condition) {
    bool result(condition(monomial.getCoefficient()));
    if (!result) {
        Monomial::VariablesToExponentsMap const& variableExponentMap(
            monomial.getVariablesToExponentsMap());
        result = any_of(
            variableExponentMap.cbegin(), variableExponentMap.cend(),
            [&](auto const& variableExponentsPair) { return condition(variableExponentsPair.second); });    }
    return result;
}

bool doAnyNumbersSatisfyTheCondition(Polynomial const& polynomial, NumberCheckingCondition const& condition) {
    Monomials const& monomials(polynomial.getMonomials());
    return any_of(monomials.cbegin(), monomials.cend(), [&](Monomial const& monomial) {
        return doAnyNumbersSatisfyTheCondition(monomial, condition);
    });}

bool doAnyNumbersSatisfyTheCondition(Expression const& expression, NumberCheckingCondition const& condition) {
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());    return any_of(termsWithDetails.cbegin(), termsWithDetails.cend(), [&](TermWithDetails const& termWithDetails) {
        return doAnyNumbersSatisfyTheCondition(
            getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer), condition);
    });
}

bool doAnyNumbersSatisfyTheCondition(Function const& function, NumberCheckingCondition const& condition) {
    return doAnyNumbersSatisfyTheCondition(function.getInputTerm(), condition);
}

bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term) { return term.isEmpty() || isTheValue(term, 0); }
bool willHaveNoEffectOnAdditionOrSubtraction(Expression const& expression) {
    return expression.isEmpty() || (expression.containsOnlyOnePositivelyAssociatedTerm() &&
                                    willHaveNoEffectOnAdditionOrSubtraction(
                                        getTermConstReferenceFromBaseTerm(expression.getFirstTerm())));
}

bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term) {    return term.isEmpty() || isTheValue(term, 1);
}

bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Expression const& expression) {
    return expression.isEmpty() || (expression.containsOnlyOnePositivelyAssociatedTerm() &&
                                    willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(
                                        getTermConstReferenceFromBaseTerm(expression.getFirstTerm())));
}

bool isTheValue(Term const& term, AlbaNumber const& number) {
    bool result(false);
    if (term.isConstant()) {
        result = isTheValue(term.getAsConstant(), number);
    } else if (term.isMonomial()) {
        result = isTheValue(term.getAsMonomial(), number);
    } else if (term.isPolynomial()) {
        result = isTheValue(term.getAsPolynomial(), number);
    } else if (term.isExpression()) {
        result = isTheValue(term.getAsExpression(), number);
    }
    return result;
}

bool isTheValue(Constant const& constant, AlbaNumber const& number) {
    return constant.getNumber() == number;
}

bool isTheValue(Monomial const& monomial, AlbaNumber const& number) {
    bool result(false);
    if (number == 0) {
        result = monomial.getCoefficient() == number;
    } else {
        result = isConstantOnly(monomial) && monomial.getCoefficient() == number;
    }
    return result;
}
bool isTheValue(Polynomial const& polynomial, AlbaNumber const& number) {
    bool result(false);
    if (number == 0) {        result = polynomial.isEmpty();
    } else {
        result = isOneMonomial(polynomial) && isTheValue(getFirstMonomial(polynomial), number);
    }
    return result;
}

bool isTheValue(Expression const& expression, AlbaNumber const& number) {
    bool result(false);
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    if (termsWithDetails.size() == 1) {
        result = isTheValue(getTermConstReferenceFromUniquePointer(termsWithDetails.front().baseTermPointer), number);
    }
    return result;
}

bool isNan(Term const& term) { return isValueSatisfyTheCondition(term, IsNanCondition); }

bool isNan(Constant const& constant) { return isValueSatisfyTheCondition(constant, IsNanCondition); }

bool isNan(Monomial const& monomial) { return isValueSatisfyTheCondition(monomial, IsNanCondition); }

bool isNan(Polynomial const& polynomial) { return isValueSatisfyTheCondition(polynomial, IsNanCondition); }

bool isNan(Expression const& expression) { return isValueSatisfyTheCondition(expression, IsNanCondition); }

bool isPositiveOrNegativeInfinity(Term const& term) {
    return isValueSatisfyTheCondition(term, IsPositiveOrNegativeInfinityCondition);
}

bool isPositiveOrNegativeInfinity(Constant const& constant) {
    return isValueSatisfyTheCondition(constant, IsPositiveOrNegativeInfinityCondition);
}

bool isPositiveOrNegativeInfinity(Monomial const& monomial) {
    return isValueSatisfyTheCondition(monomial, IsPositiveOrNegativeInfinityCondition);
}

bool isPositiveOrNegativeInfinity(Polynomial const& polynomial) {
    return isValueSatisfyTheCondition(polynomial, IsPositiveOrNegativeInfinityCondition);
}

bool isPositiveOrNegativeInfinity(Expression const& expression) {
    return isValueSatisfyTheCondition(expression, IsPositiveOrNegativeInfinityCondition);
}

bool isANegativeTerm(Term const& term) {
    bool result(false);
    if (term.isConstant()) {
        result = isANegativeConstant(term.getAsConstant());
    } else if (term.isMonomial()) {
        result = isANegativeMonomial(term.getAsMonomial());
    } else if (term.isPolynomial()) {
        result = isANegativePolynomial(term.getAsPolynomial());
    } else if (term.isExpression()) {
        result = isANegativeExpression(term.getAsExpression());
    }
    return result;
}

bool isANegativeConstant(Constant const& constant) { return constant.getNumber() < 0; }

bool isANegativeMonomial(Monomial const& monomial) { return monomial.getCoefficient() < 0; }

bool isANegativePolynomial(Polynomial const& polynomial) {
    bool result(false);
    Monomials const& monomials(polynomial.getMonomials());
    if (!monomials.empty()) {
        result = monomials.front().getCoefficient() < 0;
    }
    return result;
}
bool isANegativeExpression(Expression const& expression) {
    bool result(false);
    TermsWithDetails termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());    if (OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel()) {
        if (!termsWithDetails.empty()) {
            Term const& firstTerm(getTermConstReferenceFromUniquePointer(termsWithDetails.front().baseTermPointer));
            result = isANegativeTerm(firstTerm);
        }
    } else if (OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel()) {
        bool isNegative(false);
        for (TermWithDetails const& termWithDetails : termsWithDetails) {
            Term const& term(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
            isNegative = isNegative ^ isANegativeTerm(term);
        }
        result = isNegative;
    } else if (OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel()) {
        result = false;
    }
    return result;
}

bool isIntegerConstant(Term const& term) {
    return term.isConstant() && term.getAsNumber().isIntegerType();
}

bool isPositiveIntegerConstant(Term const& term) {
    return term.isConstant() && term.getAsNumber().isIntegerType() &&
           term.getAsNumber() >= 0;
}

bool isARealFiniteConstant(Term const& term) {
    bool result(false);
    if (term.isConstant()) {
        result = term.getAsNumber().isARealFiniteValue();
    }
    return result;
}
bool hasDoubleValues(Term const& term) { return doAnyNumbersSatisfyTheCondition(term, IsDoubleCondition); }

bool hasDoubleValues(Monomial const& monomial) { return doAnyNumbersSatisfyTheCondition(monomial, IsDoubleCondition); }
bool hasDoubleValues(Polynomial const& polynomial) {
    return doAnyNumbersSatisfyTheCondition(polynomial, IsDoubleCondition);
}

bool hasDoubleValues(Expression const& expression) {
    return doAnyNumbersSatisfyTheCondition(expression, IsDoubleCondition);
}

bool hasDoubleValues(Function const& function) { return doAnyNumbersSatisfyTheCondition(function, IsDoubleCondition); }

bool hasNan(Term const& term) { return doAnyNumbersSatisfyTheCondition(term, IsNanCondition); }

bool hasNan(Monomial const& monomial) { return doAnyNumbersSatisfyTheCondition(monomial, IsNanCondition); }

bool hasNan(Polynomial const& polynomial) { return doAnyNumbersSatisfyTheCondition(polynomial, IsNanCondition); }

bool hasNan(Expression const& expression) { return doAnyNumbersSatisfyTheCondition(expression, IsNanCondition); }

bool hasNan(Function const& function) { return doAnyNumbersSatisfyTheCondition(function, IsNanCondition); }

bool hasNonRealFiniteNumbers(Term const& term) {
    return doAnyNumbersSatisfyTheCondition(term, IsNotARealFiniteNumberCondition);
}

bool hasNonRealFiniteNumbers(Monomial const& monomial) {
    return doAnyNumbersSatisfyTheCondition(monomial, IsNotARealFiniteNumberCondition);
}

bool hasNonRealFiniteNumbers(Polynomial const& polynomial) {
    return doAnyNumbersSatisfyTheCondition(polynomial, IsNotARealFiniteNumberCondition);
}

bool hasNonRealFiniteNumbers(Expression const& expression) {
    return doAnyNumbersSatisfyTheCondition(expression, IsNotARealFiniteNumberCondition);
}

bool hasNonRealFiniteNumbers(Function const& function) {
    return doAnyNumbersSatisfyTheCondition(function, IsNotARealFiniteNumberCondition);
}

bool hasZero(Terms const& terms) {
    Terms::const_iterator it =
        find_if(terms.cbegin(), terms.cend(), [](Term const& term) { return isTheValue(term, 0); });
    return it != terms.cend();
}

bool hasNegativeExponentsWithVariable(Polynomial const& polynomial, string const& variableName) {
    bool result(false);
    for (Monomial const& monomial : polynomial.getMonomials()) {
        result = result || (monomial.getExponentForVariable(variableName) < 0);
        if (result) {
            break;        }
    }
    return result;
}
}  // namespace algebra

}  // namespace alba
