#pragma once

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Objects>
class SubsetGenerationUsingRecursion
{
public:
    using Object = typename Objects::value_type;
    using Subset = Objects;
    using Subsets = std::vector<Objects>;

    // rule of five or six
    SubsetGenerationUsingRecursion() = delete;
    ~SubsetGenerationUsingRecursion() = delete;
    SubsetGenerationUsingRecursion(SubsetGenerationUsingRecursion const&) = delete;
    SubsetGenerationUsingRecursion & operator= (SubsetGenerationUsingRecursion const&) = delete;
    SubsetGenerationUsingRecursion(SubsetGenerationUsingRecursion &&) = delete;
    SubsetGenerationUsingRecursion & operator= (SubsetGenerationUsingRecursion &&) = delete;

    static Subsets generateOrderedSubsetsUsingDfs(Objects const& objects)
    {
        Subsets result;
        Subset currentSubset;
        result.emplace_back(); // null set
        if(!objects.empty())
        {
            collectOrderedSubsetsUsingDfs(result, currentSubset, objects, 0);
        }
        return result;
    }

    static Subsets generateSubsetsUsingOnlyRecursion(Objects const& objects)
    {
        // An elegant way to go through all subsets of a set is to use recursion.
        // The following function search generates the subsets of the set {0,1,...,n¡1}.
        // The function maintains a vector subset that will contain the elements of each subset.
        // The search begins when the function is called with parameter 0.

        // When the function search is called with parameter k, it decides whether to include the element k in the subset or not,
        // and in both cases, then calls itself with parameter k+1.
        // However, if k=n, the function notices that all elements have been processed and a subset has been generated.

        Subsets result;
        Subset currentSubset;
        collectSubsetsUsingOnlyRecursion(result, currentSubset, objects, 0);
        return result;
    }
private:

    static void collectOrderedSubsetsUsingDfs(Subsets & subsets, Subset & currentSubset, Objects const& objects, unsigned int const index)
    {
        //DFS like traversal
        for(unsigned int currentIndex=index; currentIndex<objects.size(); currentIndex++) // loop indexes starting from the index
        {
            currentSubset.emplace_back(objects.at(currentIndex));
            subsets.emplace_back(currentSubset);
            collectOrderedSubsetsUsingDfs(subsets, currentSubset, objects, currentIndex+1); // increment to next index
            currentSubset.pop_back();
        }
    }

    static void collectSubsetsUsingOnlyRecursion(Subsets & subsets, Subset & currentSubset, Objects const& objects, unsigned int const index)
    {
        if(index == objects.size())
        {
            subsets.emplace_back(currentSubset);
        }
        else
        {
            collectSubsetsUsingOnlyRecursion(subsets, currentSubset, objects, index+1); // recursively call with next object (without object in subset)
            currentSubset.emplace_back(objects.at(index)); // add object in subset
            collectSubsetsUsingOnlyRecursion(subsets, currentSubset, objects, index+1); // recursively call with next object (with object in subset)
            currentSubset.pop_back(); // remove object in subset, so other instances wont be affected
        }
    }
};

}

}
