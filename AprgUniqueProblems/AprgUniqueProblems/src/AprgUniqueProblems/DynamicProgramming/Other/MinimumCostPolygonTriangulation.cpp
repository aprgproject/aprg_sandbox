#include "MinimumCostPolygonTriangulation.hpp"

#include <Geometry/TwoDimensions/Utilities/TwoDimensionsUtilities.hpp>

using namespace alba::TwoDimensions;
using namespace alba::TwoDimensions::twoDimensionsUtilities;
using namespace std;

namespace alba
{

MinimumCostPolygonTriangulation::MinimumCostPolygonTriangulation(Points const& vertices)
    : m_vertices(vertices)
{}

MinimumCostPolygonTriangulation::Cost MinimumCostPolygonTriangulation::getMinimumNumberOfOperationsUsingNaiveRecursion() const
{
    // Time Complexity: Exponential
    // Auxiliary Space: Constant

    Cost result(0);
    if(!m_vertices.empty())
    {
        result = getMinimumNumberOfOperationsUsingNaiveRecursion(0, m_vertices.size()-1);
    }
    return result;
}

MinimumCostPolygonTriangulation::Cost MinimumCostPolygonTriangulation::getMinimumNumberOfOperationsUsingMemoizationDP() const
{
    // Time Complexity: O(n^3) (should be same as Iterative DP)
    // Auxiliary Space: O(n^2)

    Cost result(0);
    if(!m_vertices.empty())
    {
        CostMatrix countMatrix(m_vertices.size(), m_vertices.size(), MAX_COUNT);
        result = getMinimumNumberOfOperationsUsingMemoizationDP(countMatrix, 0, m_vertices.size()-1);
    }
    return result;
}

MinimumCostPolygonTriangulation::Cost MinimumCostPolygonTriangulation::getMinimumNumberOfOperationsUsingIterativeDP() const
{
    // Time Complexity: O(n^3)
    // Auxiliary Space: O(n^2)

    Cost result(0);
    if(!m_vertices.empty())
    {
        CostMatrix countMatrix(m_vertices.size(), m_vertices.size(), 0U);

        for(Index length=3; length<=m_vertices.size(); length++)
        {
            for(Index left=0; left+length<=countMatrix.getNumberOfColumns(); left++)
            {
                Index right = left+length-1;
                Cost minimumCount(MAX_COUNT);
                for(Index inBetween=left+1; inBetween<right; inBetween++)
                {
                    Cost currentCount = countMatrix.getEntry(left, inBetween)
                            + countMatrix.getEntry(inBetween, right)
                            + getCostOfThreePoints(left, inBetween, right);
                    minimumCount = min(minimumCount, currentCount);
                }
                countMatrix.setEntry(left, right, minimumCount);
            }
        }
        result = countMatrix.getEntry(0, countMatrix.getNumberOfRows()-1);
    }
    return result;
}

MinimumCostPolygonTriangulation::Cost MinimumCostPolygonTriangulation::getMinimumNumberOfOperationsUsingNaiveRecursion(
        Index const left,
        Index const right) const
{
    Cost result(0);
    if(left+2 <= right) // distance should be two for at least three elements
    {
        result = MAX_COUNT;
        for(Index inBetween=left+1; inBetween<right; inBetween++)
        {
            Cost currentCount = getMinimumNumberOfOperationsUsingNaiveRecursion(left, inBetween)
                    + getMinimumNumberOfOperationsUsingNaiveRecursion(inBetween, right)
                    + getCostOfThreePoints(left, inBetween, right);
            result = min(result, currentCount);
        }
    }
    return result;
}

MinimumCostPolygonTriangulation::Cost MinimumCostPolygonTriangulation::getMinimumNumberOfOperationsUsingMemoizationDP(
        CostMatrix & countMatrix,
        Index const left,
        Index const right) const
{
    Cost result(countMatrix.getEntry(left, right));
    if(MAX_COUNT == result)
    {
        if(left+2 <= right) // distance should be two for at least three elements
        {
            // result is already set to MAX_COUNT so we can proceed on using min
            for(Index inBetween=left+1; inBetween<right; inBetween++)
            {
                Cost currentCount = getMinimumNumberOfOperationsUsingMemoizationDP(countMatrix, left, inBetween)
                        + getMinimumNumberOfOperationsUsingMemoizationDP(countMatrix, inBetween, right)
                        + getCostOfThreePoints(left, inBetween, right);
                result = min(result, currentCount);
            }
        }
        else
        {
            result = 0;
        }
        countMatrix.setEntry(left, right, result);
    }
    return result;
}

MinimumCostPolygonTriangulation::Cost MinimumCostPolygonTriangulation::getCostOfThreePoints(
        Index const index1,
        Index const index2,
        Index const index3) const
{
    // cost is perimeter

    return getDistance(m_vertices.at(index1), m_vertices.at(index2))
            + getDistance(m_vertices.at(index2), m_vertices.at(index3))
            + getDistance(m_vertices.at(index1), m_vertices.at(index3));
}

}
