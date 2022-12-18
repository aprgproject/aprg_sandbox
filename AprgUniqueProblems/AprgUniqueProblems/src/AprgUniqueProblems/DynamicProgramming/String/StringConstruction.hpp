#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <limits>
#include <vector>

namespace alba
{

class StringConstruction
{
public:
    // Given a string s of length n and a set of strings D whose total length is m,
    // consider the problem of counting the number of ways s can be formed as a concatenation of strings in D.
    // For example, if s = ABAB and D = {A, B, AB}, there are 4 ways:
    // -> A + B + A + B
    // -> AB + A + B
    // -> A + B + AB
    // -> AB + AB

    using HashValue = unsigned long long;
    using HashValues = std::vector<HashValue>;

    static constexpr HashValue RADIX=256U;
    static constexpr HashValue A_LARGE_PRIME=1229952067U;
    static constexpr HashValue UNUSED_VALUE=std::numeric_limits<unsigned int>::max();

    StringConstruction(
            std::string const& stringToConstruct,
            stringHelper::strings const& subStrings);

    unsigned int getCount();
    unsigned int getCountSquareRootAlgorithm();
private:
    void initialize();
    void removeEmptySubstrings();
    void removeDuplicateSubstrings();
    void saveHashOfAllSubstrings();
    unsigned int getCount(unsigned int const prefixLength);
    unsigned int getCountSquareRootAlgorithm(unsigned int const prefixLength);
    unsigned int count(unsigned int const prefixLength);
    unsigned int countSquareRootAlgorithm(unsigned int const prefixLength);

    std::string m_stringToConstruct;
    stringHelper::strings m_subStrings;
    HashValues m_subStringHash;
    std::vector<unsigned int> m_prefixLengthToCount; // dynamic programming
};

}
