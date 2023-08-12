#include "SmallestOfThreeIntegersWithoutComparisonOperators.hpp"

using namespace std;

namespace alba {

SmallestOfThreeIntegersWithoutComparisonOperators::SmallestOfThreeIntegersWithoutComparisonOperators() {}

SmallestOfThreeIntegersWithoutComparisonOperators::Value SmallestOfThreeIntegersWithoutComparisonOperators::getSmallest(
    Value const value1, Value const value2, Value const value3) const {
    if (isLessThan(value3, value2)) {
        if (isLessThan(value3, value1)) {
            return value3;
        }
        if (isLessThan(value2, value1)) {
            return value2;
        }
    }
    return value1;
}

bool SmallestOfThreeIntegersWithoutComparisonOperators::isLessThan(Value const value1, Value const value2) const {
    // This comparison works only on unsigned values.
    // return !(value1 / value2); // this has a problem when value1 and value 2 are both zero
    if (static_cast<bool>(value2)) {
        return !(value1 / value2);
    }
    return false;
}

}  // namespace alba