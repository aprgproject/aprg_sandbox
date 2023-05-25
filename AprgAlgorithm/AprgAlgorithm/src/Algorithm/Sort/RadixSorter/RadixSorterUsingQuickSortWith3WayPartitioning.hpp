#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <functional>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values, typename DigitValue>
class RadixSorterUsingQuickSortWith3WayPartitioning : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;
    using GetDigitAtFunction = std::function<DigitValue(Value const&, int const)>;
    using IsDigitFunction = std::function<bool(Value const&, int const)>;

    RadixSorterUsingQuickSortWith3WayPartitioning() = delete;
    RadixSorterUsingQuickSortWith3WayPartitioning(
        GetDigitAtFunction const& getDigitAtFunction, IsDigitFunction const& isDigitValidFunction)
        : m_getDigitAtFunction(getDigitAtFunction), m_isDigitValidFunction(isDigitValidFunction) {}

    void sort(Values& valuesToSort) const override {
        // You can randomize inputs here to remove dependence on input (quick sort works best if input is not sorted)
        if (!valuesToSort.empty()) {
            sortStartingAtMostSignificantDigit(valuesToSort, 0, valuesToSort.size() - 1, 0);
        }
    }

    void sortStartingAtMostSignificantDigit(
        Values& valuesToSort, int const lowContainerIndex, int const highContainerIndex, int const digitIndex) const {
        if (lowContainerIndex < static_cast<int>(valuesToSort.size()) &&
            highContainerIndex < static_cast<int>(valuesToSort.size()) && lowContainerIndex < highContainerIndex) {
            sortInternal(valuesToSort, lowContainerIndex, highContainerIndex, digitIndex);
        }
    }

private:
    void sortInternal(
        Values& valuesToSort, int const lowContainerIndex, int const highContainerIndex, int const digitIndex) const {
        int lowIndexWithEqualValue = lowContainerIndex, i = lowContainerIndex + 1,
            highIndexWithEqualValue = highContainerIndex;
        Value const& partitionValue(valuesToSort.at(lowContainerIndex));  // use first value as partition

        DigitValue partitionDigit(m_getDigitAtFunction(partitionValue, digitIndex));
        bool shouldEqualPartProceed(m_isDigitValidFunction(partitionValue, digitIndex));
        while (i <= highIndexWithEqualValue) {
            DigitValue currentDigit(m_getDigitAtFunction(valuesToSort.at(i), digitIndex));
            if (currentDigit < partitionDigit) {
                std::swap(valuesToSort[lowIndexWithEqualValue++], valuesToSort[i]);
            } else if (currentDigit > partitionDigit) {
                std::swap(valuesToSort[i], valuesToSort[highIndexWithEqualValue--]);
            } else {
                i++;
            }
        }

        if (lowContainerIndex + 1 < lowIndexWithEqualValue) {
            sortInternal(valuesToSort, lowContainerIndex, lowIndexWithEqualValue - 1, digitIndex);  // sort lower part
        }
        if (shouldEqualPartProceed && lowIndexWithEqualValue < highIndexWithEqualValue) {
            sortInternal(
                valuesToSort, lowIndexWithEqualValue, highIndexWithEqualValue, digitIndex + 1);  // sort equal part
        }
        if (highIndexWithEqualValue + 1 < highContainerIndex) {
            sortInternal(
                valuesToSort, highIndexWithEqualValue + 1, highContainerIndex, digitIndex);  // sort higher part
        }
    }

    GetDigitAtFunction m_getDigitAtFunction;
    IsDigitFunction m_isDigitValidFunction;
};

// Overview: Do 3 way partitioning on the dth character.
// -> Less overhead than R-way partition in MSD string sort
// -> Does not re-examine character equal to the partitioning char (but does re-examine characters not equal to the
// partitioning char)

// Standard quicksort vs 3-way string radix sort
// -> Standard quicksort
// ---> Uses ~2N ln (N) string compares on average
// ---> Costly for keys with long common prefixes (and this is a common case!)
// -> 3-way string radix sort
// ---> Uses ~2N ln (N) character compares on average for random strings
// ---> Avoids re-comparing long common prefixes

// MSD string sort vs 3-way string radix sort
// -> MSD string sort
// ---> Is cache inefficient
// ---> Too much memory storing count[]
// ---> Too much overhead reinitializing count[] and aux[]
// -> 3-way string radix sort
// ---> Has a short inner loop
// ---> Is cache-friendly
// ---> Is in-place
// Bottom line is 3 way string quicksort is method of choice for sorting strings.

}  // namespace algorithm

}  // namespace alba
