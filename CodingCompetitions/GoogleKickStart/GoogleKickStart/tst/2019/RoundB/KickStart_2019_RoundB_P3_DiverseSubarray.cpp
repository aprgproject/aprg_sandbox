// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundB_P3_DiverseSubarray.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_RoundB_P3_DiverseSubarray {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

struct TypeDetail {
    optional<int> negativeDeltaIndexOptional;
    deque<int> zeroDeltaIndices;
};

int numberOfTrinkets, allowableCountForAType;
vector<int> typeToCountMap;
constexpr int MAX_NUMBER_TYPES = 100001;

template <typename Index>
class SegmentTreeUtilities {
public:
    // rule of five or six
    SegmentTreeUtilities() = delete;
    ~SegmentTreeUtilities() = delete;
    SegmentTreeUtilities(SegmentTreeUtilities const&) = delete;
    SegmentTreeUtilities& operator=(SegmentTreeUtilities const&) = delete;
    SegmentTreeUtilities(SegmentTreeUtilities&&) = delete;
    SegmentTreeUtilities& operator=(SegmentTreeUtilities&&) = delete;

    static constexpr Index ROOT_PARENT_INDEX = 0;   // the first parent
    static constexpr Index NUMBER_OF_CHILDREN = 2;  // only 2 children

    static inline bool isALeftChild(Index const treeIndex) { return treeIndex % 2 == 1; }

    static inline bool isARightChild(Index const treeIndex) { return treeIndex % 2 == 0; }

    static inline Index getParent(Index const treeIndex) { return ((treeIndex + 1) / NUMBER_OF_CHILDREN) - 1; }

    static inline Index getLeftChild(Index const parent) { return (parent * NUMBER_OF_CHILDREN) + 1; }

    static inline Index getRightChild(Index const parent) { return (parent * NUMBER_OF_CHILDREN) + 2; }

    static inline Index getMinimumNumberOfParents(Index const numberOfValues) {
        Index result(0);
        if (numberOfValues > 0) {
            result = static_cast<int>(pow(NUMBER_OF_CHILDREN, ceil(log(numberOfValues) / log(NUMBER_OF_CHILDREN)))) - 1;
        }
        return result;
    }
};

template <typename Values>
class RangeQueryWithStaticSegmentTree {
public:
    using Index = int;
    using Value = typename Values::value_type;
    using Function = std::function<Value(Value const&, Value const&)>;
    using Utilities = SegmentTreeUtilities<Index>;

    RangeQueryWithStaticSegmentTree() = default;

    RangeQueryWithStaticSegmentTree(Values const& valuesToCheck, Function const& functionObject)
        : m_startOfChildren(0), m_treeValues(), m_function(functionObject) {
        initialize(valuesToCheck);
    }

    Index getStartOfChildren() const { return m_startOfChildren; }

    Values const& getTreeValues() const { return m_treeValues; }

    Value getValueOnInterval(Index const start, Index const end) const  // bottom to top approach
    {
        // This has log(N) running time
        return getValueOnIntervalFromBottomToTop(start, end);
    }

    void changeValueAtIndex(Index const index, Value const& newValue) {
        // This has log(N) running time
        changeValueAtIndexFromBottomToTop(index, newValue);
    }

