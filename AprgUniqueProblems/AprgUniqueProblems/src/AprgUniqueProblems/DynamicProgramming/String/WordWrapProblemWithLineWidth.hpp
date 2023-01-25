#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <string>

namespace alba
{

class WordWrapProblemWithLineWidth
{
public:
    using Index = unsigned int;
    using Cost = unsigned int;
    using Indices = std::vector<Index>;
    using Costs = std::vector<Cost>;
    struct RecursionDetails
    {
        Indices lengths;
    };
    using ExtraSpacesGrid = matrix::AlbaMatrix<int>;
    using CostGrid = matrix::AlbaMatrix<Cost>;
    static constexpr Cost MAX_COST = std::numeric_limits<Cost>::max();


    WordWrapProblemWithLineWidth(Index const lineWidth, stringHelper::strings const& words);

    Cost getOptimizedCostUsingNaiveRecursion() const;
    Cost getOptimizedCostByTryingAllLengths() const;
    Cost getOptimizedCostByCheckingExtraSpaces() const;

private:
    Cost getOptimizedCostUsingNaiveRecursion(RecursionDetails const& recursionDetails, Index const wordIndex) const;
    Cost getTotalLength() const;
    Cost getCost(Indices const& lengths) const;
    inline Cost getCostFromExtraSpaces(Index const numberOfExtraSpaces) const;
    Index m_lineWidth;
    stringHelper::strings m_words;
};

}

// Word Wrap Problem

// Given a sequence of words, and a limit on the number of characters that can be put in one line (line width).
// Put line breaks in the given sequence such that the lines are printed neatly.
// Assume that the length of each word is smaller than the line width.

// The word processors like MS Word do task of placing line breaks.
// The idea is to have balanced lines.
// In other words, not have few lines with lots of extra spaces and some lines with small amount of extra spaces.

// The extra spaces includes spaces put at the end of every line except the last one.
// The problem is to minimize the following total cost.
// Cost of a line = (Number of extra spaces in the line)^3
// Total Cost = Sum of costs for all lines

// For example, consider the following string and line width M = 15
// -> "Geeks for Geeks presents word wrap problem"
// -> Following is the optimized arrangement of words in 3 lines
// ---> Geeks for Geeks
// ---> presents word
// ---> wrap problem
// -> The total extra spaces in line 1, line 2 and line 3 are 0, 2 and 3 respectively.
// -> So optimal value of total cost is 0 + 2*2 + 3*3 = 13

// Please note that the total cost function is not sum of extra spaces, but sum of cubes (or square is also used) of extra spaces.
// The idea behind this cost function is to balance the spaces among lines.
// For example, consider the following two arrangement of same set of words:
// 1) There are 3 lines.
// -> One line has 3 extra spaces and all other lines have 0 extra spaces.
// -> Total extra spaces = 3 + 0 + 0 = 3.
// -> Total cost = 3*3*3 + 0*0*0 + 0*0*0 = 27.
// 2) There are 3 lines.
// -> Each of the 3 lines has one extra space.
// -> Total extra spaces = 1 + 1 + 1 = 3.
// -> Total cost = 1*1*1 + 1*1*1 + 1*1*1 = 3.
// Total extra spaces are 3 in both scenarios, but second arrangement should be preferred because extra spaces are balanced in all three lines.
// The cost function with cubic sum serves the purpose because the value of total cost in second scenario is less.

// Method 1 (Greedy Solution)
// The greedy solution is to place as many words as possible in the first line.
// Then do the same thing for the second line and so on until all words are placed.
// This solution gives optimal solution for many cases, but doesn’t give optimal solution in all cases.
// For example, consider the following string “aaa bb cc ddddd” and line width as 6.
// Greedy method will produce following output:
// -> aaa bb
// -> cc
// -> ddddd
// Extra spaces in the above 3 lines are 0, 4 and 1 respectively.
// So total cost is 0 + 64 + 1 = 65.
// But the above solution is not the best solution.
// Following arrangement has more balanced spaces.
// Therefore less value of total cost function.
// -> aaa
// -> bb cc
// -> ddddd
// Extra spaces in the above 3 lines are 3, 1 and 1 respectively.
// So total cost is 27 + 1 + 1 = 29.
// Despite being sub-optimal in some cases, the greedy approach is used by many word processors like MS Word and OpenOffice.org Writer.

// Method 2 (Dynamic Programming)
// The following Dynamic approach strictly follows the algorithm given in solution of Cormen book.
// First we compute costs of all possible lines in a 2D table lc[][].
// The value lc[i][j] indicates the cost to put words from i to j in a single line where i and j are indexes of words in the input sequences.
// If a sequence of words from i to j cannot fit in a single line, then lc[i][j] is considered infinite (to avoid it from being a part of the solution).
// Once we have the lc[][] table constructed, we can calculate total cost using following recursive formula.
// In the following formula, C[j] is the optimized total cost for arranging words from 1 to j.

