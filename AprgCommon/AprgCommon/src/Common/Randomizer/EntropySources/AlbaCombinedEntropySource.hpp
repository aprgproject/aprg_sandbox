#pragma once

#include <Common/Randomizer/EntropySources/AlbaEntropySourceBasedOnTime.hpp>

#include <cstdint>
#include <random>

namespace alba {

class AlbaCombinedEntropySource {
public:
    enum class EntropySourceType { RandomDevice, Time };
    using ValueType = std::random_device::result_type;

    AlbaCombinedEntropySource();

    ValueType operator()();
    double entropy() const;

private:
    EntropySourceType m_sourceType;
    std::random_device m_randomDeviceSource;
    AlbaEntropySourceBasedOnTime m_timeSource;
};

}  // namespace alba
