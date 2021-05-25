#pragma once

#include <fstream>
#include <vector>
#include <set>

namespace alba
{

class Pieces
{
public:
    Pieces(unsigned int numberOfColors, unsigned int maximumHeight);
    bool isPieceAvailable(unsigned int height, unsigned int color) const;
    void setPieceAsUnavailable(unsigned int height, unsigned int color);
    void setPieceAsAvailable(unsigned int height, unsigned int color);
    unsigned int getNextColorWithHeight(unsigned int height, unsigned int startingColor) const;
    unsigned int getNumberOfColors() const;
    unsigned int getMaximumHeight() const;

private:
    unsigned int getPiecesIndex(unsigned int heightIndex, unsigned int colorIndex) const;
    unsigned int m_numberOfColors;
    unsigned int m_maximumHeight;
    std::vector<bool> m_availablePieces;
};


class Board
{
public:
    Board(unsigned int rows, unsigned int columns, unsigned int numberOfColors, unsigned int maximumHeight);
    void setHeightBoard(std::initializer_list<unsigned int> heightBoard);
    void solve();
    unsigned int getHeightAt(unsigned int rowIndex, unsigned int columnIndex) const;
    unsigned int getColorAt(unsigned int rowIndex, unsigned int columnIndex) const;
    bool setNextColorAtIndex(unsigned int rowIndex, unsigned int columnIndex);
    bool isColorUniqueAtIndex(unsigned int rowIndex, unsigned int columnIndex) const;
    bool isColorUniqueAtRow(unsigned int rowIndex) const;
    bool isColorUniqueAtColumn(unsigned int columnIndex) const;
    void setColorAt(unsigned int color, unsigned int rowIndex, unsigned int columnIndex);
    void printColorsBoardAndPieces(
            std::ostream& printStream,
            std::vector<unsigned int> const& colorBoard,
            Pieces const& pieces);
    void printColorsOfFinalBoard();
    void clearColorStartingAt(unsigned int startingRow, unsigned int startingColumn);
    unsigned int getBoardSize() const;

private:
    unsigned int getBoardIndex(unsigned int rowIndex, unsigned int columnIndex) const;
    bool isColorUnique(std::set<unsigned int> const& colors, unsigned int color) const;
    unsigned int m_rows;
    unsigned int m_columns;
    std::vector<unsigned int> m_heightBoard;
    std::vector<unsigned int> m_colorBoard;
    std::vector<unsigned int> m_colorBoardFinal;
    Pieces m_pieces;
    std::ofstream m_printStream;
};

}
