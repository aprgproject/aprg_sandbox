#pragma once

#include <algorithm>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Objects>
class PermutationGenerationUsingRecursion
{
public:
    using Object = typename Objects::value_type;
    using Permutation = Objects;
    using Permutations = std::vector<Objects>;

    Permutations generatePermutationsUsingMethod1(Objects const& objects) const
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

    Permutations generatePermutationsUsingMethod2(Objects const& objects) const
    {
        Permutations result;
        Permutation currentPermutation;
        collectPermutationsUsingMethod2(result, currentPermutation, objects);
        return result;
    }

private:

    void collectPermutationsUsingMethod2(Permutations & permutations, Permutation & currentPermutation, Objects const& objects) const
    {
        static std::vector<bool> isProcessed(objects.size(), false);
        if(currentPermutation.size() == objects.size())
        {
            permutations.emplace_back(currentPermutation);
        }
        else
        {
            for(unsigned int index=0; index<objects.size(); index++)
            {
                if(!isProcessed.at(index))
                {
                    isProcessed[index] = true;
                    currentPermutation.emplace_back(objects.at(index));
                    collectPermutationsUsingMethod2(permutations, currentPermutation, objects);
                    isProcessed[index] = false;
                    currentPermutation.pop_back();
                }
            }
        }
    }
};

}

}
