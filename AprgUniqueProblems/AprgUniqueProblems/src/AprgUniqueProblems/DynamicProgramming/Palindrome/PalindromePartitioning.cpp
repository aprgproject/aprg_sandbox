#include "PalindromePartitioning.hpp"

using namespace std;

namespace alba
{

PalindromePartitioning::PalindromePartitioning(string const& stringParameter)
    : m_string(stringParameter)
{}

PalindromePartitioning::Count PalindromePartitioning::getMinimumNumberOfCutsUsingNaiveRecursion() const
{
    // Time Complexity: Exponential
    // Auxiliary Space: Constant

    Count result(0);
    if(!m_string.empty())
    {
        result = getMinimumNumberOfCutsUsingNaiveRecursion(0, m_string.length()-1);
    }
    return result;
}

PalindromePartitioning::Count PalindromePartitioning::getMinimumNumberOfCutsUsingMemoizationDP() const
{
    // Time Complexity: O(n^3) (should be same as Tabular DP)
    // Auxiliary Space: O(n^2)

    Count result(0);
    if(!m_string.empty())
    {
        CountMatrix countMatrix(m_string.length(), m_string.length(), static_cast<Count>(MAX_COUNT));
        result =  getMinimumNumberOfCutsUsingMemoizationDP(countMatrix, 0, m_string.length()-1);
    }
    return result;
}

PalindromePartitioning::Count PalindromePartitioning::getMinimumNumberOfCutsUsingTabularDP() const
{
    // Time Complexity: O(n^3)
    // Auxiliary Space: O(n^2)

    Count result(0);
    if(!m_string.empty())
    {
        Index stringLength = m_string.length();
        CountMatrix countMatrix(stringLength, stringLength, 0);

        for(Index length=1; length<=stringLength; length++)
        {
            for(Index left=0; left+length<=countMatrix.getNumberOfColumns(); left++)
            {
                Index right = left+length-1;
                Count entryResult(0);
                if(!isPalindrome(left, right))
                {
                    Count minimumCuts(MAX_COUNT);
                    for(Index cutIndex(left); cutIndex<right; cutIndex++)
                    {
                        minimumCuts = min(minimumCuts,
                                          countMatrix.getEntry(left, cutIndex)
                                          + countMatrix.getEntry(cutIndex+1, right));
                    }
                    entryResult = minimumCuts+1; // plus one because its cut in cutMatrix
                }
                countMatrix.setEntry(left, right, entryResult);
            }
        }
        result = countMatrix.getEntry(0, countMatrix.getNumberOfRows()-1);
    }
    return result;
}

PalindromePartitioning::Count PalindromePartitioning::getLongestLengthUsingTabularDPAndTimeEfficient() const
{
    // Time Complexity: O(n^2)
    // Auxiliary Space: O(n^2) (partialCounts is linear, but isSubstrAPalindrome is quadratic)

    Count result(0);
    if(!m_string.empty())
    {
        Index const stringLength = m_string.length();
        Counts partialCounts(stringLength, 0);
        BoolMatrix isSubstrAPalindrome(stringLength, stringLength, false);

        for(Index index=0; index<stringLength; index++)
        {
            isSubstrAPalindrome.setEntry(index, index, 1);
        }
        for(Index length=2; length<=stringLength; length++)
        {
            for(Index left=0; left+length<=stringLength; left++)
            {
                Index right = left+length-1;
                bool isCurrentSubstrAPalindrome(false);
                if(length==2)
                {
                    isCurrentSubstrAPalindrome = m_string.at(left)==m_string.at(right);
                }
                else
                {
                    isCurrentSubstrAPalindrome = m_string.at(left)==m_string.at(right) && isSubstrAPalindrome.getEntry(left+1, right-1);
                }
                isSubstrAPalindrome.setEntry(left, right, isCurrentSubstrAPalindrome);
            }
        }

        for(Index right=0; right<stringLength; right++)
        {
            if(!isSubstrAPalindrome.getEntry(0, right))
            {
                Count & partialCountAtIndex(partialCounts[right]);
                partialCountAtIndex = MAX_COUNT;
                for(Index left=0; left<right; left++)
                {
                    if(isSubstrAPalindrome.getEntry(left+1, right))
                    {
                        partialCountAtIndex = min(partialCountAtIndex, 1+partialCounts.at(left));
                    }
                }
            }
        }

        result = partialCounts.at(stringLength-1);
    }
    return result;
}

bool PalindromePartitioning::isPalindrome(Index const left, Index const right) const
{
    bool result(false);
    if(!m_string.empty())
    {
        result=true;
        unsigned int traverseLeft(left), traverseRight(right);
        while(traverseLeft<traverseRight)
        {
            if(m_string.at(traverseLeft++) != m_string.at(traverseRight--))
            {
                result=false;
                break;
            }
        }
    }
    return result;
}

PalindromePartitioning::Count PalindromePartitioning::getMinimumNumberOfCutsUsingNaiveRecursion(
        Index const left,
        Index const right) const
{
    Count result(0);
    if(left < right && !isPalindrome(left, right))
    {
        Count minimumCuts(MAX_COUNT);
        for(Index cutMatrix(left); cutMatrix<right; cutMatrix++)
        {
            minimumCuts = min(minimumCuts,
                              getMinimumNumberOfCutsUsingNaiveRecursion(left, cutMatrix)
                              + getMinimumNumberOfCutsUsingNaiveRecursion(cutMatrix+1, right));
        }
        result = minimumCuts+1; // plus one because its cut in cutMatrix
    }
    return result;
}

PalindromePartitioning::Count PalindromePartitioning::getMinimumNumberOfCutsUsingMemoizationDP(
        CountMatrix & countMatrix,
        Index const left,
        Index const right) const
{
    Count result(countMatrix.getEntry(left, right));
    if(MAX_COUNT == result)
    {
        result = 0;
        if(left < right && !isPalindrome(left, right))
        {
            Count minimumCuts(MAX_COUNT);
            for(Index cutIndex(left); cutIndex<right; cutIndex++)
            {
                minimumCuts = min(minimumCuts,
                                  getMinimumNumberOfCutsUsingMemoizationDP(countMatrix, left, cutIndex)
                                  + getMinimumNumberOfCutsUsingMemoizationDP(countMatrix, cutIndex+1, right));
            }
            result = minimumCuts+1; // plus one because its cut in cutMatrix
        }
        countMatrix.setEntry(left, right, result);
    }
    return result;
}

}
