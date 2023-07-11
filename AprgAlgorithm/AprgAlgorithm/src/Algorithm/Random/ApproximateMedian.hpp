#pragma once

#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <set>

namespace alba {

namespace algorithm {

template <typename Values>
class ApproximateMedian {
public:
    using Value = typename Values::value_type;
    using SetOfValues = std::multiset<Value>;

    ApproximateMedian() = default;

    Value getApproximateMedian(Values const& values) const {
        // What if we want in less than O(n) time with low probable error allowed?
        // -> Following steps represent an algorithm that is O((Log n) x (Log Log n)) time
        // -> and produces incorrect result with probability less than or equal to 2/n2.
        // ---> Randomly choose k elements from the array where k=c log n (c is some constant)
        // ---> Insert then into a set.
        // ---> Sort elements of the set.
        // ---> Return median of the set i.e. (k/2)th element from the set

        // Time Complexity:
        // -> We use a set provided by the STL in C++.
        // -> In STL Set, insertion for each element takes O(log k).
        // -> So for k insertions, time taken is O (k log k).
        // -> Now replacing k with c log n
        // -> -> O(c log n (log (clog n))) -> O (log n (log log n))

        constexpr int c = 10;
        int numbersOfElementsInSet = std::min(values.size(), c * mathHelper::getLogarithmWithBase2Of(values.size()));
        AlbaUniformNonDeterministicRandomizer<int> randomizer(0, static_cast<int>(values.size()) - 1);
        SetOfValues orderedValues;
        for (int i = 0; i < numbersOfElementsInSet; i++) {
            orderedValues.emplace(values[randomizer.getRandomValue()]);
        }
        Value result{};
        if (orderedValues.size() > 0) {
            result = *std::next(orderedValues.begin(), (orderedValues.size() - 1) / 2);
        }
        return result;
    }
};

}  // namespace algorithm

}  // namespace alba

// Problem Statement :
// Given an unsorted array A[] of n numbers and ε > 0,
// compute an element whose rank (position in sorted A[]) is in the range [(1 – ε)n/2, (1 + ε)n/2].
// For ½ Approximate Median Algorithm &epsilon;
// is 1/2 => rank should be in the range [n/4, 3n/4]

// How is probability of error less than 2/n2?
// -> Algorithm makes an error if the set S has at least k/2 elements are from the Left Quarter or Right Quarter.
// -> It is quite easy to visualize this statement since the median which we report will be (k/2)th element
// ---> and if we take k/2 elements from the left quarter(or right quarter)
// ---> the median will be from the left quarter (or the right quarter).
// -> An array can be divided into 4 quarters each of size n/4.
// ---> So P(selecting left quarter) is 1/4.
// ---> So what is the probability that at least k/2 elements are from the Left Quarter or Right Quarter?
// -> This probability problem is same as below:
// ---> Given a coin which gives HEADS with probability 1/4 and TAILS with 3/4.
// ---> The coin is tossed k times.
// ---> What is the probability that we get at least k/2 HEADS is less than or equal to?
// -> Explanation:
// -> If we put k = c log n for c = 10, we get
// ---> P <= (1/2)^(2 * log n)
// ---> P <= (1/2)^(log n^2)
// ---> P <= 2/(n^2)
// -> Probability of selecting at least k/2 elements from the left quarter) <= 1/(n^2)
// -> Probability of selecting at least k/2 elements from the left or right quarter) <= 2/(n^2)
// -> Therefore algorithm produces incorrect result with probability less that or equal to 2/(n^2).
