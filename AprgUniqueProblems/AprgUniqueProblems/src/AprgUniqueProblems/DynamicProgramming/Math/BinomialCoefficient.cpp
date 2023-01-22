#include "BinomialCoefficient.hpp"

#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

using namespace std;

namespace alba
{

BinomialCoefficient::BinomialCoefficient(
        Value const n,
        Value const k)
    : m_n(n)
    , m_k(k)
{}

BinomialCoefficient::Value BinomialCoefficient::getBinomialCoefficientUsingNaiveRecursion() const
{
    // Time Complexity: Exponential -> Since there are two calls per iteration:  O(2^n)
    // Auxiliary Space: Constant

    return getBinomialCoefficientUsingNaiveRecursion(m_n, m_k);
}

BinomialCoefficient::Value BinomialCoefficient::getBinomialCoefficientUsingTabularDP() const
{
    // Time Complexity: O(n*k)
    // Auxiliary Space: O(n*k)

    Value result(0);
    if(m_n>=m_k)
    {
        ValueMatrix valueMatrix(m_n+1, m_k+1, 0);
        for(Value n=0; n<=m_n; n++)
        {
            valueMatrix.setEntry(n, 0, 1);
        }
        for(Value n=1; n<=m_n; n++)
        {
            Value lastK = min(n, m_k);
            for(Value k=1; k<=lastK; k++)
            {
                if(n==k)
                {
                    valueMatrix.setEntry(n, k, 1);
                }
                else
                {
                    valueMatrix.setEntry(n, k, valueMatrix.getEntry(n-1, k) + valueMatrix.getEntry(n-1, k-1));
                }
            }
        }
        result = valueMatrix.getEntry(valueMatrix.getNumberOfColumns()-1, valueMatrix.getNumberOfRows()-1);
    }
    return result;
}

BinomialCoefficient::Value BinomialCoefficient::getBinomialCoefficientUsingTabularDPAndSpaceEfficient() const
{
    // Time Complexity: O(n*k)
    // Auxiliary Space: O(k)

    // Space efficiency analysis:
    // Since accessing the previous partial values requires only one row above,
    // we only really need 1 row (not a matrix) to keep track partial values.

    // Explanation of the algorithm:
    // 1==========>> n = 0, C(0,0) = 1
    // 1–1========>> n = 1, C(1,0) = 1, C(1,1) = 1    // 1–2–1======>> n = 2, C(2,0) = 1, C(2,1) = 2, C(2,2) = 1
    // 1–3–3–1====>> n = 3, C(3,0) = 1, C(3,1) = 3, C(3,2) = 3, C(3,3)=1
    // 1–4–6–4–1==>> n = 4, C(4,0) = 1, C(4,1) = 4, C(4,2) = 6, C(4,3)=4, C(4,4)=1
    // So here every loop on i, builds i’th row of pascal triangle, using (i-1)th row.    // Visual representation:
    // [1][0][0][0][0] += [0][1][0][0][0][0]
    // [1][1][0][0][0] += [0][1][1][0][0][0]
    // [1][2][1][0][0] += [0][1][2][1][0][0]
    // [1][3][3][1][0] += [0][1][3][3][1][0]
    // [1][4][6][4][1] += [0][1][4][6][4][1]

    // At any time, every element of array C will have some value (ZERO or more) and in next iteration,
    // value for those elements comes from previous iteration.
    // In statement:
    // -> C[j] = C[j] + C[j-1]
    // The right-hand side represents the value coming from the previous iteration (a row of Pascal’s triangle depends on the previous row).
    // The left-Hand side represents the value of the current iteration which will be obtained by this statement.

    Value result(0);
    if(m_n>=m_k)
    {
        Values partialValues(m_k+1, 0);
        partialValues[0] = 1;
        for(Value n=1; n<=m_n; n++)
        {
            Value lastK = min(n, m_k);
            for(Value k=lastK; k>0; k--)
            {
                partialValues[k] += partialValues.at(k-1);
            }
        }
        result = partialValues.at(m_k);
    }
    return result;
}

BinomialCoefficient::Value BinomialCoefficient::getBinomialCoefficientUsingMemoizationDP() const
{
    // Time Complexity: O(n*k) (should be same as Tabular DP)
    // Auxiliary Space: O(n*k)

    Value result(0);
    if(m_n>=m_k)
    {
        ValueMatrix valueMatrix(m_n+1, m_k+1, static_cast<Value>(UNUSED_VALUE));
        result = getBinomialCoefficientUsingMemoizationDP(valueMatrix, m_n, m_k);
    }
    return result;
}

BinomialCoefficient::Value BinomialCoefficient::getBinomialCoefficientUsingNaiveRecursion(
        Value const n,
        Value const k) const
{
    if(n<k)
    {
        return 0;
    }
    else if(k==0 || n==k)
    {
        return 1;
    }
    else
    {
        return getBinomialCoefficientUsingNaiveRecursion(n-1, k)
                + getBinomialCoefficientUsingNaiveRecursion(n-1, k-1);
    }
}

BinomialCoefficient::Value BinomialCoefficient::getBinomialCoefficientUsingMemoizationDP(
        ValueMatrix & valueMatrix,
        Value const n,
        Value const k) const
{
    if(n<k)
    {
        return 0;
    }
    else if(k==0 || n==k)
    {
        return 1;
    }
    else
    {
        Value result = valueMatrix.getEntry(n, k);
        if(UNUSED_VALUE == result)
        {
            result=getBinomialCoefficientUsingMemoizationDP(valueMatrix, n-1, k)
                    + getBinomialCoefficientUsingMemoizationDP(valueMatrix, n-1, k-1);
            valueMatrix.setEntry(n, k, result);
        }
        return result;
    }
}

BinomialCoefficient::Value BinomialCoefficient::getBinomialCoefficientUsingGcf() const
{
    // Time Complexity: O(n*log(n))
    // Auxiliary Space: O(1)

    // Same as with mathHelper

    Value result(0);
    if(m_n >= m_k)
    {
        result = 1;
        Value numerator=m_n;
        Value denominator=m_k;
        Value accumulatedNumerator=1;
        Value accumulatedDenominator=1;
        bool shouldContinue=true;
        while(shouldContinue)
        {
            shouldContinue = false;
            if(numerator > m_n-m_k)
            {
                accumulatedNumerator *= numerator--;
                shouldContinue = true;
            }
            if(denominator > 1)
            {
                accumulatedDenominator *= denominator--;
                shouldContinue = true;
            }
            if(shouldContinue && accumulatedDenominator>1 && mathHelper::isValueBeyondLimits<Value>(static_cast<double>(accumulatedNumerator)*numerator))
            {
                Value gcf = mathHelper::getGreatestCommonFactor(accumulatedNumerator, accumulatedDenominator);
                accumulatedNumerator /= gcf;
                accumulatedDenominator /= gcf;
            }
        }
        result = accumulatedNumerator/accumulatedDenominator;
    }
    return result;
}

}
