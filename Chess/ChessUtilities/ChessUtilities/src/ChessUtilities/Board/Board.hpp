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
    struct DeltaRange {
        CoordinateDataType interval;
        CoordinateDataType invalidDelta;
    };

    static constexpr unsigned int MAX_NUMBER_OF_MOVES = std::numeric_limits<unsigned int>::max();

    Board();
    Board(Orientation const& orientation);
    Board(Orientation const& orientation, InitializerList const& initializerList);

    bool operator==(Board const& other) const;
    bool operator!=(Board const& other) const;

    Orientation getOrientation() const;
    PieceMatrix const& getPieceMatrix() const;

    Moves getMovesFromThis(Coordinate const& startpoint) const;
    Moves getMovesToThis(
        Coordinate const& endpoint, PieceColor const& colorOfPieceToMove,
        unsigned int const maxSize = MAX_NUMBER_OF_MOVES) const;

    Move getMoveFromTwoLetterNumberNotation(std::string const& twoLetterNumber) const;
    Piece getPieceAt(Coordinate const& coordinate) const;
    Coordinate getCoordinateFromLetterNumberNotation(std::string const& letterNumber) const;

    std::string getLetterNumberNotationStringFromCoordinate(Coordinate const& coordinate) const;
    std::string getReadableStringForMove(Move const& move) const;
    std::string getNotationPartOfFenString() const;
    std::string getCastlingPartOfFenString() const;

    bool isEmptyAt(Coordinate const& coordinate) const;
    bool isACaptureMove(Move const& move) const;
    bool isAPromotionMove(Move const& move) const;
    bool isACastlingMove(Move const& move) const;
    bool isAPossibleMove(Move const& move) const;
    bool canBeCaptured(Coordinate const& endpoint) const;
    bool areThereAnyMovesToThis(Coordinate const& endpoint, PieceColor const& colorOfPieceToMove) const;
    bool hasOnlyOneMoveToThis(Coordinate const& endpoint, PieceColor const& colorOfPieceToMove) const;

    void setOrientation(Orientation const orientation);
    void setPieceAt(Coordinate const& coordinate, Piece const& piece);
    void move(Move const& move);

private:
    PieceMatrix::MatrixData getInitialValues(Orientation const& inputType) const;

    void retrieveMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrievePawnMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveKnightMovesThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveBishopMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveRookMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveQueenMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveKingMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrievePawnNonCapturesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrievePawnCapturesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveDiagonalMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveStraightMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveKingOneStepMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveKingCastlingMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveCastlingMovesFromThis(Moves& result, Coordinate const& startpoint) const;
    void retrieveMovesFromThisByIncrementingDelta(
        Moves& result, Coordinate const& startpoint, Coordinate const& delta) const;

    void retrieveMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove,
        unsigned int const maxSize) const;
    void retrievePawnReverseNonCapturesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove,
        unsigned int const maxSize) const;
    void retrievePawnReverseCapturesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove,
        unsigned int const maxSize) const;
    void retrieveKnightMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove,
        unsigned int const maxSize) const;
    void retrieveDiagonalMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove,
        unsigned int const maxSize) const;
    void retrieveStraightMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove,
        unsigned int const maxSize) const;
    void retrieveKingOneStepMovesToThis(
        Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove,
        unsigned int const maxSize) const;

    MovePairs getCastlingKingAndRookMovePairs(PieceColor const color) const;
    MovePair getMatchingCastlingKingAndRookMovePair(Move const& kingMoveThatShouldMatch) const;
    Coordinates getLDeltaCoordinates() const;
    Coordinates getDiagonalIncrementDeltaCoordinates() const;
    Coordinates getStraightIncrementDeltaCoordinates() const;
    Coordinates getOneStepDeltaCoordinates() const;
    DeltaRange getPawnNonCaptureDeltaRange(Coordinate const& startpoint, PieceColor const color) const;
    DeltaRange getPawnReverseNonCaptureDeltaRange(Coordinate const& endpoint, PieceColor const color) const;
    Coordinates getPawnCapturesDeltaCoordinates(PieceColor const color) const;
    Coordinates getPawnReverseCapturesDeltaCoordinates(PieceColor const color) const;
    CoordinateDataType getOneIncrementData(CoordinateDataType const coordinateDataType) const;

    bool isPossibleMoveBasedFromPieceType(Move const& move) const;
    bool isPossiblePawnMove(Move const& move) const;
    bool isPossibleKnightMove(Move const& move) const;
    bool isPossibleBishopMove(Move const& move) const;
    bool isPossibleRookMove(Move const& move) const;
    bool isPossibleQueenMove(Move const& move) const;
    bool isPossibleKingMove(Move const& move) const;
    bool isPossibleOneKingMove(Move const& move) const;
    bool isPossibleKingCastlingMove(Move const& kingMove) const;
    bool isAPawnNonCaptureMove(Move const& move) const;
    bool isAPawnCapture(Move const& move) const;
    bool isADiagonalMove(Move const& move) const;
    bool isAStraightMove(Move const& move) const;
    bool isAnLMove(Move const& move) const;
    bool isAOneStepMove(Move const& move) const;
    bool isCastlingValid(Move const& kingMove, Move const& rookMove) const;
    bool isEndpointEmptyOrHaveDifferentColors(Move const& move) const;
    bool isThereNoBlockingPieceInBetweenTheMove(Move const& move) const;

    void changePieceMatrixWithMove(Move const& move);

    Orientation m_orientation;
    PieceMatrix m_pieceMatrix;
};

}  // namespace chess

}  // namespace alba
