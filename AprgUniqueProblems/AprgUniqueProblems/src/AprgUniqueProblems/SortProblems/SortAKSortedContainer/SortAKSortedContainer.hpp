#pragma once

#include <queue>

namespace alba {

namespace algorithm {

template <typename Values>
class SortAKSortedContainer {
public:
    using Value = typename Values::value_type;
    using KPriorityQueue = std::priority_queue<Value, std::deque<Value>, std::greater<Value>>;

    SortAKSortedContainer() = default;

    void sort(unsigned int const maximumDistanceFromCorrectPosition, Values& valuesToSort) const {
        if (maximumDistanceFromCorrectPosition <= valuesToSort.size()) {
            unsigned int pqSize = (maximumDistanceFromCorrectPosition == valuesToSort.size())
                                      ? maximumDistanceFromCorrectPosition
                                      : maximumDistanceFromCorrectPosition + 1;
            KPriorityQueue pq(valuesToSort.cbegin(), valuesToSort.cbegin() + pqSize);

            unsigned int sortedIndex(0U);
            for (unsigned int newPqIndex = maximumDistanceFromCorrectPosition + 1; newPqIndex < valuesToSort.size();
                 newPqIndex++) {
                valuesToSort[sortedIndex++] = pq.top();
                pq.pop();
                pq.push(valuesToSort.at(newPqIndex));
            }

            while (!pq.empty()) {
                valuesToSort[sortedIndex++] = pq.top();
                pq.pop();
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// Sort a nearly sorted (or K sorted) array:
// -> Given an array of n elements, where each element is at most k away from its target position, devise an algorithm
// that sorts in O(n log k) time.

// We can sort such arrays more efficiently with the help of Heap data structure.
// Following is the detailed process that uses Heap.
// 1) Create a Min Heap of size k+1 with first k+1 elements. This will take O(k) time (See this GFact)
// 2) One by one remove min element from heap, put it in result array, and add a new element to heap from remaining
// elements. Removing an element and adding a new element to min heap will take log k time. So overall complexity will
// be O(k) + O((n-k) * log(k)).

// The Min Heap based method takes O(n log k) time and uses O(k) auxiliary space.

// We can also use a Balanced Binary Search Tree instead of Heap to store k+1 elements.
// The insert and delete operations on Balanced BST also take O(log k) time.
// So Balanced BST based method will also take O(n log k) time,
// but the Heap based method seems to be more efficient as the minimum element will always be at root.
// Also, Heap doesn’t need extra space for left and right pointers.
