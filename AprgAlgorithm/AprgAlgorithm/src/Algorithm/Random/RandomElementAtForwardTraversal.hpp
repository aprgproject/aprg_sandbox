#pragma once

#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class RandomElementAtForwardTraversal {
public:
    // This can be used to select a random node from a Singly Linked List

    using Value = typename Values::value_type;
    RandomElementAtForwardTraversal() = default;

    Value getRandomElement(Values const& values) {
        // This is similar reservoir Sampling.
        // Time Complexity: O(n), as we are using a loop to traverse n times.
        // Where n is the number of nodes in the linked list.
        // Auxiliary Space: O(1), as we are not using any extra space.

        Value result{};
        int count = 0;
        AlbaUniformNonDeterministicRandomizer<int> randomizer(0, count);
        for (Value const& value : values) {
            randomizer.setMinimumAndMaximum(0, count);
            int randomIndex = randomizer.getRandomValue();
            if (randomIndex == 0) {
                result = value;
            }
            count++;
        }
        return result;
    }
};

}  // namespace algorithm

}  // namespace alba

// -> How does this work?
// ---> Let there be total N nodes in the list. It is easier to understand from the last node.
// ---> The probability that the last node is result simply 1/N
// ---> [For the last or N’th node, we generate a random number between 0 to N-1
// ---> and make the last node as the result if the generated number is 0 (or any other fixed number]
// ---> The probability that the second last node is the result should also be 1/N.
// ---> The probability that the second last node is result:
// --->           = [Probability that the second last node replaces result] X
// --->             [Probability that the last node doesn't replace the result]
// --->           = [1 / (N-1)] * [(N-1)/N]
// --->           = 1/N
// ---> Similarly, we can show the probability for 3rd last node and other nodes.

// -> This can be used to solve this problem:
// ---> Given a singly linked list, select a random node from the linked list
// ---> (the probability of picking a node should be 1/N if there are N nodes in the list).
// ---> You are given a random number generator.
