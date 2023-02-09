#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/Math/Matrix/Utilities/AlbaMatrixUtilities.hpp>
namespace alba
{
namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class ShortestDistanceByTraverseCountUsingAdjacencyMatrix
{
public:
    // Using a similar idea in a weighted graph, we can calculate for each pair of nodes the minimum length of a path
    // between them that contains exactly n edges.
    // To calculate this, we have to define matrix multiplication in a new way,
    // so that we do not calculate the numbers of paths but minimize the lengths of paths.

    using AdjacencyMatrix = matrix::AlbaMatrix<bool>;
    using DistanceEntry = AlbaNumber;
    using DistancetMatrix = matrix::AlbaMatrix<DistanceEntry>;

    ShortestDistanceByTraverseCountUsingAdjacencyMatrix(
            EdgeWeightedGraph const& graph,
            unsigned int const traverseCount)
        : m_shortestDistanceMatrix(createDistanceMatrix(traverseCount, graph))
    {}

    Weight getShortestDistance(Vertex const& start, Vertex const& end) const
    {
        return static_cast<Weight>(m_shortestDistanceMatrix.getEntry(start, end).getDouble());
    }

private:

    DistancetMatrix createDistanceMatrix(
            unsigned int const traverseCount,
            EdgeWeightedGraph const& graph)
    {
        AdjacencyMatrix const& adjacencyMatrix(graph.getAdjacencyMatrix());
        DistancetMatrix initialDistanceMatrix(adjacencyMatrix.getNumberOfColumns(), adjacencyMatrix.getNumberOfRows());
        adjacencyMatrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            // Let us construct an adjacency matrix where INFINITY means that an edge does not exist, and other values correspond to edge weights.
            AlbaNumber entryValue = adjacencyMatrix.getEntry(x, y) ?
                        AlbaNumber(graph.getWeight(x, y)) : AlbaNumberConstants::ALBA_NUMBER_POSITIVE_INFINITY;
            initialDistanceMatrix.setEntry(x, y, entryValue);
        });
        return transformMultipleTimes(initialDistanceMatrix, traverseCount);    }

    DistancetMatrix transformMultipleTimes(
            DistancetMatrix const& base,            unsigned int const scalarExponent)
    {
        assert(base.getNumberOfColumns() == base.getNumberOfRows());

        DistancetMatrix result(base);
        if(scalarExponent > 0)
        {
            DistancetMatrix newBase(base);
            unsigned int newExponent(scalarExponent-1);
            while(newExponent > 0)
            {
                if(mathHelper::isEven(newExponent))
                {
                    newBase = transformOneTime(newBase, newBase);
                    newExponent /= 2;
                }
                else
                {
                    result = transformOneTime(result, newBase);
                    newExponent--;
                }
            }
        }
        return result;
    }

    DistancetMatrix transformOneTime(
            DistancetMatrix const& first,
            DistancetMatrix const& second)
    {
        assert(first.getNumberOfColumns() == second.getNumberOfRows());

        // For matrix multiplication, so we calculate a minimum instead of a sum, and a sum of elements instead of a product.
        // After this modification, matrix powers correspond to shortest paths in the graph.

        DistancetMatrix result(second.getNumberOfColumns(), first.getNumberOfRows());
        DistancetMatrix::ListOfMatrixData rowsOfFirstMatrix, columnsOfSecondMatrix;
        first.retrieveRows(rowsOfFirstMatrix);
        second.retrieveColumns(columnsOfSecondMatrix);
        unsigned int y=0;
        for(DistancetMatrix::MatrixData const& rowOfFirstMatrix : rowsOfFirstMatrix)
        {
            unsigned int x=0;
            for(DistancetMatrix::MatrixData const& columnOfSecondMatrix : columnsOfSecondMatrix)
            {
                result.setEntry(x, y, transformOneSetOfValues(rowOfFirstMatrix, columnOfSecondMatrix));
                x++;
            }
            y++;
        }
        return result;
    }

    DistanceEntry transformOneSetOfValues(
            DistancetMatrix::MatrixData const& first,
            DistancetMatrix::MatrixData const& second)
    {
        DistanceEntry result(AlbaNumberConstants::ALBA_NUMBER_POSITIVE_INFINITY);
        unsigned int minSize = std::min(first.size(), second.size());
        for(unsigned int i=0; i<minSize; i++)
        {            AlbaNumber currentValue = first.at(i) + second.at(i);
            if(currentValue < result)
            {
                result = currentValue;            }
        }
        return result;
    }

    DistancetMatrix m_shortestDistanceMatrix;
};

}

}
