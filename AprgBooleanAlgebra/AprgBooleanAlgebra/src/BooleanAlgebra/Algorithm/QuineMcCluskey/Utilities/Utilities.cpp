#include "Utilities.hpp"

namespace alba {

namespace booleanAlgebra {

LogicalValue getLogicalValue(bool const value) { return value ? LogicalValue::True : LogicalValue::False; }

}  // namespace booleanAlgebra

}  // namespace alba
