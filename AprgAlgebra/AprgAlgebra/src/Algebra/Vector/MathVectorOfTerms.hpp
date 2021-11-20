#pragma once

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Vector/AlbaMathVector.hpp>

namespace alba
{

template<>
algebra::Term raiseToPowerForMathVectorDataType(algebra::Term const& value1, algebra::Term const& value2);

}

namespace alba
{

namespace algebra
{
template <unsigned int SIZE> using MathVectorOfTerms = AlbaMathVector<Term, SIZE>;
using MathVectorOfTwoTerms = MathVectorOfTerms<2>;
using MathVectorOfThreeTerms = MathVectorOfTerms<3>;
}

}
