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
    using DistanceMatrix = matrix::AlbaMatrix<unsigned int>;

    CountPathsWithLengthUsingAdjacencyMatrix(
            unsigned int const lengthOfPath,
            AdjacencyMatrix const& adjacencyMatrix)
        : m_distanceMatrix(createDistanceMatrix(lengthOfPath, adjacencyMatrix))
    {}

    unsigned int getCount(Vertex const& start, Vertex const& end) const
    {
        return m_distanceMatrix.getEntry(start, end);
    }

private:

    DistanceMatrix createDistanceMatrix(
            unsigned int const lengthOfPath,
            AdjacencyMatrix const& adjacencyMatrix)
    {
        DistanceMatrix temporaryMatrix(adjacencyMatrix.getNumberOfColumns(), adjacencyMatrix.getNumberOfRows());
        adjacencyMatrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            temporaryMatrix.setEntry(x, y, adjacencyMatrix.getEntry(x, y));
        });
        return temporaryMatrix^lengthOfPath;
    }

    DistanceMatrix m_distanceMatrix;
};

}

}
