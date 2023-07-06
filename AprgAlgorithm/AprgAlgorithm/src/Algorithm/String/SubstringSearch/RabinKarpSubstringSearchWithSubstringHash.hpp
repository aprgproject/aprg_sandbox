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

    RabinKarpSubstringSearchWithSubstringHash(std::string const& substringToMatch)
        : m_substringToMatch(substringToMatch),
          m_substringLength(substringToMatch.length()),
          m_substringHash(
              HornerHashFunctionForWholeString<HashValue>(RADIX, A_LARGE_PRIME).getHashCode(substringToMatch)) {}

    Index search(std::string const& mainString) {
        Index result(static_cast<Index>(std::string::npos));
        if (m_substringLength > 0 && m_substringLength <= static_cast<Index>(mainString.length())) {
            HornerHashFunctionForSubstrings<HashValue> hashFunction(RADIX, A_LARGE_PRIME, mainString);
            for (Index offset = 0; offset + m_substringLength <= static_cast<Index>(mainString.length()); offset++) {
                if (m_substringHash ==
                    hashFunction.getHashCodeOfSubstring(offset, offset + m_substringLength - 1)) {
                    result = offset;  // Monte carlo approach (no double check)
                    break;
                }
            }
        }
        return result;
    }

    std::string const m_substringToMatch;
    Index const m_substringLength;
    HashValue m_substringHash;
};

}  // namespace algorithm

}  // namespace alba
