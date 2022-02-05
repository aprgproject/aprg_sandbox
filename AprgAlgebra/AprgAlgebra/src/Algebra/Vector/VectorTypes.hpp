#pragma once

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Common/Math/Vector/AlbaMathVector.hpp>

namespace alba
{
template<> bool isEqualForMathVectorDataType(algebra::Term const& value1, algebra::Term const& value2);
template<> algebra::Term raiseToPowerForMathVectorDataType(algebra::Term const& value1, algebra::Term const& value2);
}

namespace alba
{

namespace algebra
{

template <unsigned int SIZE> using MathVectorOfNumbers = AlbaMathVector<AlbaNumber, SIZE>;
using MathVectorOfTwoNumbers = MathVectorOfNumbers<2>;
using MathVectorOfThreeNumbers = MathVectorOfNumbers<3>;

template <unsigned int SIZE> using ArrayOfStrings = std::array<std::string, SIZE>;
using ArrayOfTwoStrings = ArrayOfStrings<2U>;
using ArrayOfThreeStrings = ArrayOfStrings<3U>;

template <unsigned int SIZE> using MathVectorOfAngles = AlbaMathVector<AlbaAngle, SIZE>;
using MathVectorOfTwoAngles = MathVectorOfAngles<2U>;
using MathVectorOfThreeAngles = MathVectorOfAngles<3U>;

template <unsigned int SIZE> using MathVectorOfTerms = AlbaMathVector<Term, SIZE>;
using MathVectorOfTwoTerms = MathVectorOfTerms<2U>;
using MathVectorOfThreeTerms = MathVectorOfTerms<3U>;

}

}
