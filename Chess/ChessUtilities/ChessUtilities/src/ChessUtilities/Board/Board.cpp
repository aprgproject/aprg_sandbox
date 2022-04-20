#include "Board.hpp"

#include <ChessUtilities/Board/Piece.hpp>

#include <algorithm>
#include <sstream>

using namespace std;

namespace alba
{

namespace matrix
{
template <> bool isEqualForMathMatrixDataType(chess::Piece const& value1, chess::Piece const& value2)
{
    return value1 == value2;
}
}

namespace chess
{

Board::Board()
    : m_orientation(Orientation::Unknown)
    , m_pieceMatrix(8U, 8U)
{}

Board::Board(Orientation const& orientation)
    : m_orientation(orientation)
    , m_pieceMatrix(8U, 8U, getInitialValues(orientation))
{}

Board::Board(Orientation const& orientation, InitializerList const& initializerList)
    : m_orientation(orientation)
    , m_pieceMatrix(8U, 8U, initializerList)
{}

bool Board::isCoordinateOnBoard(Coordinate const& coordinate) const{
    auto x(coordinate.getX());
    auto y(coordinate.getY());
    return (x>=0 && x<=7) && (y>=0 && y<=7);}

bool Board::isEmpty(Coordinate const& coordinate) const
{
    return PieceType::Empty == getPieceAt(coordinate).getType();
}

bool Board::isMovePossible(Move const& move) const{
    Moves moves(getPossibleMoves(move.first));
    auto it = find(moves.cbegin(), moves.cend(), move);
    return it != moves.cend();}

bool Board::isPromotionMove(Move const& move) const
{
    return PieceType::Pawn == getPieceAt(move.first).getType()
            && (move.second.getY() == 0 || move.second.getY() == 7)
            && isMovePossible(move);
}

Board::PieceMatrix const& Board::getPieceMatrix() const
{
    return m_pieceMatrix;
}

Piece Board::getPieceAt(Coordinate const& coordinate) const
{
    Piece result;
    if((isCoordinateOnBoard(coordinate)))
    {
        result = m_pieceMatrix.getEntry(coordinate.getX(), coordinate.getY());
    }
    return result;
}
char Board::getPieceCharacter(Coordinate const& coordinate) const
{
    return getPieceAt(coordinate).getCharacter();
}

Moves Board::getPossibleMoves(Coordinate const& coordinate) const{
    Moves result;
    retrievePossibleMovesBaseFromPieceType(result, coordinate);
    return result;}

std::string Board::getFenString() const
{
    string result;
    for(CoordinateDataType rank=0; rank<8; rank++)
    {
        int emptyCellsInRank = 0;
        stringstream ssFenInRank;
        for(CoordinateDataType file=0; file<8; file++)
        {
            Coordinate coordinate(file, rank);
            if(isEmpty(coordinate))
            {
                emptyCellsInRank++;
            }
            else
            {
                if(emptyCellsInRank != 0)
                {
                    ssFenInRank << emptyCellsInRank;
                }
                ssFenInRank << getPieceCharacter(coordinate);
                emptyCellsInRank = 0;
            }
        }
        if (emptyCellsInRank != 0)
        {
            ssFenInRank << emptyCellsInRank;
        }
        result += ssFenInRank.str();
        if(rank != 7U)
        {
            result += "/";
        }
    }
    return result;
}

void Board::setOrientation(Orientation const orientation)
{
    m_orientation = orientation;
}

void Board::setPieceAt(
        Coordinate const& coordinate,
        Piece const& piece)
{
    if((isCoordinateOnBoard(coordinate)))
    {
        m_pieceMatrix.setEntry(coordinate.getX(), coordinate.getY(), piece.getUnderlyingValue());
    }
}

void Board::retrievePossibleMovesBaseFromPieceType(
        Moves & result,
        Coordinate const& coordinate) const
{
    Piece piece(getPieceAt(coordinate));
    PieceType pieceType = piece.getType();
    switch(pieceType)
    {
    case PieceType::Pawn:    {
        retrievePossiblePawnMoves(result, coordinate);
        break;
    }    case PieceType::Knight:
    {
        retrievePossibleKnightMoves(result, coordinate);
        break;
    }
    case PieceType::Bishop:
    {
        retrievePossibleBishopMoves(result, coordinate);
        break;
    }
    case PieceType::Rook:
    {
        retrievePossibleRookMoves(result, coordinate);
        break;
    }
    case PieceType::Queen:
    {
        retrievePossibleQueenMoves(result, coordinate);
        break;
    }
    case PieceType::King:
    {
        retrievePossibleKingMoves(result, coordinate);
        break;
    }
    default :
    {
        break;
    }
    }
}

void Board::retrievePossiblePawnMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    Piece piece(getPieceAt(coordinate));
    if(PieceColor::White == piece.getColor())
    {
        if(Orientation::BlackUpWhiteDown == m_orientation)
        {            addMove(result, coordinate, coordinate + Coordinate(0, -1));
            if(6 == coordinate.getY())
            {
                addMove(result, coordinate, coordinate + Coordinate(0, -2));            }
        }
        else if(Orientation::WhiteUpBlackDown == m_orientation)
        {
            addMove(result, coordinate, coordinate + Coordinate(0, 1));
            if(1 == coordinate.getY())
            {
                addMove(result, coordinate, coordinate + Coordinate(0, 2));
            }
        }
    }
    else if(PieceColor::Black == piece.getColor())
    {
        if(Orientation::BlackUpWhiteDown == m_orientation)
        {            addMove(result, coordinate, coordinate + Coordinate(0, 1));
            if(1 == coordinate.getY())
            {
                addMove(result, coordinate, coordinate + Coordinate(0, 2));            }
        }
        else if(Orientation::WhiteUpBlackDown == m_orientation)
        {
            addMove(result, coordinate, coordinate + Coordinate(0, -1));
            if(6 == coordinate.getY())
            {
                addMove(result, coordinate, coordinate + Coordinate(0, -2));
            }
        }
    }
}

void Board::retrievePossibleKnightMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    addMove(result, coordinate, coordinate + Coordinate(-2, -1));
    addMove(result, coordinate, coordinate + Coordinate(-2, 1));
    addMove(result, coordinate, coordinate + Coordinate(-1, -2));
    addMove(result, coordinate, coordinate + Coordinate(-1, 2));
    addMove(result, coordinate, coordinate + Coordinate(1, -2));
    addMove(result, coordinate, coordinate + Coordinate(1, 2));
    addMove(result, coordinate, coordinate + Coordinate(2, -1));
    addMove(result, coordinate, coordinate + Coordinate(2, 1));
}

