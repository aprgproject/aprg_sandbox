#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename DigitValue>
class Alphabet {
public:
    using DigitValues = std::vector<DigitValue>;

    Alphabet(std::string const& characters) : m_characters(characters) {}

    bool contains(char const c) { return stringHelper::isNotNpos(static_cast<int>(m_characters.find_first_of(c))); }

    char getCharacter(DigitValue const& digitValue) {
        char result{};
        if (digitValue < m_characters.size()) {
            result = m_characters[digitValue];
        }
        return result;
    }
    DigitValue getDigitValue(char const c) {
        DigitValue result{};
        int indexOfCharacter = m_characters.find_first_of(c);        if (stringHelper::isNotNpos(indexOfCharacter)) {
            result = static_cast<DigitValue>(indexOfCharacter);
        }
        return result;
    }

    int getRadix() { return m_characters.size(); }

    int getNumbersOfBitsToRepresentCharacters() {
        return AlbaBitValueUtilities<int>::getLogarithmWithBase2Of(getRadix());
    }

    DigitValues convertStringToDigitValues(std::string const& stringParameter) {
        DigitValues result;
        result.reserve(stringParameter.length());
        std::transform(stringParameter.cbegin(), stringParameter.cend(), std::back_inserter(result), [&](char const c) {
            return getDigitValue(c);
        });
        return result;
    }

    std::string convertDigitValuesToString(DigitValues const& digitValues) {
        std::string result;
        result.reserve(digitValues.size());
        std::transform(
            digitValues.cbegin(), digitValues.cend(), std::back_inserter(result),
            [&](DigitValue const& digitValue) { return getCharacter(digitValue); });
        return result;
    }

    std::string const& getCharacters() { return m_characters; }

private:
    std::string m_characters;
};

}  // namespace algorithm

}  // namespace alba
