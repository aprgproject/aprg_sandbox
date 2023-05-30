// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundD_P1_XOrWhat.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_RoundD_P1_XOrWhat {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

template <typename Values, typename BlockValues>
class RangeQueryWithBlocks {
public:
    // This supports "selector", "accumulator" and "count" type queries.

    // Assuming there are k blocks:
    // The preprocessing of partial sum can be constructed in O(n) time.
    // The range query can be done in max(O(k), O(n/k)) time.
    // The updating of a value can be done in O(n/k) time.

    // Note that having sqrt(n) of blocks is special.
    // The idea is to divide the array into blocks of size sqrt(n) so that each block contains the sum of elements
    // inside the block. Since the number of single elements is O(sqrt(n)) and the number of blocks is also O(sqrt(n)),
    // the sum query takes O(sqrt(n)) time. The purpose of the block size sqrt(n) is that it balances two things:
    // -> the array is divided into sqrt(n) blocks, each of which contains sqrt(n) elements.
    // So all operations take O(sqrt(n)) time.

    using Index = int;
    using Value = typename Values::value_type;
    using BlockValue = typename BlockValues::value_type;
    using Output = BlockValue;
    using ValuesFunction = std::function<BlockValue(typename Values::const_iterator, typename Values::const_iterator)>;
    using BlockValuesFunction =
        std::function<BlockValue(typename BlockValues::const_iterator, typename BlockValues::const_iterator)>;

    RangeQueryWithBlocks(
        Values const& valuesToCheck, Index const suggestedNumberOfBlocks, ValuesFunction const& valuesFunction,
        BlockValuesFunction const& blockValuesFunction)
        : m_values(valuesToCheck),
          m_blockSize(0),
          m_blocks(),
          m_valuesFunction(valuesFunction),
          m_blockValuesFunction(blockValuesFunction) {
        initialize(valuesToCheck, suggestedNumberOfBlocks);
    }

    Index getBlockSize() const { return m_blockSize; }

    BlockValues const& getBlocks() const { return m_blocks; }

    Output getResultOnInterval(Index const start, Index const end) const {
        // This is max(O(k), O(n/k)) time.
        Output result{};
        if (start < m_values.size() && end < m_values.size() && start <= end) {
            Index startOfBlocks = getMultipleThatIsGreaterOrEqual(m_blockSize, start);
            Index endOfBlocks = getMultipleThatIsLesserOrEqual(m_blockSize, end);
            if (startOfBlocks + m_blockSize <= endOfBlocks) {
                Index blockStart = startOfBlocks / m_blockSize;
                Index blockEnd = endOfBlocks / m_blockSize;

                Values resultParts;
                if (start < startOfBlocks) {
                    resultParts.emplace_back(
                        m_valuesFunction(m_values.cbegin() + start, m_values.cbegin() + startOfBlocks));
                }
                if (blockStart < blockEnd) {
                    resultParts.emplace_back(
                        m_blockValuesFunction(m_blocks.cbegin() + blockStart, m_blocks.cbegin() + blockEnd));
                }
                if (endOfBlocks <= end) {
                    resultParts.emplace_back(
                        m_valuesFunction(m_values.cbegin() + endOfBlocks, m_values.cbegin() + end + 1));
                }

                if (!resultParts.empty()) {
                    result = m_blockValuesFunction(resultParts.cbegin(), resultParts.cend());
                }
            } else {
                result = m_valuesFunction(m_values.cbegin() + start, m_values.cbegin() + end + 1);
            }
        }
        return result;
    }

    void changeValueAtIndex(Index const index, Value const& newValue) {
        // This has O(n/k) time.
        if (index < m_values.size()) {
            m_values[index] = newValue;

            Index start = getMultipleThatIsLesserOrEqual(m_blockSize, index);
            Index end = std::min(start + m_blockSize, static_cast<int>(m_values.size()));
            m_blocks[start / m_blockSize] = m_valuesFunction(m_values.cbegin() + start, m_values.cbegin() + end);
        }
    }

protected:
    void initialize(Values const& valuesToCheck, Index const suggestedNumberOfBlocks) {
        if (!valuesToCheck.empty()) {
            m_blockSize = std::max(static_cast<int>(valuesToCheck.size() / suggestedNumberOfBlocks), 1);
            Index numberOfBlocks =
                getMultipleThatIsGreaterOrEqual(static_cast<int>(valuesToCheck.size()), m_blockSize);
            m_blocks.reserve(numberOfBlocks);
            for (Index start = 0; start < m_values.size(); start += m_blockSize) {
                Index end = std::min(start + m_blockSize, static_cast<int>(m_values.size()));
                m_blocks.emplace_back(m_valuesFunction(m_values.cbegin() + start, m_values.cbegin() + end));
            }
            m_blocks.shrink_to_fit();
        }
    }

    Index getMultipleThatIsGreaterOrEqual(Index const multiple, Index const number) const {
        Index result(0);
        if (multiple > 0 && number > 0) {
            result = ((number - 1) / multiple + 1) * multiple;
        }
        return result;
    }

    Index getMultipleThatIsLesserOrEqual(Index const multiple, Index const number) const {
        Index result(0);
        if (multiple > 0) {
            result = number / multiple * multiple;
        }
        return result;
    }

    Values m_values;
    Index m_blockSize;
    BlockValues m_blocks;
    ValuesFunction m_valuesFunction;
    BlockValuesFunction m_blockValuesFunction;
};

using Value = uint16_t;
using Values = vector<Value>;
using Modification = pair<int, Value>;
using Modifications = vector<Modification>;
using RangeQuery = RangeQueryWithBlocks<Values, Values>;

RangeQuery::ValuesFunction xorARangeOfValues = [](Values::const_iterator itStart, Values::const_iterator itEnd) {
    return accumulate(
        itStart + 1, itEnd, *itStart, [](Value const value1, Value const value2) { return value1 ^ value2; });
};

void runTestCase(int const testCaseNumber) {
    int numberOfValues, numberOfModifications;
    my_cin >> numberOfValues >> numberOfModifications;
    Values values(numberOfValues);
    Modifications modifications(numberOfModifications);

    for (int i = 0; i < numberOfValues; i++) {
        my_cin >> values[i];
    }
    for (int i = 0; i < numberOfModifications; i++) {
        my_cin >> modifications[i].first >> modifications[i].second;
    }

    my_cout << "Case #" << testCaseNumber << ":";

    for (Modification const& modification : modifications) {
        values[modification.first] = modification.second;

        int lengthWithEvenParity(0);
        for (int left = 0; left < (int)values.size(); ++left) {
            Value xorSum = 0;
            for (int right = left; right < (int)values.size(); ++right) {
                xorSum ^= values[right];
                if (__builtin_parity(xorSum) == 0) {
                    lengthWithEvenParity = max(lengthWithEvenParity, right - left + 1);
                }
            }
        }
        my_cout << " " << lengthWithEvenParity;
    }
    my_cout << '\n';
}

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
}  // namespace KickStart_2019_RoundD_P1_XOrWhat
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
