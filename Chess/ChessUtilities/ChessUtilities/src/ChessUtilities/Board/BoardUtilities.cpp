#include "BoardUtilities.hpp"

#include <Common/Macros/AlbaMacros.hpp>

#include <sstream>

using namespace std;

namespace alba
{

namespace chess
{

bool isCoordinateOnBoard(Coordinate const& coordinate)
{
    auto x(coordinate.getX());
    auto y(coordinate.getY());
    return (x>=0 && x<=7) && (y>=0 && y<=7);
}

bool isValidMove(Move const& move)
{
    return move.first != move.second
            && isCoordinateOnBoard(move.first)
            && isCoordinateOnBoard(move.second);
}

PieceColor getOppositeColor(PieceColor const pieceColor)
{
    PieceColor result{};
    if(PieceColor::White == pieceColor)
    {
        result = PieceColor::Black;
    }
    else if(PieceColor::Black == pieceColor)
    {
        result = PieceColor::White;
    }
    return result;
}

std::string getEnumString(PieceColor const pieceColor)
{
    switch(pieceColor)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColor::White, "White")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColor::Black, "Black")
            default:
        return "default";
    }
}

std::string getEnumString(PieceType const pieceType)
{
    switch(pieceType)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Empty, "Empty")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Pawn, "Pawn")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Knight, "Knight")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Bishop, "Bishop")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Rook, "Rook")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::Queen, "Queen")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceType::King, "King")
            default:
        return "default";
    }
}
std::string getEnumString(PieceColorAndType const pieceColorAndType)
{
    switch(pieceColorAndType)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::Empty, "Empty")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhitePawn, "WhitePawn")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteKnight, "WhiteKnight")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteBishop, "WhiteBishop")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteRook, "WhiteRook")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteQueen, "WhiteQueen")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::WhiteKing, "WhiteKing")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackPawn, "BlackPawn")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackKnight, "BlackKnight")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackBishop, "BlackBishop")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackRook, "BlackRook")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackQueen, "BlackQueen")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(PieceColorAndType::BlackKing, "BlackKing")
            default:
        return "default";
    }
}

string constructFenString(
        Board const& board,
        PieceColor const colorToMove,
        string const& castlingAvailability,
        string const& enPassantTarget,
        unsigned int const halfMoveClock,
        unsigned int const fullMoveNumber)
{
    stringstream ss;
    ss << board.getFenString() << " ";
    if(PieceColor::White == colorToMove)
    {
        ss << "w ";
    }
    else if(PieceColor::Black == colorToMove)
    {
        ss << "b ";
    }
    ss << castlingAvailability << " " << enPassantTarget << " " << halfMoveClock << " " << fullMoveNumber;
    return ss.str();
}

Moves getSequenceOfMoves(
        Board const& board1,
        Board const& board2)
{
    // this is difficult
    Coordinates coordinatesWithPiecesInDifference1;
    Coordinates coordinatesWithPiecesInDifference2;
    for(CoordinateDataType x=0; x<8; x++)
    {
        for(CoordinateDataType y=0; y<8; y++)
        {
            Coordinate coordinate(x, y);
            Piece piece1(board1.getPieceAt(coordinate));
            Piece piece2(board2.getPieceAt(coordinate));
            if(piece1 != piece2)
            {
                if(board1.isEmptyAt(coordinate))
                {
                    coordinatesWithPiecesInDifference1.emplace_back(coordinate);
                }
                if(board2.isEmptyAt(coordinate))
                {
                    coordinatesWithPiecesInDifference2.emplace_back(coordinate);
                }
            }
        }
    }

    Moves possibleMoves;
    for(unsigned int i=0; i<coordinatesWithPiecesInDifference1.size(); i++)
    {
        Coordinate const& coordinate1(coordinatesWithPiecesInDifference1.at(i));
        Piece piece1(board1.getPieceAt(coordinate1));
        for(unsigned int j=0; j<coordinatesWithPiecesInDifference2.size(); j++)
        {
            Coordinate const& coordinate2(coordinatesWithPiecesInDifference2.at(i));
            Piece piece2(board2.getPieceAt(coordinate2));
            Move moveFrom1To2(coordinate1, coordinate2);
            if((piece1 == piece2 && board1.isPossibleMove(moveFrom1To2))
                    || board1.isPromotionMove(moveFrom1To2))
            {
                possibleMoves.emplace_back(moveFrom1To2);            }
        }
    }
    return possibleMoves;}

}

}
