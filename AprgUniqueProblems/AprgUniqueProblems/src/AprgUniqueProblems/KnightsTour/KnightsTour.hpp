#pragma once

#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

namespace alba
{

class KnightsTour
{
public:
    // A knight’s tour is a sequence of moves of a knight on an n £ n chessboard following the rules of chess such that the knight visits each square exactly once.
    // A knight’s tour is called a closed tour if the knight finally returns to the starting square and otherwise it is called an open tour.

    using ChessBoardIndexes=std::vector<unsigned int>;
    using CountToCoordinatesMap=std::map<unsigned int, std::pair<int, int>>;

    KnightsTour(unsigned int const chessBoardLength, unsigned int const chessBoardWidth);
    ChessBoardIndexes getAnOpenKnightsTour() const;
    ChessBoardIndexes getAClosedKnightsTour() const;
private:
    void initialize();
    void connectAllAt(int const x, int const y);
    void connectIfNeeded(unsigned int const sourceIndex,int const x, int const y);
    unsigned int countNeighbors(int const x, int const y);
    bool isInside(int const x, int const y) const;
    unsigned int getChessBoardIndex(unsigned int const x, unsigned int const y) const;
    unsigned int const m_chessBoardX;    unsigned int const m_chessBoardY;
    algorithm::DirectedGraphWithListOfEdges<unsigned int> m_graph;
};


}
