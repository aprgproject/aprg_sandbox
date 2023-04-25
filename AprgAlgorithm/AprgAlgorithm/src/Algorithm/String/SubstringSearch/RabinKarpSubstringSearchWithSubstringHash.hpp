#pragma once

#include <Algorithm/HashFunctions/ForString/HornerHashFunctionForSubstrings.hpp>
#include <Algorithm/HashFunctions/ForString/HornerHashFunctionForWholeString.hpp>

#include <string>

namespace alba {

namespace algorithm {

template <typename Index, typename HashValue>
class RabinKarpSubstringSearchWithSubstringHash {
public:
    using RadixType = unsigned int;
    static constexpr RadixType RADIX = 256U;
    static constexpr HashValue A_LARGE_PRIME = 1229952067U;  // hard coded for now (think of an implementation later)

    RabinKarpSubstringSearchWithSubstringHash(std::string const& substringToMatch)
        : m_substringToMatch(substringToMatch),
          m_substringLength(substringToMatch.length()),
          m_substringToMatchHash(
              HornerHashFunctionForWholeString<HashValue>(RADIX, A_LARGE_PRIME).getHashCode(substringToMatch)) {}

    Index search(std::string const& mainString) {
        Index result(static_cast<Index>(std::string::npos));
        if (m_substringLength > 0U && m_substringLength <= mainString.length()) {
            HornerHashFunctionForSubstrings<HashValue> hashFunction(RADIX, A_LARGE_PRIME, mainString);
            for (Index offset = 0; offset + m_substringLength <= mainString.length(); offset++) {
                if (m_substringToMatchHash ==
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
    HashValue m_substringToMatchHash;
};

}  // namespace algorithm

}  // namespace alba
