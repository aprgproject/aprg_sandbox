#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <array>
#include <functional>

namespace alba {

namespace algorithm {

template <typename Values, int MAX_NUMBER_OF_DIGIT_VALUES>
class LeastSignificantDigitSorter : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;
    using DigitValue = int;  // this needs to be indexable
    using ArrayOfCountPerDigitValue = std::array<int, MAX_NUMBER_OF_DIGIT_VALUES + 1>;
    using GetNumberOfDigitsFunction = std::function<int(Values const&)>;
    using GetDigitAtFunction = std::function<DigitValue(Value const&, int const)>;

    LeastSignificantDigitSorter() = delete;
    LeastSignificantDigitSorter(
        GetNumberOfDigitsFunction const& getNumberOfDigitsFunction, GetDigitAtFunction const& getDigitAtFunction)
        : m_getNumberOfDigitsFunction(getNumberOfDigitsFunction), m_getDigitAtFunction(getDigitAtFunction) {}

    void sort(Values& valuesToSort) const override {
        // highest index so least signficant first
        for (int digitIndex = static_cast<int>(m_getNumberOfDigitsFunction(valuesToSort)) - 1; 0 <= digitIndex;
             digitIndex--) {
            sortAtLeastSignificantDigit(valuesToSort, digitIndex);
        }
    }
    void sortAtLeastSignificantDigit(Values& valuesToSort, int const digitIndex) const {
        // This is called: "key indexed counting"
        // Character index starts in 1 because this array will be used to compute cumulates
        // For example (alphabet is a, b, c, d...), position translate to this:
        // 1) [0][a count][b count][c count]...
        // 2) [0][cumulate with a][cumulate with b][cumulate with c]...
        // 3) [a starting index][b starting index][c starting index][d starting index]...

        ArrayOfCountPerDigitValue newIndexes{};
        countTheFrequencyForEachCharacterAt(newIndexes, valuesToSort, digitIndex);
        computeCumulatesToGetNewIndexes(newIndexes);
        copyBackUsingNewIndexes(valuesToSort, newIndexes, digitIndex);
    }

private:
    void countTheFrequencyForEachCharacterAt(
        ArrayOfCountPerDigitValue& countPerDigitValue, Values const& valuesToSort, int const digitIndex) const {
        for (Value const& value : valuesToSort) {
            countPerDigitValue[m_getDigitAtFunction(value, digitIndex) + 1]++;
        }
    }

    void computeCumulatesToGetNewIndexes(ArrayOfCountPerDigitValue& newIndexes) const {
        int newIndexesSize = newIndexes.size();
        for (int i = 0; i + 1 < static_cast<int>(newIndexesSize); i++) {
            newIndexes[i + 1] += newIndexes[i];
        }
    }

    void copyBackUsingNewIndexes(
        Values& valuesToSort, ArrayOfCountPerDigitValue& newIndexes, int const digitIndex) const {
        Values copiedValues(valuesToSort);  // copy first and then copy back to output in the new indexes;
        for (Value const& copiedValue : copiedValues) {
            valuesToSort[newIndexes[m_getDigitAtFunction(copiedValue, digitIndex)]++] = copiedValue;
        }
    }

    GetNumberOfDigitsFunction m_getNumberOfDigitsFunction;
    GetDigitAtFunction m_getDigitAtFunction;
};

// Proposition: Key indexed counting uses ~11N+4R array accesses to sort N items whose keys are integers between 0 and
// R-1 Proposition: Key indexed counting uses extra space proportional to N+R. This is stable

// LSD string (radix) sort
// -> Consider characters from right to left
// -> Stably sort using dth character as the key (using key-indexed counting).

// Proposition: LSD sorts fixed length strings in ascending order
// Proof (by induction):
// -> After pass i, string are sorted by last i characters
// ---> If two strings differ on sort key, key indexed sort puts them in proper relative order.
// ---> If two strings agree on sort key, stability keeps them in proper relative order.

// Interview question: Sort a million 32-bit integers? -> LSD can be better because of fixed width
// -> Check the other RadixSorter for proof.

// LSD has history with punch cards

}  // namespace algorithm

}  // namespace alba
