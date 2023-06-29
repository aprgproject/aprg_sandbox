#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>
class PancakeSorter : public BaseSorter<Values> {
public:
    using Iterator = typename Values::iterator;
    PancakeSorter() = default;

    void sort(Values& valuesToSort) const override {
        if (!valuesToSort.empty()) {
            for (auto itLast = std::prev(valuesToSort.end()); itLast != valuesToSort.begin(); itLast--) {
                auto itMax = std::max_element(valuesToSort.begin(), std::next(itLast));
                flipLowerPartAt(valuesToSort, itMax);
                flipLowerPartAt(valuesToSort, itLast);
            }
        }
    }

private:
    void flipLowerPartAt(Values& valuesToSort, Iterator const flipIt) const {
        for (auto lowIt = valuesToSort.begin(), highIt = flipIt; lowIt != highIt && lowIt != std::next(highIt);
             lowIt++, highIt--) {
            std::swap(*lowIt, *highIt);
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// -> Pancake sorting
// ---> Pancake sorting is the mathematical problem of sorting a disordered stack of pancakes in order of size when a
// spatula can be inserted at any point in the stack and used to flip all pancakes above it.
// -----> A pancake number is the minimum number of flips required for a given number of pancakes.
// -----> A variant of the problem is concerned with burnt pancakes, where each pancake has a burnt side and all
// pancakes must, in addition, end up with the burnt side on bottom.
// ---> All sorting methods require pairs of elements to be compared.
// -----> For the traditional sorting problem, the usual problem studied is to minimize the number of comparisons
// required to sort a list.
// -----> The number of actual operations, such as swapping two elements, is then irrelevant.
// -----> For pancake sorting problems, in contrast, the aim is to minimize the number of operations, where the only
// allowed operations are reversals of the elements of some prefix of the sequence.
// -----> Now, the number of comparisons is irrelevant.
// -> Algorithm
// ---> An example of the pancake sorting algorithm is given below in Python.
// -----> def flip(arr, k):
// ----->     left = 0
// ----->     while left < k:
// ----->         arr[left], arr[k] = arr[k], arr[left]
// ----->         k -= 1
// ----->         left += 1
// -----> def max_index(arr, k):
// ----->     index = 0
// ----->     for i in range(k):
// ----->         if arr[i] > arr[index]:
// ----->             index = i
// ----->     return index
// -----> def pancake_sort(arr):
// ----->     n = len(arr)
// ----->     while n > 1:
// ----->         maxdex = max_index(arr, n)
// ----->         flip(arr, maxdex)
// ----->         flip(arr, n - 1)
// ----->         n -= 1
// -----> arreglo = [15, 8, 9, 1, 78, 30, 69, 4, 10]
// -----> pancake_sort(arreglo)
// -----> print(arreglo)
// ---> Note: The problem was first discussed by American geometer Jacob E. Goodman.
//
