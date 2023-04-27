#include "AlbaEntropySourceBasedOnTime.hpp"

#include <Common/Time/AlbaLocalTimeHelper.hpp>

using namespace std;
using namespace std::chrono;

namespace alba {

AlbaEntropySourceBasedOnTime::ValueType AlbaEntropySourceBasedOnTime::operator()() const {
    return static_cast<ValueType>(duration_cast<nanoseconds>(getSteadyTimeNow().time_since_epoch()).count());
    // return nanoseconds (poor entropy source)
}

double AlbaEntropySourceBasedOnTime::entropy() const {
    // Based from the formula:
    // https://en.cppreference.com/w/cpp/numeric/random/random_device/entropy
    return static_cast<double>(std::numeric_limits<ValueType>::digits);
}

}  // namespace alba