void Board::retrievePossibleBishopMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    retrievePossibleMovesByIncrements(result, coordinate, Coordinate(-1, -1));
    retrievePossibleMovesByIncrements(result, coordinate, Coordinate(-1, 1));
    retrievePossibleMovesByIncrements(result, coordinate, Coordinate(1, -1));
    retrievePossibleMovesByIncrements(result, coordinate, Coordinate(1, 1));
}

void Board::retrievePossibleRookMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    retrievePossibleMovesByIncrements(result, coordinate, Coordinate(0, -1));
    retrievePossibleMovesByIncrements(result, coordinate, Coordinate(0, 1));
    retrievePossibleMovesByIncrements(result, coordinate, Coordinate(-1, 0));
    retrievePossibleMovesByIncrements(result, coordinate, Coordinate(1, 0));
}

void Board::retrievePossibleQueenMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    retrievePossibleBishopMoves(result, coordinate);
    retrievePossibleRookMoves(result, coordinate);
}

void Board::retrievePossibleKingMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    addMove(result, coordinate, coordinate + Coordinate(-1, -1));
    addMove(result, coordinate, coordinate + Coordinate(-1, 0));
    addMove(result, coordinate, coordinate + Coordinate(-1, 1));
    addMove(result, coordinate, coordinate + Coordinate(0, -1));
    addMove(result, coordinate, coordinate + Coordinate(0, 1));
    addMove(result, coordinate, coordinate + Coordinate(1, -1));
    addMove(result, coordinate, coordinate + Coordinate(1, 0));
    addMove(result, coordinate, coordinate + Coordinate(1, 1));
}

void Board::retrievePossibleMovesByIncrements(
        Moves & result,
        Coordinate const& coordinate,
        Coordinate const& increment) const
{
    Coordinate newCoordinate(coordinate + increment);
    while(true)
    {
        if(!isCoordinateOnBoard(newCoordinate))
        {
            break;
        }
        else if(isEmpty(newCoordinate))
        {
            addMove(result, coordinate, newCoordinate);
        }
        else if(haveDifferentColors(coordinate, newCoordinate))
        {
            addMove(result, coordinate, newCoordinate);
            break;
        }
        else
        {
            break;
        }
        newCoordinate = newCoordinate + increment;
    }
}

bool Board::haveDifferentColors(
        Coordinate const& sourceCoordinate,
        Coordinate const& destinationCoordinate) const
{
    return getPieceAt(sourceCoordinate).getColor() != getPieceAt(destinationCoordinate).getColor();
}

void Board::addMove(Moves & moves,                    Coordinate const& sourceCoordinate,
                    Coordinate const& destinationCoordinate) const
{
    if(isCoordinateOnBoard(sourceCoordinate)            && isCoordinateOnBoard(destinationCoordinate))
    {
        if(isEmpty(destinationCoordinate) || haveDifferentColors(sourceCoordinate, destinationCoordinate))
        {
            moves.emplace_back(sourceCoordinate, destinationCoordinate);
        }
    }

}

Board::PieceMatrix::MatrixData Board::getInitialValues(
        Orientation const& inputType) const
{
    PieceMatrix::MatrixData result;
    if(Orientation::BlackUpWhiteDown == inputType)
    {
        result =        {12,10,11,14,13,11,10,12,
         9,9,9,9,9,9,9,9,
         0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,         0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,
         1,1,1,1,1,1,1,1,
         4,2,3,6,5,3,2,4};
    }
    else if(Orientation::WhiteUpBlackDown == inputType)
    {
        result =
        {4,2,3,6,5,3,2,4,
         1,1,1,1,1,1,1,1,
         0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,
         9,9,9,9,9,9,9,9,
         12,10,11,14,13,11,10,12};
    }
    return result;
}

}

}
