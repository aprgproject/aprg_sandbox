#pragma once

#include <algorithm>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Objects>
class PermutationsGeneration {
public:
    using Object = typename Objects::value_type;
    using Permutation = Objects;
    using Permutations = std::vector<Objects>;
    using BooleanVector = std::vector<bool>;

    struct BuildingRecursionData {
        Permutations& permutations;
        Permutation currentPermutation;
        BooleanVector isProcessed;
        Objects const& objects;
        int const targetPermutationLength;
    };

    struct SwappingRecursionData {
        Permutations& permutations;
        Permutation currentPermutation;
        int lowIndex;
        int highIndex;
    };

    // rule of five or six
    PermutationsGeneration() = delete;
    ~PermutationsGeneration() = delete;
    PermutationsGeneration(PermutationsGeneration const&) = delete;
    PermutationsGeneration& operator=(PermutationsGeneration const&) = delete;
    PermutationsGeneration(PermutationsGeneration&&) = delete;
    PermutationsGeneration& operator=(PermutationsGeneration&&) = delete;

    static Permutations generatePermutationsUsingCppFunctions(Objects const& objects) {
        // Another method for generating permutations is to begin with the permutation {0,1,...,n-1}
        // and repeatedly use a function that constructs the next permutation in increasing order.
        // The C++ standard library contains the function next_permutation that can be used for this.

        Permutations result;
        Permutation currentPermutation(objects);
        do {
            result.emplace_back(currentPermutation);
        } while (std::next_permutation(currentPermutation.begin(), currentPermutation.end()));
        return result;
    }

    static Permutations generatePermutationsByBuilding(Objects const& objects) {
        // Like subsets, permutations can be generated using recursion.
        // The followIndexing function search goes through the permutations of the set {0,1,...,n-1}.
        // The function builds a vector permutation that contains the permutation,
        // and the search begins when the function is called without parameters..

        // Each function call adds a new element to permutation.
        // The array "chosen" indicates which elements are already included in the permutation.
        // If the size of permutation equals the size of the set, a permutation has been generated.

        Permutations result;
        BuildingRecursionData recursionData(createBuildingRecursionData(result, objects, objects.size()));
        collectPermutationsByBuilding(recursionData);
        return result;
    }

    static Permutations generatePermutationsByBuildingWithLength(
        Objects const& objects, int const targetPermutationLength) {
        Permutations result;
        BuildingRecursionData recursionData(createBuildingRecursionData(
            result, objects, std::min(targetPermutationLength, static_cast<int>(objects.size()))));
        collectPermutationsByBuilding(recursionData);
        return result;
    }

    static Permutations generatePermutationsBySwapping(Objects const& objects) {
        Permutations result;
        SwappingRecursionData recursionData(
            createSwappingRecursionData(result, objects, 0, static_cast<int>(objects.size()) - 1));
        collectPermutationsBySwapping(recursionData);
        return result;
    }

    static Permutations generatePermutationsBySwappingInRange(
        Objects const& objects, int const lowIndex, int const highIndex) {
        Permutations result;
        SwappingRecursionData recursionData(createSwappingRecursionData(result, objects, lowIndex, highIndex));
        collectPermutationsBySwapping(recursionData);
        return result;
    }

private:
    static BuildingRecursionData createBuildingRecursionData(
        Permutations& permutations, Objects const& objects, int const length) {
        return BuildingRecursionData{
            permutations, Permutation(), BooleanVector(objects.size(), false), objects, length};
    }

    static SwappingRecursionData createSwappingRecursionData(
        Permutations& permutations, Objects const& objects, int const lowIndex, int const highIndex) {
        return SwappingRecursionData{permutations, objects, lowIndex, highIndex};
    }

    static void collectPermutationsByBuilding(BuildingRecursionData& recursionData) {
        if (static_cast<int>(recursionData.currentPermutation.size()) == recursionData.targetPermutationLength) {
            recursionData.permutations.emplace_back(recursionData.currentPermutation);
        } else {
            Objects const& objects(recursionData.objects);
            Permutation& currentPermutation(recursionData.currentPermutation);
            BooleanVector& isProcessed(recursionData.isProcessed);

            for (int index = 0; index < static_cast<int>(objects.size()); index++) {
                if (!isProcessed[index]) {
                    currentPermutation.emplace_back(objects[index]);
                    isProcessed[index] = true;
                    collectPermutationsByBuilding(recursionData);
                    isProcessed[index] = false;
                    currentPermutation.pop_back();
                }
            }
        }
    }

    static void collectPermutationsBySwapping(SwappingRecursionData& recursionData) {
        if (recursionData.lowIndex == recursionData.highIndex) {
            recursionData.permutations.emplace_back(recursionData.currentPermutation);
        } else {
            Permutation& currentPermutation(recursionData.currentPermutation);

            for (int swapIndex = recursionData.lowIndex; swapIndex <= recursionData.highIndex; swapIndex++) {
                std::swap(currentPermutation[recursionData.lowIndex], currentPermutation[swapIndex]);
                ++recursionData.lowIndex;

                collectPermutationsBySwapping(recursionData);

                // Go back to original permutation (backtrack)
                --recursionData.lowIndex;
                std::swap(currentPermutation[recursionData.lowIndex], currentPermutation[swapIndex]);
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba
