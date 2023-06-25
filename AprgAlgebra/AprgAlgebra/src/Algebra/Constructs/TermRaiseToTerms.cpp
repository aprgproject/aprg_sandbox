#include "TermRaiseToTerms.hpp"

#include <Algebra/Constructs/PolynomialRaiseToAnUnsignedInt.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <algorithm>

using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace algebra {

TermRaiseToTerms::TermRaiseToTerms()
    : m_shouldSimplifyToFactors(false),
      m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(false),
      m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(false) {}

TermRaiseToTerms::TermRaiseToTerms(TermsWithDetails const& termsInRaiseToPowerExpression)
    : m_shouldSimplifyToFactors(false),
      m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(false),
      m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(false) {
    initializeUsingTermsInRaiseToPowerExpression(termsInRaiseToPowerExpression);
}

TermRaiseToTerms::TermRaiseToTerms(Term const& base, Terms const& exponents)
    : m_base(base),
      m_exponents(),
      m_shouldSimplifyToFactors(false),
      m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(false),
      m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(false) {
    initializeExponentsInTerms(exponents);
}

TermRaiseToTerms::TermRaiseToTerms(Term const& base, Term const& exponent)
    : m_base(base),
      m_exponents{TermWithDetails(exponent, TermAssociationType::Positive)},
      m_shouldSimplifyToFactors(false),
      m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(false),
      m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(false) {}

bool TermRaiseToTerms::isEmpty() const { return m_base.isEmpty(); }

bool TermRaiseToTerms::doesEvenExponentCancellationHappen() const {
    bool result(false);
    AlbaNumbers exponentValues;
    for (TermWithDetails const& exponentWithDetails : m_exponents) {
        Term const& exponent(getTermConstReferenceFromUniquePointer(exponentWithDetails.baseTermPointer));
        AlbaNumber exponentValue(getConstantFactor(exponent));
        if (exponentWithDetails.hasNegativeAssociation()) {
            exponentValue = exponentValue ^ -1;
        }
        exponentValues.emplace_back(exponentValue);
    }
    bool hasAnyNumeratorEven(false);
    bool hasAnyDenominatorEven(false);
    for (AlbaNumber const& exponentValue : exponentValues) {
        AlbaNumber::FractionData fractionData(exponentValue.getFractionData());
        hasAnyNumeratorEven = hasAnyNumeratorEven || isEven(getAbsoluteValue<int>(fractionData.numerator));
        hasAnyDenominatorEven = hasAnyDenominatorEven || isEven(fractionData.denominator);
    }
    result = hasAnyNumeratorEven && hasAnyDenominatorEven;
    return result;
}

Term TermRaiseToTerms::getCombinedTerm() const { return getCombinedBaseAndExponents(); }

Term TermRaiseToTerms::getCombinedExponents() const {
    Term exponentCombinedTerm;
    accumulateTermsForMultiplicationAndDivision(exponentCombinedTerm, m_exponents);
    return exponentCombinedTerm;
}

Term const& TermRaiseToTerms::getBase() const { return m_base; }

TermsWithDetails const& TermRaiseToTerms::getExponents() const { return m_exponents; }

Term& TermRaiseToTerms::getBaseReference() { return m_base; }

void TermRaiseToTerms::setBase(Term const& base) { m_base = base; }

void TermRaiseToTerms::setBaseAndExponent(Term const& base, Term const& exponent) {
    m_base = base;
    m_exponents.clear();
    m_exponents.emplace_back(exponent, TermAssociationType::Positive);
}

void TermRaiseToTerms::setAsShouldSimplifyToFactors(bool const shouldSimplifyToFactors) {
    m_shouldSimplifyToFactors = shouldSimplifyToFactors;
}

void TermRaiseToTerms::setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(bool const shouldSimplify) {
    m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt = shouldSimplify;
}

void TermRaiseToTerms::setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(
    bool const shouldSimplify) {
    m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase = shouldSimplify;
}

void TermRaiseToTerms::simplify() {
    simplifyByCheckingPolynomialRaiseToAnUnsignedIntIfNeeded();
    simplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseIfNeeded();
    simplifyBaseAndExponents();
}

void TermRaiseToTerms::simplifyByCheckingPolynomialRaiseToAnUnsignedIntIfNeeded() {
    if (m_shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt && canBeConvertedToPolynomial(m_base)) {
        PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(createPolynomialIfPossible(m_base));
        if (!polynomialRaiseToAnUnsignedInt.isExponentOne()) {
            m_base = polynomialRaiseToAnUnsignedInt.getBase();
            m_exponents.emplace(
                m_exponents.begin(), Term(polynomialRaiseToAnUnsignedInt.getExponent()), TermAssociationType::Positive);
        }
    }
}

void TermRaiseToTerms::simplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBaseIfNeeded() {
    if (m_shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase &&
        doesEvenExponentCancellationHappen()) {
        m_base = simplifyAndConvertFunctionToSimplestTerm(abs(createOrCopyExpressionFromATerm(m_base)));
    }
}

void TermRaiseToTerms::simplifyBaseAndExponents() {
    Term exponentCombinedTerm;
    accumulateTermsForMultiplicationAndDivision(exponentCombinedTerm, m_exponents);

    m_exponents.clear();

    if (m_base.isConstant() && m_base.getConstantValueConstReference() == 0) {
    } else if (m_base.isConstant() && m_base.getConstantValueConstReference() == 1) {
    } else if (exponentCombinedTerm.isEmpty()) {
    } else if (exponentCombinedTerm.isConstant() && exponentCombinedTerm.getConstantValueConstReference() == 0) {
        m_base = 1;
    } else if (exponentCombinedTerm.isConstant() && exponentCombinedTerm.getConstantValueConstReference() == 1) {
    } else if (m_base.isConstant() && exponentCombinedTerm.isFunction()) {
        simplifyConstantRaiseToFunction(m_base, m_exponents, exponentCombinedTerm);
    } else if (canBeConvertedToMonomial(m_base) && exponentCombinedTerm.isConstant()) {
        simplifyMonomialRaiseToConstant(
            m_base, createMonomialIfPossible(m_base), exponentCombinedTerm.getConstantValueConstReference());
    } else if (m_base.isPolynomial() && !m_shouldSimplifyToFactors && isPositiveIntegerConstant(exponentCombinedTerm)) {
        int exponent = static_cast<int>(exponentCombinedTerm.getConstantValueConstReference().getInteger());
        simplifyPolynomialRaiseToPositiveInteger(m_base, createPolynomialIfPossible(m_base), exponent);
    } else if (
        !m_shouldSimplifyToFactors && isPositiveIntegerConstant(exponentCombinedTerm) && m_base.isExpression() &&
        OperatorLevel::AdditionAndSubtraction == m_base.getExpressionConstReference().getCommonOperatorLevel()) {
        int exponent = static_cast<int>(exponentCombinedTerm.getConstantValueConstReference().getInteger());
        simplifyAdditionAndSubtractionExpressionRaiseToPositiveInteger(
            m_base, m_base.getExpressionConstReference(), exponent);
    } else if (
        m_base.isConstant() && exponentCombinedTerm.isExpression() &&
        OperatorLevel::MultiplicationAndDivision ==
            exponentCombinedTerm.getExpressionConstReference().getCommonOperatorLevel()) {
        simplifyConstantRaiseToMultiplicationAndDivisionExpression(m_base, m_exponents, exponentCombinedTerm);
    } else {
        m_exponents.emplace_back(exponentCombinedTerm, TermAssociationType::Positive);
    }
}

void TermRaiseToTerms::simplifyConstantRaiseToFunction(
    Term& base, TermsWithDetails& exponents, Term const& exponentCombinedTerm) {
    Function const& functionObject(exponentCombinedTerm.getFunctionConstReference());
    string const& functionName(functionObject.getFunctionName());
    if ((getEAsATerm() == base && "ln" == functionName) || (Term(10) == base && "log" == functionName)) {
        base = getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference());
    } else {
        exponents.emplace_back(exponentCombinedTerm, TermAssociationType::Positive);
    }
}

