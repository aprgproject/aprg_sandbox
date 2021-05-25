#include "Cube36.hpp"

#include <iostream>
#include <windows.h>

using namespace std;

namespace alba
{

Pieces::Pieces(int numberOfColors, int maximumHeight)
    : m_numberOfColors(numberOfColors)
    , m_maximumHeight(maximumHeight)
    , m_availablePieces(numberOfColors*maximumHeight, true)
{}

int Pieces::getNextColorWithHeight(int height, int startingColor) const
{
    int heightIndex=(height-1)*m_numberOfColors;
    for(int colorIndex=startingColor-1; colorIndex<m_numberOfColors; colorIndex++)
    {
        if(m_availablePieces[heightIndex+colorIndex])
        {
            return colorIndex+1;
        }
    }
    return 0;
}


int Pieces::getNumberOfColors() const
{
    return m_numberOfColors;
}

void Pieces::printPieces() const
{
    cout<<"Pieces:"<<endl;
    for(int heightIndex=0; heightIndex<m_maximumHeight; heightIndex++)
    {
        for(int colorIndex=0; colorIndex<m_numberOfColors; colorIndex++)
        {
            cout<<m_availablePieces[getPiecesIndex(colorIndex, heightIndex)];
        }
        cout<<endl;
    }
}

bool Pieces::isPieceAvailable(int height, int color)
{
    return m_availablePieces[getPiecesIndex(height-1, color-1)];
}

void Pieces::setPieceAsUnavailable(int height, int color)
{
    if(color>0)
    {
        m_availablePieces[getPiecesIndex(height-1, color-1)] = false;
    }
}

void Pieces::setPieceAsAvailable(int height, int color)
{
    if(color>0)
    {
        m_availablePieces[getPiecesIndex(height-1, color-1)] = true;
    }
}

int Pieces::getPiecesIndex(int heightIndex, int colorIndex) const
{
    return (heightIndex*m_numberOfColors)+colorIndex;
}



Board::Board(int rows, int columns)
    : m_rows(rows)
    , m_columns(columns)
    , m_heightBoard{1,2,5,4,6,3, 5,3,6,1,4,2, 4,6,3,5,2,1, 2,1,4,3,5,6, 3,5,2,6,1,4, 6,4,1,2,3,5}
    , m_colorBoard(rows*columns, 0)
    , m_colorBoardFinal(rows*columns, 0)
    , m_pieces(6,6)
{}

void Board::solve(int row, int column)
{
    static bool isFinished(false);
    cout<<"solve row:"<<row<<" column:"<<column<<endl;
    printColorsOfWorkingBoard();
    int height = getHeightAt(row, column);
    int nextRow=row,nextColumn=column;
    nextRow++;
    if(nextRow>=m_rows)
    {
        nextColumn++;
        nextRow=0;
    }
    if(nextColumn<m_columns)
    {
        for(int color=1; color<=m_pieces.getNumberOfColors(); color++)
        {
            m_pieces.setPieceAsAvailable(height,  getColorAt(row, column));
            if(m_pieces.isPieceAvailable(height, color))
            {
                setColorAt(color, row, column);
                if(isColorUniqueAtIndex(row, column))
                {
                    m_pieces.setPieceAsUnavailable(height, color);
                    solve(nextRow, nextColumn);
                    if(isFinished)
                    {
                        return;
                    }
                }
            }
        }
    }
    else
    {
        isFinished=true;
    }
    m_pieces.setPieceAsAvailable(height,  getColorAt(row, column));
    setColorAt(0, row, column);
}

bool Board::setNextColorAtIndex(int rowIndex, int columnIndex)
{
    int color = getColorAt(rowIndex, columnIndex);
    int height = getHeightAt(rowIndex, columnIndex);
    m_pieces.setPieceAsAvailable(height, color);
    while(1)
    {
        int nextColor = m_pieces.getNextColorWithHeight(height, color+1);
        if(nextColor==0)
        {
            return false;
        }
        setColorAt(nextColor, rowIndex, columnIndex);
        if(isColorUniqueAtIndex(rowIndex, columnIndex))
        {
            m_pieces.setPieceAsUnavailable(height, nextColor);
            return true;
        }
        color = nextColor;
    }
    return false;
}

int Board::getHeightAt(int rowIndex, int columnIndex) const
{
    return m_heightBoard[getBoardIndex(rowIndex, columnIndex)];
}

int Board::getColorAt(int rowIndex, int columnIndex) const
{
    return m_colorBoard[getBoardIndex(rowIndex, columnIndex)];
}

bool Board::isColorUniqueAtIndex(int rowIndex, int columnIndex) const
{
    return isColorUniqueAtRow(rowIndex) && isColorUniqueAtColumn(columnIndex);
}

bool Board::isColorUniqueAtRow(int rowIndex) const
{
    set<int> uniqueColors;
    for(int columnIndex=0; columnIndex<m_columns; columnIndex++)
    {
        int color(m_colorBoard[getBoardIndex(rowIndex, columnIndex)]);
        if(isColorUnique(uniqueColors, color))
        {
            uniqueColors.emplace(color);
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool Board::isColorUniqueAtColumn(int columnIndex) const
{
    set<int> uniqueColors;
    for(int rowIndex=0; rowIndex<m_rows; rowIndex++)
    {
        int color(m_colorBoard[getBoardIndex(rowIndex, columnIndex)]);
        if(isColorUnique(uniqueColors, color))
        {
            uniqueColors.emplace(color);
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Board::setColorAt(int color, int rowIndex, int columnIndex)
{
    m_colorBoard[getBoardIndex(rowIndex, columnIndex)] = color;
}

void Board::printColorsOfWorkingBoard() const
{
    cout<<"Board:"<<endl;
    for(int columnIndex=0; columnIndex<m_columns; columnIndex++)
    {
        for(int rowIndex=0; rowIndex<m_rows; rowIndex++)
        {
            cout<<m_colorBoard[getBoardIndex(rowIndex, columnIndex)];
        }
        cout<<endl;
    }
}

void Board::printColorsOfFinalBoard() const
{
    cout<<"FinalBoard:"<<endl;
    for(int columnIndex=0; columnIndex<m_columns; columnIndex++)
    {
        for(int rowIndex=0; rowIndex<m_rows; rowIndex++)
        {
            cout<<m_colorBoardFinal[getBoardIndex(rowIndex, columnIndex)];
        }
        cout<<endl;
    }
}

void Board::clearColorStartingAt(int startingRow, int startingColumn)
{
    for(int columnIndex=startingColumn; columnIndex<m_columns; columnIndex++)
    {
        for(int rowIndex=startingRow; rowIndex<m_rows; rowIndex++)
        {
            int color = getColorAt(rowIndex, columnIndex);
            int height = getHeightAt(rowIndex, columnIndex);
            m_pieces.setPieceAsAvailable(height, color);
            m_colorBoard[getBoardIndex(rowIndex, columnIndex)]=0;
        }
    }
}

int Board::getBoardIndex(int rowIndex, int columnIndex) const
{
    return (columnIndex*m_rows)+rowIndex;
}

bool Board::isColorUnique(set<int> const& uniqueColors, int color) const
{
    if(color != 0)
    {
        if(uniqueColors.find(color) != uniqueColors.end())
        {
            return false;
        }
    }
    return true;
}

}