#pragma once

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Value>
class SubArraySum
{
public:
    // As the first example, consider a problem where we are given an array of n positive integers and a target sum x,
    // and we want to find a subarray whose sum is x or report that there is no such subarray.

    using Index = unsigned int;
    using Values = std::vector<Value>;

    SubArraySum(Values const& valuesToCheck)
        : m_valuesToCheck(valuesToCheck)
    {}

    Values getSubArrayWithSum(Value const targetSum) const
    {
        Values result;
        if(!m_valuesToCheck.empty())
        {
            bool isFound(false);
            Index start=0, end=0, size=m_valuesToCheck.size();
            Value currentSum=m_valuesToCheck.at(0);
            while(start<size && end<size)
            {
                if(currentSum==targetSum)
                {
                    isFound = true;
                    break;
                }
                else if(currentSum>targetSum)
                {
                    if(start<end)
                    {
                        currentSum-=m_valuesToCheck.at(start);
                        start++;
                    }
                    else if(end+1<size)
                    {
                        start++;
                        end++;
                        currentSum=m_valuesToCheck.at(end);
                    }
                    else
                    {
                        break;
                    }
                }
                else if(currentSum<targetSum)
                {
                    if(end+1<size)
                    {
                        end++;
                        currentSum+=m_valuesToCheck.at(end);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if(isFound) // empty if not found
            {
                result = Values(m_valuesToCheck.cbegin()+start, m_valuesToCheck.begin()+end+1);
            }
        }
        return result;
    }

private:
    Values m_valuesToCheck;
};

}

}
