#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <algorithm>
#include <array>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Values, int NUMBER_OF_BUCKETS>
class BucketSorter : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;
    using Bucket = std::vector<Value>;
    using Buckets = std::array<Bucket, NUMBER_OF_BUCKETS>;

    BucketSorter() = delete;
    BucketSorter(Value const& minValue, Value const& maxValue) : m_minValue(minValue), m_maxValue(maxValue) {}

    void sort(Values& valuesToSort) const override {
        Buckets buckets;  // Create n empty buckets

        double factor = static_cast<double>(NUMBER_OF_BUCKETS) / (m_maxValue - m_minValue);
        for (Value const& value : valuesToSort)  // Put array elements in different buckets
        {
            int bucketIndex = mathHelper::getIntegerAfterRoundingADoubleValue<int>((value - m_minValue) * factor);
            if (bucketIndex < NUMBER_OF_BUCKETS) {
                buckets[bucketIndex].emplace_back(value);
            }
        }

        auto itCopy = valuesToSort.begin();
        for (Bucket& bucket : buckets) {
            std::sort(bucket.begin(), bucket.end());  // change to stable sort if its need to be stable
            itCopy = std::copy(bucket.cbegin(), bucket.cend(), itCopy);  // copy back to original container
        }
    }

    Value m_minValue;
    Value m_maxValue;
};

}  // namespace algorithm

}  // namespace alba

// Bucket sort is mainly useful when input is uniformly distributed over a range.
// For example, consider the following problem.
// Sort a large set of floating point numbers which are in range from 0.0 to 1.0 and are uniformly distributed across
// the range. How do we sort the numbers efficiently? A simple way is to apply a comparison based sorting algorithm. The
// lower bound for Comparison based sorting algorithm (Merge Sort, Heap Sort, Quick-Sort .. etc) is Ω(n Log n), i.e.,
// they cannot do better than nLogn. Can we sort the array in linear time? Counting sort can not be applied here as we
// use keys as index in counting sort. Here keys are floating point numbers. The idea is to use bucket sort.

// Following is bucket algorithm:
// bucketSort(arr[], n)
// 1) Create n empty buckets (Or lists).
// 2) Do following for every array element arr[i].
// -> a) Insert arr[i] into bucket[n*array[i]]
// 3) Sort individual buckets using insertion sort.
// 4) Concatenate all sorted buckets.

// Bucket Sort for numbers having integer part:
// Algorithm :
// 1. Find maximum element and minimum of the array
// 2. Calculate the range of each bucket
// -> range = (max - min) / n
// -> n is the number of buckets
// 3. Create n buckets of calculated range
// 4. Scatter the array elements to these buckets
// -> BucketIndex = (arr[i] - min) / range
// 6. Now sort each bucket individually
// 7. Gather the sorted elements from buckets to original array
