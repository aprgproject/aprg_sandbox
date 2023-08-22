#include "Rand7FromRand5.hpp"

using namespace std;

namespace alba {

Rand7FromRand5::Rand7FromRand5() : m_randomizerFrom0To4(0, 4) {}

Rand7FromRand5::Value Rand7FromRand5::getRandomFrom0To6() {
    // We just need to generate a range of values where each value is equally likely
    // (and where the range has at least seven elements).
    // If we can do this, then we can discard the elements greater than the previous multiple of 7,
    // and mod the rest of them by 7.
    // This will get us a value within the range of O to 6, with each value being equally likely.
    // In the below code, we generate the range O through 24 by doing 5 * rand5() + rand5().
    // Then, we discard the values between 21 and 24,
    // since they would otherwise make rand7() unfairly weighted towards O through 3.
    // Finally, we mod by 7 to give us the values in the range O to 6 with equal probability.
    // Note that because we discard values in this approach,
    // we have no guarantee on the number of rand5() calls it may take to return a value.
    // This is what is meant by a nondeterministic number of calls.

    while (true) {
        int randomFrom0To24 = 5 * getRandomFrom0To4() + getRandomFrom0To4();
        if (randomFrom0To24 < 21) {
            return randomFrom0To24 % 7;
        }
    }
}

Rand7FromRand5::Value Rand7FromRand5::getRandomFrom0To4() { return m_randomizerFrom0To4.getRandomValue(); }

}  // namespace alba
