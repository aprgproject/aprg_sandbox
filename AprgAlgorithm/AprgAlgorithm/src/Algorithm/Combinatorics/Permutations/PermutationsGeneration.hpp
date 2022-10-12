#pragma once

#include <algorithm>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Objects>
class PermutationsGeneration
{
public:
    using Object = typename Objects::value_type;
    using Permutation = Objects;
    using Permutations = std::vector<Objects>;
    using BooleanVector = std::vector<bool>;

    struct RecursionData
    {
        Permutations & permutations;
        Permutation currentPermutation;
        BooleanVector isProcessed;
        Objects const& objects;
        unsigned int const targetPermutationLength;
    };

    Permutations generatePermutationsUsingCppFunctions(Objects const& objects) const
    {
        Permutations result;
        Permutation currentPermutation(objects);
        do
        {
            result.emplace_back(currentPermutation);
        }
        while(std::next_permutation(currentPermutation.begin(), currentPermutation.end()));
        return result;
    }

    Permutations generatePermutationsUsingRecursion(Objects const& objects) const
    {
        Permutations result;
        RecursionData recursionData(createRecursionData(result, objects, objects.size()));
        collectPermutationsUsingRecursion(recursionData);
        return result;
    }

    Permutations generatePermutationsWithLength(Objects const& objects, unsigned int const targetPermutationLength) const
    {
        Permutations result;
        RecursionData recursionData(createRecursionData(result, objects, std::min(targetPermutationLength, objects.size())));
        collectPermutationsUsingRecursion(recursionData);
        return result;
    }

private:

    RecursionData createRecursionData(
            Permutations & permutations,
            Objects const& objects,
            unsigned int const length) const
    {
        return RecursionData{permutations, Permutation(), BooleanVector(objects.size(), false), objects, length};
    }

    void collectPermutationsUsingRecursion(RecursionData & recursionData) const
    {
        if(recursionData.currentPermutation.size() == recursionData.targetPermutationLength)
        {
            recursionData.permutations.emplace_back(recursionData.currentPermutation);
        }
        else
        {
            Objects const& objects(recursionData.objects);
            Permutation & currentPermutation(recursionData.currentPermutation);
            BooleanVector & isProcessed(recursionData.isProcessed);

            for(unsigned int index=0; index<objects.size(); index++)
            {
                if(!isProcessed.at(index))
                {
                    currentPermutation.emplace_back(objects.at(index));
                    isProcessed[index] = true;
                    collectPermutationsUsingRecursion(recursionData);
                    isProcessed[index] = false;
                    currentPermutation.pop_back();
                }
            }
        }
    }
};

}

}
