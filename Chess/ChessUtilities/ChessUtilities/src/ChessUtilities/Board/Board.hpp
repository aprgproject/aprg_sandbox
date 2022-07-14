#pragma once

#include <ChessUtilities/Board/BoardTypes.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <cstdint>
#include <string>

namespace alba
{

namespace matrix
{
template <> bool isEqualForMathMatrixDataType(chess::Piece const& value1, chess::Piece const& value2);
}

namespace chess
{

struct Board
{
public:
    enum class Orientation
    {
        Unknown,
        BlackUpWhiteDown,
        WhiteUpBlackDown
    };
    using PieceValue = uint16_t;
    using InitializerList = std::initializer_list<Piece>;
    using PieceMatrix = matrix::AlbaMatrix<Piece>;

    Board();
    Board(Orientation const& orientation);
    Board(Orientation const& orientation, InitializerList const& initializerList);

    bool isCoordinateOnBoard(Coordinate const& coordinate) const;
    bool isEmpty(Coordinate const& coordinate) const;
    bool isMovePossible(Move const& move) const;
    bool isPromotionMove(Move const& move) const;

    Orientation getOrientation() const;
    PieceMatrix const& getPieceMatrix() const;
    Piece getPieceAt(Coordinate const& coordinate) const;
    Coordinate getCoordinateFromLetterNumberNotation(std::string const& letterNumber) const;
    Move getMoveFromTwoLetterNumberNotation(std::string const& twoLetterNumber) const;
    Moves getPossibleMoves(Coordinate const& coordinate) const;
    std::string getFenString() const;
    std::string getCastlingFenString() const;

    void setOrientation(Orientation const orientation);
    void setPieceAt(Coordinate const& coordinate, Piece const& piece);
private:
    void retrievePossibleMovesBaseFromPieceType(Moves & result, Coordinate const& coordinate) const;
    void retrievePossiblePawnMoves(Moves & result, Coordinate const& coordinate) const;    void retrievePossibleKnightMoves(Moves & result, Coordinate const& coordinate) const;
    void retrievePossibleBishopMoves(Moves & result, Coordinate const& coordinate) const;
    void retrievePossibleRookMoves(Moves & result, Coordinate const& coordinate) const;
    void retrievePossibleQueenMoves(Moves & result, Coordinate const& coordinate) const;
    void retrievePossibleKingMoves(Moves & result, Coordinate const& coordinate) const;
    void retrievePossibleMovesByIncrements(
            Moves & result,
            Coordinate const& coordinate,
            Coordinate const& increment) const;

    bool haveDifferentColors(
            Coordinate const& sourceCoordinate,
            Coordinate const& destinationCoordinate) const;
    void addMove(Moves & moves, Coordinate const& coordinate1, Coordinate const& coordinate2) const;
    PieceMatrix::MatrixData getInitialValues(Orientation const& inputType) const;

    Orientation m_orientation;
    PieceMatrix m_pieceMatrix;
};

}

}
