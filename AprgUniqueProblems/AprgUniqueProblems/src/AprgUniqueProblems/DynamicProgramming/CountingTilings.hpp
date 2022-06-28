#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <map>
#include <string>
#include <vector>

namespace alba
{

class CountingTilings
{
public:
    // Sometimes the states of a dynamic programming solution are more complex than fixed combinations of numbers.
    // As an example, consider the problem of calculating the number of distinct ways to fill an nxm grid using 1x2 and 2x1 size tiles.

    using Count = unsigned int;
    using Grid = matrix::AlbaMatrix<char>;
    struct NextIterationDetail
    {
        std::string currentFilledRow;
        std::string nextNonFilledRow;
    };
    using NextIterationDetails = std::vector<NextIterationDetail>;
    using StringToNextIterationDetailsMap=std::map<std::string, NextIterationDetails>;

    CountingTilings(Count const numberOfColumns, Count const numberOfRows);

    Count getNumberOfSolutionsUsingDynamicProgramming();
    Count getNumberOfSolutionsUsingCompleteSearch();

private:
    std::string getEmptyRowString(Count const length) const;
    void searchNextRow(
            Count const rowIndex,
            std::string const& currentRow);
    NextIterationDetails const& getNextIterationDetails(std::string const& currentNonFilledRow);
    void calculateNextIterationDetails(
            NextIterationDetails & nextIterationDetails,
            std::string & rowToBeFilled,
            std::string & nextNonFilledRow,
            Count const index);
    void startCompleteSearch();
    void doCompleteSearchAt(Count const gridIndex);
    Count m_numberOfColumns;
    Count m_numberOfRows;
    Count const m_numberOfCells;
    Count m_numberFilledCells;
    Count m_numberOfSolutions;
    Grid m_grid;
    StringToNextIterationDetailsMap m_currentToNextDetails;
};

}
