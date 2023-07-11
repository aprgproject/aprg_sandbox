#include "TermsRaiseToExponents.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba {

namespace algebra {

template <typename ExponentType, typename BaseRaiseToExponentType>
TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::TermsRaiseToExponents() {}
template TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::TermsRaiseToExponents();
template TermsRaiseToExponents<Term, TermRaiseToTerms>::TermsRaiseToExponents();

template <typename ExponentType, typename BaseRaiseToExponentType>
TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::TermsRaiseToExponents(
    BaseToExponentMap const& baseToExponentMap)
    : m_baseToExponentMap(baseToExponentMap) {}
template TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::TermsRaiseToExponents(
    BaseToExponentMap const& baseToExponentMap);
template TermsRaiseToExponents<Term, TermRaiseToTerms>::TermsRaiseToExponents(
    BaseToExponentMap const& baseToExponentMap);

template <typename ExponentType, typename BaseRaiseToExponentType>
typename TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::BaseToExponentMap const&
TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::getBaseToExponentMap() const {
    return m_baseToExponentMap;
}
template TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::BaseToExponentMap const&
TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::getBaseToExponentMap() const;
template TermsRaiseToExponents<Term, TermRaiseToTerms>::BaseToExponentMap const&
TermsRaiseToExponents<Term, TermRaiseToTerms>::getBaseToExponentMap() const;

template <typename ExponentType, typename BaseRaiseToExponentType>
ExponentType TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::getExponentOfBase(Term const& base) const {
    ExponentType result;
    auto const& it = m_baseToExponentMap.find(base);
    if (it != m_baseToExponentMap.cend()) {
        result = it->second;
    }
    return result;
}
template AlbaNumber TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::getExponentOfBase(Term const& base) const;
template Term TermsRaiseToExponents<Term, TermRaiseToTerms>::getExponentOfBase(Term const& base) const;

template <typename ExponentType, typename BaseRaiseToExponentType>
Terms TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::getTermsInMultiplicationOperation() const {
    Terms result;
    for (auto const& baseExponentPair : m_baseToExponentMap) {
        result.emplace_back(convertToTerm(baseExponentPair.first, baseExponentPair.second));
    }
    return result;
}
template Terms TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::getTermsInMultiplicationOperation() const;
template Terms TermsRaiseToExponents<Term, TermRaiseToTerms>::getTermsInMultiplicationOperation() const;

template <typename ExponentType, typename BaseRaiseToExponentType>
TermsWithDetails TermsRaiseToExponents<
    ExponentType, BaseRaiseToExponentType>::getTermWithDetailsInMultiplicationAndDivisionOperation() const {
    TermsWithDetails result;
    for (auto const& baseExponentPair : m_baseToExponentMap) {
        Term const& base(baseExponentPair.first);
        ExponentType const& exponent(baseExponentPair.second);
        if (isNegative(exponent)) {
            result.emplace_back(convertToTerm(base, exponent * -1), TermAssociationType::Negative);
        } else {
            result.emplace_back(convertToTerm(base, exponent), TermAssociationType::Positive);
        }
    }
    return result;
}
template TermsWithDetails
TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::getTermWithDetailsInMultiplicationAndDivisionOperation() const;
template TermsWithDetails
TermsRaiseToExponents<Term, TermRaiseToTerms>::getTermWithDetailsInMultiplicationAndDivisionOperation() const;

template <typename ExponentType, typename BaseRaiseToExponentType>
Term TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::getCombinedTerm() const {
    TermsWithDetails termsWithDetails(getTermWithDetailsInMultiplicationAndDivisionOperation());
    if (termsWithDetails.empty()) {
        termsWithDetails.emplace_back(Term(1), TermAssociationType::Positive);
    }
    return convertExpressionToSimplestTerm(Expression(OperatorLevel::MultiplicationAndDivision, termsWithDetails));
}
template Term TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::getCombinedTerm() const;
template Term TermsRaiseToExponents<Term, TermRaiseToTerms>::getCombinedTerm() const;

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::addExponents(
    TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType> const& termsRaiseToNumbers) {
    for (auto const& baseExponentPair : termsRaiseToNumbers.m_baseToExponentMap) {
        m_baseToExponentMap[baseExponentPair.first] += baseExponentPair.second;
    }
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::addExponents(
    TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber> const& termsRaiseToNumbers);
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::addExponents(
    TermsRaiseToExponents<Term, TermRaiseToTerms> const& termsRaiseToNumbers);

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::subtractExponents(
    TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType> const& termsRaiseToNumbers) {
    for (auto const& baseExponentPair : termsRaiseToNumbers.m_baseToExponentMap) {
        m_baseToExponentMap[baseExponentPair.first] -= baseExponentPair.second;
    }
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::subtractExponents(
    TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber> const& termsRaiseToNumbers);
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::subtractExponents(
    TermsRaiseToExponents<Term, TermRaiseToTerms> const& termsRaiseToNumbers);

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::multiplyToExponents(ExponentType const& exponent) {
    for (auto& baseExponentPair : m_baseToExponentMap) {
        baseExponentPair.second *= exponent;
    }
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::multiplyToExponents(AlbaNumber const& exponent);
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::multiplyToExponents(Term const& exponent);

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::putTerm(
    Term const& term, TermAssociationType const association) {
    int sign = (association == TermAssociationType::Positive) ? 1 : -1;
    if (canBeConvertedToMonomial(term)) {
        Monomial monomial(createMonomialIfPossible(term));
        AlbaNumber const& constant(monomial.getCoefficient());
        if (constant != 1) {
            if (constant.isFractionType()) {
                AlbaNumber::FractionData fractionData(constant.getFractionData());                if (fractionData.numerator != 1) {
                    m_baseToExponentMap[Term(fractionData.numerator)] += ExponentType(sign);
                }
                if (fractionData.denominator != 1) {                    m_baseToExponentMap[Term(fractionData.denominator)] += ExponentType(sign * -1);
                }
            } else {
                m_baseToExponentMap[Term(constant)] += ExponentType(sign);
            }
        }
        for (auto const& variableExponentPair : monomial.getVariablesToExponentsMap()) {
            m_baseToExponentMap[Term(variableExponentPair.first)] += ExponentType(variableExponentPair.second * sign);
        }
    } else {        putTermUsingBaseToExponentType(term, sign);
    }
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::putTerm(    Term const& term, TermAssociationType const association);
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::putTerm(
    Term const& term, TermAssociationType const association);

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::putTerms(
    Terms const& terms, TermAssociationType const association) {
    for (Term const& term : terms) {
        putTerm(term, association);
    }
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::putTerms(
    Terms const& terms, TermAssociationType const association);
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::putTerms(
    Terms const& terms, TermAssociationType const association);

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::setBaseAndExponent(
    Term const& base, ExponentType const& exponent) {
    m_baseToExponentMap[base] = exponent;
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::setBaseAndExponent(
    Term const& base, AlbaNumber const& exponent);
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::setBaseAndExponent(Term const& base, Term const& exponent);

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::removeItemWithBase(Term const& base) {
    m_baseToExponentMap.erase(base);
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::removeItemWithBase(Term const& base);
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::removeItemWithBase(Term const& base);

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::clear() {
    m_baseToExponentMap.clear();
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::clear();
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::clear();

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::simplify() {
    removeItemsWithExponentsZero();
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::simplify();
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::simplify();

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::removeItemsWithExponentsZero() {
    for (auto it = m_baseToExponentMap.begin(); it != m_baseToExponentMap.end();) {
        if (isTheValue(it->second, 0)) {
            m_baseToExponentMap.erase(it);
            it = m_baseToExponentMap.begin();
        } else {
            it++;
        }
    }
}
template void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::removeItemsWithExponentsZero();
template void TermsRaiseToExponents<Term, TermRaiseToTerms>::removeItemsWithExponentsZero();

template <typename ExponentType, typename BaseRaiseToExponentType>
Term TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::convertToTerm(
    Term const& base, ExponentType const& exponent) const {
    Term result;
    if (exponent == ExponentType(1)) {
        result = base;
    } else {
        result = BaseRaiseToExponentType(base, exponent).getCombinedTerm();
    }
    return result;
}
template Term TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::convertToTerm(
    Term const& base, AlbaNumber const& exponent) const;
template Term TermsRaiseToExponents<Term, TermRaiseToTerms>::convertToTerm(
    Term const& base, Term const& exponent) const;

template <typename ExponentType, typename BaseRaiseToExponentType>
void TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::putTermUsingBaseToExponentType(
    Term const& term, int const sign) {}
template <>
void TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::putTermUsingBaseToExponentType(
    Term const& term, int const sign) {
    TermRaiseToANumber termRaiseToExponent(createTermRaiseToANumberFromTerm(term));
    m_baseToExponentMap[termRaiseToExponent.getBase()] += termRaiseToExponent.getExponent() * sign;
}
template <>
void TermsRaiseToExponents<Term, TermRaiseToTerms>::putTermUsingBaseToExponentType(Term const& term, int const sign) {
    TermRaiseToTerms termRaiseToExponent(createTermRaiseToTermsFromTerm(term));
    m_baseToExponentMap[termRaiseToExponent.getBase()] += Term(termRaiseToExponent.getCombinedExponents() * sign);
}

template <typename ExponentType, typename BaseRaiseToExponentType>
bool TermsRaiseToExponents<ExponentType, BaseRaiseToExponentType>::isNegative(ExponentType const&) const {
    return false;
}
template <>
bool TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>::isNegative(AlbaNumber const& exponent) const {
    return exponent < 0;
}
template <>
bool TermsRaiseToExponents<Term, TermRaiseToTerms>::isNegative(Term const& exponent) const {
    return isANegativeTerm(exponent);
}

}  // namespace algebra

}  // namespace alba
