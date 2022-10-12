#pragma once

#include <set>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Objects>
class CombinationsGeneration
{
public:
    using Object = typename Objects::value_type;
    using ProcessedObjects = std::set<Object>;
    using Combination = Objects;
    using Combinations = std::vector<Objects>;

    struct RecursionData
    {
        Combinations & combinations;
        Combination & currentCombination;
        unsigned int currentIndex;
        Objects const& objects;
        unsigned int const targetCombinationLength;
    };

    Combinations generateCombinationsWithLength(Objects const& objects, unsigned int const targetCombinationLength) const
    {
        Combinations result;
        Combination currentCombination;
        RecursionData recursionData(createRecursionData(result, currentCombination, objects, std::min(targetCombinationLength, objects.size())));
        collectCombinationsUsingRecursion(recursionData);
        return result;
    }

private:

    RecursionData createRecursionData(
            Combinations & combinations,
            Combination & currentCombination,
            Objects const& objects,
            unsigned int const length) const
    {
        return RecursionData{combinations, currentCombination, 0U, objects, length};
    }

    void collectCombinationsUsingRecursion(RecursionData & recursionData) const
    {
        if(recursionData.currentCombination.size() == recursionData.targetCombinationLength)
        {
            recursionData.combinations.emplace_back(recursionData.currentCombination);
        }
        else
        {
            Objects const& objects(recursionData.objects);
            Combination & currentCombination(recursionData.currentCombination);

            for(unsigned int index=recursionData.currentIndex; index<objects.size(); index++)
            {
                currentCombination.emplace_back(objects.at(index));
                recursionData.currentIndex = index+1;
                collectCombinationsUsingRecursion(recursionData);
                currentCombination.pop_back();
            }
        }
    }
};

}

}
