#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <algorithm>
#include <array>
#include <functional>

namespace alba {

namespace algorithm {

template <typename Values, int MAX_NUMBER_OF_DIGIT_VALUES>
class MostSignificantDigitSorter : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;
    using DigitValue = int;  // this needs to be indexable
    using ArrayOfCountPerDigitValue =
        std::array<int, MAX_NUMBER_OF_DIGIT_VALUES + 2>;  // offset of two for cumulate and copying back
    using GetDigitAtFunction = std::function<DigitValue(Value const&, int const)>;
    using IsDigitFunction = std::function<bool(Value const&, int const)>;
    static constexpr int CUTOFF_TO_SMALLER_SORT = 0;  // switch to different sort when size is small

    MostSignificantDigitSorter() = delete;
    MostSignificantDigitSorter(
        GetDigitAtFunction const& getDigitAtFunction, IsDigitFunction const& isDigitInvalidFunction)
        : m_getDigitAtFunction(getDigitAtFunction), m_isDigitInvalidFunction(isDigitInvalidFunction) {}

    void sort(Values& valuesToSort) const override {
        sortStartingAtMostSignificantDigit(valuesToSort, 0, valuesToSort.size() - 1, 0);
    }

    void sortStartingAtMostSignificantDigit(
        Values& valuesToSort, int const lowContainerIndex, int const highContainerIndex, int const digitIndex) const {
        if (lowContainerIndex < static_cast<int>(valuesToSort.size()) &&
            highContainerIndex < static_cast<int>(valuesToSort.size()) && lowContainerIndex < highContainerIndex) {
            sortStartingAtMostSignificantDigitInternal(valuesToSort, lowContainerIndex, highContainerIndex, digitIndex);
        }
    }

private:
    void sortStartingAtMostSignificantDigitInternal(
        Values& valuesToSort, int const lowContainerIndex, int const highContainerIndex, int const digitIndex) const {
        if (highContainerIndex <= lowContainerIndex + CUTOFF_TO_SMALLER_SORT) {
            sortForSmallerSizes(valuesToSort, lowContainerIndex, highContainerIndex);
        } else {
            sortStartingAtMostSignificantDigitUsingNewIndexes(
                valuesToSort, lowContainerIndex, highContainerIndex, digitIndex);
        }
    }

    void sortForSmallerSizes(Values& valuesToSort, int const lowContainerIndex, int const highContainerIndex) const {
        std::sort(valuesToSort.begin() + lowContainerIndex, valuesToSort.begin() + highContainerIndex + 1);
    }

    void sortStartingAtMostSignificantDigitUsingNewIndexes(
        Values& valuesToSort, int const lowContainerIndex, int const highContainerIndex, int const digitIndex) const {
        // Key indexed counting
        // Character index start at two because interval must be noted
        // The reason its two, is because (1) is used for offset for cumulate and (2) is used for index for copying back
        // For example (alphabet is a, b, c, d...), position translate to this:
        // 1) [0][0][a count][b count][c count]...
        // 2) [0][0][cumulate with a][cumulate with b][cumulate with c]...
        // 3) [0][a count for copying back][cumulate with a]
        // 4) [a low index][b low index (a high index+1)][c low index (b high index+1)][d low index (c high index+1)]...

        ArrayOfCountPerDigitValue newIndexes{};
        bool areAllDigitsInvalid(true);
        saveFrequencyForEachCharacterAt(
            newIndexes, areAllDigitsInvalid, valuesToSort, lowContainerIndex, highContainerIndex, digitIndex);
        if (!areAllDigitsInvalid) {
            computeCumulatesToGetNewIndexes(newIndexes);
            copyBackUsingNewIndexes(valuesToSort, newIndexes, lowContainerIndex, highContainerIndex, digitIndex);
            sortForEachCharacterValue(valuesToSort, newIndexes, lowContainerIndex, digitIndex);
        }
    }

