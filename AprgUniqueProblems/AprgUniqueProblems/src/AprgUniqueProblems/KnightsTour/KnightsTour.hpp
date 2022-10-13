#pragma once

#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AprgUniqueProblems/Utilities/PrintUtilities.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba{

using VertexOfKnightsTour = std::pair<unsigned int, unsigned int>; // Count and ChessBoardIndex pair

class KnightsTour
{
public:
    // A knight’s tour is a sequence of moves of a knight on an n x n chessboard following the rules of chess such that the knight visits each square exactly once.
    // A knight’s tour is called a closed tour if the knight finally returns to the starting square and otherwise it is called an open tour.

    using ChessBoardIndexes=std::vector<unsigned int>;    using Coordinate = std::pair<int, int>;
    using CountCoordinatePair=std::pair<unsigned int, std::pair<int, int>>;
    using CountToCoordinateMap=std::multimap<unsigned int, std::pair<int, int>>;

    KnightsTour(unsigned int const chessBoardX, unsigned int const chessBoardY);

    ChessBoardIndexes getAnOpenKnightsTour() const;
    ChessBoardIndexes getAClosedKnightsTour() const;

private:
    void initialize();
    void initializeNeighborMatrix();
    void initializeGraph();
    void connectAllAt(int const x, int const y);
    void connectIfNeeded(unsigned int const sourceNeighbors, unsigned int const sourceIndex,int const x, int const y);
    bool isInside(int const x, int const y) const;
    unsigned int getNumberOfNeighbors(int const x, int const y) const;
    unsigned int countNumberOfNeighbors(int const x, int const y) const;
    unsigned int getChessBoardIndex(int const x, int const y) const;
    unsigned int const m_chessBoardX;
    unsigned int const m_chessBoardY;
    algorithm::UndirectedGraphWithListOfEdges<VertexOfKnightsTour> m_graph;
    matrix::AlbaMatrix<unsigned int> m_neighborMatrix;
};

}