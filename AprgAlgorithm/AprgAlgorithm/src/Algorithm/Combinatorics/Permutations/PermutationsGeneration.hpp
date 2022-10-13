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

    // rule of five or six
    PermutationsGeneration() = delete;
    ~PermutationsGeneration() = delete;
    PermutationsGeneration(PermutationsGeneration const&) = delete;
    PermutationsGeneration & operator= (PermutationsGeneration const&) = delete;
    PermutationsGeneration(PermutationsGeneration &&) = delete;
    PermutationsGeneration & operator= (PermutationsGeneration &&) = delete;

    static Permutations generatePermutationsUsingCppFunctions(Objects const& objects)
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

    static Permutations generatePermutationsUsingRecursion(Objects const& objects)
    {
        Permutations result;
        RecursionData recursionData(createRecursionData(result, objects, objects.size()));
        collectPermutationsUsingRecursion(recursionData);
        return result;
    }

    static Permutations generatePermutationsWithLength(Objects const& objects, unsigned int const targetPermutationLength)
    {
        Permutations result;
        RecursionData recursionData(createRecursionData(result, objects, std::min(targetPermutationLength, objects.size())));
        collectPermutationsUsingRecursion(recursionData);
        return result;
    }

private:

    static RecursionData createRecursionData(
            Permutations & permutations,
            Objects const& objects,
            unsigned int const length)
    {
        return RecursionData{permutations, Permutation(), BooleanVector(objects.size(), false), objects, length};
    }

    static void collectPermutationsUsingRecursion(RecursionData & recursionData)
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
