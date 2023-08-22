#include "StringConstruction.hpp"

#include <Algorithm/HashFunctions/String/HornerHashFunctionForSubstrings.hpp>
#include <Algorithm/HashFunctions/String/HornerHashFunctionForWholeString.hpp>

#include <algorithm>

using namespace alba::algorithm;
using namespace std;

namespace alba {

StringConstruction::StringConstruction(string const& stringToConstruct, stringHelper::strings const& subStrings)
    : m_stringToConstruct(stringToConstruct),
      m_subStrings(subStrings),
      m_prefixLengthToCount(stringToConstruct.length() + 1, UNUSED_VALUE) {
    initialize();
}

int StringConstruction::getCount() {
    int result(0);
    if (!m_stringToConstruct.empty()) {
        result = getCount(m_stringToConstruct.length());
    }
    return result;
}

int StringConstruction::getCountSquareRootAlgorithm() {
    int result(0);
    if (!m_stringToConstruct.empty()) {
        result = getCountSquareRootAlgorithm(m_stringToConstruct.length());
    }
    return result;
}

void StringConstruction::initialize() {
    removeEmptySubstrings();
    removeDuplicateSubstrings();
    saveHashOfAllSubstrings();
}

void StringConstruction::removeEmptySubstrings() {
    m_subStrings.erase(
        remove_if(m_subStrings.begin(), m_subStrings.end(), [](string const& subString) { return subString.empty(); }),
        m_subStrings.end());
}

void StringConstruction::removeDuplicateSubstrings() {
    sort(m_subStrings.begin(), m_subStrings.end());
    m_subStrings.erase(unique(m_subStrings.begin(), m_subStrings.end()), m_subStrings.end());
    // Note since that duplicate are removed so substrings are distinct.
}

void StringConstruction::saveHashOfAllSubstrings() {
    HornerHashFunctionForWholeString<HashValue> hashFunction(RADIX, A_LARGE_PRIME);
    m_subStringHash.reserve(m_subStrings.size());
    for (string const& subString : m_subStrings) {
        m_subStringHash.emplace_back(hashFunction.getHashCode(subString));
    }
}

int StringConstruction::getCount(int const prefixLength) {
    if (UNUSED_VALUE == m_prefixLengthToCount[prefixLength]) {
        m_prefixLengthToCount[prefixLength] = count(prefixLength);
    }
    return m_prefixLengthToCount[prefixLength];
}

int StringConstruction::getCountSquareRootAlgorithm(int const prefixLength) {
    if (UNUSED_VALUE == m_prefixLengthToCount[prefixLength]) {
        m_prefixLengthToCount[prefixLength] = countSquareRootAlgorithm(prefixLength);
    }
    return m_prefixLengthToCount[prefixLength];
}

int StringConstruction::count(int const prefixLength) {
    // We can solve the problem using dynamic programming:
    // Let count(k) denote the number of ways to construct the prefix s[0...k] using the strings in D.
    // Now count(n-1) gives the answer to the problem, and we can solve the problem in O(n2) time using a trie
    // structure.

    int result(0);
    for (string const& subString : m_subStrings) {
        int subStringLength = subString.length();
        if (subStringLength < prefixLength &&
            subString == m_stringToConstruct.substr(prefixLength - subStringLength, subStringLength)) {
            result += getCount(prefixLength - subStringLength);
        } else if (subStringLength == prefixLength && subString == m_stringToConstruct.substr(0, prefixLength)) {
            result++;
        }
    }
    return result;
}

int StringConstruction::countSquareRootAlgorithm(int const prefixLength) {
    // However, we can solve the problem more efficiently by using string hashing
    // and the fact that there are at most O(sqrt(m)) distinct string lengths in D.
    // First, we construct a set H that contains all hash values of the strings in D.
    // Then, when calculating a value of count(k), we go through all values of p such that
    // there is a string of length p in D, calculate the hash value of s[k-p+1...k] and check if it belongs to H.
    // Since there are at most O(sqrt(m)) distinct string lengths, this results in an algorithm whose running time is
    // O(n*sqrt(m)).

    HornerHashFunctionForSubstrings<HashValue> mainHashFunction(RADIX, A_LARGE_PRIME, m_stringToConstruct);

    int result(0);
    int limit = min(m_subStrings.size(), m_subStringHash.size());
    for (int i = 0; i < limit; i++) {
        int subStringLength = m_subStrings[i].length();
        HashValue subStringHash = m_subStringHash[i];

        // Note that getHashCodeOfSubstring is on constant time.
        if (subStringLength < prefixLength && subStringHash == mainHashFunction.getHashCodeOfSubstring(
                                                                   prefixLength - subStringLength, prefixLength - 1)) {
            result += getCountSquareRootAlgorithm(prefixLength - subStringLength);
        } else if (
            subStringLength == prefixLength &&
            subStringHash == mainHashFunction.getHashCodeOfSubstring(0, prefixLength - 1)) {
            result++;
        }
    }
    return result;
}

}  // namespace alba