void TermRaiseToTerms::simplifyMonomialRaiseToConstant(
    Term& base, Monomial const& monomialBase, AlbaNumber const& exponent) {
    Monomial result(monomialBase);
    result.raiseToPowerNumber(exponent);
    base = simplifyAndConvertMonomialToSimplestTerm(result);
}

void TermRaiseToTerms::simplifyPolynomialRaiseToPositiveInteger(
    Term& base, Polynomial const& polynomialBase, int const exponent) {
    Polynomial result(polynomialBase);
    result.raiseToUnsignedInteger(exponent);
    base = simplifyAndConvertPolynomialToSimplestTerm(result);
}

void TermRaiseToTerms::simplifyAdditionAndSubtractionExpressionRaiseToPositiveInteger(
    Term& base, Expression const& expressionBase, int const exponent) {
    Term result(1);
    Term termToMultiply(expressionBase);
    for (int i = 0; i < exponent; i++) {
        result = result * termToMultiply;
    }
    result.simplify();
    base = result;
}

void TermRaiseToTerms::simplifyConstantRaiseToMultiplicationAndDivisionExpression(
    Term& base, TermsWithDetails& exponents, Term const& exponentCombinedTerm) {
    TermsWithDetails termsWithDetails(
        exponentCombinedTerm.getExpressionConstReference().getTermsWithAssociation().getTermsWithDetails());
    for (int i = 0; i < static_cast<int>(termsWithDetails.size()); i++) {
        TermWithDetails const& exponentWithDetails(termsWithDetails[i]);
        Term const& exponent(getTermConstReferenceFromUniquePointer(exponentWithDetails.baseTermPointer));
        if (exponentWithDetails.hasPositiveAssociation() && exponent.isFunction()) {
            Function const& functionObject(exponent.getFunctionConstReference());            string const& functionName(functionObject.getFunctionName());
            if ((getEAsATerm() == base && "ln" == functionName) || (Term(10) == base && "log" == functionName)) {
                base = getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference());
                termsWithDetails.erase(termsWithDetails.begin() + i);                break;
            }
        }
    }
    exponents = termsWithDetails;
}

