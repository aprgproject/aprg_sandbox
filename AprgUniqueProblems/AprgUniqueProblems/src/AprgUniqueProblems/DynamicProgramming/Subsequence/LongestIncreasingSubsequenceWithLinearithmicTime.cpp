#include "LongestIncreasingSubsequenceWithLinearithmicTime.hpp"

using namespace std;

namespace alba
{

LongestIncreasingSubsequenceWithLinearithmicTime::LongestIncreasingSubsequenceWithLinearithmicTime(Sequence const& sequenceToCheck)
    : m_sequenceToCheck(sequenceToCheck)
{}

LongestIncreasingSubsequenceWithLinearithmicTime::Length LongestIncreasingSubsequenceWithLinearithmicTime::getLongestIncreasingSubsequenceLength()
{
    Length result(0);
    if (!m_sequenceToCheck.empty())
    {
        Sequence tails(m_sequenceToCheck.size(), 0);
        result = 1U;

        tails[0] = m_sequenceToCheck.front();

        for (Index i=1; i<m_sequenceToCheck.size(); i++) {

            // Do binary search for the element in
            // the range from begin to begin + length
            auto beginTailIt = tails.begin(), endTailIt = tails.begin() + result;
            auto lowerBoundIt = lower_bound(beginTailIt, endTailIt, m_sequenceToCheck.at(i));

            // If not present change the tail element to v[i]
            if (lowerBoundIt == tails.begin() + result)
            {
                tails[result++] = m_sequenceToCheck.at(i);
            }
            else
            {
                *lowerBoundIt = m_sequenceToCheck.at(i);
            }
        }

    }
    return result;
}

}
