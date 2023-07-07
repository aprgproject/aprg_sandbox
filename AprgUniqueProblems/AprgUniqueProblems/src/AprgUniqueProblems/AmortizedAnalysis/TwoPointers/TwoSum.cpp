#include "TwoSum.hpp"

#include <algorithm>

using namespace std;

namespace alba {

TwoSum::TwoSum(Values const& valuesToCheck) : m_sortedValues(valuesToCheck) {
    sort(m_sortedValues.begin(), m_sortedValues.end());  // sort first
}

TwoSum::ValuesPair TwoSum::getTwoValuesWithSum(Value const targetSum) const {
    ValuesPair result{};
    if (!m_sortedValues.empty()) {
        bool isFound(false);
        Index lowIndex = 0, highIndex = m_sortedValues.size() - 1;
        while (lowIndex < highIndex) {
            Value currentSum(m_sortedValues[lowIndex] + m_sortedValues[highIndex]);
            if (currentSum > targetSum) {
                highIndex--;
            } else if (currentSum < targetSum) {
                lowIndex++;
            } else {  // (currentSum == targetSum)
                isFound = true;
                break;
            }
        }
        if (isFound)  // empty if not found
        {
            result = {m_sortedValues[lowIndex], m_sortedValues[highIndex]};
        }
    }
    return result;
}

}  // namespace alba

/*
// two sum with indices
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> valueToIndexMap;
        for(int i=0; i<nums.size(); i++)
        {
            auto it = valueToIndexMap.find(target-nums[i]);
            if(it == valueToIndexMap.cend())
            {
                valueToIndexMap.emplace(nums[i], i);
            }
            else
            {
                return {i, it->second};
            }
        }
        return {};
    }
};
*/