#pragma once

#include <Algorithm/Graph/Utilities/LaplaceanMatrix.hpp>
#include <Common/Math/Matrix/Utilities/Determinant.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class CountSpanningTreesUsingKirchhoffTheorem
{
public:
    // Kirchhoff’s theorem provides a way to calculate the number of spanning trees of a graph as a determinant of a special matrix.

    using XyIndices = std::pair<unsigned int, unsigned int>;

    template<unsigned int MAX_VERTEX_VALUE>    static unsigned int getCount(BaseGraph<Vertex> const& graph)
    {
        LaplaceanMatrix laplaceanMatrix(createLaplaceanMatrix<Vertex, MAX_VERTEX_VALUE>(graph));
        XyIndices xy(getBestXYToRemove(laplaceanMatrix));
        LaplaceanMatrix reducedMatrix(matrix::getMatrixWithOneColumnAndOneRowRemoved(laplaceanMatrix, xy.first, xy.second));
        return matrix::getDeterminant(reducedMatrix);
    }

private:

    static XyIndices getBestXYToRemove(
            LaplaceanMatrix const& laplaceanMatrix)
    {
        LaplaceanMatrix::ListOfMatrixData columns;
        LaplaceanMatrix::ListOfMatrixData rows;
        laplaceanMatrix.retrieveColumns(columns);
        laplaceanMatrix.retrieveRows(rows);

        return XyIndices{matrix::getIndexWithHighestNumberOfNonZeros(columns), matrix::getIndexWithHighestNumberOfNonZeros(rows)};
    }

};

}

}
