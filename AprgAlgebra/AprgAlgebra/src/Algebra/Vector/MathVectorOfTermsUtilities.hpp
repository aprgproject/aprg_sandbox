#pragma once

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Retrieval/SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Vector/VectorTypes.hpp>
#include <Math/Angle/AlbaAngle.hpp>

#include <algorithm>

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

void simplifyForTermInVector(Term & term);

Term getDyOverDx(MathVectorOfTwoTerms const& termVector, std::string const& variableName);
Term getDirectionalDerivativeInTwoDimensions(Term const& term, ArrayOfTwoStrings const& coordinateVariables, AlbaAngle const& angleOfDirection);
Term getDirectionalDerivativeInThreeDimensions(Term const& term, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeAngles const& coordinateAngles);
MathVectorOfThreeTerms getNormalOfASurfaceOnAPoint(Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);
Equation getTangentPlaneOnAPointOfASurface(Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);
Equations getPerpendicularLineOnAPointOfASurface(Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);

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
template <unsigned int SIZE> Term getTermWithGradient(MathVectorOfTerms<SIZE> const& gradient, ArrayOfStrings<SIZE> const& coordinateVariables);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getLimit(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& valueToApproach);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> differentiate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> integrate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getUnitTangentVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getUnitNormalVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getCurvatureVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getGradient( Term const& term, ArrayOfStrings<SIZE> const& coordinateVariables);


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
Term getTermWithGradient(
        MathVectorOfTerms<SIZE> const& gradient,
        ArrayOfStrings<SIZE> const& coordinateVariables,
        bool & isExactDifferential)
{
    Term result;
    bool isFirst(true);
    isExactDifferential = true;
    Term termToCompare;
    for(unsigned int i=0; isExactDifferential && i<SIZE; i++)
    {
        std::string const& coordinateVariableName(coordinateVariables.at(i));
        SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever retrieverWithAllCoordinates(
                    stringHelper::strings(coordinateVariables.cbegin(), coordinateVariables.cend()));
        retrieverWithAllCoordinates.retrieveFromTerm(gradient.getValueAt(i));
        Term uniquePart(retrieverWithAllCoordinates.getRemainingTerm());
        Term commonPart(retrieverWithAllCoordinates.getTermWithMultipleVariableNames());
        for(auto const& variableNameAndTermPair : retrieverWithAllCoordinates.getVariableNameToTermMap())
        {
            if(variableNameAndTermPair.first == coordinateVariableName)
            {
                uniquePart += variableNameAndTermPair.second;
            }
            else
            {
                commonPart += variableNameAndTermPair.second;
            }
        }
        Integration integration(coordinateVariableName);
        if(isFirst)
        {
            termToCompare = integration.integrate(commonPart);
            isFirst = false;
        }
        else
        {
            Term currentTermToCompare(integration.integrate(commonPart));
            SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever retriever1({coordinateVariableName});
            SegregateTermsByVariableNamesInAdditionAndSubtractionRetriever retriever2({coordinateVariableName});
            retriever1.retrieveFromTerm(termToCompare);
            retriever2.retrieveFromTerm(currentTermToCompare);
            Term term1WithVariableName(retriever1.getVariableNameToTermMap().at(coordinateVariableName));
            Term term2WithVariableName(retriever2.getVariableNameToTermMap().at(coordinateVariableName));
            Term term1WithoutVariableName(retriever1.getTermWithMultipleVariableNames() + retriever1.getRemainingTerm());
            Term term2WithoutVariableName(retriever2.getTermWithMultipleVariableNames() + retriever2.getRemainingTerm());
            if(term1WithoutVariableName.isEmpty() && !term2WithoutVariableName.isEmpty())
            {
                termToCompare = term2WithVariableName + term2WithoutVariableName;
            }
            isExactDifferential = term1WithVariableName == term2WithVariableName;
        }
        result += integration.integrate(uniquePart);
    }
    if(isExactDifferential)
    {
        result += termToCompare;
    }
    else
    {
        result.clear();
    }
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
    Differentiation differentiation(variableName);
    Values const& values(termVector.getValues());
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
    Differentiation differentiation(variableName);
    Values const& values(termVector.getValues());
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
    Integration integration(variableName);
    Values const& values(termVector.getValues());
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

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getGradient(
        Term const& term,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Values & values(result.getValuesReference());
    for(unsigned int i=0; i<SIZE; i++)
    {
        values.at(i) = getPartialDerivative(term, coordinateVariables.at(i));
    }
    return result;
}

}

}

}
