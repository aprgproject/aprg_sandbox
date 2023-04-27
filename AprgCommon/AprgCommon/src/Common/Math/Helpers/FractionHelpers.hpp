#pragma once

#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <vector>

namespace alba::mathHelper {

template <typename NumberType>
struct FractionDetails {
    static_assert(typeHelper::isIntegralType<NumberType>(), "NumberType must be an integer");
    static_assert(typeHelper::isUnsignedType<NumberType>(), "NumberType must be a Unsigned Type");
    using SignType = typeHelper::GetSignedType<NumberType>;

    SignType sign;
    NumberType numerator;
    NumberType denominator;
};

template <typename NumeratorType, typename DenominatorType, typename GcfType>
void changeFractionToSimplestForm(NumeratorType& numerator, DenominatorType& denominator) {
    static_assert(typeHelper::isIntegralType<NumeratorType>(), "NumeratorType must be an integer");
    static_assert(typeHelper::isIntegralType<DenominatorType>(), "DenominatorType must be an integer");
    static_assert(typeHelper::isIntegralType<GcfType>(), "GcfType must be an integer");
    static_assert(typeHelper::isSignedType<NumeratorType>(), "NumeratorType must be a signed type");

    GcfType gcf = getGreatestCommonFactor<GcfType>(numerator, denominator);
    if (gcf != 0) {
        numerator = static_cast<NumeratorType>(numerator / gcf);
        denominator = static_cast<DenominatorType>(denominator / gcf);
        numerator = getAbsoluteValue(numerator) * getSign(numerator) * getSign(denominator);
        denominator = getAbsoluteValue(denominator);
    }
}

template <typename NumberType>
void changeFractionToSimplestFormForUnsigned(NumberType& numerator, NumberType& denominator) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    static_assert(typeHelper::isUnsignedType<NumberType>(), "Number type must be unsigned");

    NumberType gcf = getGreatestCommonFactor(numerator, denominator);
    if (gcf != 0) {
        numerator /= gcf;
        denominator /= gcf;
    }
}

template <typename NumberType>
void changeFractionToSimplestFormForSigned(NumberType& numerator, NumberType& denominator) {
    static_assert(typeHelper::isIntegralType<NumberType>(), "Number type must be an integer");
    static_assert(std::is_signed<NumberType>(), "Number type must be signed");

    NumberType gcf = getGreatestCommonFactor(numerator, denominator);
    if (gcf != 0) {
        numerator /= gcf;
        denominator /= gcf;
        numerator = getAbsoluteValue(numerator) * getSign(numerator) * getSign(denominator);
        denominator = getAbsoluteValue(denominator);
    }
}

template <typename NumeratorType>
NumeratorType getPartialNumerator(
    double const doubleValue, double& fractionalPart, double& doubleValueForNextIteration) {
    static_assert(typeHelper::isIntegralType<NumeratorType>(), "Number type must be an integer");

    double absoluteValueOfDouble = getAbsoluteValue(doubleValue);
    fractionalPart = getFractionalPartInDouble(absoluteValueOfDouble);
    doubleValueForNextIteration = 1 / fractionalPart;
    return static_cast<NumeratorType>(absoluteValueOfDouble);
}

template <typename NumberType>
FractionDetails<NumberType> getFractionFromPartialNumerators(
    std::vector<NumberType> const& calculatedPartialNumerators, bool& isBeyondUnsignedIntegerLimits) {
    double numerator(0), denominator(0);
    if (!calculatedPartialNumerators.empty()) {
        numerator = calculatedPartialNumerators.back();
        denominator = 1;
        for (auto itPartialNumerator = calculatedPartialNumerators.crbegin() + 1;
             itPartialNumerator != calculatedPartialNumerators.crend(); itPartialNumerator++) {
            double previousNumerator = numerator;
            numerator = (*itPartialNumerator * numerator) + denominator;
            denominator = previousNumerator;
            isBeyondUnsignedIntegerLimits =
                isValueBeyondLimits<NumberType>(numerator) || isValueBeyondLimits<NumberType>(denominator);
            if (isBeyondUnsignedIntegerLimits) {
                break;
            }
        }
    }
    return FractionDetails<NumberType>{
        1, getIntegerAfterRoundingADoubleValue<NumberType>(numerator),
        getIntegerAfterRoundingADoubleValue<NumberType>(denominator)};
}

template <typename NumberType>
FractionDetails<NumberType> getBestFractionDetailsForDoubleValue(double const doubleValue) {
    constexpr double tolerance(1E-12);
    FractionDetails<NumberType> result{1, 0, 1};

    std::vector<NumberType> partialNumerators;
    double fractionalPart(getAbsoluteValue(doubleValue)), doubleValueForNextIteration(doubleValue);
    bool isBeyondUnsignedIntegerLimits(false);
    while (fractionalPart > tolerance && !isBeyondUnsignedIntegerLimits) {
        partialNumerators.emplace_back(
            getPartialNumerator<NumberType>(doubleValueForNextIteration, fractionalPart, doubleValueForNextIteration));
        result = getFractionFromPartialNumerators(partialNumerators, isBeyondUnsignedIntegerLimits);
    }
    if (isBeyondUnsignedIntegerLimits) {
        partialNumerators.pop_back();
        result = getFractionFromPartialNumerators(partialNumerators, isBeyondUnsignedIntegerLimits);
    }
    result.sign = getSign(doubleValue);
    return result;
}

}  // namespace alba::mathHelper
