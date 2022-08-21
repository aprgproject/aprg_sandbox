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

void findDistinctNonConsecutiveFibonacciNumbersForSum(
        bool & isComplete,
        UnsignedNumbers & fibonaccisForSum,
        UnsignedNumbers const& fibonaccis,
        UnsignedNumber const sum,
        UnsignedNumber const index)
{
    // This can be improved by dynamic programming
    for(UnsignedNumber i=index; i<fibonaccis.size(); i++)
    {
        UnsignedNumber fibonacci(fibonaccis.at(i));
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

bool isLagrangeTheoremTrue(UnsignedNumber const number)
{
    // Lagrange’s theorem states that every positive integer can be represented as a sum of four squares, i.e., a^2 + b^2 + c^2 + d^2.
    // For example, the number 123 can be represented as the sum 8^2 + 5^2 + 5^2 + 3^2.

    UnsignedNumber maxElement(pow(number, 0.5)); // max element is square root
    UnsignedNumbers squaredElements;
    squaredElements.reserve(maxElement-1);
    for(UnsignedNumber i=1; i<maxElement; i++)
    {
        squaredElements.emplace_back(i*i);
    }

    FourSum<UnsignedNumbers> fourSum(squaredElements);
    auto fourValues = fourSum.getPossibleDuplicatedFourValuesWithSum(number);
    UnsignedNumber sumOfSquares = get<0>(fourValues) + get<1>(fourValues) + get<2>(fourValues) + get<3>(fourValues);

    return sumOfSquares == number;
}

bool isZeckendorfTheoremTrue(UnsignedNumber const number)
{
    // Zeckendorf’s theorem states that every positive integer has a unique representation as a sum of Fibonacci numbers
    // such that no two numbers are equal or consecutive Fibonacci numbers.
    // For example, the number 74 can be represented as the sum 55 + 13 + 5 + 1.

    bool result(false);
    UnsignedNumbers fibonaccis(getFibonacciNumbersBelowThisNumber(number));

    bool isComplete(false);
    UnsignedNumbers fibonaccisForSum;
    findDistinctNonConsecutiveFibonacciNumbersForSum(isComplete, fibonaccisForSum, fibonaccis, number, 0);

    if(isComplete)
    {
        UnsignedNumber sumOfFibonaccis = accumulate(fibonaccisForSum.cbegin(), fibonaccisForSum.cend(), 0, std::plus<UnsignedNumber>());
        result = sumOfFibonaccis == number;
    }
    return result;
}

UnsignedNumber getNthFibonacciNumber(UnsignedNumber const number)
{
    // Binets formula:
    double sqrtOf5 = sqrt(5);
    double fibonacciInDouble = (pow(1+sqrtOf5, number)-pow(1-sqrtOf5, number)) / (pow(2, number)*sqrtOf5);
    return getIntegerAfterRoundingADoubleValue<UnsignedNumber>(fibonacciInDouble);
}

UnsignedNumbers getFibonacciNumbersBelowThisNumber(UnsignedNumber const number)
{
    UnsignedNumbers result;
    UnsignedNumber previousPreviousFibonacci(0);
    UnsignedNumber previousFibonacci(0);
    UnsignedNumber currentFibonacci(1);
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
