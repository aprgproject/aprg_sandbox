#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Integration/DetailsForDefiniteIntegralWithTerms.hpp>
#include <Algebra/Retrieval/SegregateTermsByConditionInAdditionAndSubtractionRetriever.hpp>
#include <Algebra/Vector/VectorTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba {

namespace algebra {

namespace VectorUtilities {

template <size_t SIZE>
bool isContinuousAt(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value);
template <size_t SIZE>
bool isDifferentiableAt(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value);
template <size_t SIZE>
bool areOriginalAndDerivativeVectorsOrthogonal(MathVectorOfTerms<SIZE> const& termVector);
template <size_t SIZE>
Term getLengthOfArcDerivative(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <size_t SIZE>
Term getLengthOfArc(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <size_t SIZE>
Term getLengthOfArcFromStartToEnd(
    MathVectorOfTerms<SIZE> const& termVector, DetailsForDefiniteIntegralWithTerms const& integralDetails);
template <size_t SIZE>
Term getCurvature(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <size_t SIZE>
Term getTermThatYieldsToThisGradient(
    MathVectorOfTerms<SIZE> const& gradient, ArrayOfStrings<SIZE> const& coordinateVariables,
    bool& isExactDifferential);
template <size_t SIZE>
MathVectorOfTerms<SIZE> getLimit(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& valueToApproach);
template <size_t SIZE>
MathVectorOfTerms<SIZE> differentiate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <size_t SIZE>
MathVectorOfTerms<SIZE> integrate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <size_t SIZE>
MathVectorOfTerms<SIZE> getUnitTangentVector(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <size_t SIZE>
MathVectorOfTerms<SIZE> getUnitNormalVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <size_t SIZE>
MathVectorOfTerms<SIZE> getCurvatureVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <size_t SIZE>
MathVectorOfTerms<SIZE> getGradient(Term const& term, ArrayOfStrings<SIZE> const& coordinateVariables);
template <size_t SIZE>
MathVectorOfTerms<SIZE> getDel(
    MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables);
template <size_t SIZE>
MathVectorOfTerms<SIZE> getDoubleDel(
    MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables);

// utilities function
template <size_t SIZE>
void simplifyForTermVector(MathVectorOfTerms<SIZE>& termVector);

}  // namespace VectorUtilities
}  // namespace algebra

}  // namespace alba