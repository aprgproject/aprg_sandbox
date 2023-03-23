#include "FibonacciExample.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Matrix/Utilities/AlbaMatrixUtilities.hpp>

using namespace alba::matrix;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

FibonacciExample::Number FibonacciExample::getNthFibonacciUsingNaiveRecursion(Number const number) const
{
    // Time Complexity: T(n) = T(n-1) + T(n-2) which is exponential.
    // Extra Space: O(n) if we consider the function call stack size, otherwise O(1).

    // We can observe that this implementation does a lot of repeated work, thus this is a bad implementation for nth Fibonacci number.

    if(number<=1)
    {
        return number;
    }
    else
    {
        return getNthFibonacciUsingNaiveRecursion(number-1) + getNthFibonacciUsingNaiveRecursion(number-2);
    }
}

FibonacciExample::Number FibonacciExample::getNthFibonacciUsingMemoizationDP(Number const number)
{
    // Time Complexity: O(n) // same as iterative DP
    // Extra Space: O(n)

    // a) Memoization (Top Down):    // The memoized program for a problem is similar to the recursive version
    // with a small modification that it looks into a lookup table before computing solutions.
    // We initialize a lookup array with all initial values as UNUSED_VALUE.
    // Whenever we need the solution to a subproblem, we first look into the lookup table.
    // If the precomputed value is there then we return that value,
    // otherwise, we calculate the value and put the result in the lookup table so that it can be reused later.

    Number size = max(number+1, 2U);
    Numbers memoizationData(size, static_cast<unsigned int>(UNUSED_VALUE));
    memoizationData[0] = 0;
    memoizationData[1] = 1;
    return getNthFibonacciUsingMemoizationDP(memoizationData, number);
}

FibonacciExample::Number FibonacciExample::getNthFibonacciUsingIterativeDP(Number const number)
{
    // Time Complexity: O(n)
    // Extra Space: O(n)
    // b) Tabulation (Bottom Up):
    // The tabulated program for a given problem builds a table in bottom up fashion and returns the last entry from table.
    // For example, for the same Fibonacci number, we first calculate fib(0) then fib(1) then fib(2) then fib(3) and so on.
    // So literally, we are building the solutions of subproblems bottom-up.

    Number size = max(number+1, 2U);
    Numbers tabulationData(size);
    tabulationData[0] = 0;
    tabulationData[1] = 1;
    for (Number i=2; i<=number; i++)
    {
        tabulationData[i] = tabulationData.at(i-1)+tabulationData.at(i-2);
    }
    return tabulationData.at(number);
}

FibonacciExample::Number FibonacciExample::getNthFibonacciUsingIterativeDPAndSpaceEfficient(Number const number)
{
    // NOTE: Same implementation in AprgMath
    // Time Complexity: O(n)
    // Extra Space: O(1)
    // -> We can optimize the space used in method 2 by storing the previous two numbers only
    // because that is all we need to get the next Fibonacci number in series.

    if(number==0)
    {
        return 0;
    }
    else
    {
        Number previousFibonacci(0);
        Number currentFibonacci(1);
        for(Number n=2; n<=number; n++)
        {
            Number nextFibonacci = currentFibonacci + previousFibonacci;
            previousFibonacci = currentFibonacci;
            currentFibonacci = nextFibonacci;
        }
        return currentFibonacci;
    }
}

FibonacciExample::Number FibonacciExample::getNthFibonacciNumberUsingBinetsFormula(Number const number)
{
    // NOTE: Same implementation in AprgMath

    // NOTE: The time complexity is constant but it uses double precision so its not that accurate
    // NOTE: The pow() might be logarithmic but its not clearly written on the standard.

    // Binets formula:
    double sqrtOf5 = sqrt(5);
    double phi = (1+sqrtOf5)/2;
    return getIntegerAfterRoundingADoubleValue<Number>(pow(phi, number)/sqrtOf5);
}

FibonacciExample::Number FibonacciExample::getNthFibonacciUsingMatrixMultiplication(Number const number)
{
    // NOTE: Same implementation in AprgMath (Linear Recurrence)

    // Time Complexity: O(log(n))  (This is the only logarithmic solution here)
    // Extra Space: O(1)

    // This another O(n) which relies on the fact that if we n times multiply the matrix M = {{1,1},{1,0}} to itself
    // (in other words calculate power(M, n)), then we get the (n+1)th Fibonacci number as the element at row and column (0, 0) in the resultant matrix.
    // The matrix representation gives the following closed expression for the Fibonacci numbers:
    //  |f(n-1)|f(n)  |
    //  |f(n)  |f(n+1)|

    if(number==0)
    {
        return 0;
    }
    else
    {
        NumberMatrix formulaicTransform(2, 2,
        {0, 1,
         1, 1});

        NumberMatrix fibonacciMatrix(formulaicTransform);
        for (Number i=2; i<number; i++)
        {
            fibonacciMatrix*=formulaicTransform;
        }
        return fibonacciMatrix.getEntry(1U, 1U);
    }
}

FibonacciExample::Number FibonacciExample::getNthFibonacciUsingMatrixPowerWithLogarithmicTime(Number const number)
{
    // NOTE: Same implementation in AprgMath (Linear Recurrence)

    // Time Complexity: O(n)
    // Extra Space: O(1)

    if(number==0)
    {
        return 0;
    }
    else
    {
        // Matrix representation:
        // |f(n-1)|f(n)  |
        // |f(n)  |f(n+1)|

        NumberMatrix formulaicTransform(2, 2,
        {0, 1,
         1, 1});

        NumberMatrix fibonacciMatrix(getMatrixRaiseToScalarPower(formulaicTransform, number-1)); // logarithmic
        return fibonacciMatrix.getEntry(1U, 1U);
    }
}

