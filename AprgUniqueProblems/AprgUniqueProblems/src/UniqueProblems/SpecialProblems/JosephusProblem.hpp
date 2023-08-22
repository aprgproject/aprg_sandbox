#pragma once

#include <vector>

namespace alba {

class JosephusProblem {
public:
    using Value = int;
    using Values = std::vector<Value>;
    Values getJosephusPermutationUsingIntervalTree(int const numberOfPeople, int const skipCount);

private:
};

}  // namespace alba

// Josephus Permutation
// -> We define the Josephus Problem as follows.
// ---> Suppose that n poeple form a circle and that we are given a positive integer m <= n.
// ---> Beginning with a designated first person, we proceed around the circle, removin every mth person.
// ---> After each person is removed, counthing continues around the circle that remains.
// ---> This process continues until we have removed all n people.
// -> The order in which the people are removed from the circle
// -> defines the (n,m)-Josephus permutation of the integers 1,2,...,n
// -> For example, the (7,3)-Josephus permutation is {3,6,2,7,5,1,4}
// -> (a) Suppose that m is a constant.
// ---> Describe an O(n) time algorithm that, given an integer n, outputs the (n,m) - Josephus permutation.
// -> (b) Suppose that m is not a constant.
// ---> Describe an O(n lg n) time algorithm that, given integers n and m, outputs the (n,m) - Josephus permutation.
