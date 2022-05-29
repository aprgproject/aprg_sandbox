#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <string>

namespace alba
{

class LevenshteinDistance
{
public:
    // Note there is an implementation in AlbaStringHelper and its more cost effective in space (but there is swapping vectors involved)

    // The edit distance or Levenshtein distance is the minimum number of editing operations needed to transform a string into another string.
    // The allowed editing operations are as follows:
    // -> insert a character (e.g. ABC ! ABCA)
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
