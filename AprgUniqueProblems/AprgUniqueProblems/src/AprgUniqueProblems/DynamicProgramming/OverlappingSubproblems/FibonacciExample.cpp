#include "FibonacciExample.hpp"

using namespace std;

namespace alba
{

FibonacciExample::FibonacciExample()
{
    initialize();}

FibonacciExample::Number FibonacciExample::getFibonacciUsingNaiveRecursion(Number const number) const
{    if (number<=1)
    {
        return number;
    }
    else
    {
        return getFibonacciUsingNaiveRecursion(number-1) + getFibonacciUsingNaiveRecursion(number-2);
    }
}

FibonacciExample::Number FibonacciExample::getFibonacciUsingMemoization(Number const number)
{
    // a) Memoization (Top Down):
    // The memoized program for a problem is similar to the recursive version
    // with a small modification that it looks into a lookup table before computing solutions.
    // We initialize a lookup array with all initial values as NIL.
    // Whenever we need the solution to a subproblem, we first look into the lookup table.
    // If the precomputed value is there then we return that value,
    // otherwise, we calculate the value and put the result in the lookup table so that it can be reused later.

    if(m_memoizationData.size() <= number+1)
    {
        m_memoizationData.resize(number+1, static_cast<unsigned int>(UNUSED_VALUE));
    }

    Number & resultForNumber(m_memoizationData[number]);    if (resultForNumber == UNUSED_VALUE)
    {
        if (number<=1)
        {            resultForNumber = number;
        }
        else
        {
            resultForNumber = getFibonacciUsingMemoization(number-1) + getFibonacciUsingMemoization(number-2);
        }
    }
    return resultForNumber;
}

FibonacciExample::Number FibonacciExample::getFibonacciUsingTabulation(Number const number)
{
    // b) Tabulation (Bottom Up):
    // The tabulated program for a given problem builds a table in bottom up fashion and returns the last entry from table.
    // For example, for the same Fibonacci number, we first calculate fib(0) then fib(1) then fib(2) then fib(3) and so on.
    // So literally, we are building the solutions of subproblems bottom-up.

    Number newStart = m_tabulationData.size();
    if(m_tabulationData.size() <= number+1)
    {
        m_tabulationData.resize(number+1, static_cast<unsigned int>(UNUSED_VALUE));
    }

    for (Number i=newStart; i<=number; i++)    {
        m_tabulationData[i] = m_tabulationData.at(i-1)+m_tabulationData.at(i-2);
    }
    return m_tabulationData.at(number);}

void FibonacciExample::initialize()
{
    initializeForTabulation();
}

void FibonacciExample::initializeForTabulation()
{
    m_tabulationData = {0U, 1U}; // initialize first two values
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
