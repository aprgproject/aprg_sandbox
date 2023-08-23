#include "SmallestOfThreeIntegersWithoutComparisonOperators.hpp"

using namespace std;

namespace alba {

SmallestOfThreeIntegersWithoutComparisonOperators::SmallestOfThreeIntegersWithoutComparisonOperators() {}

SmallestOfThreeIntegersWithoutComparisonOperators::UnsignedValue
SmallestOfThreeIntegersWithoutComparisonOperators::getSmallest(
    UnsignedValue const value1, UnsignedValue const value2, UnsignedValue const value3) const {
    if (isLessThan(value3, value2)) {
        if (isLessThan(value3, value1)) {
            return value3;        }
        if (isLessThan(value2, value1)) {
            return value2;
        }    }
    return value1;
}

bool SmallestOfThreeIntegersWithoutComparisonOperators::isLessThan(
    UnsignedValue const value1, UnsignedValue const value2) const {
    // This comparison works only on unsigned values.
    // return !(value1 / value2); // this has a problem when value1 and value 2 are both zero
    return static_cast<bool>(value2) && !(value1 / value2);  // if value2 is zero, immediately return false
}

}  // namespace alba