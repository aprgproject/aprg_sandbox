#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <cstdint>
#include <limits>
#include <vector>
namespace alba {

class StringConstruction {public:
    // Given a string s of length n and a set of strings D whose total length is m,
    // consider the problem of counting the number of ways s can be formed as a concatenation of strings in D.
    // For example, if s = ABAB and D = {A, B, AB}, there are 4 ways:
    // -> A + B + A + B
    // -> AB + A + B
    // -> A + B + AB
    // -> AB + AB

    using HashValue = uint64_t;
    using HashValues = std::vector<HashValue>;

    static constexpr HashValue RADIX = 256;
    static constexpr HashValue A_LARGE_PRIME = 1229952067;
    static constexpr HashValue UNUSED_VALUE = std::numeric_limits<int>::max();

    StringConstruction(std::string const& stringToConstruct, stringHelper::strings const& subStrings);

    int getCount();
    int getCountSquareRootAlgorithm();

private:
    void initialize();
    void removeEmptySubstrings();
    void removeDuplicateSubstrings();
    void saveHashOfAllSubstrings();
    int getCount(int const prefixLength);
    int getCountSquareRootAlgorithm(int const prefixLength);
    int count(int const prefixLength);
    int countSquareRootAlgorithm(int const prefixLength);

    std::string m_stringToConstruct;
    stringHelper::strings m_subStrings;
    HashValues m_subStringHash;
    std::vector<int> m_prefixLengthToCount;  // dynamic programming using memoization
};

}  // namespace alba