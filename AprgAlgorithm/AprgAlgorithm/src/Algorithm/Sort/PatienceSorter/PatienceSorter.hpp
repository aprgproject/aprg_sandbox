#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <algorithm>
#include <queue>

namespace alba
{

namespace algorithm
{

template <typename Values>
class PatienceSorter : public BaseSorter<Values>
{
public:
    using Value = typename Values::value_type;
    using PileValues = std::vector<Value>;
    struct Pile
    {
        Value valueAtTopOfPile;
        PileValues pileValues;

        Pile(Value const& value)
            : valueAtTopOfPile(value)
            , pileValues({value})
        {}
        bool operator<(Value const& valueToCheck) const
        {
            return valueAtTopOfPile < valueToCheck;
        }
    };
    using Piles = std::vector<Pile>;
    using PriorityQueueOfValues = std::priority_queue<Value, std::deque<Value>, std::greater<Value>>;

    PatienceSorter() = default;

    void sort(Values & valuesToSort) const override
    {
        Piles piles;
        for (Value const& value : valuesToSort) // put into piles
        {
            auto itLowerBound = std::lower_bound(piles.begin(), piles.end(), value);
            if(itLowerBound == piles.end())
            {
                piles.emplace_back(value);
            }
            else
            {
                itLowerBound->pileValues.emplace_back(value);
            }
        }
        auto updateIt = valuesToSort.begin();
        for (Pile const& pile : piles) // put into piles
        {
            PileValues const& pileValues(pile.pileValues);
            PriorityQueueOfValues priorityQueue(pileValues.cbegin(), pileValues.cend());
            while(!priorityQueue.empty())
            {
                *(updateIt++) = priorityQueue.top();
                priorityQueue.pop();
            }
        }
    }
};

}

}


// The algorithm's name derives from a simplified variant of the patience card game.
// The game begins with a shuffled deck of cards.
// The cards are dealt one by one into a sequence of piles on the table, according to the following rules.[2]
// 1) Initially, there are no piles.
// -> The first card dealt forms a new pile consisting of the single card.
// 2) Each subsequent card is placed on the leftmost existing pile whose top card has a value greater than or equal to the new card's value,
// -> or to the right of all of the existing piles, thus forming a new pile.
// 3) When there are no more cards remaining to deal, the game ends.

// This card game is turned into a two-phase sorting algorithm, as follows.
// Given an array of n elements from some totally ordered domain, consider this array as a collection of cards and simulate the patience sorting game.
// When the game is over, recover the sorted sequence by repeatedly picking off the minimum visible card;
// in other words, perform a k-way merge of the p piles, each of which is internally sorted.


// Analysis
// The first phase of patience sort, the card game simulation,
// can be implemented to take O(n log n) comparisons in the worst case for an n-element input array:
// there will be at most n piles, and by construction, the top cards of the piles form an increasing sequence from left to right,
// so the desired pile can be found by binary search.
// The second phase, the merging of piles, can be done in O(n log n) time as well using a priority queue.

// When the input data contain natural "runs", i.e., non-decreasing subarrays, then performance can be strictly better.
// In fact, when the input array is already sorted, all values form a single pile and both phases run in O(n) time.
// The average-case complexity is still O(n log n):
// any uniformly random sequence of values will produce an expected number of O(√n) piles,
// which take O(n log √n) = O(n log n) time to produce and merge.

// An evaluation of the practical performance of patience sort is given by Chandramouli and Goldstein,
// who show that a naïve version is about ten to twenty times slower than a state-of-the-art quicksort on their benchmark problem.
// They attribute this to the relatively small amount of research put into patience sort,
// and develop several optimizations that bring its performance to within a factor two of that of quicksort.

// If values of cards are in the range 1, . . . , n, there is an efficient implementation with O(n log n)
// worst-case running time for putting the cards into piles, relying on a Van Emde Boas tree.
