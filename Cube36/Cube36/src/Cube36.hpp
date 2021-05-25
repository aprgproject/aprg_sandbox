#pragma once

#include <vector>
#include <set>

namespace alba
{

class Pieces
{
public:
    Pieces(int numberOfColors, int maximumHeight);
    bool isPieceAvailable(int height, int color);
    void setPieceAsUnavailable(int height, int color);
    void setPieceAsAvailable(int height, int color);
    int getNextColorWithHeight(int height, int startingColor) const;
    void printPieces() const;
    int getNumberOfColors() const;

private:
    int getPiecesIndex(int heightIndex, int colorIndex) const;
    int m_numberOfColors;
    int m_maximumHeight;
    std::vector<bool> m_availablePieces;
};


class Board
{
public:
    Board(int rows, int columns);
    void solve(int row, int column);
    int getHeightAt(int rowIndex, int columnIndex) const;
    int getColorAt(int rowIndex, int columnIndex) const;
    bool setNextColorAtIndex(int rowIndex, int columnIndex);
    bool isColorUniqueAtIndex(int rowIndex, int columnIndex) const;
    bool isColorUniqueAtRow(int rowIndex) const;
    bool isColorUniqueAtColumn(int columnIndex) const;
    void setColorAt(int color, int rowIndex, int columnIndex);
    void printColorsOfWorkingBoard() const;
    void printColorsOfFinalBoard() const;
    void clearColorStartingAt(int startingRow, int startingColumn);

private:
    int getBoardIndex(int rowIndex, int columnIndex) const;
    bool isColorUnique(std::set<int> const& colors, int color) const;
    int m_rows;
    int m_columns;
    std::vector<int> m_heightBoard;
    std::vector<int> m_colorBoard;
    std::vector<int> m_colorBoardFinal;
    Pieces m_pieces;
};

}