#pragma once

#include <functional>

namespace alba {

namespace algorithm {

using LasVegasAlgorithm = std::function<void(void)>;

void performALasVegasAlgorithm(LasVegasAlgorithm const& lasVegasAlgorithm) {
    // A Las Vegas algorithm is a randomized algorithm that always gives the correct answer,
    // but its running time varies randomly.
    // The goal is to design an algorithm that is efficient with high probability.

    lasVegasAlgorithm();
}

}  // namespace algorithm

}  // namespace alba
