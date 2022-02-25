#pragma once

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Vector/MathVectorOfTermsUtilitiesTemplateHeaders.hpp>
#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Common/Math/Vector/AlbaMathVectorUtilities.hpp>

#include <algorithm>

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

bool isDivergenceOfCurlZero(MathVectorOfThreeTerms const& termVector, ArrayOfThreeStrings const& coordinateVariables);
bool isGaussDivergenceTheoremInAPlaneTrue(
        MathVectorOfTwoTerms const& vectorField,
        MathVectorOfTwoTerms const& regionOfLineIntegral,
        MathVectorOfTwoTerms const& unitOutwardNormal,
        DetailsForDefiniteIntegralWithTerms const& unitOutwardNormalDetails,
        DetailsForDefiniteIntegralWithTerms const& areaDetailsInX,
        DetailsForDefiniteIntegralWithTerms const& areaDetailsInY,
        ArrayOfTwoStrings const& coordinateVariables);
bool isStokesTheoremInAPlaneTrue(
        MathVectorOfTwoTerms const& vectorField,
        MathVectorOfTwoTerms const& regionOfLineIntegral,
        MathVectorOfTwoTerms const& unitTangentVector,
        DetailsForDefiniteIntegralWithTerms const& lineIntegralDetails,
        DetailsForDefiniteIntegralWithTerms const& areaDetailsInX,
        DetailsForDefiniteIntegralWithTerms const& areaDetailsInY,
        ArrayOfTwoStrings const& coordinateVariables);
Term getDyOverDx(MathVectorOfTwoTerms const& termVector, std::string const& variableName);
Term getDirectionalDerivativeInTwoDimensions(Term const& term, ArrayOfTwoStrings const& coordinateVariables, AlbaAngle const& angleOfDirection);
Term getDirectionalDerivativeInThreeDimensions(Term const& term, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeAngles const& coordinateAngles);
Term getLineIntegralOfAClosedNonIntersectingPathUsingGreensTheorem(MathVectorOfTwoTerms const& vectorField, ArrayOfTwoStrings const& coordinateVariables, DetailsForDefiniteIntegralWithTerms const& xDetailsForLinePath, DetailsForDefiniteIntegralWithTerms const& yDetailsForLinePath);
Term getAreaOfAClosedNonIntersectingPathUsingGreensTheorem(ArrayOfTwoStrings const& coordinateVariables, MathVectorOfTwoTerms const& linePath, DetailsForDefiniteIntegralWithTerms const& linePathIntegralDetails);
MathVectorOfThreeTerms getNormalOfASurfaceOnAPoint(Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);
Equation getTangentPlaneOnAPointOfASurface(Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);
Equations getPerpendicularLineOnAPointOfASurface(Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);
MathVectorOfThreeTerms getCurl(MathVectorOfThreeTerms const& termVector, ArrayOfThreeStrings const& coordinateVariables);

