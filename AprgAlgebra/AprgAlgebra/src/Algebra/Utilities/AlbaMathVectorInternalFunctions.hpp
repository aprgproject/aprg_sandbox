#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

// Template declaration

template <typename DataType>
bool isEqualForMathVectorDataType(DataType const& value1, DataType const& value2);

template <typename DataType>
DataType raiseToPowerForMathVectorDataType(DataType const& value1, DataType const& value2);


// Template specialization

template<>
bool isEqualForMathVectorDataType(algebra::Term const& value1, algebra::Term const& value2);

template<>
algebra::Term raiseToPowerForMathVectorDataType(algebra::Term const& value1, algebra::Term const& value2);

}
