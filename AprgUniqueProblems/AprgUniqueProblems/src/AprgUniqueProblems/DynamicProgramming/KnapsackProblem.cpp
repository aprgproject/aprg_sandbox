#include "KnapsackProblem.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

KnapsackProblem::KnapsackProblem(Values const& values)
    : m_inputValues(values)
{}

KnapsackProblem::Values KnapsackProblem::getAllPossiblePartialSums() const
{
    Values result;
    Value sum(accumulate(m_inputValues.cbegin(), m_inputValues.cend(), 0));
    vector<bool> isAPossiblePartialSum(sum+1, false); // zero index is for zero value, sum index is for the sum
    isAPossiblePartialSum[0] = true;
    for(unsigned int inputIndex=0; inputIndex<m_inputValues.size(); inputIndex++)
    {
        for(int partialSumIndex=sum; partialSumIndex>=0; partialSumIndex--) // reverse traversal so that the changed values wont be changed again in one iteration
        {
            if(isAPossiblePartialSum.at(partialSumIndex))
            {
                isAPossiblePartialSum[static_cast<Value>(partialSumIndex)+m_inputValues.at(inputIndex)] = true;
            }
        }
    }
    for(unsigned int partialSumIndex=0; partialSumIndex<sum+1; partialSumIndex++)
    {
        if(isAPossiblePartialSum.at(partialSumIndex))
        {
            result.emplace_back(partialSumIndex);
        }    }
    return result;
}
}
