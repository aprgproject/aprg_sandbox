#include "BoardUtilities.hpp"

#include <Common/Macros/AlbaMacros.hpp>

#include <sstream>

using namespace std;
namespace alba
{

namespace chess
{

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

string constructFenString(
        Board const& board,
        PieceColor const colorToMove,        string const& castlingAvailability,
        string const& enPassantTarget,
        unsigned int const halfMoveClock,
        unsigned int const fullMoveNumber){
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
                if(board1.isEmpty(coordinate))                {
                    coordinatesWithPiecesInDifference1.emplace_back(coordinate);
                }
                if(board2.isEmpty(coordinate))                {
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
            if((piece1 == piece2 && board1.isMovePossible(moveFrom1To2))
                    || board1.isPromotionMove(moveFrom1To2))            {
                possibleMoves.emplace_back(moveFrom1To2);
            }
        }    }
    return possibleMoves;
}

}

}