    void saveFrequencyForEachCharacterAt(
        ArrayOfCountPerDigitValue& countPerDigitValue, bool& areAllDigitsInvalid, Values const& valuesToSort,
        int const lowContainerIndex, int const highContainerIndex, int const digitIndex) const {
        int limit(std::min(highContainerIndex + 1, static_cast<int>(valuesToSort.size())));
        // starts at low container index and ends at high container index
        for (auto it = valuesToSort.cbegin() + lowContainerIndex; it != valuesToSort.cbegin() + limit; it++) {
            Value const& value(*it);
            countPerDigitValue[m_getDigitAtFunction(value, digitIndex) + 2]++;
            areAllDigitsInvalid &= m_isDigitInvalidFunction(value, digitIndex);        }
    }

    void computeCumulatesToGetNewIndexes(ArrayOfCountPerDigitValue& newIndexes) const {
        for (int i = 0; i + 1 < static_cast<int>(newIndexes.size()); i++) {
            newIndexes[i + 1] += newIndexes[i];
        }
    }

    void copyBackUsingNewIndexes(
        Values& valuesToSort, ArrayOfCountPerDigitValue& newIndexes, int const lowContainerIndex,
        int const highContainerIndex, int const digitIndex) const {
        Values copiedValues(valuesToSort);  // copy first and then copy back to output in the new indexes;
        int limit(std::min(highContainerIndex + 1, static_cast<int>(copiedValues.size())));
        // starts at low container index and ends at high container index
        for (auto it = copiedValues.cbegin() + lowContainerIndex; it != copiedValues.cbegin() + limit; it++) {
            // replace index uses the character index before it
            Value const& copiedValue(*it);
            int replaceIndex = lowContainerIndex + newIndexes[m_getDigitAtFunction(copiedValue, digitIndex) + 1]++;            valuesToSort[replaceIndex] = copiedValue;
        }
    }

    void sortForEachCharacterValue(
        Values& valuesToSort, ArrayOfCountPerDigitValue const& newIndexes, int const lowContainerIndex,
        int const digitIndex) const {
        for (int i = 0; i < MAX_NUMBER_OF_DIGIT_VALUES; i++) {
            if (newIndexes[i] + 1 < newIndexes[i + 1]) {
                int newLowContainerIndex(lowContainerIndex + newIndexes[i]);
                int newHighContainerIndex(lowContainerIndex + newIndexes[i + 1] - 1);
                sortStartingAtMostSignificantDigitInternal(
                    valuesToSort, newLowContainerIndex, newHighContainerIndex, digitIndex + 1);
            }
        }
    }

    GetDigitAtFunction m_getDigitAtFunction;
    IsDigitFunction m_isDigitInvalidFunction;
};

}  // namespace algorithm

}  // namespace alba

// MSD string (radix) sort.
// -> Partition the array into R pieces according to first character (use key-index counting).
// -> Recursively sort all strings start with each character (Key-indexed counts delineate subarrays to sort)

// MSD string sort: potential for disastrous performance
// Observation 1: Mush too slow for small subarrays
// -> Each function calls needs its own count[] array.
// -> ASCII (256 counts): 100x slower than copy pass for N=2
// -> ASCII (65536 counts): 32000x slower for N=2
// Observation 2: Huge number of small subarrays because of recursion
// Solution: Cutoff to insertion sort for small subarrays.

// Peformance: Number of characters examined
// -> MSD examines just enough characters to sort the keys
// -> Number of characters examined depends on keys.
// -> Can be sublinear in input size

// MSD string sort vs quicksort for strings
// -> Disadvantages of MSD string sort.
// ---> Accesses memory "randomly" (cache inefficient)
// ---> Inner loop has a lot of instructions
// ---> Extra space for count[]
// ---> Extra space for aux[]
// -> Disadvantages of quicksort
// ---> Linearithmic number of string compares (not linear)
// ---> Has to rescan many characters in keys with long prefix matches
// Goal combine advantages of MSD and quick sort
