#pragma once

#include <algorithm>
#include <set>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Objects>
class CombinationsGeneration {
public:
    using Object = typename Objects::value_type;
    using ProcessedObjects = std::set<Object>;
    using Combination = Objects;
    using Combinations = std::vector<Objects>;

    struct RecursionData {
        Combinations& combinations;
        Combination currentCombination;
        int currentIndex;
        Objects const& objects;
        int const targetCombinationLength;
    };

    // rule of five or six
    CombinationsGeneration() = delete;
    ~CombinationsGeneration() = delete;
    CombinationsGeneration(CombinationsGeneration const&) = delete;
    CombinationsGeneration& operator=(CombinationsGeneration const&) = delete;
    CombinationsGeneration(CombinationsGeneration&&) = delete;
    CombinationsGeneration& operator=(CombinationsGeneration&&) = delete;

    static Combinations generateCombinationsWithLength(Objects const& objects, int const targetCombinationLength) {
        Combinations result;
        RecursionData recursionData(
            createRecursionData(result, objects, std::min(targetCombinationLength, static_cast<int>(objects.size()))));
        collectCombinationsUsingRecursion(recursionData);
        return result;
    }

private:
    static RecursionData createRecursionData(Combinations& combinations, Objects const& objects, int const length) {
        return RecursionData{combinations, Combination(), 0, objects, length};
    }

    static void collectCombinationsUsingRecursion(RecursionData& recursionData) {
        if (static_cast<int>(recursionData.currentCombination.size()) == recursionData.targetCombinationLength) {
            recursionData.combinations.emplace_back(recursionData.currentCombination);
        } else {
            Objects const& objects(recursionData.objects);
            Combination& currentCombination(recursionData.currentCombination);

            for (int index = recursionData.currentIndex; index < static_cast<int>(objects.size()); index++) {
                currentCombination.emplace_back(objects[index]);
                recursionData.currentIndex = index + 1;
                collectCombinationsUsingRecursion(recursionData);
                currentCombination.pop_back();
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba
