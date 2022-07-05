#include "CountingTilings.hpp"

using namespace std;

namespace alba{

CountingTilings::CountingTilings(Count const numberOfColumns, Count const numberOfRows)
    : m_numberOfColumns(numberOfColumns)    , m_numberOfRows(numberOfRows)
    , m_numberOfCells(m_numberOfColumns*m_numberOfRows)
    , m_numberFilledCells(0U)
    , m_numberOfSolutions(0U)
    , m_grid() // just initialize this when searching
{}

CountingTilings::Count CountingTilings::getNumberOfSolutionsUsingDynamicProgramming()
{
    // lets make the column the smaller dimension
    if(m_numberOfColumns > m_numberOfRows)
    {
        swap(m_numberOfColumns, m_numberOfRows);
    }

    m_numberOfSolutions=0;

    string currentRow(getEmptyRowString(m_numberOfColumns));
    searchNextRow(0U, currentRow);

    return m_numberOfSolutions;
}

CountingTilings::Count CountingTilings::getNumberOfSolutionsUsingCompleteSearch()
{
    // This is not exactly DP but "complete search".
    startCompleteSearch();
    return m_numberOfSolutions;
}

string CountingTilings::getEmptyRowString(Count const length) const
{
    return string(length, ' ');
}

void CountingTilings::searchNextRow(
        Count const rowIndex,
        string const& currentRow)
{
    if(rowIndex < m_numberOfRows-1)
    {
        for(NextIterationDetail const& nextIterationDetail : getNextIterationDetails(currentRow))
        {
            searchNextRow(rowIndex+1, nextIterationDetail.nextNonFilledRow);
        }
    }
    else if(rowIndex == m_numberOfRows-1)
    {
        string emptyRow(getEmptyRowString(currentRow.length()));
        for(auto const& detail : getNextIterationDetails(currentRow))
        {
            if(emptyRow == detail.nextNonFilledRow)
            {
                m_numberOfSolutions++;
            }
        }
    }
}

CountingTilings::NextIterationDetails const& CountingTilings::getNextIterationDetails(string const& currentNonFilledRow)
{
    auto it = m_currentToNextDetails.find(currentNonFilledRow);
    if(it != m_currentToNextDetails.cend())
    {
        return it->second;
    }
    else
    {
        string rowToBeFilled(currentNonFilledRow);
        string nextNonFilledRow(getEmptyRowString(currentNonFilledRow.length()));
        calculateNextIterationDetails(m_currentToNextDetails[currentNonFilledRow], rowToBeFilled, nextNonFilledRow, 0U);
        return m_currentToNextDetails.at(currentNonFilledRow);
    }
}

void CountingTilings::calculateNextIterationDetails(
        NextIterationDetails & nextIterationDetails,
        string & rowToBeFilled,
        string & nextNonFilledRow,
        Count const index)
{
    // This is not exactly DP but "complete search".

    if(index < rowToBeFilled.length())
    {
        if(rowToBeFilled.at(index) == ' ')
        {
            if(index+1 < rowToBeFilled.length() && rowToBeFilled.at(index+1) == ' ')
            {
                rowToBeFilled[index] = 'H';
                rowToBeFilled[index+1] = 'H';
                calculateNextIterationDetails(nextIterationDetails, rowToBeFilled, nextNonFilledRow, index+2);
                rowToBeFilled[index] = ' ';
                rowToBeFilled[index+1] = ' ';
            }
            rowToBeFilled[index] = 'V';
            nextNonFilledRow[index] = 'V';
            calculateNextIterationDetails(nextIterationDetails, rowToBeFilled, nextNonFilledRow, index+1);
            rowToBeFilled[index] = ' ';
            nextNonFilledRow[index] = ' ';
        }
        else
        {
            calculateNextIterationDetails(nextIterationDetails, rowToBeFilled, nextNonFilledRow, index+1);
        }
    }
    else if(index == rowToBeFilled.length()) // only things that fit will be added
    {
        nextIterationDetails.emplace_back(NextIterationDetail{rowToBeFilled, nextNonFilledRow});
    }
}

void CountingTilings::startCompleteSearch()
{
    // This is not exactly DP but "complete search".

    m_numberOfSolutions=0;
    m_numberFilledCells=0;
    m_grid.clearAndResize(m_numberOfColumns, m_numberOfRows);

    doCompleteSearchAt(0U);
}

void CountingTilings::doCompleteSearchAt(Count const gridIndex)
{
    // This is not exactly DP but "complete search".

    if(m_numberFilledCells == m_numberOfCells)
    {
        m_numberOfSolutions++;
    }
    else if(gridIndex < m_numberOfCells)
    {
        Count x;
        Count y;
        m_grid.retrieveXAndYFromIndex(x, y, gridIndex);
        if(m_grid.getEntry(x, y) == '\0')
        {
            if(m_grid.isInside(x+1, y) && m_grid.getEntry(x+1, y) == '\0')
            {
                m_grid.setEntry(x, y, 'H');
                m_grid.setEntry(x+1, y, 'H');
                m_numberFilledCells += 2;
                doCompleteSearchAt(gridIndex+2);
                m_grid.setEntry(x, y, '\0');
                m_grid.setEntry(x+1, y, '\0');
                m_numberFilledCells -= 2;
            }
            if(m_grid.isInside(x, y+1) && m_grid.getEntry(x, y+1) == '\0')
            {
                m_grid.setEntry(x, y, 'V');
                m_grid.setEntry(x, y+1, 'V');
                m_numberFilledCells += 2;
                doCompleteSearchAt(gridIndex+1);
                m_grid.setEntry(x, y, '\0');
                m_grid.setEntry(x, y+1, '\0');
                m_numberFilledCells -= 2;
            }
        }
        else
        {
            doCompleteSearchAt(gridIndex+1);
        }
    }
}

}
