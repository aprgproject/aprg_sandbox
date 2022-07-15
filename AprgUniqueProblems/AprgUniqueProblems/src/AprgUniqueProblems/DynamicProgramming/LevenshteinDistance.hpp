#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <string>

namespace alba
{

class LevenshteinDistance
{
public:
    // Note this ia dynamic programming solution
    // -> There is an implementation in AlbaStringHelper and it takes less space
    // ---> (but there is a swapping vector operation in the algorithm (so the last 2 rows in the dynamic programming matrix are maintained))

    // The edit distance or Levenshtein distance is the minimum number of editing operations needed to transform a string into another string.
    // The allowed editing operations are as follows:
    // -> insert a character (e.g. ABC ! ABCA)
    // -> remove a character (e.g. ABC ! AC)
    // -> modify a character (e.g. ABC ! ADC)

    // Recurrence formulation:
    // -> Lets define a function distance(a,b) that gives the edit distance between prefixes x[0...a] and y[0...b].
    // -> Thus, using this function, the edit distance between x and y equals distance(n-1,m-1).
    // -> distance(a,b) = min(distance(a,b-1)+1, distance(a-1,b)+1, distance(a-1,b-1)+cost(a,b)).
    // ---> distance(a,b) = min("insert part", "remove part", "modify part")
    // ---> Here cost(a,b) = 0 if x[a] = y[b], and otherwise cost(a,b) = 1.


    using Distance = unsigned int;
    using DistanceGrid = matrix::AlbaMatrix<Distance>;
    LevenshteinDistance(std::string const& string1, std::string const& string2);

    Distance getLevenshteinDistance() const;private:
    void calculateDistances();
    std::string m_string1;
    std::string m_string2;
    DistanceGrid m_distanceGrid;
};

}
