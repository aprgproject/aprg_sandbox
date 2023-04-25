#pragma once

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>
void mergeTheTwoSortedParts(
    Values& valuesToSort, Values& auxiliary, unsigned int const lowest, unsigned int const middle,
    unsigned int const highest) {
    std::copy(valuesToSort.cbegin() + lowest, valuesToSort.cbegin() + highest + 1, auxiliary.begin() + lowest);
    unsigned int lowPartIndex = lowest, highPartIndex = middle + 1;
    for (unsigned int mainIndex = lowest; mainIndex <= highest; mainIndex++) {
        if (lowPartIndex > middle)  // low index is out of bounds means that low part is finished
        {
            std::copy(
                auxiliary.cbegin() + highPartIndex, auxiliary.cbegin() + highest + 1,
                valuesToSort.begin() + mainIndex);  // copy all remaining from high part
            break;
        } else if (highPartIndex > highest)  // high index is out of bounds means that high part is finished
        {
            std::copy(
                auxiliary.cbegin() + lowPartIndex, auxiliary.cbegin() + middle + 1,
                valuesToSort.begin() + mainIndex);  // copy all remaining from low part
            break;
        } else if (auxiliary.at(highPartIndex) < auxiliary.at(lowPartIndex))  // high part has lower value
        {
            valuesToSort[mainIndex] = auxiliary.at(highPartIndex++);  // copy and move high index
        } else {
            valuesToSort[mainIndex] = auxiliary.at(lowPartIndex++);  // copy and move low index
        }
    }
}

template <typename Values>
Values mergeTwoSortedSequences(Values const& sortedValues1, Values const& sortedValues2) {
    Values result;
    unsigned int i = 0, j = 0;
    while (i < sortedValues1.size() || j < sortedValues2.size()) {
        if (i >= sortedValues1.size())  // out of bounds means that its finished
        {
            std::copy(
                sortedValues2.cbegin() + j, sortedValues2.cend(),
                std::back_inserter(result));  // copy remaining from the other array
            break;
        } else if (j >= sortedValues2.size())  // out of bounds means that its finished
        {
            std::copy(
                sortedValues1.cbegin() + i, sortedValues1.cend(),
                std::back_inserter(result));  // copy remaining from the other array
            break;
        } else if (sortedValues2.at(j) < sortedValues1.at(i))  // second has lower value
        {
            result.emplace_back(sortedValues2.at(j++));  // copy and move second index
        } else                                           // first has lower value
        {
            result.emplace_back(sortedValues1.at(i++));  // copy and move first index
        }
    }
    return result;
}

}  // namespace algorithm

}  // namespace alba
