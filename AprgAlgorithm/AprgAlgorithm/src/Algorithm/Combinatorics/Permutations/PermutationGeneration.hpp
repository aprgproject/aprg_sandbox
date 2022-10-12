#pragma once

#include <algorithm>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Objects>
class PermutationGeneration
{
public:
    using Object = typename Objects::value_type;
    using Permutation = Objects;
    using Permutations = std::vector<Objects>;
    using BooleanVector = std::vector<bool>;

    struct RecursionData
    {
        Permutations & permutations;
        Permutation & currentPermutation;
        BooleanVector isProcessed;
        Objects const& objects;
        unsigned int const permutationLength;
    };

    Permutations generatePermutationsUsingCppFunctions(Objects const& objects) const
    {
        Permutations result;
        Permutation currentPermutation(objects);
        do        {
            result.emplace_back(currentPermutation);
        }
        while(std::next_permutation(currentPermutation.begin(), currentPermutation.end()));
        return result;
    }

    Permutations generatePermutationsUsingRecursion(Objects const& objects) const
    {
        Permutations result;
        Permutation currentPermutation;
        RecursionData recursionData(createRecursionData(result, currentPermutation, objects, objects.size()));
        collectPermutationsUsingRecursion(recursionData);
        return result;
    }

    Permutations generatePermutationsWithLength(Objects const& objects, unsigned int const permutationLength) const
    {
        Permutations result;
        Permutation currentPermutation;
        RecursionData recursionData(createRecursionData(result, currentPermutation, objects, std::min(permutationLength, objects.size())));
        collectPermutationsUsingRecursion(recursionData);
        return result;
    }

private:

    RecursionData createRecursionData(
            Permutations & permutations,
            Permutation & currentPermutation,
            Objects const& objects,
            unsigned int const length) const
    {
        return RecursionData{
            permutations,
                    currentPermutation,
                    BooleanVector(objects.size(), false),
                    objects,
                    length};
    }

    void collectPermutationsUsingRecursion(RecursionData & recursionData) const
    {
        if(recursionData.currentPermutation.size() == recursionData.permutationLength)
        {
            recursionData.permutations.emplace_back(recursionData.currentPermutation);
        }
        else
        {
            for(unsigned int index=0; index<recursionData.objects.size(); index++)
            {
                if(!recursionData.isProcessed.at(index))
                {
                    recursionData.isProcessed[index] = true;
                    recursionData.currentPermutation.emplace_back(recursionData.objects.at(index));
                    collectPermutationsUsingRecursion(recursionData);
                    recursionData.isProcessed[index] = false;
                    recursionData.currentPermutation.pop_back();
                }
            }
        }    }
};

}
}
