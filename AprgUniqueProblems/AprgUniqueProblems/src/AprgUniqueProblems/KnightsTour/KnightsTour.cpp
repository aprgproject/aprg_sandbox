#include "KnightsTour.hpp"

#include <Algorithm/Graph/PathSearch/HamiltonianPath/UndirectedGraph/HamiltonianPathSearchForUndirectedGraphWithDfs.hpp>

using namespace alba::algorithm;
using namespace std;

namespace alba
{

KnightsTour::KnightsTour(
        unsigned int const chessBoardLength,
        unsigned int const chessBoardWidth)
    : m_chessBoardX(chessBoardLength)
    , m_chessBoardY(chessBoardWidth)
{
    initialize();
}

KnightsTour::ChessBoardIndexes KnightsTour::getAnOpenKnightsTour() const
{
    HamiltonianPathSearchForUndirectedGraphWithDfs<unsigned int> hamiltonianPathSearch(m_graph);
    return hamiltonianPathSearch.getOneHamiltonianPath();
}

KnightsTour::ChessBoardIndexes KnightsTour::getAClosedKnightsTour() const
{
    HamiltonianPathSearchForUndirectedGraphWithDfs<unsigned int> hamiltonianPathSearch(m_graph);
    return hamiltonianPathSearch.getOneHamiltonianCycle();
}

void KnightsTour::initialize()
{
    for(int x=0; x<static_cast<int>(m_chessBoardX); x++)
    {
        for(int y=0; y<static_cast<int>(m_chessBoardX); y++)
        {
            connectAllAt(x, y);
        }
    }
}

void KnightsTour::connectAllAt(
        int const x,
        int const y)
{
    unsigned int sourceIndex = getChessBoardIndex(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
    connectIfNeeded(sourceIndex, x-2, y-1);
    connectIfNeeded(sourceIndex, x-2, y+1);
    connectIfNeeded(sourceIndex, x-1, y-2);
    connectIfNeeded(sourceIndex, x-1, y+2);
    connectIfNeeded(sourceIndex, x+1, y-2);
    connectIfNeeded(sourceIndex, x+1, y+2);
    connectIfNeeded(sourceIndex, x+2, y-1);
    connectIfNeeded(sourceIndex, x+2, y+1);
}

void KnightsTour::connectIfNeeded(
        unsigned int const sourceIndex,
        int const x,
        int const y)
{
    if(isInside(x, y))
    {
        unsigned int destinationIndex = getChessBoardIndex(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
        m_graph.connect(sourceIndex, destinationIndex);
    }
}

bool KnightsTour::isInside(
        int const x,
        int const y) const
{
    return x>=0 && x<m_chessBoardX && y>=0 && y<m_chessBoardY;
}

unsigned int KnightsTour::getChessBoardIndex(
        unsigned int const x,
        unsigned int const y) const
{
    return m_chessBoardX*y + x;
}

}
