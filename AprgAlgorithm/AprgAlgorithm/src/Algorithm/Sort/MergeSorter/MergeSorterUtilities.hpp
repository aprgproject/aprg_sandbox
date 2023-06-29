#pragma once

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>
void mergeTheTwoSortedParts(
    Values& valuesToSort, Values& auxiliary, int const lowest, int const middle, int const highest) {
    std::copy(valuesToSort.cbegin() + lowest, valuesToSort.cbegin() + highest + 1, auxiliary.begin() + lowest);
    int mainIndex = lowest, lowPartIndex = lowest, highPartIndex = middle + 1;
    for (; mainIndex <= highest && lowPartIndex <= middle && highPartIndex <= highest; mainIndex++) {
        if (auxiliary[highPartIndex] < auxiliary[lowPartIndex]) {  // high part has lower value
            valuesToSort[mainIndex] = auxiliary[highPartIndex++];  // copy and move high index
        } else {
            valuesToSort[mainIndex] = auxiliary[lowPartIndex++];  // copy and move low index
        }
    }
    std::copy(auxiliary.cbegin() + lowPartIndex, auxiliary.cbegin() + middle + 1, valuesToSort.begin() + mainIndex);
    std::copy(auxiliary.cbegin() + highPartIndex, auxiliary.cbegin() + highest + 1, valuesToSort.begin() + mainIndex);
}

template <typename Values>Values mergeTwoSortedSequences(Values const& sortedValues1, Values const& sortedValues2) {
    Values result;
    result.reserve(sortedValues1.size() + sortedValues2.size());
    int i = 0, j = 0;
    while (i < static_cast<int>(sortedValues1.size()) && j < static_cast<int>(sortedValues2.size())) {
        if (sortedValues2[j] < sortedValues1[i]) {    // second has lower value
            result.emplace_back(sortedValues2[j++]);  // copy and move second index
        } else {                                      // first has lower value
            result.emplace_back(sortedValues1[i++]);  // copy and move first index
        }
    }
    if (i < static_cast<int>(sortedValues1.size())) {        // copy remaining from the other array
        std::copy(sortedValues1.cbegin() + i, sortedValues1.cend(), std::back_inserter(result));
    }
    if (j < static_cast<int>(sortedValues2.size())) {
        // copy remaining from the other array
        std::copy(sortedValues2.cbegin() + j, sortedValues2.cend(), std::back_inserter(result));
    }
    return result;
}

}  // namespace algorithm

}  // namespace alba
