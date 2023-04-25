#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba {

class MobileNumericKeypadProblem {
public:
    using NumpadValue = unsigned int;
    using Count = unsigned int;
    using NumpadValues = std::vector<NumpadValue>;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_VALUE = std::numeric_limits<Count>::max();

    MobileNumericKeypadProblem(Count const length);

    Count getCountUsingNaiveRecursion() const;
    Count getCountUsingMemoizationDP() const;
    Count getCountUsingIterativeDP() const;
    Count getCountUsingIterativeDPAndSpaceEfficient() const;

private:
    Count getCountForValueUsingNaiveRecursion(Count const length, NumpadValue const numpadValue) const;
    Count getCountForValueUsingMemoizationDP(
        CountMatrix& countMatrix, Count const length, NumpadValue const numpadValue) const;
    // no memoization because there is no recomputation
    Count const m_length;
};

}  // namespace alba

// Mobile Numeric Keypad Problem
//
// Given the mobile numeric keypad.
// You can only press buttons that are up, left, right or down to the current button.
// You are not allowed to press bottom row corner buttons (i.e. * and # ).

// Given a number N, find out the number of possible numbers of given length.
// Examples:
// For N=1, number of possible numbers would be 10 (0, 1, 2, 3, …., 9)
// For N=2, number of possible numbers would be 36
// Possible numbers: 00,08 11,12,14 22,21,23,25 and so on.
// If we start with 0, valid numbers will be 00, 08 (count: 2)
// If we start with 1, valid numbers will be 11, 12, 14 (count: 3)
// If we start with 2, valid numbers will be 22, 21, 23,25 (count: 4)
// If we start with 3, valid numbers will be 33, 32, 36 (count: 3)
// If we start with 4, valid numbers will be 44,41,45,47 (count: 4)
// If we start with 5, valid numbers will be 55,54,52,56,58 (count: 5)
// ...

// We need to print the count of possible numbers.

// N = 1 is trivial case, number of possible numbers would be 10 (0, 1, 2, 3, …., 9)
// For N > 1, we need to start from some button,
// then move to any of the four direction (up, left, right or down) which takes to a valid button (should not go to *,
// #). Keep doing this until N length number is obtained (depth first traversal).

// Recursive Solution:
// Mobile Keypad is a rectangular grid of 4X3 (4 rows and 3 columns)
// Lets say Count(i, j, N) represents the count of N length numbers starting from position (i, j)

// If N = 1
//   Count(i, j, N) = 10
// Else
//   Count(i, j, N) = Sum of all Count(r, c, N-1) where (r, c) is new
//                    position after valid move of length 1 from current
//                    position (i, j)
