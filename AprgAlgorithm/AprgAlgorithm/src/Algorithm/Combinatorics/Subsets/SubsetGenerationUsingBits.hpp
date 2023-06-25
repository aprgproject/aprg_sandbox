#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <bitset>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Objects, typename BitDataType>
class SubsetGenerationUsingBits {
public:
    using Object = typename Objects::value_type;
    using Subset = Objects;
    using Subsets = std::vector<Objects>;

    // rule of five or six
    SubsetGenerationUsingBits() = delete;
    ~SubsetGenerationUsingBits() = delete;
    SubsetGenerationUsingBits(SubsetGenerationUsingBits const &) = delete;
    SubsetGenerationUsingBits &operator=(SubsetGenerationUsingBits const &) = delete;
    SubsetGenerationUsingBits(SubsetGenerationUsingBits &&) = delete;
    SubsetGenerationUsingBits &operator=(SubsetGenerationUsingBits &&) = delete;

    static Subsets generateSubsetsUsingBits(Objects const &objects) {
        // Another way to generate subsets is based on the bit representation of integers.
        // Each subset of a set of n elements can be represented as a sequence of n bits, which corresponds to an
        // integer between 0...2n-1. The ones in the bit sequence indicate which elements are included in the subset.

        // The usual convention is that the last bit corresponds to element 0, the second last bit corresponds to
        // element 1, and so on. For example, the bit representation of 25 is 11001, which corresponds to the subset
        // {0,3,4}.

        Subsets result;
        BitDataType finalValue = 1 << objects.size();
        for (BitDataType iteration = 0; iteration < finalValue; iteration++) {
            Subset currentSubset;
            std::bitset<AlbaBitValueUtilities<BitDataType>::getNumberOfBits()> iterationBits(iteration);
            for (int index = 0; index < static_cast<int>(objects.size()); index++) {
                if (iterationBits[index]) {
                    currentSubset.emplace_back(objects[index]);
                }
            }
            result.emplace_back(currentSubset);        }
        return result;
    }
};
}  // namespace algorithm

}  // namespace alba
