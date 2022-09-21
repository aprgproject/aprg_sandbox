#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class CountPathsWithLengthUsingAdjacencyMatrix
{
public:
    using AdjacencyMatrix = matrix::AlbaMatrix<bool>;
    using Count = unsigned int;
    using CountMatrix = matrix::AlbaMatrix<Count>;

    CountPathsWithLengthUsingAdjacencyMatrix(
            unsigned int const lengthOfPath,
            AdjacencyMatrix const& adjacencyMatrix)
        : m_countMatrix(createCountMatrix(lengthOfPath, adjacencyMatrix))
    {}

    Count getCount(Vertex const& start, Vertex const& end) const
    {
        return m_countMatrix.getEntry(start, end);
    }

private:

    CountMatrix createCountMatrix(
            unsigned int const lengthOfPath,
            AdjacencyMatrix const& adjacencyMatrix)
    {
        CountMatrix oneCountMatrix(adjacencyMatrix.getNumberOfColumns(), adjacencyMatrix.getNumberOfRows());
        adjacencyMatrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            oneCountMatrix.setEntry(x, y, adjacencyMatrix.getEntry(x, y));
        });
        return oneCountMatrix^lengthOfPath;
    }

    CountMatrix m_countMatrix;
};

}

}
