#include "MaximumSubMatrixSum.hpp"

#include <AprgUniqueProblems/DynamicProgramming/Other/MaximumSubArraySum.hpp>

using namespace std;

namespace alba
{

MaximumSubMatrixSum::MaximumSubMatrixSum(
        ValueMatrix const& valueMatrix)
    : m_valueMatrix(valueMatrix)
{}

MaximumSubMatrixSum::Value MaximumSubMatrixSum::getMaximumSubMatrixSum() const
{
    // Uses Kadane’s algorithm

    // Time Complexity: O(n^3)
    // Auxiliary Space: O(n)

    Value result = MIN_VALUE;
    for (Index left = 0; left < m_valueMatrix.getNumberOfColumns(); left++)    {
        Values accumulatedColumn;
        m_valueMatrix.retrieveColumn(accumulatedColumn, left);
        for (Index right = left+1; right < m_valueMatrix.getNumberOfColumns(); right++)
        {
            MaximumSubArraySum maximumSubArraySum(accumulatedColumn);
            result = max(result, maximumSubArraySum.getMaximumSubArraySum()); // linear

            for (Index rowIndex = 0; rowIndex < m_valueMatrix.getNumberOfRows(); rowIndex++) // add next column
            {                accumulatedColumn[rowIndex] += m_valueMatrix.getEntry(right, rowIndex);
            }
        }
    }    return result;
}

MaximumSubMatrixSum::SubArrayDetails MaximumSubMatrixSum::getMaximumSubMatrixSumWithDetails() const
{
    // Time Complexity: O(n^3)
    // Auxiliary Space: O(n)

    SubArrayDetails result{0U, 0U, 0U, 0U, MIN_VALUE};
    for (Index left = 0; left < m_valueMatrix.getNumberOfColumns(); left++)
    {        Values accumulatedColumn;
        m_valueMatrix.retrieveColumn(accumulatedColumn, left);
        for (Index right = left+1; right < m_valueMatrix.getNumberOfColumns(); right++)
        {
            MaximumSubArraySum maximumSubArraySum(accumulatedColumn);

            auto columnSumDetails(maximumSubArraySum.getMaximumSubArraySumWithDetails()); // linear
            if(result.sum < columnSumDetails.sum)
            {
                result.sum = columnSumDetails.sum;                result.left = left;
                result.right = right;
                result.up = columnSumDetails.lowIndex;
                result.down = columnSumDetails.highIndex;            }

            for (Index rowIndex = 0; rowIndex < m_valueMatrix.getNumberOfRows(); rowIndex++) // add next column
            {
                accumulatedColumn[rowIndex] += m_valueMatrix.getEntry(right, rowIndex);
            }
        }
    }
    return result;
}

}
