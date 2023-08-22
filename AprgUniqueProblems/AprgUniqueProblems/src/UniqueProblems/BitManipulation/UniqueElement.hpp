#pragma once

#include <cstdint>
#include <vector>

namespace alba {

class UniqueElement {
public:
    using Value = uint64_t;
    using ValuePairs = std::pair<Value, Value>;
    using Values = std::vector<Value>;

    UniqueElement();
    Value getAUniqueElementOnTwoDuplicatedValues(Values const& values) const;
    ValuePairs getTwoUniqueElementsOnTwoDuplicatedValues(Values const& values) const;
    Value getAUniqueElementOnThreeDuplicatedValues(Values const& values) const;
    Value getAnElementOccuringOddNumberOfTimes(Values const& values) const;

private:
    Value getXorResult(Values const& values) const;

    Values m_values;
};

}  // namespace alba
