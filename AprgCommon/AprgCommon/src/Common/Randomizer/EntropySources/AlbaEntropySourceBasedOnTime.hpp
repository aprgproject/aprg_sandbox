#pragma once

#include <random>

namespace alba {

class AlbaEntropySourceBasedOnTime {
public:
    using ValueType = std::random_device::result_type;

    ValueType operator()() const;
    double entropy() const;
};

}  // namespace alba
