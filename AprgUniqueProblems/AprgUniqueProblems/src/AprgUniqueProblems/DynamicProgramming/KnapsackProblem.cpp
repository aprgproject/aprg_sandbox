#include "KnapsackProblem.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

KnapsackProblem::KnapsackProblem(Values const& values)
    : m_inputValues(values)
{}

KnapsackProblem::Values KnapsackProblem::getPossiblePartialSums() const
{
    Values result;
    Value sum(accumulate(m_inputValues.cbegin(), m_inputValues.cend(), 0));
    vector<bool> isPossiblePartialSum(sum+1, false);
    isPossiblePartialSum[0] = true;
    for(unsigned int inputIndex=0; inputIndex<m_inputValues.size(); inputIndex++)
    {
        for(int partialSumIndex=sum; partialSumIndex>=0; partialSumIndex--)
        {
            if(isPossiblePartialSum.at(partialSumIndex))
            {
                isPossiblePartialSum[static_cast<Value>(partialSumIndex)+m_inputValues.at(inputIndex)] = true;
            }
        }
    }
    for(unsigned int partialSumIndex=0; partialSumIndex<sum+1; partialSumIndex++)
    {
        if(isPossiblePartialSum.at(partialSumIndex))
        {
            result.emplace_back(partialSumIndex);
        }
    }
    return result;
}

}
