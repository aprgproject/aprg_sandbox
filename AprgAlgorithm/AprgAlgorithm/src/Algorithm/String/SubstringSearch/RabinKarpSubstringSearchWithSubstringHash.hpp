#pragma once

#include <Algorithm/HashFunctions/String/HornerHashFunctionForSubstrings.hpp>
#include <Algorithm/HashFunctions/String/HornerHashFunctionForWholeString.hpp>

#include <string>

namespace alba {

namespace algorithm {

template <typename Index, typename HashValue>
class RabinKarpSubstringSearchWithSubstringHash {
public:
    using RadixType = int;
    static constexpr RadixType RADIX = 256;
    static constexpr HashValue A_LARGE_PRIME = 1229952067;  // hard coded for now (think of an implementation later)

    RabinKarpSubstringSearchWithSubstringHash(std::string const& query)
        : m_query(query),
          m_queryLength(query.length()),
          m_queryHash(
              HornerHashFunctionForWholeString<HashValue>(RADIX, A_LARGE_PRIME).getHashCode(query)) {}

    Index search(std::string const& searchSpace) {
        Index result(static_cast<Index>(std::string::npos));
        if (m_queryLength > 0 && m_queryLength <= static_cast<Index>(searchSpace.length())) {
            HornerHashFunctionForSubstrings<HashValue> hashFunction(RADIX, A_LARGE_PRIME, searchSpace);
            for (Index offset = 0; offset + m_queryLength <= static_cast<Index>(searchSpace.length()); offset++) {
                if (m_queryHash == hashFunction.getHashCodeOfSubstring(offset, offset + m_queryLength - 1)) {
                    result = offset;  // Monte carlo approach (no double check)
                    break;
                }            }
        }
        return result;
    }

    std::string const m_query;
    Index const m_queryLength;
    HashValue m_queryHash;
};

}  // namespace algorithm
}  // namespace alba