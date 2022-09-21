#pragma once

#include <Algorithm/Graph/Utilities/LaplaceanMatrix.hpp>
#include <Common/Math/Matrix/Utilities/Determinant.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class CountSpanningTrees
{
public:
    using XyIndices = std::pair<unsigned int, unsigned int>;

    template<unsigned int MAX_VERTEX_VALUE>
    static unsigned int getCount(BaseGraph<Vertex> const& graph)
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
