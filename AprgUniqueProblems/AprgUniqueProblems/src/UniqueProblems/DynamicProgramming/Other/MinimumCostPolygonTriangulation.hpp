#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <limits>
#include <vector>

namespace alba {

class MinimumCostPolygonTriangulation {
public:
    using Cost = double;
    using Index = int;
    using CostMatrix = matrix::AlbaMatrix<Cost>;
    static constexpr Cost MAX_COUNT = std::numeric_limits<Cost>::max();

    MinimumCostPolygonTriangulation(TwoDimensions::Points const& points);

    Cost getMinimumNumberOfOperationsUsingNaiveRecursion() const;
    Cost getMinimumNumberOfOperationsUsingMemoizationDP() const;
    Cost getMinimumNumberOfOperationsUsingIterativeDP() const;

private:
    Cost getMinimumNumberOfOperationsUsingNaiveRecursion(Index const left, Index const right) const;
    Cost getMinimumNumberOfOperationsUsingMemoizationDP(
        CostMatrix& countMatrix, Index const left, Index const right) const;
    Cost getCostOfThreePoints(Index const index1, Index const index2, Index const index3) const;
    TwoDimensions::Points m_vertices;
};

}  // namespace alba

// Minimum Cost Polygon Triangulation

// A triangulation of a convex polygon is formed by drawing diagonals between non-adjacent vertices (corners) such that
// the diagonals never intersect. The problem is to find the cost of triangulation with the minimum cost. The cost of a
// triangulation is sum of the weights of its component triangles. Weight of each triangle is its perimeter (sum of
// lengths of all sides)

// This problem has recursive substructure.
// The idea is to divide the polygon into three parts: a single triangle, the sub-polygon to the left, and the
// sub-polygon to the right. We try all possible divisions like this and find the one that minimizes the cost of the
// triangle plus the cost of the triangulation of the two sub-polygons.

// Let Minimum Cost of triangulation of vertices from i to j be minCost(i, j)
// -> If j < i + 2 Then
// ---> minCost(i, j) = 0
// -> Else
// ---> minCost(i, j) = Min { minCost(i, k) + minCost(k, j) + cost(i, k, j) }
// -----> Here k varies from 'i+1' to 'j-1'
// ->
// -> Cost of a triangle formed by edges (i, j), (j, k) and (k, i) is
// ---> cost(i, j, k)  = dist(i, j) + dist(j, k) + dist(k, i)
