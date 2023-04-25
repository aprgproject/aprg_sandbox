#include "AlbaMathVectorInternalFunctions.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>

using namespace alba::algebra;

namespace alba {

template <>
bool isEqualForMathVectorDataType(Term const& value1, Term const& value2) {
    return value1 == value2;
}

template <>
Term raiseToPowerForMathVectorDataType(Term const& value1, Term const& value2) {
    return value1 ^ value2;
}

}  // namespace alba
