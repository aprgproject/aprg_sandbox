#pragma once

#include <ChessUtilities/Board/BoardTypes.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <cstdint>
#include <string>

namespace alba {

namespace matrix {
template <>
bool isEqualForMathMatrixDataType(chess::Piece const& value1, chess::Piece const& value2);
}

namespace chess {

struct Board {
public:
    enum class Orientation { Unknown, BlackUpWhiteDown, WhiteUpBlackDown };
    using PieceValue = uint16_t;
    using InitializerList = std::initializer_list<Piece>;
    using PieceMatrix = matrix::AlbaMatrix<Piece>;

    Board();
    Board(Orientation const& orientation);
    Board(Orientation const& orientation, InitializerList const& initializerList);

    bool isEmptyAt(Coordinate const& coordinate) const;
    bool isPossibleMove(Move const& move) const;
    bool isAMovePossibleToThisDestination(Coordinate const& destination, PieceColor const& color) const;
    bool hasOnlyOneMovePossibleToThisDestination(Coordinate const& destination, PieceColor const& color) const;
    bool canBeCaptured(Coordinate const& destination) const;
    bool isPromotionMove(Move const& move) const;
    bool isCastlingMove(Move const& move) const;

    Orientation getOrientation() const;
    PieceMatrix const& getPieceMatrix() const;
    Piece getPieceAt(Coordinate const& coordinate) const;
    Coordinate getCoordinateFromLetterNumberNotation(std::string const& letterNumber) const;
    Move getMoveFromTwoLetterNumberNotation(std::string const& twoLetterNumber) const;
    Moves getPossibleMoves(Coordinate const& start) const;
    std::string getFenString() const;
    std::string getCastlingFenString() const;

    void setOrientation(Orientation const orientation);
    void setPieceAt(Coordinate const& coordinate, Piece const& piece);
    void move(Move const& move);

private:
    bool isEndEmptyOrHaveDifferentColors(Move const& move) const;
    bool isPossibleMoveBasedFromPieceType(Move const& move) const;
    bool isPossiblePawnMove(Move const& move) const;
    bool isPossibleKnightMove(Move const& move) const;
    bool isPossibleBishopMove(Move const& move) const;
    bool isPossibleRookMove(Move const& move) const;
    bool isPossibleQueenMove(Move const& move) const;
    bool isPossibleKingMove(Move const& move) const;
    bool isPossibleOneKingMove(Move const& move) const;
    bool isPossibleKingCastlingMove(Move const& kingMove) const;
    bool isAPawnMove(Move const& move) const;
    bool isAPawnCapture(Move const& move) const;
    bool isADiagonalMove(Move const& move) const;
    bool isAStraightMove(Move const& move) const;
    bool isAnLMove(Move const& move) const;
    bool isAOneStepMove(Move const& move) const;
    bool doesMoveHasNoBlockingPieceInBetween(Move const& move) const;
    unsigned int getDiagonalMovesPossibleToThisDestination(
        Coordinate const& destination, PieceColor const oppositeColor, unsigned int const maximumCount) const;
    unsigned int getStraightMovesPossibleToThisDestination(
        Coordinate const& destination, PieceColor const oppositeColor, unsigned int const maximumCount) const;
    unsigned int getKnightMovesPossibleToThisDestination(
        Coordinate const& destination, PieceColor const oppositeColor, unsigned int const maximumCount) const;
    unsigned int getKingMovesPossibleToThisDestination(
        Coordinate const& destination, PieceColor const oppositeColor, unsigned int const maximumCount) const;
    unsigned int getPawnReverseMovesPossibleToThisDestination(
        Coordinate const& destination, PieceColor const color, unsigned int const maximumCount) const;
    unsigned int getPawnReverseCapturesPossibleToThisDestination(
        Coordinate const& destination, PieceColor const color, unsigned int const maximumCount) const;
    CoordinateDataType getOneIncrementData(CoordinateDataType const coordinateDataType) const;
    Coordinates getLDeltaCoordinates() const;
    Coordinates getDiagonalIncrementDeltaCoordinates() const;
    Coordinates getStraightIncrementDeltaCoordinates() const;
    Coordinates getOneStepDeltaCoordinates() const;
    Coordinates getPossiblePawnMovesDeltaCoordinates(Coordinate const& start, PieceColor const color) const;
    Coordinates getPossiblePawnReverseMovesDeltaCoordinates(Coordinate const& end, PieceColor const color) const;
    Coordinates getPossiblePawnCapturesDeltaCoordinates(PieceColor const color) const;
    Coordinates getPossiblePawnReverseCapturesDeltaCoordinates(PieceColor const color) const;
    MovePairs getPossibleCastlingKingAndRookMovePairs(PieceColor const color) const;
    MovePair getMatchingCastlingKingAndRookMovePair(Move const& kingMoveThatShouldMatch) const;
    void retrievePossibleMovesBasedFromPieceType(Moves& result, Coordinate const& start) const;
    void retrievePossiblePawnMoves(Moves& result, Coordinate const& start) const;
    void retrievePossibleKnightMoves(Moves& result, Coordinate const& start) const;
    void retrievePossibleBishopMoves(Moves& result, Coordinate const& start) const;
    void retrievePossibleRookMoves(Moves& result, Coordinate const& start) const;
    void retrievePossibleQueenMoves(Moves& result, Coordinate const& start) const;
    void retrievePossibleKingMoves(Moves& result, Coordinate const& start) const;
    void retrievePossibleOneKingMoves(Moves& result, Coordinate const& start) const;
    void retrievePossibleKingCastlingMoves(Moves& result, Coordinate const& start) const;
    void retrievePossibleCastlingMoves(MovePairs& kingAndRookMoves, PieceColor const color) const;
    void retrievePossibleMovesByIncrements(Moves& result, Coordinate const& source, Coordinate const& increment) const;
    void addMoveToListOfMoves(Moves& moves, Move const& move) const;

    PieceMatrix::MatrixData getInitialValues(Orientation const& inputType) const;
    void changePieceMatrixWithMove(Move const& move);

    Orientation m_orientation;
    PieceMatrix m_pieceMatrix;
};

}  // namespace chess

}  // namespace alba
