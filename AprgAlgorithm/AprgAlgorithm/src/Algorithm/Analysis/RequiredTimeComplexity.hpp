#pragma once

namespace alba
{

namespace algorithm
{

}

}

// Given the input size, we can try to guess the required time complexity of the algorithm that solves the problem.

// The following table contains some useful estimates assuming a time limit of ONE SECOND.
// | input size | required time complexity
// | n<=10      | O(n!)
// | n<=20      | O(2^n)
// | n<=500     | O(n^3)
// | n<=5000    | O(n^2)
// | n<=106     | O(nlogn) or O(n)
// | n is large | O(1) or O(logn)


// For example, if the input size is n = 10^5, it is probably expected that the time complexity of the algorithm is O(n) or O(nlogn).
// This information makes it easier to design the algorithm, because it rules out approaches that would yield an algorithm with a worse time complexity.
// Still, it is important to remember that a time complexity is only an estimate of efficiency, because it hides the constant factors.

// For example, an algorithm that runs in O(n) time may perform n/2 or 5n operations.
// This has an important effect on the actual running time of the algorithm.
