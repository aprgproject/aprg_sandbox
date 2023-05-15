#include "StreamOperators.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/User/DisplayTable.hpp>

#include <iomanip>
#include <iostream>

using namespace std;
namespace alba {

namespace chess {

ostream& operator<<(ostream& out, PieceColor const pieceColor) {
    out << getEnumString(pieceColor);
    return out;
}

ostream& operator<<(ostream& out, PieceType const pieceType) {
    out << getEnumString(pieceType);
    return out;
}

ostream& operator<<(ostream& out, PieceColorAndType const pieceType) {
    out << getEnumString(pieceType);
    return out;
}

ostream& operator<<(ostream& out, Piece const& piece) {
    out << piece.getFenCharacter();
    return out;
}

ostream& operator<<(ostream& out, Move const& move) {
    out << move.first.getX() << " ";
    out << move.first.getY() << " ";
    out << move.second.getX() << " ";
    out << move.second.getY();
    return out;
}

istream& operator>>(istream& in, Move& move) {
    int firstX, firstY, secondX, secondY;
    in >> firstX;
    in >> firstY;
    in >> secondX;
    in >> secondY;
    move = Move{{firstX, firstY}, {secondX, secondY}};
    return in;
}

ostream& operator<<(ostream& out, Board const& board) {
    Board::PieceGrid const& pieceGrid(board.getPieceGrid());
    DisplayTable displayTable(Board::CHESS_SIDE_SIZE, Board::CHESS_SIDE_SIZE);
    displayTable.setBorders("-", "|");
    int i = 0;
    for (int y = 0; y < Board::CHESS_SIDE_SIZE; y++) {
        for (int x = 0; x < Board::CHESS_SIDE_SIZE; x++) {
            displayTable.getCellReferenceAt(x, y).setText(
                string(" ") + pieceGrid.at(i++).getFenCharacter() + string(" "));
        }
    }
    out << displayTable;
    return out;
}

ostream& operator<<(ostream& out, BoardValue const& boardValue) {
    out << boardValue.m_data.at(0) << " ";
    out << boardValue.m_data.at(1) << " ";
    out << boardValue.m_data.at(2) << " ";
    out << boardValue.m_data.at(3);
    return out;
}

istream& operator>>(istream& in, BoardValue& boardValue) {
    in >> boardValue.m_data[0];
    in >> boardValue.m_data[1];
    in >> boardValue.m_data[2];
    in >> boardValue.m_data[3];
    return in;
}

void printHexValuesInBoard(ostream& out, Board const& board) {
    Board::PieceGrid const& pieceGrid(board.getPieceGrid());
    int i = 0;
    out << hex << uppercase;
    for (int y = 0; y < Board::CHESS_SIDE_SIZE; y++) {
        for (int x = 0; x < Board::CHESS_SIDE_SIZE; x++) {
            out << "0x" << static_cast<unsigned int>(pieceGrid.at(i++).getData()) << ", ";
        }
    }
    out << dec;
    out << "\n";
}

}  // namespace chess

}  // namespace alba