#pragma once

#include <functional>

namespace alba {

namespace algorithm {

using MonteCarloAlgorithm = std::function<bool(void)>;

void performAMonteCarloAlgorithm(MonteCarloAlgorithm const& monteCarloAlgorithm) { monteCarloAlgorithm(); }

}  // namespace algorithm

}  // namespace alba

// A Monte Carlo algorithm is a randomized algorithm that may sometimes give a wrong answer.
// For such an algorithm to be useful, the probability of a wrong answer should be small.

// Monte Carlo:
// -> Produce correct or optimum result with some probability.
// -> These algorithms have deterministic running time
// and it is generally easier to find out worst case time complexity.
// -> For example this implementation of Karger’s Algorithm produces minimum cut with probability greater than
// or equal to 1/n2 (n is number of vertices) and has worst case time complexity as O(E).
// -> Another example is Fermet Method for Primality Testing.
