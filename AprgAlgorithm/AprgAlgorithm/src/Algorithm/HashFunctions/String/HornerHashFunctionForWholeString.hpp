#pragma once

#include <string>
#include <vector>

namespace alba {

namespace algorithm {

template <typename HashValue>
class HornerHashFunctionForWholeString  // horners rule: continuously mod to keep the value
{
public:
    HornerHashFunctionForWholeString(HashValue const radix, HashValue const largeRandomPrime)
        : m_radix(radix), m_largeRandomPrime(largeRandomPrime) {}

    HashValue getHashCode(std::string const& stringToHash) const { return getFinalHPart(stringToHash); }

private:
    HashValue getFinalHPart(std::string const& stringToHash) const {
        // Based from formula (check substrings file notes): h[k] = (h[k-1]*A + s[k]) mod B

        HashValue finalHPart(0);
        // linear time
        for (char const c : stringToHash) {
            finalHPart = (finalHPart * m_radix + c) % m_largeRandomPrime;
        }
        return finalHPart;
    }

    HashValue m_radix;
    HashValue m_largeRandomPrime;
};
}  // namespace algorithm

}  // namespace alba
