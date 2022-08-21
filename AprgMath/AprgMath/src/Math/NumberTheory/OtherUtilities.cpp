#include "OtherUtilities.hpp"

#include <Algorithm/Search/SumSearch/FourSum.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::algorithm;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

namespace
{

void findDistinctNonConsecutiveFibonacciNumbersForSum(bool & isComplete, Numbers & fibonaccisForSum, Numbers const& fibonaccis, Number const sum, Number const index)
{
    // This can be improved by dynamic programming
    for(Number i=index; i<fibonaccis.size(); i++)
    {
        Number fibonacci(fibonaccis.at(i));
        if(sum > fibonacci)
        {
            fibonaccisForSum.emplace_back(fibonacci);
            findDistinctNonConsecutiveFibonacciNumbersForSum(isComplete, fibonaccisForSum, fibonaccis, sum-fibonacci, index+2);
            if(isComplete)
            {
                break;
            }
            fibonaccisForSum.pop_back();
        }
        else if(sum == fibonacci)
        {
            fibonaccisForSum.emplace_back(fibonacci);
            isComplete = true;
            break;
        }
    }
}

}

bool isLagrangeTheoremTrue(Number const number)
{
    // Lagrange’s theorem states that every positive integer can be represented as a sum of four squares, i.e., a^2 + b^2 + c^2 + d^2.
    // For example, the number 123 can be represented as the sum 8^2 + 5^2 + 5^2 + 3^2.

    bool result(false);
    if(number >= 0)
    {
        Number maxElement(pow(number, 0.5)); // max element is square root
        Numbers squaredElements;
        squaredElements.reserve(maxElement-1);
        for(Number i=1; i<maxElement; i++)
        {
            squaredElements.emplace_back(i*i);
        }

        FourSum<Numbers> fourSum(squaredElements);
        auto fourValues = fourSum.getPossibleDuplicatedFourValuesWithSum(number);
        Number sumOfSquares = get<0>(fourValues) + get<1>(fourValues) + get<2>(fourValues) + get<3>(fourValues);

        result = sumOfSquares == number;
    }
    return result;
}

bool isZeckendorfTheoremTrue(Number const number)
{
    // Zeckendorf’s theorem states that every positive integer has a unique representation as a sum of Fibonacci numbers
    // such that no two numbers are equal or consecutive Fibonacci numbers.
    // For example, the number 74 can be represented as the sum 55 + 13 + 5 + 1.

    bool result(false);
    if(number >= 0)
    {
        Numbers fibonaccis(getFibonacciNumbersBelowThisNumber(number));

        bool isComplete(false);
        Numbers fibonaccisForSum;
        findDistinctNonConsecutiveFibonacciNumbersForSum(isComplete, fibonaccisForSum, fibonaccis, number, 0);

        if(isComplete)
        {
            Number sumOfFibonaccis = accumulate(fibonaccisForSum.cbegin(), fibonaccisForSum.cend(), 0, std::plus<Number>());
            result = sumOfFibonaccis == number;
        }
    }
    return result;
}

Numbers getFibonacciNumbersBelowThisNumber(Number const number)
{
    Numbers result;
    Number previousPreviousFibonacci(0);
    Number previousFibonacci(1);
    Number currentFibonacci(1);
    while(currentFibonacci < number)
    {
        result.emplace_back(currentFibonacci);
        previousPreviousFibonacci = previousFibonacci;
        previousFibonacci = currentFibonacci;
        currentFibonacci = previousFibonacci + previousPreviousFibonacci;
    }
    return result;
}

}

}
