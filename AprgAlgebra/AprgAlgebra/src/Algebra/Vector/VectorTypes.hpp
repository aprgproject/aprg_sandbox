#pragma once

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Utilities/AlbaMathVectorInternalFunctions.hpp>
#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Common/Math/Vector/AlbaMathVector.hpp>

namespace alba {

namespace algebra {

template <int SIZE>
using MathVectorOfNumbers = AlbaMathVector<AlbaNumber, SIZE>;
using MathVectorOfTwoNumbers = MathVectorOfNumbers<2>;
using MathVectorOfThreeNumbers = MathVectorOfNumbers<3>;

template <int SIZE>
using ArrayOfStrings = std::array<std::string, SIZE>;
using ArrayOfTwoStrings = ArrayOfStrings<2>;
using ArrayOfThreeStrings = ArrayOfStrings<3>;

template <int SIZE>
using MathVectorOfAngles = AlbaMathVector<AlbaAngle, SIZE>;
using MathVectorOfTwoAngles = MathVectorOfAngles<2>;
using MathVectorOfThreeAngles = MathVectorOfAngles<3>;

template <int SIZE>
using MathVectorOfTerms = AlbaMathVector<Term, SIZE>;
using MathVectorOfTwoTerms = MathVectorOfTerms<2>;
using MathVectorOfThreeTerms = MathVectorOfTerms<3>;

}  // namespace algebra

}  // namespace alba
