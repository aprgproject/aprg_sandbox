#include "Board.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Container/AlbaValueRange.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <sstream>

using namespace alba::stringHelper;
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

bool Board::isCoordinateOnBoard(Coordinate const& coordinate) const
{
    auto x(coordinate.getX());
    auto y(coordinate.getY());
    return (x>=0 && x<=7) && (y>=0 && y<=7);
}

bool Board::isEmptyAt(Coordinate const& coordinate) const
{
    return getPieceAt(coordinate).isEmpty();
}

bool Board::canBeCaptured(Coordinate const& coordinate) const
{
    Piece piece(getPieceAt(coordinate));
    PieceColor oppositeColor(getOppositeColor(piece.getColor()));
    return canBeDiagonalCaptured(coordinate, oppositeColor)
            || canBeStraightCaptured(coordinate, oppositeColor)
            || canBeKnightCaptured(coordinate, oppositeColor)
            || canBePawnCaptured(coordinate, oppositeColor)
            || canBeKingCaptured(coordinate, oppositeColor);
}

bool Board::isMovePossible(Move const& move) const
{
    Moves moves(getPossibleMoves(move.first));
    auto it = find(moves.cbegin(), moves.cend(), move);
    return it != moves.cend();
}

bool Board::isPromotionMove(Move const& move) const
{
    return PieceType::Pawn == getPieceAt(move.first).getType()
            && (move.second.getY() == 0 || move.second.getY() == 7)
            && isMovePossible(move);
}

bool Board::isCastlingMove(Move const& move) const
{
    Move savedRookMove;
    return isCastlingMove(move, savedRookMove);
}

