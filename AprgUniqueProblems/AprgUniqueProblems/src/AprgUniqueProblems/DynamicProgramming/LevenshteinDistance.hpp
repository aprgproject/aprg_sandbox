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
    // The allowed editing operations are as follows:    // -> insert a character (e.g. ABC ! ABCA)
    // -> remove a character (e.g. ABC ! AC)
    // -> modify a character (e.g. ABC ! ADC)
    using Distance = unsigned int;
    using DistanceGrid = matrix::AlbaMatrix<Distance>;

    LevenshteinDistance(std::string const& string1, std::string const& string2);

    Distance getLevenshteinDistance() const;
private:
    void calculateDistances();
    std::string m_string1;
    std::string m_string2;
    DistanceGrid m_distanceGrid;
};

}
