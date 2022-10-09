#pragma once

#include <string>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename HashValue>
class HornerHashFunctionForSubstrings // horners rule: continuously mod to keep the value
{
public:
    using HashValues = std::vector<HashValue>;

    HornerHashFunctionForSubstrings(
            HashValue const radix,
            HashValue const largeRandomPrime)
        : m_radix(radix)
        , m_largeRandomPrime(largeRandomPrime)
    {}

    HornerHashFunctionForSubstrings(
            HashValue const radix,
            HashValue const largeRandomPrime,
            std::string const& stringToHash)
        : m_radix(radix)
        , m_largeRandomPrime(largeRandomPrime)
        , m_stringToHash(stringToHash)
    {
        reinitializeHPartsAndPParts();
    }

    HashValue getHashCodeOfWholeString()
    {
        // The hash value of any substring s[a...b] can be calculated in O(1) time using the formula:
        // (h[b] - (h[a-1] * p[b-a+1])) mod B
        // assuming that a>0.
        // If a=0, the hash value is simply h[b].

        HashValue result{};
        if(m_stringToHash.length() > 0U)
        {
            result = getHashCodeOfSubstring(0U, m_stringToHash.length()-1);
        }
        return result;
    }

    HashValue getHashCodeOfSubstring(
            unsigned int const startIndex,
            unsigned int const endIndex)
    {
        // The hash value of any substring s[a...b] can be calculated in O(1) time using the formula:
        // (h[b] - (h[a-1] * p[b-a+1])) mod B
        // assuming that a>0.
        // If a=0, the hash value is simply h[b].

        HashValue result{};
        if(startIndex < m_stringToHash.length() && endIndex < m_stringToHash.length() && startIndex <= endIndex)
        {
            if(startIndex > 0)
            {
                result = ( m_largeRandomPrime + m_hParts.at(endIndex) - ((m_hParts.at(startIndex-1)*m_pParts.at(endIndex-startIndex+1)) % m_largeRandomPrime) )
                        % m_largeRandomPrime;
            }
            else
            {
                result = m_hParts.at(endIndex);
            }
        }
        return result;
    }

    void setNewString(std::string const& newStringToHash)
    {
        m_stringToHash = newStringToHash;
        clearHPartsAndPParts();
        reinitializeHPartsAndPParts();
    }

private:

    void clearHPartsAndPParts()
    {
        m_hParts.clear();
        m_pParts.clear();
    }

    void reinitializeHPartsAndPParts()
    {
        // Based from formula (check below): h[k] = (h[k-1]*A + s[k]) mod B
        // Based from formula (check below): p[k] = (p[k-1]*A) mod B

        m_hParts.reserve(m_stringToHash.length());
        m_pParts.reserve(m_stringToHash.length());
        m_hParts.emplace_back(m_stringToHash.front());
        m_pParts.emplace_back(1);
        for(auto it=m_stringToHash.cbegin()+1; it!=m_stringToHash.cend(); it++) // linear time
        {
            m_hParts.emplace_back((m_hParts.back() * m_radix + *it) % m_largeRandomPrime);
            m_pParts.emplace_back((m_pParts.back() * m_radix) % m_largeRandomPrime);
        }
        m_hParts.shrink_to_fit();
        m_pParts.shrink_to_fit();
    }

    HashValue m_radix;
    HashValue m_largeRandomPrime;
    std::string m_stringToHash;
    HashValues m_hParts;
    HashValues m_pParts;
};

// String hashing
// String hashing is a technique that allows us to efficiently check whether two strings are equal.
// The idea in string hashing is to compare hash values of strings instead of their individual characters.

// Calculating hash values
// A hash value of a string is a number that is calculated from the characters of the string.
// If two strings are the same, their hash values are also the same, which makes it possible to compare strings based on their hash values.
// A usual way to implement string hashing is polynomial hashing,
// which means that the hash value of a string s of length n is
// (s[0]A^(n-1) + s[1]A^(n-2) + ... + s[n-1]A^0) mod B
// where s[0], s[1],..., s[n-1] are interpreted as the codes of the characters of s, and A and B are pre-chosen constants.
// -> For example, the codes of the characters of ALLEY are:
// ---> 'A'=65, 'L'=76, 'L'=76, 'E'=69, 'Y'=89,
// -> Thus, if A=3 and B=97, the hash value of ALLEY is(65*3^4 + 76*3^3 + 76*3^2 + 69*3^1 + 89*3^0) mod 97 = 52.

