#include "BoardUtilities.hpp"

using namespace std;

namespace alba
{

namespace chess
{

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
            Board::PieceValue piece1(board1.getPieceValue(coordinate));
            Board::PieceValue piece2(board2.getPieceValue(coordinate));
            if(piece1 != piece2)
            {
                if(board1.isEmpty(coordinate))
                {
                    coordinatesWithPiecesInDifference1.emplace_back(coordinate);
                }
                if(board2.isEmpty(coordinate))
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
        Board::PieceValue piece1(board1.getPieceValue(coordinate1));
        for(unsigned int j=0; j<coordinatesWithPiecesInDifference2.size(); j++)
        {
            Coordinate const& coordinate2(coordinatesWithPiecesInDifference2.at(i));
            Board::PieceValue piece2(board2.getPieceValue(coordinate2));
            Move moveFrom1To2(coordinate1, coordinate2);
            if((piece1 == piece2 && board1.isMovePossible(moveFrom1To2))
                    || board1.isPromotionMove(moveFrom1To2))
            {
                possibleMoves.emplace_back(moveFrom1To2);
            }
        }
    }
    return possibleMoves;
}

}

}
