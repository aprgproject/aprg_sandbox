#include "JosephusProblem.hpp"

#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithStaticSegmentTree.hpp>

#include <algorithm>

using namespace alba::algorithm;
using namespace std;

namespace alba {

JosephusProblem::Values JosephusProblem::getJosephusPermutationUsingIntervalTree(
    int const numberOfPeople, int const skipCount) {
    Values result;
    if (skipCount > 0) {
        RangeQueryWithStaticSegmentTree<Values> skipTree(Values(numberOfPeople, 1), plus<>());
        bool isFirst(true);
        for (int index = skipCount - 1; static_cast<int>(result.size()) < numberOfPeople;) {
            int actualSkip = 0;
            while (actualSkip < skipCount && !isFirst) {
                int possibleIndex = skipTree.getIndexWithTargetValue(index, skipCount - actualSkip, minus<>());
                if (possibleIndex == -1) {
                    actualSkip += skipTree.getValueOnInterval(index, numberOfPeople - 1);
                    index = 0;
                } else {
                    actualSkip = skipCount;
                    index = possibleIndex;
                }
            }
            isFirst = false;

            result.emplace_back(index + 1);
            skipTree.changeValueAtIndex(index, 0);
        }
    }
    return result;
}

}  // namespace alba
