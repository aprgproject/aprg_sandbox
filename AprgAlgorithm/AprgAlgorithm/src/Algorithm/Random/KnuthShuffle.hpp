#pragma once

#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <iterator>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class KnuthShuffle {
public:
    KnuthShuffle() = default;

    void shuffle(Values& valuesToShuffle) const {
        if (!valuesToShuffle.empty()) {
            AlbaUniformNonDeterministicRandomizer<int> randomizer;
            auto itLast = std::prev(valuesToShuffle.end());
            for (auto it = valuesToShuffle.begin(); it != itLast; ++it) {
                randomizer.setMinimumAndMaximum(std::distance(valuesToShuffle.begin(), it), valuesToShuffle.size() - 1);
                std::swap(*it, valuesToShuffle[randomizer.getRandomValue()]);
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// -> Fisher–Yates shuffle
// ---> This is (also known as the Knuth shuffle): randomly shuffle a finite set
// ---> The Fisher–Yates shuffle is an algorithm for generating a random permutation of a finite sequence—in plain
// terms, the algorithm shuffles the sequence.
// -----> The algorithm effectively puts all the elements into a hat; it continually determines the next element by
// randomly drawing an element from the hat until no elements remain.
// -----> The algorithm produces an unbiased permutation: every permutation is equally likely.
// -----> The modern version of the algorithm is efficient: it takes time proportional to the number of items being
// shuffled and shuffles them in place.
// ---> The Fisher–Yates shuffle is named after Ronald Fisher and Frank Yates, who first described it, and is also known
// as the Knuth shuffle after Donald Knuth.
// -----> A variant of the Fisher–Yates shuffle, known as Sattolo's algorithm, may be used to generate random cyclic
// permutations of length n instead of random permutations.
// ---> Fisher and Yates' original method
// -----> Their description of the algorithm used pencil and paper; a table of random numbers provided the randomness.
// -------> The basic method given for generating a random permutation of the numbers 1 through N goes as follows:
// ---------> Write down the numbers from 1 through N.
// ---------> Pick a random number k between one and the number of unstruck numbers remaining (inclusive).
// ---------> Counting from the low end, strike out the kth number not yet struck out, and write it down at the end of a
// separate list.
// ---------> Repeat from step 2 until all the numbers have been struck out.
// ---------> The sequence of numbers written down in step 3 is now a random permutation of the original numbers.
// -----> Provided that the random numbers picked in step 2 above are truly random and unbiased, so will be the
// resulting permutation.
// -------> Fisher and Yates took care to describe how to obtain such random numbers in any desired range from the
// supplied tables in a manner which avoids any bias.
// -------> They also suggested the possibility of using a simpler method — picking random numbers from one to N and
// discarding any duplicates—to generate the first half of the permutation,
// -------> and only applying the more complex algorithm to the remaining half, where picking a duplicate number would
// otherwise become frustratingly common.
// -----> The Fisher–Yates shuffle, in its original form, was described in 1938 by Ronald Fisher and Frank Yates in
// their book Statistical tables for biological, agricultural and medical research.
// ---> The modern algorithm
// -----> The algorithm described by Durstenfeld differs from that given by Fisher and Yates in a small but significant
// way.
// -------> Whereas a naïve computer implementation of Fisher and Yates' method would spend needless time counting the
// remaining numbers in step 3 above,
// -------> Durstenfeld's solution is to move the "struck" numbers to the end of the list by swapping them with the last
// unstruck number at each iteration.
// -------> This reduces the algorithm's time complexity to O(n) compared to O(n^2) for the naïve implementation.
// -------> This change gives the following algorithm (for a zero-based array).
// ---------> -- To shuffle an array a of n elements (indices 0..n-1):
// ---------> for i from n−1 downto 1 do
// --------->      j ← random integer such that 0 ≤ j ≤ i
// --------->      exchange a[j] and a[i]
// ---------> An equivalent version which shuffles the array in the opposite direction (from lowest index to highest)
// is:
// ---------> -- To shuffle an array a of n elements (indices 0..n-1):
// ---------> for i from 0 to n−2 do
// --------->      j ← random integer such that i ≤ j < n
// --------->      exchange a[i] and a[j]
// -----> The modern version of the Fisher–Yates shuffle, designed for computer use, was introduced by Richard
// Durstenfeld in 1964
// -------> and popularized by Donald E. Knuth in The Art of Computer Programming as "Algorithm P (Shuffling)".
// -----> Neither Durstenfeld's article nor Knuth's first edition of The Art of Computer Programming acknowledged the
// work of Fisher and Yates; they may not have been aware of it.
// -------> Subsequent editions of Knuth's The Art of Computer Programming mention Fisher and Yates' contribution.
