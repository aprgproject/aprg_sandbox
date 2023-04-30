#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>

using namespace std;

// Taken from Sean Parent's lecture ("C++ Seasoning")
// Taken from Conor Hoekstra ("Algorithm Intuition")
// Taken from Michael VanLoon's lecture ("STL Algorithms in Action")

namespace alba {

TEST(AlgorithmExamplesTest, SlideToTheRightWorksByUsingRotate) {
    // Move 3,4,5 after 8
    // {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    // { ,  ,  , f,  ,  , l,  ,  , p}; // call rotate(f,l,p);
    // {0, 1, 2, 6, 7, 8, 3, 4, 5, 9};
    array input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto output = input;
    rotate(begin(output) + 3, begin(output) + 6, begin(output) + 9);

    printParameter(cout, output);
}

TEST(AlgorithmExamplesTest, SlideToTheLeftWorksByUsingRotate) {
    // Move 3,4,5 after 2
    // {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    // {p,  ,  , f,  ,  , l,  ,  ,  }; // call rotate(p,f,l);
    // {0, 3, 4, 5, 1, 2, 6, 7, 8, 9};
    array input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto output = input;
    rotate(begin(output) + 1, begin(output) + 3, begin(output) + 6);

    printParameter(cout, output);
    cout << "\n";
}

TEST(AlgorithmExamplesTest, SlideWorksByUsingRotate) {
    auto slideStart = 3;
    auto slideEnd = 5;
    auto destination = 7;  // move after destination
    array input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto output = input;
    using Iterator = decltype(input)::iterator;
    pair<Iterator, Iterator> destinationPair;
    if (destination < slideStart) {
        Iterator it = rotate(begin(output) + destination + 1, begin(output) + slideStart, begin(output) + slideEnd + 1);
        destinationPair = {begin(output) + destination + 1, prev(it)};
    } else if (slideEnd < destination) {
        Iterator it = rotate(begin(output) + slideStart, begin(output) + slideEnd + 1, begin(output) + destination + 1);
        destinationPair = {it, begin(output) + destination};
    } else {
        destinationPair = {begin(output) + slideStart, begin(output) + slideEnd};
    }

    printParameter(cout, output);
    cout << "\n";
    cout << "DestinationPair: (" << *(destinationPair.first) << ", " << *(destinationPair.second) << ")\n";
}

TEST(AlgorithmExamplesTest, GatherToTheLeftWorksByUsingStablePartition) {
    // gather items divisible by 3 and put it at the start
    array input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto output = input;
    stable_partition(begin(output), end(output), [](auto value) { return mathHelper::isDivisible(value, 3); });

    printParameter(cout, output);
    cout << "\n";
}

TEST(AlgorithmExamplesTest, GatherToTheRightWorksByUsingStablePartition) {
    // gather items divisible by 3 and put it at the start
    array input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto output = input;
    stable_partition(begin(output), end(output), [](auto value) { return !(mathHelper::isDivisible(value, 3)); });

    printParameter(cout, output);
    cout << "\n";
}

TEST(AlgorithmExamplesTest, GatherToACenterWorksByUsingStablePartition) {
    // gather items divisible by 3 and put it at the start
    array input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto center = 5;

    auto output = input;
    using Iterator = decltype(input)::iterator;
    pair<Iterator, Iterator> destinationPair;
    Iterator itRight = stable_partition(
        begin(output) + center, end(output), [](auto value) { return mathHelper::isDivisible(value, 3); });
    Iterator itLeft = stable_partition(
        begin(output), begin(output) + center, [](auto value) { return !(mathHelper::isDivisible(value, 3)); });
    destinationPair = {itLeft, prev(itRight)};

    printParameter(cout, output);
    cout << "\n";
    cout << "DestinationPair: (" << *(destinationPair.first) << ", " << *(destinationPair.second) << ")\n";
}

TEST(AlgorithmExamplesTest, PartialSortVsNthElementPlusSort) {
    // Partial sort or nth element + sort?
    // In old implementations (nthElement+sort) used to be better

    // sort first four elements
    array input = {2, 8, 1, 9, 3, 5, 7, 4, 6};

    // Partial sort
    auto output1 = input;
    partial_sort(begin(output1), begin(output1) + 4, end(output1));

    // nthElement+sort
    auto output2 = input;
    nth_element(begin(output2), begin(output2) + 3, end(output2));
    sort(begin(output2), begin(output2) + 4);

    printParameter(cout, output1);
    cout << "\n";
    printParameter(cout, output2);
    cout << "\n";
}

TEST(AlgorithmExamplesTest, ProcessConfigurationUpdates) {
    vector<string> current{
        "Configuration1", "ConfigurationA", "ConfigurationAlpha", "ConfigurationB", "ConfigurationBeta"};
    vector<string> update{"Configuration2", "ConfigurationA", "ConfigurationAlpha", "ConfigurationC"};
    vector<string> newItems, removedItems;

    // sort(begin(current), end(current)); // no need for sort because already sorted
    // sort(begin(update), end(update)); // no need for sort because already sorted
    set_difference(begin(update), end(update), begin(current), end(current), back_inserter(newItems));
    set_difference(begin(current), end(current), begin(update), end(update), back_inserter(removedItems));

    printParameter(cout, newItems);
    cout << "\n";
    printParameter(cout, removedItems);
    cout << "\n";
}

TEST(AlgorithmExamplesTest, GettingTheDifferenceBetweenMaximumAndMinimumWorks) {
    // Given an array of integers find the difference between the minimum and maximum?
    // Note its guaranteed that input is not empty.

    array input = {2, 1, 3, 5, 4};

    auto [minIterator, maxIterator] = minmax_element(cbegin(input), cend(input));
    auto output = *maxIterator - *minIterator;
    cout << "Output: " << output << "\n";
}

TEST(AlgorithmExamplesTest, GettingTheAdjacentDifferentWorksUsingAdjacentDifference) {
    // Jon Kalb is going to give Michael and Odin each one coin.
    // Jon has N coincs with different values.
    // Jon want the absolute difference between the value of the coins to be minimized so Michael
    // and Odin don't fight with each other.
    // Given an array of coin values help Jon find this minimum.
    // In short, find the minimum difference between two values in a list.
    // Note its guaranteed that input is not empty.

    array input = {2, 1, 3, 5, 4};

    sort(input.begin(), input.end());
    decltype(input) differences;
    adjacent_difference(cbegin(input), cend(input), begin(differences));
    auto output = *min_element(cbegin(differences) + 1, cend(differences));
    cout << "Output: " << output << "\n";
}

TEST(AlgorithmExamplesTest, GettingTheAdjacentDifferentWorksUsingAccumulateOrReduce) {
    // Same question as above
    // The current compiler does not have reduce

    array input = {2, 1, 3, 5, 4};
    using ValueType = typename decltype(input)::value_type;

    sort(input.begin(), input.end());
    auto output = accumulate(
        cbegin(input) + 1, cend(input), std::numeric_limits<ValueType>::max(),
        [previousValue = input.front()](auto const minDifference, auto const currentValue) mutable {
            auto currentDifference = currentValue - previousValue;
            previousValue = currentValue;
            return min(currentDifference, minDifference);
        });

    // transform reduce solution
    // auto output = transform_reduce(
    //     cbegin(input), --cend(input), ++cbegin(input), numeric_limits<int>::max(),
    //     [](auto a, auto b) { return min(a, b); }, minus{});

    cout << "Output: " << output << "\n";
}

TEST(AlgorithmExamplesTest, RootMeanSquaredWorks) {
    // You are given the length (l) of N posters, and the wall heights (w) at which they will be hung.
    // They are hung at 75% mark of the poster.
    // Given Chandler has height of h, how tall a ladder does he need?
    // Note its guaranteed that input is not empty.

    // The current compiler does not have transform reduce

    array input = {2.0, 1.0, 3.0, 5.0, 4.0};

    auto output = sqrt(inner_product(input.begin(), input.end(), input.begin(), 0.0) / input.size());

    // transform_reduce operation
    // auto output =
    //    sqrt(transform_reduce(input.begin(), input.end(), input.begin(), 0.0, plus{}, multiplies{}) / input.size());

    cout << "Output: " << output << "\n";
}

TEST(AlgorithmExamplesTest, TrappingRainWater) {
    // Given n non-negative integers representing an elevation map where the width of each bar is 1,
    // compute how much water it is able to trap after raining?
    // Example graph:
    // | | | | | | | |B| | | | |
    // | | | |B|W|W|W|B|B|W|B| |
    // | |B|W|B|B|W|B|B|B|B|B|B|
    // Legend: B is a block, W is water.

    array elevations = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    auto highestIterator = max_element(cbegin(elevations), cend(elevations));
    // transform reduce solution
    // decltype(elevations) aux;
    // inclusive_scan(begin(elevations), next(highestIterator), begin(aux), max{});
    // inclusive_scan(rbegin(elevations), rev(highestIterator), rbegin(aux), max{});
    // auto output = transform_reduce(cbegin(aux), cend(aux), cbegin(elevations), 0, plus{}, minus{});

    // accumulate solution
    auto getTotalWater = [maxHeight = 0](auto totalWater, auto blockHeight) mutable {
        auto waterBlocks = blockHeight < maxHeight ? maxHeight - blockHeight : 0;
        maxHeight = max(maxHeight, blockHeight);
        return totalWater + waterBlocks;
    };
    auto waterFromLeftOfHighest = accumulate(cbegin(elevations), highestIterator, 0, getTotalWater);
    auto waterFromRightOfHighest =
        accumulate(crbegin(elevations), make_reverse_iterator(highestIterator), 0, getTotalWater);
    auto output = waterFromLeftOfHighest + waterFromRightOfHighest;

    cout << "Output: " << output << "\n";
}

TEST(AlgorithmExamplesTest, LongestContiguousSubstring) {
    // Given a string of 1s and 0s, return true if the longest (contiguous)
    // substring of equal elements is greater than or equal to 7

    string input = "001001000000010";

    auto output = accumulate(
        next(cbegin(input)), cend(input), 1,
        [previousChar = input.front(), totalLength = 1](auto maxLength, auto currentChar) mutable {
            totalLength = previousChar == currentChar ? totalLength + 1 : 1;
            previousChar = currentChar;
            return max(totalLength, maxLength);
        });

    cout << "Output: " << output << "\n";
}

TEST(AlgorithmExamplesTest, GenerateFibonacciNumbersUsingAdjacentDifference) {
    auto input = 20;

    vector fibonacciNumbers(input, 1);
    adjacent_difference(cbegin(fibonacciNumbers), prev(cend(fibonacciNumbers)), next(begin(fibonacciNumbers)), plus{});
    auto output = fibonacciNumbers;

    printParameter(cout, output);
    cout << "\n";
}

}  // namespace alba

// Notes

// -> rotate is very common as a solution in real problems

// -> This are not the same:
// ---> This is wrong:
// -----> auto x = reduce(cbegin(v), cend(v), 0, [](auto a, auto b){return a+b*b});
// ---> This is correct:
// -----> auto x = transform_reduce(cbegin(v), cend(v), 0, plus{} [](auto e){return e*e});
