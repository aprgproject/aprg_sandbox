#include "Cube36.hpp"

#include <algorithm>
#include <iostream>


#include <Debug/AlbaDebug.hpp>
#define ALBA_TEMP_PRINT0(parameter) m_printStream << "ALBA_TEMP_PRINT0 in " << __FUNCTION__ << "(...): " << parameter << endl
#define ALBA_TEMP_PRINT1(...) m_printStream << "ALBA_TEMP_PRINT1 in " << __FUNCTION__ << "(...): " << Z_ALBA_PRIVATE_GET_STRING_PRINT1(__VA_ARGS__) << endl
#define ALBA_TEMP_PRINT2(...) m_printStream << "ALBA_TEMP_PRINT2 in " << __FUNCTION__ << "(...): " << Z_ALBA_PRIVATE_GET_STRING_PRINT2(__VA_ARGS__) << endl
#define ALBA_TEMP_PRINT3(...) m_printStream << "ALBA_TEMP_PRINT3 in " << __FUNCTION__ << "(...): " << Z_ALBA_PRIVATE_GET_STRING_PRINT3(__VA_ARGS__) << endl
#define ALBA_TEMP_PRINT4(...) m_printStream << "ALBA_TEMP_PRINT4 in " << __FUNCTION__ << "(...): " << Z_ALBA_PRIVATE_GET_STRING_PRINT4(__VA_ARGS__) << endl
#define ALBA_TEMP_PRINT5(...) m_printStream << "ALBA_TEMP_PRINT5 in " << __FUNCTION__ << "(...): " << Z_ALBA_PRIVATE_GET_STRING_PRINT5(__VA_ARGS__) << endl
#define ALBA_TEMP_PRINT6(...) m_printStream << "ALBA_TEMP_PRINT6 in " << __FUNCTION__ << "(...): " << Z_ALBA_PRIVATE_GET_STRING_PRINT6(__VA_ARGS__) << endl

using namespace std;

