#pragma once

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Vector/111_MathVectorInternalFunctions.hpp>
#include <Math/Vector/AlbaMathVector.hpp>

namespace alba
{

namespace algebra
{

template <unsigned int SIZE> using MathVectorOfTerms = AlbaMathVector<Term, SIZE>;
using MathVectorOfTwoTerms = MathVectorOfTerms<2>;
using MathVectorOfThreeTerms = MathVectorOfTerms<3>;

}

}
