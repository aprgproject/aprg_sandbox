#pragma once

#include <functional>

namespace alba {

namespace algorithm {

using LasVegasAlgorithm = std::function<void(void)>;

void performALasVegasAlgorithm(LasVegasAlgorithm const& lasVegasAlgorithm) { lasVegasAlgorithm(); }

}  // namespace algorithm

}  // namespace alba

// A Las Vegas algorithm is a randomized algorithm that always gives the correct answer,
// but its running time varies randomly.
// The goal is to design an algorithm that is efficient with high probability.

// Las Vegas algorithm:
// -> These algorithms always produce correct or optimum result.
// -> Time complexity of these algorithms is based on a random value
// and time complexity is evaluated as expected value.
// -> For example, Randomized QuickSort always sorts an input array
// -> and expected worst case time complexity of QuickSort is O(nLogn).