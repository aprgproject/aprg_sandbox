#include "CountWaysToReachTheNthStair.hpp"

#include <Math/NumberTheory/OtherUtilities.hpp>

using namespace alba::math;
using namespace std;

namespace alba {

CountWaysToReachTheNthStair::CountWaysToReachTheNthStair(Count const numberOfStairs)
    : m_numberOfStairs(numberOfStairs) {}

CountWaysToReachTheNthStair::Count CountWaysToReachTheNthStair::getCountUsingFibonacci() const {
    // Time Complexity: O(1) (depends on how fibonacci number is computed)
    // Auxiliary Space: O(1)

    Count result(0);
    if (m_numberOfStairs > 0) {
        result = getNthFibonacciNumberUsingBinetsFormula(m_numberOfStairs + 1);
    }
    return result;
}

}  // namespace alba
