#pragma once

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Vector/MathVectorOfTerms.hpp>

#include <algorithm>

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

void simplifyForTermInVector(Term & term);

Term getDyOverDx(MathVectorOfTwoTerms const& termVector, std::string const& variableName);


template <unsigned int SIZE>
void simplifyForTermVector(
        MathVectorOfTerms<SIZE> & termVector)
{
    for(Term & term : termVector.getValuesReference())
    {
        simplifyForTermInVector(term);
    }
}

template <unsigned int SIZE> bool isContinuousAt(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value);
template <unsigned int SIZE> bool isDifferentiableAt(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value);
template <unsigned int SIZE> bool areOriginalAndDerivativeVectorsOrthogonal( MathVectorOfTerms<SIZE> const& termVector);
Term getDyOverDx(MathVectorOfTwoTerms const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getLengthOfArcDerivative(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getLengthOfArc(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getLengthOfArcFromStartToEnd(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, Term const& lowerValueTerm, Term const& higherValueTerm);
template <unsigned int SIZE> Term getCurvature(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getLimit(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& valueToApproach);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> differentiate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> integrate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getUnitTangentVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getUnitNormalVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getCurvatureVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);


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

template <unsigned int SIZE>
Term getLengthOfArcDerivative(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    return differentiate(termVector, variableName).getMagnitude();
}

template <unsigned int SIZE>
Term getLengthOfArc(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    Integration integration(variableName);
    return integration.integrate(getLengthOfArcDerivative(termVector, variableName));
}

template <unsigned int SIZE>
Term getLengthOfArcFromStartToEnd(
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
Term getCurvature(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    MathVectorOfTerms<SIZE> curvatureVector(getCurvatureVector(termVector, variableName));
    Term result(curvatureVector.getMagnitude());
    simplifyForTermInVector(result);
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
MathVectorOfTerms<SIZE> differentiateMultipleTimes(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName,
        unsigned int const numberOfTimes)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Values const& values(termVector.getValues());
    Differentiation differentiation(variableName);
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term)
    {
        return differentiation.differentiateMultipleTimes(term, numberOfTimes);
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
MathVectorOfTerms<SIZE> getUnitTangentVector(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    MathVectorOfTerms<SIZE> result(differentiate(termVector, variableName));
    result /= result.getMagnitude();
    simplifyForTermVector(result);
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getUnitNormalVector(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    MathVectorOfTerms<SIZE> result(differentiate(getUnitTangentVector(termVector, variableName), variableName));
    result /= result.getMagnitude();
    simplifyForTermVector(result);
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getCurvatureVector(
        MathVectorOfTerms<SIZE> const& termVector,
        std::string const& variableName)
{
    MathVectorOfTerms<SIZE> derivativeOfTermVector(differentiate(termVector, variableName));
    MathVectorOfTerms<SIZE> result(differentiate(getUnitTangentVector(termVector, variableName), variableName));
    result /= derivativeOfTermVector.getMagnitude();
    simplifyForTermVector(result);
    return result;
}

}

}

}
