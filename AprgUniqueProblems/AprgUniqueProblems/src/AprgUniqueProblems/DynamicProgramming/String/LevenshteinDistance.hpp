#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <string>

namespace alba {

class LevenshteinDistance {
public:
    using Index = unsigned int;
    using Count = unsigned int;
    using Counts = std::vector<Count>;
    using CountGrid = matrix::AlbaMatrix<Count>;
    static constexpr Index UNUSED_INDEX = std::numeric_limits<Index>::max();

    LevenshteinDistance(std::string const& string1, std::string const& string2);

    Count getLevenshteinDistanceUsingNaiveRecursion() const;
    Count getLevenshteinDistanceUsingMemoizationDP() const;
    Count getLevenshteinDistanceUsingIterativeDP() const;
    Count getLevenshteinDistanceUsingIterativeDPAndSpaceEfficient() const;

private:
    Count getLevenshteinDistanceUsingNaiveRecursion(Index const index1, Index const index2) const;
    Count getLevenshteinDistanceUsingMemoizationDP(CountGrid& indexGrid, Index const index1, Index const index2) const;
    std::string m_string1;
    std::string m_string2;
};

}  // namespace alba
// Note this ia dynamic programming solution
// -> There is an implementation in AlbaStringHelper and it takes less space
// ---> (but there is a swapping vector operation in the algorithm (so the last 2 rows in the dynamic programming matrix
// are maintained))

// The edit distance or Levenshtein distance is the minimum number of editing operations needed to transform a string
// into another string. The allowed editing operations are as follows:
// -> insert a character (e.g. ABC ! ABCA)
// -> remove a character (e.g. ABC ! AC)
// -> modify a character (e.g. ABC ! ADC)

// Recurrence formulation:
// -> Lets define a function distance(a,b) that gives the edit distance between prefixes x[0...a] and y[0...b].
// -> Thus, using this function, the edit distance between x and y equals distance(n-1,m-1).
// -> distance(a,b) = min(distance(a,b-1)+1, distance(a-1,b)+1, distance(a-1,b-1)+cost(a,b)).
// ---> distance(a,b) = min("insert part", "remove part", "modify part")
// ---> Here cost(a,b) = 0 if x[a] = y[b], and otherwise cost(a,b) = 1.

// Other discussions:
// Given two strings str1 and str2 and below operations that can performed on str1.
// Find minimum number of edits (operations) required to convert ‘str1’ into ‘str2’.
// -> Insert
// -> Remove
// -> Replace
// All of the above operations are of equal cost.
// Examples:
// -> Input:   str1 = "geek", str2 = "gesek"
// ---> Output:  1
// ---> We can convert str1 into str2 by inserting a 's'.
// -> Input:   str1 = "cat", str2 = "cut"
// ---> Output:  1
// ---> We can convert str1 into str2 by replacing 'a' with 'u'.
// -> Input:   str1 = "sunday", str2 = "saturday"
// ---> Output:  3
// ---> Last three and first characters are same.
// ---> We basically need to convert "un" to "atur".
// ---> This can be done using below three operations.
// ---> Replace 'n' with 'r', insert t, insert a.

// What are the subproblems in this case?
// The idea is process all characters one by one staring from either from left or right sides of both strings.
// Let us traverse from right corner, there are two possibilities for every pair of character being traversed.
// -> m: Length of str1 (first string)
// -> n: Length of str2 (second string)
// -> If last characters of two strings are same, nothing much to do.
// ---> Ignore last characters and get count for remaining strings.
// ---> So we recur for lengths m-1 and n-1.
// -> Else (If last characters are not same), we consider all operations on ‘str1’,
// ---> consider all three operations on last character of first string,
// ---> recursively compute minimum cost for all three operations and take minimum of three values.
// -----> Insert: Recur for m and n-1
// -----> Remove: Recur for m-1 and n
// -----> Replace: Recur for m-1 and n-1

// We can see that many subproblems are solved, again and again, for example, eD(2, 2) is called three times.
// Since same subproblems are called again, this problem has Overlapping Subproblems property.
// So Edit Distance problem has both properties (see this and this) of a dynamic programming problem.
// Like other typical Dynamic Programming(DP) problems,
// recomputations of same subproblems can be avoided by constructing a temporary array that stores results of
// subproblems.

// Applications: There are many practical applications of edit distance algorithm, refer Lucene API for sample.
// -> Another example, display all the words in a dictionary that are near proximity to a given word incorrectly spelled
// word.