FibonacciExample::Number FibonacciExample::getNthFibonacciUsingLogarithmicMemoizationDP(Number const number)
{
    // Time Complexity: O(log(n))
    // Extra Space: O(n)

    Number size = max(number+1, 2U);
    Numbers memoizationData(size, static_cast<unsigned int>(UNUSED_VALUE));
    memoizationData[0] = 0;
    memoizationData[1] = 1;
    return getNthFibonacciUsingMemoizationDP(memoizationData, number);
}

FibonacciExample::Number FibonacciExample::getNthFibonacciUsingLogarithmicIterativeDP(Number const number)
{
    // Derived using matrix power (check notes at header file)
    Number result(number);
    if(result > 1)
    {
        Number size = max(number+1, 2U);
        Numbers iterativeData(size);
        iterativeData[0] = 0;
        iterativeData[1] = 1;

        NumberSet logarithmicSteps{number};
        Number k(number);        while(k >= 3)
        {
            k = mathHelper::isOdd(k) ? (k+1)/2 : k/2;
            logarithmicSteps.emplace(k);
            logarithmicSteps.emplace(k-1);
        }

        for(Number const step : logarithmicSteps)
        {
            Number & resultForStep(iterativeData[step]);
            if(mathHelper::isOdd(step))
            {
                Number k = (step+1)/2;
                Number fibonacciAtK = iterativeData.at(k);
                Number fibonacciAtKMinus1 = iterativeData.at(k-1);
                resultForStep = fibonacciAtK*fibonacciAtK + fibonacciAtKMinus1*fibonacciAtKMinus1;
            }
            else
            {
                Number k = step/2;
                Number fibonacciAtK = iterativeData.at(k);
                Number fibonacciAtKMinus1 = iterativeData.at(k-1);
                resultForStep = (2*fibonacciAtKMinus1 + fibonacciAtK)*fibonacciAtK;
            }
        }
        result = iterativeData.at(number);
    }
    return result;
}
FibonacciExample::Number FibonacciExample::getNthFibonacciUsingMemoizationDP(
        Numbers & memoizationData,
        Number const number)
{
    Number & resultForNumber(memoizationData[number]);
    if(resultForNumber == UNUSED_VALUE)
    {
        resultForNumber = getNthFibonacciUsingMemoizationDP(memoizationData, number-1)
                + getNthFibonacciUsingMemoizationDP(memoizationData, number-2);
    }
    return resultForNumber;
}

FibonacciExample::Number FibonacciExample::getNthFibonacciUsingLogarithmicMemoizationDP(
        Numbers & memoizationData,
        Number const number)
{
    // Derived using matrix power

    Number & resultForNumber(memoizationData[number]);
    if(resultForNumber == UNUSED_VALUE)
    {
        if(mathHelper::isOdd(number))
        {
            Number k = (number+1)/2;
            Number fibonacciAtK = getNthFibonacciUsingLogarithmicMemoizationDP(memoizationData, k);
            Number fibonacciAtKMinus1 = getNthFibonacciUsingLogarithmicMemoizationDP(memoizationData, k-1);
            resultForNumber = fibonacciAtK*fibonacciAtK + fibonacciAtKMinus1*fibonacciAtKMinus1;
        }
        else
        {
            Number k = number/2;
            Number fibonacciAtK = getNthFibonacciUsingLogarithmicMemoizationDP(memoizationData, k);
            Number fibonacciAtKMinus1 = getNthFibonacciUsingLogarithmicMemoizationDP(memoizationData, k-1);
            resultForNumber = (2*fibonacciAtKMinus1 + fibonacciAtK)*fibonacciAtK;
        }
    }
    return resultForNumber;
}

}

// Like Divide and Conquer, Dynamic Programming combines solutions to sub-problems.
// Dynamic Programming is mainly used when solutions of same subproblems are needed again and again.
// In dynamic programming, computed solutions to subproblems are stored in a table so that these don’t have to be recomputed.
// So Dynamic Programming is not useful when there are no common (overlapping) subproblems
// because there is no point storing the solutions if they are not needed again.
// For example, Binary Search doesn’t have common subproblems.
// If we take an example of following recursive program for Fibonacci Numbers,
// there are many subproblems which are solved again and again.


// Recursion tree for execution of fib(5)
//                             f(5)
//                              ##
//                             #  #
//                            #    #
//                           #      #
//                          #        #
//                         #          #
//                        #            #
//                       #              #
//                      #                #
//                     #                  #
//                    #                    #
//                   #                      #
//                  #                        #
//                f(4)                      f(3)
//                 ##                        ##
//                #  #                      #  #
//               #    #                    #    #
//              #      #                  #      #
//             #        #                #        #
//            #          #              #          #
//           #            #            #            #
//         f(3)          f(2)        f(2)          f(1)
//          ##            ##          ##
//         #  #          #  #        #  #
//        #    #        #    #      #    #
//      f(2)  f(1)    f(1)  f(0)  f(1)  f(0)
//       ##
//      #  #
//     #    #
//   f(1)  f(0)

// We can see that the function fib(3) is being called 2 times.
// If we would have stored the value of fib(3), then instead of computing it again, we could have reused the old stored value.
// There are following two different ways to store the values so that these values can be reused:
// -> a) Memoization (Top Down)
// -> b) Tabulation (Bottom Up)

// Both Tabulated and Memoized store the solutions of subproblems.
// In Memoized version, table is filled on demand while in Tabulated version,
// starting from the first entry, all entries are filled one by one.
// Unlike the Tabulated version, all entries of the lookup table are not necessarily filled in Memoized version.
// For example, Memoized solution of the LCS problem doesn’t necessarily fill all entries.