void TermRaiseToTerms::initializeUsingTermsInRaiseToPowerExpression(
    TermsWithDetails const& termsInRaiseToPowerExpression) {
    if (!termsInRaiseToPowerExpression.empty()) {
        m_base = getTermConstReferenceFromUniquePointer(termsInRaiseToPowerExpression[0].baseTermPointer);
        m_exponents.reserve(distance(termsInRaiseToPowerExpression.cbegin() + 1, termsInRaiseToPowerExpression.cend()));
        copy(
            termsInRaiseToPowerExpression.cbegin() + 1, termsInRaiseToPowerExpression.cend(),            back_inserter(m_exponents));
    }
}
void TermRaiseToTerms::initializeExponentsInTerms(Terms const& exponents) {
    transform(exponents.cbegin(), exponents.cend(), back_inserter(m_exponents), [](Term const& exponent) {
        return TermWithDetails(exponent, TermAssociationType::Positive);
    });
}

Term TermRaiseToTerms::getCombinedBaseAndExponents() const {
    Term combinedTerm;
    if (m_exponents.empty()) {
        combinedTerm = m_base;
    } else {
        Term exponent(getCombinedExponents());
        combinedTerm = convertExpressionToSimplestTerm(createExpressionIfPossible({m_base, "^", exponent}));
        if ((m_base.isConstant() || m_base.isVariable() || m_base.isMonomial()) && exponent.isConstant()) {
            combinedTerm.simplify();
        }
    }
    return combinedTerm;
}

}  // namespace algebra

}  // namespace alba
