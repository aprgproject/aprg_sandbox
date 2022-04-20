#pragma once

#include <ChessUtilities/Board/BoardTypes.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <cstdint>
#include <string>

namespace alba
{

namespace chess
{

struct Board
{
public:
    enum class Orientation
    {
        BlackUpWhiteDown,
        WhiteUpBlackDown
    };
    using PieceValue = uint16_t;
    using InitializerList = std::initializer_list<PieceValue>;
    using PieceValueMatrix = matrix::AlbaMatrix<PieceValue>;

    Board(Orientation const& orientation);
    Board(Orientation const& orientation, InitializerList const& initializerList);

    bool isCoordinateOnBoard(Coordinate const& coordinate) const;
    bool isEmpty(Coordinate const& coordinate) const;
    bool isMovePossible(Move const& move) const;
    bool isPromotionMove(Move const& move) const;

    PieceValueMatrix const& getPieceValueMatrix() const;
    PieceValue getPieceValue(Coordinate const& coordinate) const;
    char getPieceCharacter(Coordinate const& coordinate) const;
    Moves getPossibleMoves(Coordinate const& coordinate) const;
    std::string getFenString() const;

private:
    void retrievePossibleMovesBaseFromPieceType(Moves & result, Coordinate const& coordinate) const;
    void retrievePossiblePawnMoves(Moves & result, Coordinate const& coordinate) const;
    void retrievePossibleKnightMoves(Moves & result, Coordinate const& coordinate) const;
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
    InitializerList getInitializerList(Orientation const& inputType) const;

    Orientation m_orientation;
    PieceValueMatrix m_pieceValueMatrix;
};

}

}