// Preprocessing
// Using polynomial hashing, we can calculate the hash value of any substring of a string s in O(1) time after an O(n) time preprocessing.
// The idea is to construct an array h such that h[k] contains the hash value of the prefix s[0...k].
// The array values can be recursively calculated as follows:
// -> h[0] = s[0]
// -> h[k] = (h[k-1]*A + s[k]) mod B
// In addition, we construct an array p where p[k] Æ Ak mod B:
// -> p[0] = 1
// -> p[k] = (p[k-1]*A) mod B.
// Constructing these arrays takes O(n) time.
// After this, the hash value of any substring s[a...b] can be calculated in O(1) time using the formula
// (h[b] - h[a-1] * p[b-a+1]) mod B
// assuming that a>0.
// If a=0, the hash value is simply h[b].

// Using hash values
// We can efficiently compare strings using hash values.
// Instead of comparing the individual characters of the strings, the idea is to compare their hash values.
// If the hash values are equal, the strings are probably equal, and if the hash values are different, the strings are certainly different.
// Using hashing, we can often make a brute force algorithm efficient.
// -> As an example, consider the pattern matching problem:
// -> given a string s and a pattern p, find the positions where p occurs in s.
// ---> A brute force algorithm goes through all positions where p may occur and compares the strings character by character.
// ---> The time complexity of such an algorithm is O(n2).
// ---> We can make the brute force algorithm more efficient by using hashing, because the algorithm compares substrings of strings.
// ---> Using hashing, each comparison only takes O(1) time, because only hash values of substrings are compared.
// ---> This results in an algorithm with time complexity O(n), which is the best possible time complexity for this problem.
// By combining hashing and binary search, it is also possible to find out the lexicographic order of two strings in logarithmic time.
// This can be done by calculating the length of the common prefix of the strings using binary search.
// Once we know the length of the common prefix, we can just check the next character after the prefix, because this determines the order of the strings.

// Collisions and parameters
// An evident risk when comparing hash values is a collision, which means that two strings have different contents but equal hash values.
// In this case, an algorithm that relies on the hash values concludes that the strings are equal,
// but in reality they are not, and the algorithm may give incorrect results.
// Collisions are always possible, because the number of different strings is larger than the number of different hash values.
// However, the probability of a collision is small if the constants A and B are carefully chosen.
// A usual way is to choose random constants near 10^9, for example as follows: A=911382323 and B=972663749
// Using such constants, the long long type can be used when calculating hash values, because the products AB and BB will fit in long long.
// But is it enough to have about 10^9 different hash values?

// Let us consider three scenarios where hashing can be used:
// -> Scenario 1: Strings x and y are compared with each other.
// ---> The probability of a collision is 1/B assuming that all hash values are equally probable.
// -> Scenario 2: A string x is compared with strings y1, y2,..., yn.
// ---> The probability of one or more collisions is 1 - (1-1/B)^n.
// -> Scenario 3: All pairs of strings x1, x2,..., xn are compared with each other.
// ---> The probability of one or more collisions is 1 - (B*(B-1)*(B-2)*...*(B-n+1))/(B^n)

// The following table shows the collision probabilities when n = 10^6 and the value of B varies:
// |constant B|scenario 1|scenario 2|scenario 3
// |10^3      |0.001000  |1.000000  |1.000000
// |10^6      |0.000001  |0.632121  |1.000000
// |10^9      |0.000000  |0.001000  |1.000000
// |10^12     |0.000000  |0.000000  |0.393469
// |10^15     |0.000000  |0.000000  |0.000500
// |10^18     |0.000000  |0.000000  |0.000001
// The table shows that in scenario 1, the probability of a collision is negligible when B is near 10^9.
// In scenario 2, a collision is possible but the probability is still quite small.
// However, in scenario 3 the situation is very different: a collision will almost always happen when B is near 10^9.
// The phenomenon in scenario 3 is known as the birthday paradox:
// if there are n people in a room, the probability that some two people have the same birthday is large even if n is quite small.
// In hashing, correspondingly, when all hash values are compared with each other, the probability that some two hash values are equal is large.
// We can make the probability of a collision smaller by calculating multiple hash values using different parameters.
// It is unlikely that a collision would occur in all hash values at the same time.
// For example, two hash values with parameter B is near 10^9 correspond to one hash value with parameter B is near 10^18,
// which makes the probability of a collision very small.
// Some people use constants B =2^32 and B=2^64, which is convenient, because operations with 32 and 64 bit integers are calculated modulo 2^32 and 2^64.
// However, this is not a good choice, because it is possible to construct stringToHashs that always generate collisions when constants of the form 2^x are used.

}

}