Board::Orientation Board::getOrientation() const
{
    return m_orientation;
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

Coordinate Board::getCoordinateFromLetterNumberNotation(std::string const& letterNumber) const
{
    Coordinate result{};
    if(letterNumber.size() == 2)
    {
        char letter = tolower(letterNumber.at(0));
        char number = letterNumber.at(1);
        if(isLetter(letter) && isNumber(number) && 'a' <= letter && letter <= 'h' && '1' <= number && number <= '8')
        {
            unsigned int numberValue = number-'0';
            if(Orientation::BlackUpWhiteDown == m_orientation)
            {
                result = Coordinate(letter-'a', 8U-numberValue);
            }
            else if(Orientation::WhiteUpBlackDown == m_orientation)
            {
                result = Coordinate(7-(letter-'a'), numberValue-1);
            }
        }
    }
    return result;
}

Move Board::getMoveFromTwoLetterNumberNotation(std::string const& twoLetterNumber) const
{
    Move result{};
    if(twoLetterNumber.size() == 4 || twoLetterNumber.size() == 5) // 5 is for promotion
    {
        result = {getCoordinateFromLetterNumberNotation(twoLetterNumber.substr(0, 2)), getCoordinateFromLetterNumberNotation(twoLetterNumber.substr(2, 2))};
    }
    return result;
}

Moves Board::getPossibleMoves(Coordinate const& coordinate) const
{
    Moves result;
    retrievePossibleMovesBaseFromPieceType(result, coordinate);
    return result;
}

std::string Board::getFenString() const
{
    string result;
    CoordinateDataType start=0, end=7;
    if(Orientation::WhiteUpBlackDown == m_orientation)
    {
        start=7;
        end=0;
    }
    AlbaValueRange<CoordinateDataType> rankRange(start, end, 1);
    rankRange.traverse([&](CoordinateDataType const rank)
    {
        unsigned int emptyCellsInRank = 0;
        stringstream ssFenInRank;
        AlbaValueRange<CoordinateDataType> fileRange(start, end, 1);
        fileRange.traverse([&](CoordinateDataType const file)
        {
            Coordinate coordinate(file, rank);
            Piece piece(getPieceAt(coordinate));
            if(piece.isEmpty())
            {
                emptyCellsInRank++;
            }
            else
            {
                if(emptyCellsInRank != 0)
                {
                    ssFenInRank << emptyCellsInRank;
                }
                ssFenInRank << piece.getCharacter();
                emptyCellsInRank = 0;
            }
        });
        if (emptyCellsInRank != 0)
        {
            ssFenInRank << emptyCellsInRank;
        }
        result += ssFenInRank.str();
        if(rank != end)
        {
            result += "/";
        }

    });
    return result;
}

string Board::getCastlingFenString() const
{
    string result;
    if(Board::Orientation::BlackUpWhiteDown == m_orientation)
    {
        Piece pieceAtWhiteKing(getPieceAt(Coordinate(4, 7)));
        Piece pieceAtWhiteRookOnKingSide(getPieceAt(Coordinate(7, 7)));
        Piece pieceAtWhiteRookOnQueenSide(getPieceAt(Coordinate(0, 7)));
        Piece pieceAtBlackKing(getPieceAt(Coordinate(4, 0)));
        Piece pieceAtBlackRookOnKingSide(getPieceAt(Coordinate(7, 0)));
        Piece pieceAtBlackRookOnQueenSide(getPieceAt(Coordinate(0, 0)));
        if(PieceType::King == pieceAtWhiteKing.getType() && PieceColor::White == pieceAtWhiteKing.getColor()
                && PieceType::Rook == pieceAtWhiteRookOnKingSide.getType() && PieceColor::White == pieceAtWhiteRookOnKingSide.getColor())
        {
            result += "K";
        }
        if(PieceType::King == pieceAtWhiteKing.getType() && PieceColor::White == pieceAtWhiteKing.getColor()
                && PieceType::Rook == pieceAtWhiteRookOnQueenSide.getType() && PieceColor::White == pieceAtWhiteRookOnQueenSide.getColor())
        {
            result += "Q";
        }
        if(PieceType::King == pieceAtBlackKing.getType() && PieceColor::Black == pieceAtBlackKing.getColor()
                && PieceType::Rook == pieceAtBlackRookOnKingSide.getType() && PieceColor::Black == pieceAtBlackRookOnKingSide.getColor())
        {
            result += "k";
        }
        if(PieceType::King == pieceAtBlackKing.getType() && PieceColor::Black == pieceAtBlackKing.getColor()
                && PieceType::Rook == pieceAtBlackRookOnQueenSide.getType() && PieceColor::Black == pieceAtBlackRookOnQueenSide.getColor())
        {
            result += "q";
        }
    }
    else if(Board::Orientation::WhiteUpBlackDown == m_orientation)
    {
        Piece pieceAtWhiteKing(getPieceAt(Coordinate(3, 0)));
        Piece pieceAtWhiteRookOnKingSide(getPieceAt(Coordinate(0, 0)));
        Piece pieceAtWhiteRookOnQueenSide(getPieceAt(Coordinate(7, 0)));
        Piece pieceAtBlackKing(getPieceAt(Coordinate(3, 7)));
        Piece pieceAtBlackRookOnKingSide(getPieceAt(Coordinate(0, 7)));
        Piece pieceAtBlackRookOnQueenSide(getPieceAt(Coordinate(7, 7)));
        if(PieceType::King == pieceAtWhiteKing.getType() && PieceColor::White == pieceAtWhiteKing.getColor()
                && PieceType::Rook == pieceAtWhiteRookOnKingSide.getType() && PieceColor::White == pieceAtWhiteRookOnKingSide.getColor())
        {
            result += "K";
        }
        if(PieceType::King == pieceAtWhiteKing.getType() && PieceColor::White == pieceAtWhiteKing.getColor()
                && PieceType::Rook == pieceAtWhiteRookOnQueenSide.getType() && PieceColor::White == pieceAtWhiteRookOnQueenSide.getColor())
        {
            result += "Q";
        }
        if(PieceType::King == pieceAtBlackKing.getType() && PieceColor::Black == pieceAtBlackKing.getColor()
                && PieceType::Rook == pieceAtBlackRookOnKingSide.getType() && PieceColor::Black == pieceAtBlackRookOnKingSide.getColor())
        {
            result += "k";
        }
        if(PieceType::King == pieceAtBlackKing.getType() && PieceColor::Black == pieceAtBlackKing.getColor()
                && PieceType::Rook == pieceAtBlackRookOnQueenSide.getType() && PieceColor::Black == pieceAtBlackRookOnQueenSide.getColor())
        {
            result += "q";
        }
    }
    if(result.empty())
    {
        result = "-";
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
        m_pieceMatrix.setEntry(coordinate.getX(), coordinate.getY(), piece);
    }
}

void Board::move(Move const& move)
{
    if(isMovePossible(move))
    {
        Move savedRookMove;
        if(isCastlingMove(move, savedRookMove))
        {
            changePieceMatrixWithMove(move);
            changePieceMatrixWithMove(savedRookMove);
        }
        else
        {
            changePieceMatrixWithMove(move);
        }
    }
}

bool Board::canBeDiagonalCaptured(Coordinate const& coordinate, PieceColor const oppositeColor) const
{
    bool result(false);
    for(Coordinate const& deltaCoordinate : getDiagonalIncrementDeltaCoordinates())
    {
        Coordinate runningCoordinate = coordinate + deltaCoordinate;
        while(isCoordinateOnBoard(runningCoordinate))
        {
            Piece piece(getPieceAt(runningCoordinate));
            if(!piece.isEmpty())
            {
                if(oppositeColor == piece.getColor()
                        && (PieceType::Bishop == piece.getType() || PieceType::Queen == piece.getType()))
                {
                    result = true;
                }
                break;
            }
            runningCoordinate += deltaCoordinate;
        }
        if(result)
        {
            break;
        }
    }
    return result;
}

bool Board::canBeStraightCaptured(Coordinate const& coordinate, PieceColor const oppositeColor) const
{
    bool result(false);
    for(Coordinate const& deltaCoordinate : getStraightIncrementDeltaCoordinates())
    {
        Coordinate runningCoordinate = coordinate + deltaCoordinate;
        while(isCoordinateOnBoard(runningCoordinate))
        {
            Piece piece(getPieceAt(runningCoordinate));
            if(!piece.isEmpty())
            {
                if(oppositeColor == piece.getColor()
                        && (PieceType::Rook == piece.getType() || PieceType::Queen == piece.getType()))
                {
                    result = true;
                }
                break;
            }
            runningCoordinate += deltaCoordinate;
        }
        if(result)
        {
            break;
        }
    }
    return result;
}

bool Board::canBeKnightCaptured(Coordinate const& coordinate, PieceColor const oppositeColor) const
{
    bool result(false);
    for(Coordinate const& deltaCoordinate : getLDeltaCoordinates())
    {
        Piece piece(getPieceAt(coordinate + deltaCoordinate));
        if(oppositeColor == piece.getColor() && PieceType::Knight == piece.getType())
        {
            result = true;
            break;
        }
    }
    return result;
}

bool Board::canBePawnCaptured(Coordinate const& coordinate, PieceColor const oppositeColor) const
{
    bool result(false);
    if(Board::Orientation::BlackUpWhiteDown == m_orientation)
    {
        if(PieceColor::White == oppositeColor)
        {
            Piece piece1(getPieceAt(coordinate + Coordinate(-1, 1)));
            Piece piece2(getPieceAt(coordinate + Coordinate(1, 1)));
            return (oppositeColor == piece1.getColor() && PieceType::Pawn == piece1.getType())
                    || (oppositeColor == piece2.getColor() && PieceType::Pawn == piece2.getType());
        }
        else if(PieceColor::Black == oppositeColor)
        {
            Piece piece1(getPieceAt(coordinate + Coordinate(-1, -1)));
            Piece piece2(getPieceAt(coordinate + Coordinate(1, -1)));
            return (oppositeColor == piece1.getColor() && PieceType::Pawn == piece1.getType())
                    || (oppositeColor == piece2.getColor() && PieceType::Pawn == piece2.getType());
        }
    }
    else if(Board::Orientation::WhiteUpBlackDown == m_orientation)
    {
        if(PieceColor::White == oppositeColor)
        {
            Piece piece1(getPieceAt(coordinate + Coordinate(-1, -1)));
            Piece piece2(getPieceAt(coordinate + Coordinate(1, -1)));
            return (oppositeColor == piece1.getColor() && PieceType::Pawn == piece1.getType())
                    || (oppositeColor == piece2.getColor() && PieceType::Pawn == piece2.getType());
        }
        else if(PieceColor::Black == oppositeColor)
        {
            Piece piece1(getPieceAt(coordinate + Coordinate(-1, 1)));
            Piece piece2(getPieceAt(coordinate + Coordinate(1, 1)));
            return (oppositeColor == piece1.getColor() && PieceType::Pawn == piece1.getType())
                    || (oppositeColor == piece2.getColor() && PieceType::Pawn == piece2.getType());
        }
    }
    return result;
}

bool Board::canBeKingCaptured(Coordinate const& coordinate, PieceColor const oppositeColor) const
{
    bool result(false);
    for(Coordinate const& deltaCoordinate : getOneStepDeltaCoordinates())
    {
        Piece piece(getPieceAt(coordinate + deltaCoordinate));
        if(oppositeColor == piece.getColor() && PieceType::King == piece.getType())
        {
            result = true;
            break;
        }
    }
    return result;
}

bool Board::isCastlingMove(Move const& move, Move & savedRookMove) const
{
    bool result(false);
    Piece pieceAtKing(getPieceAt(move.first));
    if(PieceType::King == pieceAtKing.getType())
    {
        if(Board::Orientation::BlackUpWhiteDown == m_orientation)
        {
            if(Coordinate(4, 0) == move.first && PieceColor::Black == pieceAtKing.getColor()) // black king
            {
                if(Coordinate(2, 0) == move.second) // queen side castle
                {
                    Piece pieceAtRook(getPieceAt(Coordinate(0, 0)));
                    savedRookMove = {Coordinate(0, 0), Coordinate(3, 0)};
                    result = PieceType::Rook == pieceAtRook.getType() && PieceColor::Black == pieceAtRook.getColor();
                }
                else if(Coordinate(6, 0) == move.second) // king side castle
                {
                    Piece pieceAtRook(getPieceAt(Coordinate(7, 0)));
                    savedRookMove = {Coordinate(7, 0), Coordinate(5, 0)};
                    result = PieceType::Rook == pieceAtRook.getType() && PieceColor::Black == pieceAtRook.getColor();
                }
            }
            else if(Coordinate(4, 7) == move.first && PieceColor::White == pieceAtKing.getColor()) //white king
            {
                if(Coordinate(2, 7) == move.second) // queen side castle
                {
                    Piece pieceAtRook(getPieceAt(Coordinate(0, 7)));
                    savedRookMove = {Coordinate(0, 7), Coordinate(3, 7)};
                    result = PieceType::Rook == pieceAtRook.getType() && PieceColor::White == pieceAtRook.getColor();
                }
                else if(Coordinate(6, 7) == move.second) // king side castle
                {
                    Piece pieceAtRook(getPieceAt(Coordinate(7, 7)));
                    savedRookMove = {Coordinate(0, 7), Coordinate(5, 7)};
                    result = PieceType::Rook == pieceAtRook.getType() && PieceColor::White == pieceAtRook.getColor();
                }
            }
        }
        else if(Board::Orientation::WhiteUpBlackDown == m_orientation)
        {
            if(Coordinate(3, 0) == move.first && PieceColor::White == pieceAtKing.getColor()) // white king
            {
                if(Coordinate(1, 0) == move.second) // king side castle
                {
                    Piece pieceAtRook(getPieceAt(Coordinate(0, 0)));
                    savedRookMove = {Coordinate(0, 0), Coordinate(2, 0)};
                    result = PieceType::Rook == pieceAtRook.getType() && PieceColor::White == pieceAtRook.getColor();
                }
                else if(Coordinate(5, 0) == move.second) // queen side castle
                {
                    Piece pieceAtRook(getPieceAt(Coordinate(7, 0)));
                    savedRookMove = {Coordinate(7, 0), Coordinate(4, 0)};
                    result = PieceType::Rook == pieceAtRook.getType() && PieceColor::White == pieceAtRook.getColor();
                }
            }
            else if(Coordinate(3, 7) == move.first && PieceColor::Black == pieceAtKing.getColor()) //black king
            {
                if(Coordinate(1, 7) == move.second) // king side castle
                {
                    Piece pieceAtRook(getPieceAt(Coordinate(0, 7)));
                    savedRookMove = {Coordinate(0, 7), Coordinate(2, 7)};
                    result = PieceType::Rook == pieceAtRook.getType() && PieceColor::Black == pieceAtRook.getColor();
                }
                else if(Coordinate(5, 7) == move.second) // queen side castle
                {
                    Piece pieceAtRook(getPieceAt(Coordinate(7, 7)));
                    savedRookMove = {Coordinate(7, 7), Coordinate(4, 7)};
                    result = PieceType::Rook == pieceAtRook.getType() && PieceColor::Black == pieceAtRook.getColor();
                }
            }
        }
    }
    return result;
}

Coordinates Board::getLDeltaCoordinates() const
{
    return Coordinates{{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
}

Coordinates Board::getDiagonalIncrementDeltaCoordinates() const
{
    return Coordinates{{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
}

Coordinates Board::getStraightIncrementDeltaCoordinates() const
{
    return Coordinates{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
}

Coordinates Board::getOneStepDeltaCoordinates() const
{
    return Coordinates{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
}

void Board::retrievePossibleMovesBaseFromPieceType(
        Moves & result,
        Coordinate const& coordinate) const
{
    Piece piece(getPieceAt(coordinate));
    PieceType pieceType = piece.getType();
    switch(pieceType)
    {
    case PieceType::Pawn:
    {
        retrievePossiblePawnMoves(result, coordinate);
        break;
    }
    case PieceType::Knight:
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
        {
            addMoveToListOfMoves(result, coordinate, coordinate + Coordinate(0, -1));
            if(6 == coordinate.getY())
            {
                addMoveToListOfMoves(result, coordinate, coordinate + Coordinate(0, -2));
            }
        }
        else if(Orientation::WhiteUpBlackDown == m_orientation)
        {
            addMoveToListOfMoves(result, coordinate, coordinate + Coordinate(0, 1));
            if(1 == coordinate.getY())
            {
                addMoveToListOfMoves(result, coordinate, coordinate + Coordinate(0, 2));
            }
        }
    }
    else if(PieceColor::Black == piece.getColor())
    {
        if(Orientation::BlackUpWhiteDown == m_orientation)
        {
            addMoveToListOfMoves(result, coordinate, coordinate + Coordinate(0, 1));
            if(1 == coordinate.getY())
            {
                addMoveToListOfMoves(result, coordinate, coordinate + Coordinate(0, 2));
            }
        }
        else if(Orientation::WhiteUpBlackDown == m_orientation)
        {
            addMoveToListOfMoves(result, coordinate, coordinate + Coordinate(0, -1));
            if(6 == coordinate.getY())
            {
                addMoveToListOfMoves(result, coordinate, coordinate + Coordinate(0, -2));
            }
        }
    }
}

void Board::retrievePossibleKnightMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    Coordinates lDeltaCoordinates(getLDeltaCoordinates());
    for(Coordinate const& deltaCoordinate : lDeltaCoordinates)
    {
        addMoveToListOfMoves(result, coordinate, coordinate + deltaCoordinate);
    }
}

void Board::retrievePossibleBishopMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    Coordinates diagonalIncrementDeltaCoordinates(getDiagonalIncrementDeltaCoordinates());
    for(Coordinate const& deltaCoordinate : diagonalIncrementDeltaCoordinates)
    {
        retrievePossibleMovesByIncrements(result, coordinate, deltaCoordinate);
    }
}

void Board::retrievePossibleRookMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    Coordinates straightlIncrementDeltaCoordinates(getStraightIncrementDeltaCoordinates());
    for(Coordinate const& deltaCoordinate : straightlIncrementDeltaCoordinates)
    {
        retrievePossibleMovesByIncrements(result, coordinate, deltaCoordinate);
    }
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
    Coordinates oneStepDeltaCoordinates(getOneStepDeltaCoordinates());
    for(Coordinate const& deltaCoordinate : oneStepDeltaCoordinates)
    {
        addMoveToListOfMoves(result, coordinate, coordinate + deltaCoordinate);
    }
    retrievePossibleKingCastlingMoves(result, coordinate);
}

void Board::retrievePossibleKingCastlingMoves(
        Moves & result,
        Coordinate const& coordinate) const
{
    Piece pieceAtKing(getPieceAt(coordinate));
    if(Board::Orientation::BlackUpWhiteDown == m_orientation)
    {
        if(Coordinate(4, 0) == coordinate && PieceColor::Black == pieceAtKing.getColor()) // black king
        {
            Piece pieceAtRookOnQueenSide(getPieceAt(Coordinate(0, 0)));
            Piece pieceAtRookOnKingSide(getPieceAt(Coordinate(7, 0)));
            if(PieceType::Rook == pieceAtRookOnQueenSide.getType() && PieceColor::Black == pieceAtRookOnQueenSide.getColor())
            {
                addMoveToListOfMoves(result, Coordinate(4, 0), Coordinate(2, 0)); // queen side castle
            }
            else if(PieceType::Rook == pieceAtRookOnKingSide.getType() && PieceColor::Black == pieceAtRookOnKingSide.getColor())
            {
                addMoveToListOfMoves(result, Coordinate(4, 0), Coordinate(6, 0));  // king side castle
            }
        }
        else if(Coordinate(4, 7) == coordinate && PieceColor::White == pieceAtKing.getColor()) //white king
        {
            Piece pieceAtRookOnQueenSide(getPieceAt(Coordinate(0, 7)));
            Piece pieceAtRookOnKingSide(getPieceAt(Coordinate(7, 7)));
            if(PieceType::Rook == pieceAtRookOnQueenSide.getType() && PieceColor::White == pieceAtRookOnQueenSide.getColor())
            {
                addMoveToListOfMoves(result, Coordinate(4, 7), Coordinate(2, 7)); // queen side castle
            }
            else if(PieceType::Rook == pieceAtRookOnKingSide.getType() && PieceColor::White == pieceAtRookOnKingSide.getColor())
            {
                addMoveToListOfMoves(result, Coordinate(4, 7), Coordinate(6, 7));  // king side castle
            }
        }
    }
    else if(Board::Orientation::WhiteUpBlackDown == m_orientation)
    {
        if(Coordinate(3, 0) == coordinate && PieceColor::White == pieceAtKing.getColor()) // white king
        {
            Piece pieceAtRookOnQueenSide(getPieceAt(Coordinate(0, 0)));
            Piece pieceAtRookOnKingSide(getPieceAt(Coordinate(7, 0)));
            if(PieceType::Rook == pieceAtRookOnQueenSide.getType() && PieceColor::White == pieceAtRookOnQueenSide.getColor())
            {
                addMoveToListOfMoves(result, Coordinate(3, 0), Coordinate(1, 0)); // queen side castle
            }
            else if(PieceType::Rook == pieceAtRookOnKingSide.getType() && PieceColor::White == pieceAtRookOnKingSide.getColor())
            {
                addMoveToListOfMoves(result, Coordinate(3, 0), Coordinate(5, 0));  // king side castle
            }
        }
        else if(Coordinate(3, 7) == coordinate && PieceColor::Black == pieceAtKing.getColor()) //black king
        {
            Piece pieceAtRookOnQueenSide(getPieceAt(Coordinate(0, 7)));
            Piece pieceAtRookOnKingSide(getPieceAt(Coordinate(7, 7)));
            if(PieceType::Rook == pieceAtRookOnQueenSide.getType() && PieceColor::Black == pieceAtRookOnQueenSide.getColor())
            {
                addMoveToListOfMoves(result, Coordinate(3, 7), Coordinate(1, 7)); // queen side castle
            }
            else if(PieceType::Rook == pieceAtRookOnKingSide.getType() && PieceColor::Black == pieceAtRookOnKingSide.getColor())
            {
                addMoveToListOfMoves(result, Coordinate(3, 7), Coordinate(5, 7));  // king side castle
            }
        }
    }
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
        else if(isEmptyAt(newCoordinate))
        {
            addMoveToListOfMoves(result, coordinate, newCoordinate);
        }
        else if(haveDifferentColors(coordinate, newCoordinate))
        {
            addMoveToListOfMoves(result, coordinate, newCoordinate);
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

void Board::addMoveToListOfMoves(Moves & moves,
                    Coordinate const& sourceCoordinate,
                    Coordinate const& destinationCoordinate) const
{
    if(isCoordinateOnBoard(sourceCoordinate)
            && isCoordinateOnBoard(destinationCoordinate))
    {
        if(isEmptyAt(destinationCoordinate) || haveDifferentColors(sourceCoordinate, destinationCoordinate))
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
        result =
        {12,10,11,13,14,11,10,12,
         9,9,9,9,9,9,9,9,
         0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,
         1,1,1,1,1,1,1,1,
         4,2,3,5,6,3,2,4};
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

void Board::changePieceMatrixWithMove(Move const& move)
{
    m_pieceMatrix.setEntry(move.second.getX(), move.second.getY(), m_pieceMatrix.getEntry(move.first.getX(), move.first.getY()));
    m_pieceMatrix.setEntry(move.first.getX(), move.first.getY(), Piece());
}

}

}