namespace alba
{

Pieces::Pieces(unsigned int numberOfColors, unsigned int maximumHeight)
    : m_numberOfColors(numberOfColors)
    , m_maximumHeight(maximumHeight)
    , m_availablePieces(numberOfColors*maximumHeight, true)
{}

unsigned int Pieces::getNextColorWithHeight(unsigned int height, unsigned int startingColor) const
{
    unsigned int heightIndex=(height-1)*m_numberOfColors;
    for(unsigned int colorIndex=startingColor-1; colorIndex<m_numberOfColors; colorIndex++)
    {
        if(m_availablePieces[heightIndex+colorIndex])
        {
            return colorIndex+1;
        }
    }
    return 0;
}

unsigned int Pieces::getNumberOfColors() const
{
    return m_numberOfColors;
}

unsigned int Pieces::getMaximumHeight() const
{
    return m_maximumHeight;
}

bool Pieces::isPieceAvailable(unsigned int height, unsigned int color) const
{
    return m_availablePieces.at(getPiecesIndex(height-1, color-1));
}

void Pieces::setPieceAsUnavailable(unsigned int height, unsigned int color)
{
    if(color>0)
    {
        m_availablePieces[getPiecesIndex(height-1, color-1)] = false;
    }
}

void Pieces::setPieceAsAvailable(unsigned int height, unsigned int color)
{
    if(color>0)
    {
        m_availablePieces[getPiecesIndex(height-1, color-1)] = true;
    }
}

unsigned int Pieces::getPiecesIndex(unsigned int heightIndex, unsigned int colorIndex) const
{
    return (heightIndex*m_numberOfColors)+colorIndex;
}



Board::Board(unsigned int rows, unsigned int columns, unsigned int numberOfColors, unsigned int maximumHeight)
    : m_rows(rows)
    , m_columns(columns)
    , m_heightBoard(getBoardSize(), 0)
    , m_colorBoard(getBoardSize(), 0)
    , m_colorBoardFinal(getBoardSize(), 0)
    , m_pieces(numberOfColors, maximumHeight)
    , m_printStream(R"(N:\cube36logs.txt)")
{}

void Board::setHeightBoard(std::initializer_list<unsigned int> heightBoard)
{
    unsigned int boardSize = getBoardSize();
    unsigned int sizeToCopy = min(heightBoard.size(), boardSize);
    copy(heightBoard.begin(), heightBoard.begin()+sizeToCopy, m_heightBoard.begin());
}

void Board::solve()
{
    std::vector<unsigned int> nearestBoard(36,0);
    unsigned int maxNearestScore=0;
    Pieces nearestPieces(6,6);
    unsigned int printCounter=0;
    for(unsigned int column=0; column<m_columns; )
    {
        for(unsigned int row=0; row<m_rows; )
        {
            unsigned int nearestScore=(column*m_rows)+row;
            ALBA_TEMP_PRINT2(nearestScore, maxNearestScore);
            if(nearestScore>maxNearestScore)
            {
                maxNearestScore=nearestScore;
                nearestBoard=m_colorBoard;
                nearestPieces=m_pieces;
            }
            printColorsBoardAndPieces(m_printStream, m_colorBoard, m_pieces);
            printColorsBoardAndPieces(m_printStream, nearestBoard, nearestPieces);
            printColorsBoardAndPieces(cout, m_colorBoard, m_pieces);
            printColorsBoardAndPieces(cout, nearestBoard, nearestPieces);



            bool isWrongConfiguration(true);
            unsigned int height = getHeightAt(row, column);
            unsigned int color = getColorAt(row, column);
            color++;
            ALBA_TEMP_PRINT4(row, column, height, color);
            for(;color<=m_pieces.getNumberOfColors(); color++)
            {
                ALBA_TEMP_PRINT3(m_pieces.isPieceAvailable(height, color), height, color);
                if(m_pieces.isPieceAvailable(height, color))
                {
                    setColorAt(color, row, column);
                    ALBA_TEMP_PRINT3(isColorUniqueAtIndex(row, column), row, column);
                    if(isColorUniqueAtIndex(row, column))
                    {
                        m_pieces.setPieceAsUnavailable(height, color);
                        isWrongConfiguration=false;
                        break;
                    }
                }
            }
            if(isWrongConfiguration)
            {
                ALBA_TEMP_PRINT5(isWrongConfiguration, row, column, height, color);
                m_pieces.setPieceAsAvailable(getHeightAt(row, column), getColorAt(row, column));
                ALBA_TEMP_PRINT4(row, column, getHeightAt(row, column), getColorAt(row, column));
                setColorAt(0, row, column);
                if(row>0)
                {
                    row--;
                }
                else
                {
                    row=m_rows-1;
                    column--;
                }
                m_pieces.setPieceAsAvailable(getHeightAt(row, column), getColorAt(row, column));
                ALBA_TEMP_PRINT4(row, column, getHeightAt(row, column), getColorAt(row, column));
            }
            else
            {
                row++;
                if(row>=m_rows)
                {
                    column++;
                }
            }
        }
    }
    printColorsBoardAndPieces(cout, nearestBoard, nearestPieces);
}

bool Board::setNextColorAtIndex(unsigned int rowIndex, unsigned int columnIndex)
{
    unsigned int color = getColorAt(rowIndex, columnIndex);
    unsigned int height = getHeightAt(rowIndex, columnIndex);
    m_pieces.setPieceAsAvailable(height, color);
    while(1)
    {
        unsigned int nextColor = m_pieces.getNextColorWithHeight(height, color+1);
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

unsigned int Board::getBoardSize() const
{
    return m_rows*m_columns;
}

unsigned int Board::getHeightAt(unsigned int rowIndex, unsigned int columnIndex) const
{
    return m_heightBoard[getBoardIndex(rowIndex, columnIndex)];
}

unsigned int Board::getColorAt(unsigned int rowIndex, unsigned int columnIndex) const
{
    return m_colorBoard[getBoardIndex(rowIndex, columnIndex)];
}

bool Board::isColorUniqueAtIndex(unsigned int rowIndex, unsigned int columnIndex) const
{
    return isColorUniqueAtRow(rowIndex) && isColorUniqueAtColumn(columnIndex);
}

bool Board::isColorUniqueAtRow(unsigned int rowIndex) const
{
    set<unsigned int> uniqueColors;
    for(unsigned int columnIndex=0; columnIndex<m_columns; columnIndex++)
    {
        unsigned int color(m_colorBoard[getBoardIndex(rowIndex, columnIndex)]);
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

bool Board::isColorUniqueAtColumn(unsigned int columnIndex) const
{
    set<unsigned int> uniqueColors;
    for(unsigned int rowIndex=0; rowIndex<m_rows; rowIndex++)
    {
        unsigned int color(m_colorBoard[getBoardIndex(rowIndex, columnIndex)]);
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

void Board::setColorAt(unsigned int color, unsigned int rowIndex, unsigned int columnIndex)
{
    m_colorBoard[getBoardIndex(rowIndex, columnIndex)] = color;
}

void Board::printColorsBoardAndPieces(
        std::ostream& printStream,
        std::vector<unsigned int> const& colorBoard,
        Pieces const& pieces)
{
    printStream<<"[Color Board] [Height Board] [Pieces]"<<endl;
    for(unsigned int i=0; i<6; i++)
    {
        for(unsigned int j=0; j<6; j++)
        {
            printStream<<colorBoard[getBoardIndex(j, i)];
        }
        printStream<<"        ";
        for(unsigned int j=0; j<6; j++)
        {
            printStream<<m_heightBoard[getBoardIndex(j, i)];
        }
        printStream<<"        ";
        for(unsigned int j=0; j<6; j++)
        {
            printStream<<static_cast<unsigned int>(pieces.isPieceAvailable(j+1, i+1));
        }
        printStream<<endl;
    }
    printStream<<endl;
}

void Board::printColorsOfFinalBoard()
{
    m_printStream<<"FinalBoard:"<<endl;
    for(unsigned int columnIndex=0; columnIndex<m_columns; columnIndex++)
    {
        for(unsigned int rowIndex=0; rowIndex<m_rows; rowIndex++)
        {
            m_printStream<<m_colorBoardFinal[getBoardIndex(rowIndex, columnIndex)];
        }
        m_printStream<<endl;
    }
}

void Board::clearColorStartingAt(unsigned int startingRow, unsigned int startingColumn)
{
    for(unsigned int columnIndex=startingColumn; columnIndex<m_columns; columnIndex++)
    {
        for(unsigned int rowIndex=startingRow; rowIndex<m_rows; rowIndex++)
        {
            unsigned int color = getColorAt(rowIndex, columnIndex);
            unsigned int height = getHeightAt(rowIndex, columnIndex);
            m_pieces.setPieceAsAvailable(height, color);
            m_colorBoard[getBoardIndex(rowIndex, columnIndex)]=0;
        }
    }
}

unsigned int Board::getBoardIndex(unsigned int rowIndex, unsigned int columnIndex) const
{
    return (columnIndex*m_rows)+rowIndex;
}

bool Board::isColorUnique(set<unsigned int> const& uniqueColors, unsigned int color) const
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