// utilities function
void simplifyForTermInVector(Term & term);
SegregateTermsByConditionInAdditionAndSubtractionRetriever getRetrieverForComparison(Term const& termToAnalyze, std::string const& coordinateVariableName, stringHelper::strings const& processedCoordinates);
void retrieveWithAndWithoutOtherCoordinates(Term & termWithOtherCoordinates, Term & termWithoutOtherCoordinates, Term const& termToAnalyze, std::string const& coordinateVariableName, stringHelper::strings const& allCoordinates);


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
        DetailsForDefiniteIntegralWithTerms const& integralDetails)
{
    return evaluateTermsAndGetDifference(
                getLengthOfArc(termVector, integralDetails.variableName),
                integralDetails.variableName,
                integralDetails.lowerEnd,
                integralDetails.higherEnd);
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
Term getTermThatYieldsToThisGradient(
        MathVectorOfTerms<SIZE> const& gradient,
        ArrayOfStrings<SIZE> const& coordinateVariables,
        bool & isExactDifferential)
{
    Term result;
    bool isFirst(true);
    isExactDifferential = true;
    Term partForComparison;
    stringHelper::strings processedCoordinates;
    stringHelper::strings allCoordinates(coordinateVariables.cbegin(), coordinateVariables.cend());
    for(unsigned int i=0; isExactDifferential && i<SIZE; i++)
    {
        std::string const& coordinateVariableName(coordinateVariables.at(i));
        Term termWithOtherCoordinates, termWithoutOtherCoordinates;
        retrieveWithAndWithoutOtherCoordinates(termWithOtherCoordinates, termWithoutOtherCoordinates, gradient.getValueAt(i), coordinateVariableName, allCoordinates);
        processedCoordinates.emplace_back(coordinateVariableName);
        Integration integration(coordinateVariableName);
        if(isFirst)
        {
            partForComparison = integration.integrate(termWithOtherCoordinates);
            isFirst = false;
        }
        else
        {
            Term currentPartForComparison(integration.integrate(termWithOtherCoordinates));
            SegregateTermsByConditionInAdditionAndSubtractionRetriever retriever1(getRetrieverForComparison(partForComparison, coordinateVariableName, processedCoordinates));
            SegregateTermsByConditionInAdditionAndSubtractionRetriever retriever2(getRetrieverForComparison(currentPartForComparison, coordinateVariableName, processedCoordinates));
            isExactDifferential = retriever1.getTermWithCondition() == retriever2.getTermWithCondition();
            if(isExactDifferential)
            {
                partForComparison = retriever1.getTermWithCondition() + retriever1.getTermWithoutCondition() + retriever2.getTermWithoutCondition();
            }
            else
            {
                break;
            }
        }
        result += integration.integrate(termWithoutOtherCoordinates);
    }
    if(isExactDifferential)
    {
        result += partForComparison;
    }
    else
    {
        result.clear();
    }
    simplifyForTermInVector(result);
    return result;
}

template <unsigned int SIZE>
Term getPotentialFunctionForVectorFieldGradient(
        MathVectorOfTerms<SIZE> const& gradient,
        ArrayOfStrings<SIZE> const& coordinateVariables,
        bool & isConservative)
{
    return getTermThatYieldsToThisGradient<SIZE>(gradient, coordinateVariables, isConservative);
}

template <unsigned int SIZE>
Term getDivergence(
        MathVectorOfTerms<SIZE> const& termVector,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> del(getDel<SIZE>(termVector, coordinateVariables));
    Values const& values(del.getValues());
    return std::accumulate(values.cbegin(), values.cend(), Term(0), std::plus<Term>());
}

template <unsigned int SIZE>
Term getLaplaceTerm(
        MathVectorOfTerms<SIZE> const& termVector,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> del(getDoubleDel<SIZE>(termVector, coordinateVariables));
    Values const& values(del.getValues());
    return std::accumulate(values.cbegin(), values.cend(), Term(0), std::plus<Term>());
}

template <unsigned int SIZE>
Term getLineIntegral(
        MathVectorOfTerms<SIZE> const& vectorField,
        ArrayOfStrings<SIZE> const& coordinateVariables,
        MathVectorOfTerms<SIZE> const& linePath,
        DetailsForDefiniteIntegralWithTerms const& linePathIntegralDetails)
{
    SubstitutionOfVariablesToTerms substitution;
    Differentiation differentiation(linePathIntegralDetails.variableName);
    for(unsigned int i=0; i<SIZE; i++)
    {
        substitution.putVariableWithTerm(coordinateVariables.at(i), linePath.getValueAt(i));
        DerivativeVariableName derivativeVariableName(1, "", coordinateVariables.at(i));
        substitution.putVariableWithTerm(derivativeVariableName.getNameInLeibnizNotation(), differentiation.differentiate(linePath.getValueAt(i)));
    }
    MathVectorOfTerms<SIZE> linePathInVectorField;
    for(unsigned int i=0; i<SIZE; i++)
    {
        linePathInVectorField.getValueReferenceAt(i) = substitution.performSubstitutionTo(vectorField.getValueAt(i));
    }
    MathVectorOfTerms<SIZE> differentiatedLinePath(differentiate(linePath, linePathIntegralDetails.variableName));
    Term termIntegrate(getDotProduct(linePathInVectorField, differentiatedLinePath));
    Integration integration(linePathIntegralDetails.variableName);
    return integration.integrateAtDefiniteTerms(termIntegrate, linePathIntegralDetails.lowerEnd, linePathIntegralDetails.higherEnd);
}

template <unsigned int SIZE>
Term getLineIntegralIndependentOfPath(
        MathVectorOfTerms<SIZE> const& vectorField,
        ArrayOfStrings<SIZE> const& coordinateVariables,
        MathVectorOfNumbers<SIZE> const& lowerValues,
        MathVectorOfNumbers<SIZE> const& higherValues)
{
    bool isConservative(false);
    Term potential(getPotentialFunctionForVectorFieldGradient<SIZE>(vectorField, coordinateVariables, isConservative));

    Term result;
    if(isConservative)
    {
        SubstitutionOfVariablesToValues substitutionForLowerValues;
        SubstitutionOfVariablesToValues substitutionForHigherValues;
        for(unsigned int i=0; i<SIZE; i++)
        {
            substitutionForLowerValues.putVariableWithValue(coordinateVariables.at(i), lowerValues.getValueAt(i));
            substitutionForHigherValues.putVariableWithValue(coordinateVariables.at(i), higherValues.getValueAt(i));
        }
        result = substitutionForHigherValues.performSubstitutionTo(potential) - substitutionForLowerValues.performSubstitutionTo(potential);
    }
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
    MathVectorOfTerms<SIZE> result;
    for(unsigned int i=0; i<SIZE; i++)
    {
        result.getValueReferenceAt(i) = getPartialDerivative(term, coordinateVariables.at(i));
    }
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getDel(
        MathVectorOfTerms<SIZE> const& termVector,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    MathVectorOfTerms<SIZE> result(termVector);
    for(unsigned int i=0; i<SIZE; i++)
    {
        result.getValueReferenceAt(i) = getPartialDerivative(termVector.getValueAt(i), coordinateVariables.at(i));
    }
    return result;
}

template <unsigned int SIZE>
MathVectorOfTerms<SIZE> getDoubleDel(
        MathVectorOfTerms<SIZE> const& termVector,
        ArrayOfStrings<SIZE> const& coordinateVariables)
{
    MathVectorOfTerms<SIZE> result;
    for(unsigned int i=0; i<SIZE; i++)
    {
        result.getValueReferenceAt(i) = getPartialDerivative(getPartialDerivative(termVector.getValueAt(i), coordinateVariables.at(i)), coordinateVariables.at(i));
    }
    return result;
}

template <unsigned int SIZE>
void simplifyForTermVector(
        MathVectorOfTerms<SIZE> & termVector)
{
    for(Term & term : termVector.getValuesReference())
    {
        simplifyForTermInVector(term);
    }
}

}

}

}
