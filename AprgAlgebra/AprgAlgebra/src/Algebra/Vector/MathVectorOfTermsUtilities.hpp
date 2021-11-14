#pragma once

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Vector/MathVectorOfTerms.hpp>

#include <algorithm>

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

Term getDyOverDx(MathVectorOfTwoTerms const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> differentiate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getLimit(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& valueToApproach);


template <unsigned int SIZE>
bool isContinuousAt(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        AlbaNumber const& value)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    Values const& values(termVector.getValues());
    return std::all_of(values.cbegin(), values.cend(), [&](Term const& term)
    {
        return isContinuousAt(term, variableName, value, LimitAtAValueApproachType::BothSides);
    });
}

template <unsigned int SIZE>
bool isDifferentiableAt(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        AlbaNumber const& value)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    Values const& values(termVector.getValues());
    return std::all_of(values.cbegin(), values.cend(), [&](Term const& term)
    {
        return isDifferentiableAt(term, variableName, value);
    });
}

template <unsigned int SIZE>
bool areOriginalAndDerivativeVectorsOrthogonal(
        MathVectorOfTerms<SIZE> const& termVector)
{
    return termVector.getMagnitude().isConstant();
}

Term getDyOverDx(
        MathVectorOfTwoTerms const& termVector,
        std::string const& variableName)
{
    MathVectorOfTwoTerms derivative(differentiate<2U>(termVector, variableName));
    Term result(derivative.getValueAt(1)/derivative.getValueAt(0));
    result.simplify();
    return result;
}

template <unsigned int SIZE>
Term getLengthOfArc(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    MathVectorOfTerms<SIZE> derivative(differentiate(termVector, variableName));
    Integration integration(variableName);
    return integration.integrate(derivative.getMagnitude());
}

template <unsigned int SIZE>
Term getLengthOfArcFromStartValueToEndValue(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    return evaluateTermsAndGetDifference(
                getLengthOfArc(termVector, variableName),
                variableName,
                lowerValueTerm,
                higherValueTerm);
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> differentiate(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Values const& values(termVector.getValues());
    Differentiation differentiation(variableName);
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term)
    {
        return differentiation.differentiate(term);
    });
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> integrate(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Values const& values(termVector.getValues());
    Integration integration(variableName);
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term)
    {
        return integration.integrate(term);
    });
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getLimit(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        AlbaNumber const& valueToApproach)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Values const& values(termVector.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term)
    {
        return getLimit(term, variableName, valueToApproach);
    });
    return result;
}

}

}

}
