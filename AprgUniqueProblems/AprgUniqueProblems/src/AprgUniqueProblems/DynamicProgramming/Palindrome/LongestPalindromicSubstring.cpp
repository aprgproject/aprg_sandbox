#include "LongestPalindromicSubstring.hpp"

using namespace std;

namespace alba
{

LongestPalindromicSubstring::LongestPalindromicSubstring(string const& stringParameter)
    : m_string(stringParameter)
{}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingNaiveRecursion() const
{
    // Time Complexity: Exponential
    // Auxiliary Space: Constant

    Index result(0);
    if(!m_string.empty())
    {
        result = getLongestLengthUsingNaiveRecursion(0, m_string.length()-1);
    }
    return result;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingMemoizationDP() const
{
    // Time Complexity: O(n^2) (should be same as Tabular DP)
    // Auxiliary Space: O(n^2)

    Index result(0);
    if(!m_string.empty())
    {
        IndexMatrix lengthMatrix(m_string.length(), m_string.length(), static_cast<Index>(MAX_INDEX));
        result =  getLongestLengthUsingMemoizationDP(lengthMatrix, 0, m_string.length()-1);
    }
    return result;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingTabularDP() const
{
    // Time complexity: O(n^2).
    // -> Two nested traversals are needed.
    // Auxiliary Space: O(n^2).
    // -> Matrix of size n*n is needed to store the dp array.

    Index result(0);
    if(!m_string.empty())
    {
        result = 1;
        Index const stringLength = m_string.length();
        BoolMatrix isSubstrAPalindrome(stringLength, stringLength, false);

        for(Index index=0; index<stringLength; index++) // length = 1
        {
            isSubstrAPalindrome.setEntry(index, index, true);
        }
        for(Index index=0; index+1<stringLength; index++) // length = 2
        {
            if(m_string.at(index)==m_string.at(index+1))
            {
                isSubstrAPalindrome.setEntry(index, index+1, true);
                result = 2;
            }
        }
        for(Index length=3; length<=stringLength; length++) // length >= 3
        {
            for(Index left=0; left+length<=stringLength; left++)
            {
                Index right = left+length-1;
                if(m_string.at(left)==m_string.at(right) && isSubstrAPalindrome.getEntry(left+1, right-1))
                {
                    isSubstrAPalindrome.setEntry(left, right, true);
                    result = max(result, length);
                }
            }
        }
    }
    return result;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingTabularDPAndSpaceEfficient() const
{
    // Time complexity: O(n).
    // Auxiliary Space: O(n).

    Index result(0);
    if(!m_string.empty())
    {
        Index const stringLength = m_string.length();
        Indices palidromeLengths(stringLength, 1);
        for(Index right=1; right<stringLength; right++)
        {
            Index previousLength = palidromeLengths.at(right-1);
            if(previousLength==1 && m_string.at(right-1)==m_string.at(right)) // length = 2
            {
                palidromeLengths[right] = 2;
            }
            int possibleLeft = static_cast<int>(right)-1-static_cast<int>(previousLength);
            if(possibleLeft>=0 && m_string.at(possibleLeft)==m_string.at(right)) // length >= 3
            {
                palidromeLengths[right] = previousLength+2;
            }
        }
        result = *max_element(palidromeLengths.cbegin(), palidromeLengths.cend());
    }
    return result;
}

string LongestPalindromicSubstring::getLongestStringUsingTabularDPAndSpaceEfficient() const
{
    // Time complexity: O(n).
    // Auxiliary Space: O(n).

    string result;
    if(!m_string.empty())
    {
        Index const stringLength = m_string.length();
        Indices palidromeLengths(stringLength, 1);
        for(Index right=1; right<stringLength; right++)
        {
            Index previousLength = palidromeLengths.at(right-1);
            if(previousLength==1 && m_string.at(right-1)==m_string.at(right)) // length = 2
            {
                palidromeLengths[right] = 2;
            }
            int possibleLeft = static_cast<int>(right)-1-static_cast<int>(previousLength);
            if(possibleLeft>=0 && m_string.at(possibleLeft)==m_string.at(right)) // length >= 3
            {
                palidromeLengths[right] = previousLength+2;
            }
        }
        auto itMax = max_element(palidromeLengths.cbegin(), palidromeLengths.cend());
        Index indexOfLongestLength = distance(palidromeLengths.cbegin(), itMax);
        Index startIndex = indexOfLongestLength+1-palidromeLengths.at(indexOfLongestLength);
        for(; startIndex<=indexOfLongestLength; startIndex++)
        {
            result.push_back(m_string.at(startIndex));
        }
    }
    return result;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingNaiveRecursion(
        Index const left,
        Index const right) const
{
    Index result(0);
    Index length = right-left+1;
    if(length == 1)
    {
        result = 1;
    }
    else if(length == 2)
    {
        result = m_string.at(left)==m_string.at(right) ? 2 : 1;
    }
    else
    {
        bool isCompletePalindrome(false);
        if(m_string.at(left)==m_string.at(right))
        {
            Index middleLength = getLongestLengthUsingNaiveRecursion(left+1, right-1);
            if(middleLength+2 == length)
            {
                isCompletePalindrome = true;
                result=middleLength+2;
            }
        }

        if(!isCompletePalindrome)
        {
            result = max(getLongestLengthUsingNaiveRecursion(left+1, right), getLongestLengthUsingNaiveRecursion(left, right-1));
        }
    }
    return result;
}

LongestPalindromicSubstring::Index LongestPalindromicSubstring::getLongestLengthUsingMemoizationDP(
        IndexMatrix & lengthMatrix,
        Index const left,
        Index const right) const
{
    Index result(lengthMatrix.getEntry(left, right));
    if(MAX_INDEX == result)
    {
        Index length = right-left+1;
        if(length == 1)
        {
            result = 1;
        }
        else if(length == 2)
        {
            result = m_string.at(left)==m_string.at(right) ? 2 : 1;
        }
        else
        {
            bool isCompletePalindrome(false);
            if(m_string.at(left)==m_string.at(right))
            {
                Index middleLength = getLongestLengthUsingNaiveRecursion(left+1, right-1);
                if(middleLength+2 == length)
                {
                    isCompletePalindrome = true;
                    result=middleLength+2;
                }
            }

            if(!isCompletePalindrome)
            {
                result = max(getLongestLengthUsingMemoizationDP(lengthMatrix, left+1, right),
                             getLongestLengthUsingMemoizationDP(lengthMatrix, left, right-1));
            }
        }
        lengthMatrix.setEntry(left, right, result);
    }
    return result;
}

}
