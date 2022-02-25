#pragma once

#include <Algebra/Integration/DetailsForDefiniteIntegralWithTerms.hpp>
#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Retrieval/SegregateTermsByConditionInAdditionAndSubtractionRetriever.hpp>
#include <Algebra/Vector/VectorTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

template <unsigned int SIZE> bool isContinuousAt(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value);
template <unsigned int SIZE> bool isDifferentiableAt(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value);
template <unsigned int SIZE> bool areOriginalAndDerivativeVectorsOrthogonal( MathVectorOfTerms<SIZE> const& termVector);template <unsigned int SIZE> Term getLengthOfArcDerivative(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getLengthOfArc(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getLengthOfArcFromStartToEnd(MathVectorOfTerms<SIZE> const& termVector, DetailsForDefiniteIntegralWithTerms const& integralDetails);
template <unsigned int SIZE> Term getCurvature(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> Term getTermThatYieldsToThisGradient(MathVectorOfTerms<SIZE> const& gradient, ArrayOfStrings<SIZE> const& coordinateVariables, bool & isExactDifferential);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getLimit(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& valueToApproach);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> differentiate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> integrate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getUnitTangentVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getUnitNormalVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getCurvatureVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getGradient( Term const& term, ArrayOfStrings<SIZE> const& coordinateVariables);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getDel(MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables);
template <unsigned int SIZE> MathVectorOfTerms<SIZE> getDoubleDel(MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables);

// utilities function
template <unsigned int SIZE> void simplifyForTermVector(MathVectorOfTerms<SIZE> & termVector);

}

}

}
