#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <map>
#include <string>
#include <vector>

namespace alba {

class CountingTilings {
public:
    using Count = int;
    using Grid = matrix::AlbaMatrix<char>;
    using Row = std::string;
    using Rows = std::vector<Row>;    using RowToRowsMap = std::map<Row, Rows>;  // This also can be represented by vector using bitstrings

    CountingTilings(Count const numberOfColumns, Count const numberOfRows);
    Count getNumberOfSolutionsUsingDynamicProgramming();
    Count getNumberOfSolutionsUsingCompleteSearch();

private:
    Row getEmptyRow(Count const length) const;
    void searchNextRow(Count const rowIndex, Row const& currentRow);
    Rows const& getNextRows(Row const& currentRow);
    Rows calculateNextRows(Row const& currentRow);
    void startCompleteSearch();
    void doCompleteSearchAt(Count const gridIndex);
    Count m_numberOfColumns;
    Count m_numberOfRows;
    Count const m_numberOfCells;
    Count m_numberFilledCells;
    Count m_numberOfSolutions;
    Grid m_grid;
    RowToRowsMap m_currentRowToNextRows;
};

}  // namespace alba

// Tiling Problem

// Given a “2 x n” board and tiles of size “2 x 1”, count the number of ways to tile the given board using the 2 x 1
// tiles. A tile can either be placed horizontally i.e., as a 1 x 2 tile or vertically i.e., as 2 x 1 tile.

// Examples:
// Input: n = 4
// -> Output: 3
// -> Explanation:
// ---> For a 2 x 4 board, there are 3 ways
// -----> All 4 vertical
// -----> All 4 horizontal
// -----> 2 vertical and 2 horizontal
// Input: n = 3
// -> Output: 2
// -> Explanation:
// ---> We need 2 tiles to tile the board of size  2 x 3.
// ---> We can tile the board using following ways
// -----> Place all 3 tiles vertically.
// -----> Place 1 tile vertically and remaining 2 tiles horizontally.

// Other description

// Sometimes the states of a dynamic programming solution are more complex than fixed combinations of numbers.
// As an example, consider the problem of calculating the number of distinct ways to fill an nxm grid using 1x2 and 2x1
// size tiles.

// Recursive formulation:
// -> Next non filled row = all possible permutations of current row (based on previous "Next non filled row")
// -> Thus on the last row, all the complete solutions have the "Next non filled row" to be empty
