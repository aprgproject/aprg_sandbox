#include "LevenshteinDistance.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

LevenshteinDistance::LevenshteinDistance(string const& string1, string const& string2)
    : m_string1(string1)
    , m_string2(string2)
    , m_distanceGrid(string1.length()+1, string2.length()+1)
{
    calculateDistances();
}

LevenshteinDistance::Distance LevenshteinDistance::getLevenshteinDistance() const
{
    return m_distanceGrid.getEntry(m_distanceGrid.getNumberOfColumns()-1, m_distanceGrid.getNumberOfRows()-1);
}

void LevenshteinDistance::calculateDistances()
{
    // The allowed editing operations are as follows:
    // -> insert a character (e.g. ABC ! ABCA)
    // -> remove a character (e.g. ABC ! AC)
    // -> modify a character (e.g. ABC ! ADC)
    // We can calculate values of distance as follows:
    // -> distance(a,b) = min(distance(a,b-1)+1,
    //                     distance(a-1,b)+1,
    //                     distance(a-1,b-1)+cost(a,b)).
    // -> Here cost(a,b) = 0 if x[a] == y[b], and otherwise cost(a,b) == 1.
    // Operation positioning in the grid:
    // ---------------------
    // | replace | insert  |
    // ---------------------
    // | delete  | current |
    // ---------------------
    // Note that first column is for null string and first row is for null string (thats why there is a plus one in column/row size)
    m_distanceGrid.iterateAllThroughYAndThenX([&](unsigned int x, unsigned int y)
    {
        Distance replaceDistance = (m_distanceGrid.isInside(x-1, y-1)) ?
                    m_string1.at(x-1) ==  m_string2.at(y-1) ? // minus one because x and y are index+1
                        m_distanceGrid.getEntry(x-1, y-1) : m_distanceGrid.getEntry(x-1, y-1)+1 : numeric_limits<unsigned int>::max();
        Distance deleteDistance = (m_distanceGrid.isInside(x-1, y)) ?
                        m_distanceGrid.getEntry(x-1, y)+1 : numeric_limits<unsigned int>::max();
        Distance insertDistance = (m_distanceGrid.isInside(x, y-1)) ?
                        m_distanceGrid.getEntry(x, y-1)+1 : numeric_limits<unsigned int>::max();
        if(x==0 && y==0)
        {
            m_distanceGrid.setEntry(x, y, 0);
        }
        else
        {
            m_distanceGrid.setEntry(x, y, min(min(replaceDistance, deleteDistance), insertDistance));
        }
    });
}

}