    Value getMaximumSum() {
        Index maxSumParent = 0;  // start at the top
        while (true) {
            Index nextIndex = maxSumParent;
            Index leftChildIndex = Utilities::getLeftChild(nextIndex);
            if (leftChildIndex < static_cast<int>(m_treeValues.size())) {
                if (m_treeValues[nextIndex] < m_treeValues[leftChildIndex]) {
                    nextIndex = leftChildIndex;
                }
            }
            Index rightChildIndex = Utilities::getRightChild(nextIndex);
            if (rightChildIndex < static_cast<int>(m_treeValues.size())) {
                if (m_treeValues[nextIndex] < m_treeValues[rightChildIndex]) {
                    nextIndex = rightChildIndex;
                }
            }
            if (nextIndex == maxSumParent) {
                break;
            }
            maxSumParent = nextIndex;
        }

        Index maxSumLeftMostChild = maxSumParent;
        while (maxSumLeftMostChild < m_startOfChildren) {
            maxSumLeftMostChild = Utilities::getLeftChild(maxSumLeftMostChild);
        }

        Index maxSumRightMostChild = maxSumParent;
        while (maxSumRightMostChild < m_startOfChildren) {
            maxSumRightMostChild = Utilities::getRightChild(maxSumRightMostChild);
        }

        Value maxSum(m_treeValues[maxSumParent]);
        maxSumLeftMostChild--;
        while (maxSumLeftMostChild >= m_startOfChildren) {
            Value additionalValue = m_treeValues[maxSumLeftMostChild];
            if (additionalValue >= 0) {
                maxSum += additionalValue;
                maxSumLeftMostChild--;
            } else {
                break;
            }
        }
        maxSumRightMostChild++;
        while (maxSumRightMostChild >= m_startOfChildren &&
               maxSumRightMostChild < static_cast<int>(m_treeValues.size())) {
            Value additionalValue = m_treeValues[maxSumRightMostChild];
            if (additionalValue >= 0) {
                maxSum += additionalValue;
                maxSumRightMostChild++;
            } else {
                break;
            }
        }
        return maxSum;
    }

protected:
    void initialize(Values const& valuesToCheck) {
        if (!valuesToCheck.empty()) {
            m_startOfChildren = Utilities::getMinimumNumberOfParents(valuesToCheck.size());
            Index totalSize = m_startOfChildren + valuesToCheck.size();

            m_treeValues.resize(totalSize);
            m_treeValues.shrink_to_fit();
            std::copy(
                valuesToCheck.cbegin(), valuesToCheck.cend(),
                m_treeValues.begin() + m_startOfChildren);  // copy children

            Index treeBaseLeft(m_startOfChildren);
            Index treeBaseRight(totalSize - 1);
            while (treeBaseLeft < treeBaseRight)  // fill up parent values
            {
                Index treeBaseRightComplete = treeBaseRight;
                if (Utilities::isALeftChild(treeBaseRight))  // incomplete pair
                {
                    m_treeValues[Utilities::getParent(treeBaseRight)] = m_treeValues[treeBaseRight];
                    treeBaseRightComplete--;
                }
                for (Index treeIndex = treeBaseLeft; treeIndex < treeBaseRightComplete;
                     treeIndex += Utilities::NUMBER_OF_CHILDREN)  // complete pairs
                {
                    m_treeValues[Utilities::getParent(treeIndex)] =
                        m_function(m_treeValues[treeIndex], m_treeValues[treeIndex + 1]);
                }
                treeBaseLeft = Utilities::getParent(treeBaseLeft);
                treeBaseRight = Utilities::getParent(treeBaseRight);
            }
        }
    }

    Value getValueOnIntervalFromBottomToTop(Index const start, Index const end) const {
        // This has log(N) running time
        Value result{};
        Index first(m_startOfChildren + start);
        Index last(m_startOfChildren + end);
        if (first <= last && first < m_treeValues.size() && last < m_treeValues.size()) {
            result = m_treeValues[first++];
            while (first < last) {
                if (Utilities::isARightChild(first)) {
                    result = m_function(
                        result, m_treeValues[first++]);  // move to next value (right) because current value is added
                }
                if (Utilities::isALeftChild(last)) {
                    result = m_function(
                        result, m_treeValues[last--]);  // move to next value (left) because current value is added
                }
                first = Utilities::getParent(first);
                last = Utilities::getParent(last);
            }
            if (first == last)  // add value if it ends on the same place
            {
                result = m_function(result, m_treeValues[first]);
            }
        }
        return result;
    }

    void changeValueAtIndexFromBottomToTop(Index const index, Value const& newValue) {
        // This has log(N) running time
        Index treeIndex(m_startOfChildren + index);
        if (treeIndex < static_cast<int>(m_treeValues.size())) {
            m_treeValues[treeIndex] = newValue;
            if (m_treeValues.size() > 2) {
                while (treeIndex > 0) {
                    Index parentIndex(Utilities::getParent(treeIndex));
                    if (Utilities::isALeftChild(treeIndex)) {
                        if (treeIndex + 1 < static_cast<int>(m_treeValues.size())) {
                            m_treeValues[parentIndex] =
                                m_function(m_treeValues[treeIndex], m_treeValues[treeIndex + 1]);
                        } else {
                            m_treeValues[parentIndex] = m_treeValues[treeIndex];
                        }
                    } else {
                        m_treeValues[parentIndex] =
                            m_function(m_treeValues[treeIndex - 1], m_treeValues[treeIndex]);
                    }
                    treeIndex = parentIndex;
                }
                m_treeValues[0] = m_function(m_treeValues[1], m_treeValues[2]);
            } else if (m_treeValues.size() > 1) {
                m_treeValues[0] = m_treeValues[1];
            }
        }
    }

    Index m_startOfChildren;
    Values m_treeValues;
    Function m_function;
};

int getDeltaByAddingType(int const type) {
    int delta = 0;
    int& count(typeToCountMap[type]);
    if (count > allowableCountForAType) {
        // do nothing
    } else if (count == allowableCountForAType) {
        delta = -allowableCountForAType;
    } else {
        delta = 1;
    }
    count++;
    return delta;
}

