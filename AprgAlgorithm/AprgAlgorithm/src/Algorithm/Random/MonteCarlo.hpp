#pragma once

#include <functional>

namespace alba {

namespace algorithm {

using MonteCarloAlgorithm = std::function<bool(void)>;

void performAMonteCarloAlgorithm(MonteCarloAlgorithm const& monteCarloAlgorithm) {
    // A Monte Carlo algorithm is a randomized algorithm that may sometimes give a wrong answer.
    // For such an algorithm to be useful, the probability of a wrong answer should be small.

    monteCarloAlgorithm();
}

}  // namespace algorithm

}  // namespace alba
