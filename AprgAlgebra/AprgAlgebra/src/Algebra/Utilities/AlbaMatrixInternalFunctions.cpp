#include "AlbaMatrixInternalFunctions.hpp"

namespace alba {

namespace matrix {

template <>
bool isEqualForMathMatrixDataType(AlbaNumber const& value1, AlbaNumber const& value2) {
    return value1 == value2;
}

}  // namespace matrix

}  // namespace alba