void runTestCase(int const testCaseNumber) {
    my_cin >> numberOfTrinkets >> allowableCountForAType;
    vector<int> typesOfTrinkets(numberOfTrinkets, 0);
    for (int i = 0; i < numberOfTrinkets; ++i) {
        my_cin >> typesOfTrinkets[i];
    }

    typeToCountMap.assign(MAX_NUMBER_TYPES, 0);

    vector<int> deltas;
    vector<TypeDetail> typeDetails(MAX_NUMBER_TYPES);
    deltas.reserve(numberOfTrinkets);
    for (int i = 0; i < numberOfTrinkets; ++i) {
        int type = typesOfTrinkets[i];
        int delta = getDeltaByAddingType(type);
        if (delta < 0) {
            typeDetails[type].negativeDeltaIndexOptional = i;
        }
        if (delta == 0) {
            typeDetails[type].zeroDeltaIndices.emplace_back(i);
        }
        deltas.emplace_back(delta);
    }

    RangeQueryWithStaticSegmentTree<vector<int>> segmentTreeOfDeltas(deltas, std::plus<>());
    int maxAllowableCount = segmentTreeOfDeltas.getMaximumSum();

    for (int i = 0; i < numberOfTrinkets; ++i) {
        segmentTreeOfDeltas.changeValueAtIndex(i, 0);
        int type = typesOfTrinkets[i];
        TypeDetail& typeDetail(typeDetails[type]);
        if (typeDetail.negativeDeltaIndexOptional) {
            segmentTreeOfDeltas.changeValueAtIndex(typeDetail.negativeDeltaIndexOptional.value(), 1);
            if (!typeDetail.zeroDeltaIndices.empty()) {
                int firstZeroIndex = typeDetail.zeroDeltaIndices.front();
                segmentTreeOfDeltas.changeValueAtIndex(firstZeroIndex, -allowableCountForAType);
                typeDetail.negativeDeltaIndexOptional = firstZeroIndex;
                typeDetail.zeroDeltaIndices.pop_front();
            } else {
                typeDetail.negativeDeltaIndexOptional.reset();
            }
        }
        maxAllowableCount = max(maxAllowableCount, segmentTreeOfDeltas.getMaximumSum());
    }

    my_cout << "Case #" << testCaseNumber << ": " << maxAllowableCount << '\n';
}

/*
// My Solution but takes too long
void addTypeToAllowableCount(int & allowableCount, int const type)
{
    int & count(typeToCountMap[type]);
    if(count > allowableCountForAType)
    {
        // do nothing
    }
    else if(count == allowableCountForAType)
    {
        allowableCount -= count;
    }
    else
    {
        allowableCount++;
    }
    count++;
}

void removeTypeToAllowableCount(int & allowableCount, int const type)
{
    int & count(typeToCountMap[type]);
    count--;
    if(count > allowableCountForAType)
    {
        // do nothing
    }
    else if(count == allowableCountForAType)
    {
        allowableCount += count;
    }
    else
    {
        allowableCount--;
    }
}

void runTestCase(int const testCaseNumber)
{
    my_cin >> numberOfTrinkets >> allowableCountForAType;

    vector<int> typesOfTrinkets(numberOfTrinkets, 0);
    for(int i=0; i<numberOfTrinkets; ++i)
    {
        my_cin >> typesOfTrinkets[i];
    }

    typeToCountMap.assign(MAX_NUMBER_TYPES, 0);
    int maxAllowableCount=0;
    int allowableCount=0;
    for(int left=0; left<numberOfTrinkets; ++left)
    {
        if(left%2 == 0)
        {
            for(int right=left; right<numberOfTrinkets; ++right)
            {
                addTypeToAllowableCount(allowableCount, typesOfTrinkets[right]);
                maxAllowableCount = max(maxAllowableCount, allowableCount);
            }
        }
        else
        {
            for(int right=numberOfTrinkets-1; right>left; --right)
            {
                removeTypeToAllowableCount(allowableCount, typesOfTrinkets[right]);
                maxAllowableCount = max(maxAllowableCount, allowableCount);
            }
        }
        removeTypeToAllowableCount(allowableCount, typesOfTrinkets[left]);
        maxAllowableCount = max(maxAllowableCount, allowableCount);
    }
    my_cout << "Case #" << testCaseNumber << ": " << maxAllowableCount << '\n';
}*/

void runAllTestCases() {
    int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++) {
        runTestCase(testCaseNumber);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
}  // namespace KickStart_2019_RoundB_P3_DiverseSubarray
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
