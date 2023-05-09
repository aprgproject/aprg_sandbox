#include "Board.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Debug/AlbaDebug.hpp>  // for debugging
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <functional>
#include <sstream>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace matrix {
template <>
bool isEqualForMathMatrixDataType(chess::Piece const& value1, chess::Piece const& value2) {
    return value1 == value2;
}
}  // namespace matrix

namespace chess {

Board::Board() : m_orientation(Orientation::Unknown), m_pieceMatrix(8U, 8U) {}

Board::Board(Orientation const& orientation)
    : m_orientation(orientation), m_pieceMatrix(8U, 8U, getInitialValues(orientation)) {}

Board::Board(Orientation const& orientation, InitializerList const& initializerList)
    : m_orientation(orientation), m_pieceMatrix(8U, 8U, initializerList) {}

bool Board::operator==(Board const& other) const {
    return m_orientation == other.m_orientation && m_pieceMatrix == other.m_pieceMatrix;
}

bool Board::operator!=(Board const& other) const { return !operator==(other); }

Board::Orientation Board::getOrientation() const { return m_orientation; }

Board::PieceMatrix const& Board::getPieceMatrix() const { return m_pieceMatrix; }

Moves Board::getMovesFromThis(Coordinate const& startpoint) const {
    Moves result;
    retrieveMovesFromThis(result, startpoint);
    return result;
}

Moves Board::getMovesToThis(
    Coordinate const& endpoint, PieceColor const& colorOfPieceToMove, unsigned int const maxSize) const {
    Moves result;
    retrieveMovesToThis(result, endpoint, colorOfPieceToMove, maxSize);
    return result;
}

Move Board::getMoveFromTwoLetterNumberNotation(string const& twoLetterNumber) const {
    Move result{};
    if (twoLetterNumber.size() == 4 || twoLetterNumber.size() == 5)  // 5 is for promotion
    {
        result = {
            getCoordinateFromLetterNumberNotation(twoLetterNumber.substr(0, 2)),
            getCoordinateFromLetterNumberNotation(twoLetterNumber.substr(2, 2))};
    }
    return result;
}

Piece Board::getPieceAt(Coordinate const& coordinate) const {
    Piece result;
    if ((isCoordinateWithinTheBoard(coordinate))) {
        result = m_pieceMatrix.getEntry(coordinate.getX(), coordinate.getY());
    }
    return result;
}

Coordinate Board::getCoordinateFromLetterNumberNotation(string const& letterNumber) const {
    Coordinate result{};
    if (letterNumber.size() == 2) {
        char letter = tolower(letterNumber.at(0));
        char number = letterNumber.at(1);
        if (isLetter(letter) && isNumber(number) && 'a' <= letter && letter <= 'h' && '1' <= number && number <= '8') {
            unsigned int numberValue = number - '0';
            if (Orientation::BlackUpWhiteDown == m_orientation) {
                result = Coordinate(letter - 'a', 8U - numberValue);
            } else if (Orientation::WhiteUpBlackDown == m_orientation) {
                result = Coordinate(7 - (letter - 'a'), numberValue - 1);
            }
        }
    }
    return result;
}

string Board::getLetterNumberNotationStringFromCoordinate(Coordinate const& coordinate) const {
    string result;
    if (Orientation::BlackUpWhiteDown == m_orientation) {
        result = string{static_cast<char>('a' + coordinate.getX()), static_cast<char>('1' + 7 - coordinate.getY())};
    } else if (Orientation::WhiteUpBlackDown == m_orientation) {
        result = string{static_cast<char>('a' + 7 - coordinate.getX()), static_cast<char>('1' + coordinate.getY())};
    }
    return result;
}

string Board::getReadableStringForMove(Move const& move) const {
    stringstream ss;
    ss << getPieceAt(move.first).getType() << " " << getLetterNumberNotationStringFromCoordinate(move.first) << "->"
       << getLetterNumberNotationStringFromCoordinate(move.second);
    return ss.str();
}

string Board::getNotationPartOfFenString() const {
    stringstream resultStream;
    CoordinateDataType startpoint = (Orientation::BlackUpWhiteDown == m_orientation)   ? 0
                                    : (Orientation::WhiteUpBlackDown == m_orientation) ? 7
                                                                                       : 0;
    CoordinateDataType end = (Orientation::WhiteUpBlackDown == m_orientation)   ? 0
                             : (Orientation::BlackUpWhiteDown == m_orientation) ? 7
                                                                                : 0;

    auto loopCondition =
        startpoint <= end
            ? [](CoordinateDataType const current,
                 CoordinateDataType const last) { return less_equal<CoordinateDataType>{}(current, last); }
            : [](CoordinateDataType const current, CoordinateDataType const last) {
                  return greater_equal<CoordinateDataType>{}(current, last);
              };

    CoordinateDataType interval = startpoint <= end ? 1 : -1;
    for (CoordinateDataType y = startpoint; loopCondition(y, end); y += interval) {
        unsigned int emptyCellsInRank = 0;
        for (CoordinateDataType x = startpoint; loopCondition(x, end); x += interval) {
            Coordinate coordinate(x, y);
            Piece piece(getPieceAt(coordinate));
            if (piece.isEmpty()) {
                emptyCellsInRank++;
            } else {
                if (emptyCellsInRank != 0) {
                    resultStream << emptyCellsInRank;
                }
                resultStream << piece.getCharacter();
                emptyCellsInRank = 0;
            }
        }
        if (emptyCellsInRank != 0) {
            resultStream << emptyCellsInRank;
        }
        if (y != end) {
            resultStream << "/";
        }
    }
    return resultStream.str();
}

string Board::getCastlingPartOfFenString() const {
    string result;
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        Piece pieceAtWhiteKing(getPieceAt(Coordinate(4, 7)));
        Piece pieceAtWhiteRookOnKingSide(getPieceAt(Coordinate(7, 7)));
        Piece pieceAtWhiteRookOnQueenSide(getPieceAt(Coordinate(0, 7)));
        Piece pieceAtBlackKing(getPieceAt(Coordinate(4, 0)));
        Piece pieceAtBlackRookOnKingSide(getPieceAt(Coordinate(7, 0)));
        Piece pieceAtBlackRookOnQueenSide(getPieceAt(Coordinate(0, 0)));
        if (PieceColorAndType::WhiteKing == pieceAtWhiteKing.getColorAndType() &&
            PieceColorAndType::WhiteRook == pieceAtWhiteRookOnKingSide.getColorAndType()) {
            result += "K";
        }
        if (PieceColorAndType::WhiteKing == pieceAtWhiteKing.getColorAndType() &&
            PieceColorAndType::WhiteRook == pieceAtWhiteRookOnQueenSide.getColorAndType()) {
            result += "Q";
        }
        if (PieceColorAndType::BlackKing == pieceAtBlackKing.getColorAndType() &&
            PieceColorAndType::BlackRook == pieceAtBlackRookOnKingSide.getColorAndType()) {
            result += "k";
        }
        if (PieceColorAndType::BlackKing == pieceAtBlackKing.getColorAndType() &&
            PieceColorAndType::BlackRook == pieceAtBlackRookOnQueenSide.getColorAndType()) {
            result += "q";
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        Piece pieceAtWhiteKing(getPieceAt(Coordinate(3, 0)));
        Piece pieceAtWhiteRookOnKingSide(getPieceAt(Coordinate(0, 0)));
        Piece pieceAtWhiteRookOnQueenSide(getPieceAt(Coordinate(7, 0)));
        Piece pieceAtBlackKing(getPieceAt(Coordinate(3, 7)));
        Piece pieceAtBlackRookOnKingSide(getPieceAt(Coordinate(0, 7)));
        Piece pieceAtBlackRookOnQueenSide(getPieceAt(Coordinate(7, 7)));
        if (PieceColorAndType::WhiteKing == pieceAtWhiteKing.getColorAndType() &&
            PieceColorAndType::WhiteRook == pieceAtWhiteRookOnKingSide.getColorAndType()) {
            result += "K";
        }
        if (PieceColorAndType::WhiteKing == pieceAtWhiteKing.getColorAndType() &&
            PieceColorAndType::WhiteRook == pieceAtWhiteRookOnQueenSide.getColorAndType()) {
            result += "Q";
        }
        if (PieceColorAndType::BlackKing == pieceAtBlackKing.getColorAndType() &&
            PieceColorAndType::BlackRook == pieceAtBlackRookOnKingSide.getColorAndType()) {
            result += "k";
        }
        if (PieceColorAndType::BlackKing == pieceAtBlackKing.getColorAndType() &&
            PieceColorAndType::BlackRook == pieceAtBlackRookOnQueenSide.getColorAndType()) {
            result += "q";
        }
    }
    if (result.empty()) {
        result = "-";
    }
    return result;
}

bool Board::isEmptyAt(Coordinate const& coordinate) const { return getPieceAt(coordinate).isEmpty(); }

bool Board::isACaptureMove(Move const& move) const { return !isEmptyAt(move.second); }

bool Board::isAPromotionMove(Move const& move) const {
    return PieceType::Pawn == getPieceAt(move.first).getType() && (move.second.getY() == 0 || move.second.getY() == 7);
}

bool Board::isACastlingMove(Move const& move) const {
    MovePair kingAndRookCastlingMovePair(getMatchingCastlingKingAndRookMovePair(move));
    return kingAndRookCastlingMovePair.first == move;
}

bool Board::isAPossibleMove(Move const& move) const { return isPossibleMoveBasedFromPieceType(move); }

bool Board::canBeCaptured(Coordinate const& endpoint) const {
    Piece pieceAtEnd(getPieceAt(endpoint));
    bool result(false);
    if (!pieceAtEnd.isEmpty()) {
        PieceColor opponentsColor(getOppositeColor(pieceAtEnd.getColor()));
        result = areThereAnyMovesToThis(endpoint, opponentsColor);
    }
    return result;
}

bool Board::areThereAnyMovesToThis(Coordinate const& endpoint, PieceColor const& colorOfPieceToMove) const {
    return !getMovesToThis(endpoint, colorOfPieceToMove, 1U).empty();
}

bool Board::hasOnlyOneMoveToThis(Coordinate const& endpoint, PieceColor const& colorOfPieceToMove) const {
    auto numberOfMoves = getMovesToThis(endpoint, colorOfPieceToMove, 2U).size();
    return numberOfMoves == 1;
}

void Board::setOrientation(Orientation const orientation) { m_orientation = orientation; }

void Board::setPieceAt(Coordinate const& coordinate, Piece const& piece) {
    if ((isCoordinateWithinTheBoard(coordinate))) {
        m_pieceMatrix.setEntry(coordinate.getX(), coordinate.getY(), piece);
    }
}

void Board::move(Move const& move) {
    // if (isAPossibleMove(move)) // dont check if its valid to be quicker
    MovePair kingAndRookCastlingMovePair(getMatchingCastlingKingAndRookMovePair(move));
    if (kingAndRookCastlingMovePair.first == move) {
        changePieceMatrixWithMove(kingAndRookCastlingMovePair.first);
        changePieceMatrixWithMove(kingAndRookCastlingMovePair.second);
    } else {
        changePieceMatrixWithMove(move);
    }
}

Board::PieceMatrix::MatrixData Board::getInitialValues(Orientation const& inputType) const {
    PieceMatrix::MatrixData result;
    if (Orientation::BlackUpWhiteDown == inputType) {
        result = {12, 10, 11, 13, 14, 11, 10, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0,
                  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0,  0,  0,  0,  1,  1,  1,  1,  1, 1, 1, 1, 4, 2, 3, 5, 6, 3, 2, 4};
    } else if (Orientation::WhiteUpBlackDown == inputType) {
        result = {4, 2, 3, 6, 5, 3, 2, 4, 1, 1, 1, 1, 1,  1,  1,  1,  0,  0,  0,  0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0, 0, 0,
                  0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 10, 11, 14, 13, 11, 10, 12};
    }
    return result;
}

void Board::retrieveMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    Piece pieceAtStart(getPieceAt(startpoint));
    switch (pieceAtStart.getType()) {
        case PieceType::Pawn: {
            retrievePawnMovesFromThis(result, startpoint);
            break;
        }
        case PieceType::Knight: {
            retrieveKnightMovesThis(result, startpoint);
            break;
        }
        case PieceType::Bishop: {
            retrieveBishopMovesFromThis(result, startpoint);
            break;
        }
        case PieceType::Rook: {
            retrieveRookMovesFromThis(result, startpoint);
            break;
        }
        case PieceType::Queen: {
            retrieveQueenMovesFromThis(result, startpoint);
            break;
        }
        case PieceType::King: {
            retrieveKingMovesFromThis(result, startpoint);
            break;
        }
        default: {
            break;
        }
    }
}

void Board::retrievePawnMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    retrievePawnNonCapturesFromThis(result, startpoint);
    retrievePawnCapturesFromThis(result, startpoint);
}

void Board::retrieveKnightMovesThis(Moves& result, Coordinate const& startpoint) const {
    Piece pieceAtStart(getPieceAt(startpoint));
    for (Coordinate const& delta : getLDeltaCoordinates()) {
        Coordinate endpoint(startpoint + delta);
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));
            if (pieceAtEnd.isEmpty() || pieceAtStart.getColor() != pieceAtEnd.getColor()) {
                result.emplace_back(startpoint, endpoint);
            }
        }
    }
}

void Board::retrieveBishopMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    retrieveDiagonalMovesFromThis(result, startpoint);
}

void Board::retrieveRookMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    retrieveStraightMovesFromThis(result, startpoint);
}

void Board::retrieveQueenMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    retrieveDiagonalMovesFromThis(result, startpoint);
    retrieveStraightMovesFromThis(result, startpoint);
}
void Board::retrieveKingMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    retrieveKingOneStepMovesFromThis(result, startpoint);
    retrieveKingCastlingMovesFromThis(result, startpoint);
}

void Board::retrievePawnNonCapturesFromThis(Moves& result, Coordinate const& startpoint) const {
    Piece pieceAtStart(getPieceAt(startpoint));
    DeltaRange range = getPawnNonCaptureDeltaRange(startpoint, pieceAtStart.getColor());
    for (CoordinateDataType deltaY = range.interval; deltaY != range.invalidDelta; deltaY += range.interval) {
        Coordinate endpoint(startpoint.getX(), startpoint.getY() + deltaY);
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));
            if (pieceAtEnd.isEmpty()) {
                result.emplace_back(startpoint, endpoint);
            } else {
                break;
            }
        } else {
            break;
        }
    }
}

void Board::retrievePawnCapturesFromThis(Moves& result, Coordinate const& startpoint) const {
    Piece pieceAtStart(getPieceAt(startpoint));
    for (Coordinate const& delta : getPawnCapturesDeltaCoordinates(pieceAtStart.getColor())) {
        Coordinate endpoint(startpoint + delta);
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));
            if (!pieceAtEnd.isEmpty() && pieceAtStart.getColor() != pieceAtEnd.getColor()) {
                result.emplace_back(startpoint, endpoint);
            }
        }
    }
}

void Board::retrieveDiagonalMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    for (Coordinate const& delta : getDiagonalIncrementDeltaCoordinates()) {
        retrieveMovesFromThisByIncrementingDelta(result, startpoint, delta);
    }
}

void Board::retrieveStraightMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    for (Coordinate const& delta : getStraightIncrementDeltaCoordinates()) {
        retrieveMovesFromThisByIncrementingDelta(result, startpoint, delta);
    }
}

void Board::retrieveKingOneStepMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    Piece pieceAtStart(getPieceAt(startpoint));
    for (Coordinate const& delta : getOneStepDeltaCoordinates()) {
        Coordinate endpoint(startpoint + delta);
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));
            if (pieceAtEnd.isEmpty() || pieceAtStart.getColor() != pieceAtEnd.getColor()) {
                result.emplace_back(startpoint, endpoint);
            }
        }
    }
}

void Board::retrieveKingCastlingMovesFromThis(Moves& result, Coordinate const& startpoint) const {
    Piece pieceAtStart(getPieceAt(startpoint));
    for (MovePair const& kingAndRookMovePair : getCastlingKingAndRookMovePairs(pieceAtStart.getColor())) {
        Move const& kingMove(kingAndRookMovePair.first);
        Move const& rookMove(kingAndRookMovePair.second);
        if (isCastlingValid(kingMove, rookMove)) {
            result.emplace_back(kingMove);
        }
    }
}

void Board::retrieveMovesFromThisByIncrementingDelta(
    Moves& result, Coordinate const& startpoint, Coordinate const& delta) const {
    Coordinate endpoint(startpoint + delta);
    while (true) {
        Piece pieceAtStart(getPieceAt(startpoint));
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));
            if (pieceAtEnd.isEmpty()) {
                result.emplace_back(startpoint, endpoint);
            } else if (pieceAtStart.getColor() != pieceAtEnd.getColor()) {
                result.emplace_back(startpoint, endpoint);
                break;
            } else {
                break;
            }
        } else {
            break;
        }
        endpoint = endpoint + delta;
    }
}

#define CHESS_UTILITIES_BOARD_QUICK_EXIT_IN_LOOP_IF_MAX_SIZE_IS_REACHED \
    if (result.size() >= maxSize) {                                     \
        break;                                                          \
    }

void Board::retrieveMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove, unsigned int const maxSize) const {
    Piece pieceAtEnd(getPieceAt(endpoint));
    if (pieceAtEnd.isEmpty()) {  // non capture only
        retrievePawnReverseNonCapturesToThis(result, endpoint, colorOfPieceToMove, maxSize);
    } else if (colorOfPieceToMove != pieceAtEnd.getColor()) {  // capture only
        retrievePawnReverseCapturesToThis(result, endpoint, colorOfPieceToMove, maxSize);
    }
    if (pieceAtEnd.isEmpty() || colorOfPieceToMove != pieceAtEnd.getColor()) {  // non capture and capture
        retrieveKnightMovesToThis(result, endpoint, colorOfPieceToMove, maxSize);
        retrieveDiagonalMovesToThis(result, endpoint, colorOfPieceToMove, maxSize);
        retrieveStraightMovesToThis(result, endpoint, colorOfPieceToMove, maxSize);
        retrieveKingOneStepMovesToThis(result, endpoint, colorOfPieceToMove, maxSize);
    }
    // How about castling? It doesnt really make any sense though.
}

void Board::retrievePawnReverseNonCapturesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove, unsigned int const maxSize) const {
    if (result.size() < maxSize) {
        DeltaRange range = getPawnReverseNonCaptureDeltaRange(endpoint, colorOfPieceToMove);
        for (CoordinateDataType deltaY = range.interval; deltaY != range.invalidDelta; deltaY += range.interval) {
            Coordinate startpoint(endpoint.getX(), endpoint.getY() + deltaY);
            Piece pieceAtStart(getPieceAt(startpoint));
            if (colorOfPieceToMove == pieceAtStart.getColor() && PieceType::Pawn == pieceAtStart.getType()) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_EXIT_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            }
        }
    }
}

void Board::retrievePawnReverseCapturesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove, unsigned int const maxSize) const {
    if (result.size() < maxSize) {
        for (Coordinate const& delta : getPawnReverseCapturesDeltaCoordinates(colorOfPieceToMove)) {
            Coordinate startpoint = endpoint + delta;
            Piece pieceAtStart(getPieceAt(startpoint));
            if (colorOfPieceToMove == pieceAtStart.getColor() && PieceType::Pawn == pieceAtStart.getType()) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_EXIT_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            }
        }
    }
}

void Board::retrieveKnightMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove, unsigned int const maxSize) const {
    if (result.size() < maxSize) {
        for (Coordinate const& delta : getLDeltaCoordinates()) {
            Coordinate startpoint = endpoint + delta;
            Piece pieceAtStart(getPieceAt(startpoint));
            if (colorOfPieceToMove == pieceAtStart.getColor() && PieceType::Knight == pieceAtStart.getType()) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_EXIT_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            }
        }
    }
}

void Board::retrieveDiagonalMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove, unsigned int const maxSize) const {
    if (result.size() < maxSize) {
        for (Coordinate const& delta : getDiagonalIncrementDeltaCoordinates()) {
            Coordinate startpoint = endpoint + delta;
            while (isCoordinateWithinTheBoard(startpoint)) {
                Piece pieceAtStart(getPieceAt(startpoint));
                if (!pieceAtStart.isEmpty()) {
                    if (colorOfPieceToMove == pieceAtStart.getColor() &&
                        (PieceType::Bishop == pieceAtStart.getType() || PieceType::Queen == pieceAtStart.getType())) {
                        result.emplace_back(startpoint, endpoint);
                        CHESS_UTILITIES_BOARD_QUICK_EXIT_IN_LOOP_IF_MAX_SIZE_IS_REACHED
                    }
                    break;
                }
                startpoint += delta;
            }
        }
    }
}

void Board::retrieveStraightMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove, unsigned int const maxSize) const {
    if (result.size() < maxSize) {
        for (Coordinate const& delta : getStraightIncrementDeltaCoordinates()) {
            Coordinate startpoint = endpoint + delta;
            while (isCoordinateWithinTheBoard(startpoint)) {
                Piece pieceAtStart(getPieceAt(startpoint));
                if (!pieceAtStart.isEmpty()) {
                    if (colorOfPieceToMove == pieceAtStart.getColor() &&
                        (PieceType::Rook == pieceAtStart.getType() || PieceType::Queen == pieceAtStart.getType())) {
                        result.emplace_back(startpoint, endpoint);
                        CHESS_UTILITIES_BOARD_QUICK_EXIT_IN_LOOP_IF_MAX_SIZE_IS_REACHED
                    }
                    break;
                }
                startpoint += delta;
            }
        }
    }
}

void Board::retrieveKingOneStepMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const colorOfPieceToMove, unsigned int const maxSize) const {
    if (result.size() < maxSize) {
        for (Coordinate const& delta : getOneStepDeltaCoordinates()) {
            Coordinate startpoint = endpoint + delta;
            Piece pieceAtStart(getPieceAt(startpoint));
            if (colorOfPieceToMove == pieceAtStart.getColor() && PieceType::King == pieceAtStart.getType()) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_EXIT_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            }
        }
    }
}

#undef CHESS_UTILITIES_BOARD_QUICK_EXIT_IN_LOOP_IF_MAX_SIZE_IS_REACHED

MovePairs Board::getCastlingKingAndRookMovePairs(PieceColor const colorOfPieceToMove) const {
    MovePairs result;
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::Black == colorOfPieceToMove) {
            Piece pieceAtKing(getPieceAt(Coordinate(4, 0)));
            Piece pieceAtQueenSideRook(getPieceAt(Coordinate(0, 0)));
            Piece pieceAtKingSideRook(getPieceAt(Coordinate(7, 0)));
            if (PieceColorAndType::BlackKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::BlackRook == pieceAtQueenSideRook.getColorAndType()) {
                result.emplace_back(Move{{4, 0}, {2, 0}}, Move{{0, 0}, {3, 0}});
            }
            if (PieceColorAndType::BlackKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::BlackRook == pieceAtKingSideRook.getColorAndType()) {
                result.emplace_back(Move{{4, 0}, {6, 0}}, Move{{7, 0}, {5, 0}});
            }
        } else if (PieceColor::White == colorOfPieceToMove) {
            Piece pieceAtKing(getPieceAt(Coordinate(4, 7)));
            Piece pieceAtQueenSideRook(getPieceAt(Coordinate(0, 7)));
            Piece pieceAtKingSideRook(getPieceAt(Coordinate(7, 7)));
            if (PieceColorAndType::WhiteKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::WhiteRook == pieceAtQueenSideRook.getColorAndType()) {
                result.emplace_back(Move{{4, 7}, {2, 7}}, Move{{0, 7}, {3, 7}});
            }
            if (PieceColorAndType::WhiteKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::WhiteRook == pieceAtKingSideRook.getColorAndType()) {
                result.emplace_back(Move{{4, 7}, {6, 7}}, Move{{7, 7}, {5, 7}});
            }
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == colorOfPieceToMove) {
            Piece pieceAtKing(getPieceAt(Coordinate(3, 0)));
            Piece pieceAtQueenSideRook(getPieceAt(Coordinate(0, 0)));
            Piece pieceAtKingSideRook(getPieceAt(Coordinate(7, 0)));
            if (PieceColorAndType::WhiteKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::WhiteRook == pieceAtQueenSideRook.getColorAndType()) {
                result.emplace_back(Move{{3, 0}, {1, 0}}, Move{{0, 0}, {2, 0}});
            }
            if (PieceColorAndType::WhiteKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::WhiteRook == pieceAtKingSideRook.getColorAndType()) {
                result.emplace_back(Move{{3, 0}, {5, 0}}, Move{{7, 0}, {4, 0}});
            }
        } else if (PieceColor::Black == colorOfPieceToMove) {
            Piece pieceAtKing(getPieceAt(Coordinate(3, 7)));
            Piece pieceAtQueenSideRook(getPieceAt(Coordinate(0, 7)));
            Piece pieceAtKingSideRook(getPieceAt(Coordinate(7, 7)));
            if (PieceColorAndType::BlackKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::BlackRook == pieceAtQueenSideRook.getColorAndType()) {
                result.emplace_back(Move{{3, 7}, {1, 7}}, Move{{0, 7}, {2, 7}});
            }
            if (PieceColorAndType::BlackKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::BlackRook == pieceAtKingSideRook.getColorAndType()) {
                result.emplace_back(Move{{3, 7}, {5, 7}}, Move{{7, 7}, {4, 7}});
            }
        }
    }
    return result;
}

MovePair Board::getMatchingCastlingKingAndRookMovePair(Move const& kingMoveThatShouldMatch) const {
    MovePair result{};
    Piece pieceAtKing(getPieceAt(kingMoveThatShouldMatch.first));
    MovePairs kingAndRookMovePairs(getCastlingKingAndRookMovePairs(pieceAtKing.getColor()));
    auto it = find_if(
        kingAndRookMovePairs.cbegin(), kingAndRookMovePairs.cend(),
        [&kingMoveThatShouldMatch](MovePair const& kingAndRookMovePair) {
            return kingAndRookMovePair.first == kingMoveThatShouldMatch;
        });
    if (it != kingAndRookMovePairs.cend()) {
        result = *it;
    }
    return result;
}

Coordinates Board::getLDeltaCoordinates() const {
    return Coordinates{{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
}

Coordinates Board::getDiagonalIncrementDeltaCoordinates() const {
    return Coordinates{{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
}

Coordinates Board::getStraightIncrementDeltaCoordinates() const {
    return Coordinates{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
}

Coordinates Board::getOneStepDeltaCoordinates() const {
    return Coordinates{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
}

Board::DeltaRange Board::getPawnNonCaptureDeltaRange(
    Coordinate const& startpoint, PieceColor const colorOfPieceToMove) const {
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == colorOfPieceToMove) {
            if (6 == startpoint.getY()) {
                return DeltaRange{-1, -3};
            } else {
                return DeltaRange{-1, -2};
            }
        } else if (PieceColor::Black == colorOfPieceToMove) {
            if (1 == startpoint.getY()) {
                return DeltaRange{1, 3};
            } else {
                return DeltaRange{1, 2};
            }
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == colorOfPieceToMove) {
            if (1 == startpoint.getY()) {
                return DeltaRange{1, 3};
            } else {
                return DeltaRange{1, 2};
            }
        } else if (PieceColor::Black == colorOfPieceToMove) {
            if (6 == startpoint.getY()) {
                return DeltaRange{-1, -3};
            } else {
                return DeltaRange{-1, -2};
            }
        }
    }
    return {};
}

Board::DeltaRange Board::getPawnReverseNonCaptureDeltaRange(
    Coordinate const& endpoint, PieceColor const colorOfPieceToMove) const {
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == colorOfPieceToMove) {
            if (4 == endpoint.getY()) {
                return DeltaRange{1, 3};
            } else {
                return DeltaRange{1, 2};
            }
        } else if (PieceColor::Black == colorOfPieceToMove) {
            if (3 == endpoint.getY()) {
                return DeltaRange{-1, -3};
            } else {
                return DeltaRange{-1, -2};
            }
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == colorOfPieceToMove) {
            if (3 == endpoint.getY()) {
                return DeltaRange{-1, -3};
            } else {
                return DeltaRange{-1, -2};
            }
        } else if (PieceColor::Black == colorOfPieceToMove) {
            if (4 == endpoint.getY()) {
                return DeltaRange{1, 3};
            } else {
                return DeltaRange{1, 2};
            }
        }
    }
    return {};
}

Coordinates Board::getPawnCapturesDeltaCoordinates(PieceColor const colorOfPieceToMove) const {
    Coordinates result;
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == colorOfPieceToMove) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        } else if (PieceColor::Black == colorOfPieceToMove) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == colorOfPieceToMove) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        } else if (PieceColor::Black == colorOfPieceToMove) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        }
    }
    return result;
}

Coordinates Board::getPawnReverseCapturesDeltaCoordinates(PieceColor const colorOfPieceToMove) const {
    Coordinates result;
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == colorOfPieceToMove) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        } else if (PieceColor::Black == colorOfPieceToMove) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == colorOfPieceToMove) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        } else if (PieceColor::Black == colorOfPieceToMove) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        }
    }
    return result;
}

CoordinateDataType Board::getOneIncrementData(CoordinateDataType const coordinateDataType) const {
    return coordinateDataType > 0 ? 1 : coordinateDataType < 0 ? -1 : 0;
}

bool Board::isPossibleMoveBasedFromPieceType(Move const& move) const {
    bool result(false);
    Piece piece(getPieceAt(move.first));
    switch (piece.getType()) {
        case PieceType::Pawn: {
            result = isPossiblePawnMove(move);
            break;
        }
        case PieceType::Knight: {
            result = isPossibleKnightMove(move);
            break;
        }
        case PieceType::Bishop: {
            result = isPossibleBishopMove(move);
            break;
        }
        case PieceType::Rook: {
            result = isPossibleRookMove(move);
            break;
        }
        case PieceType::Queen: {
            result = isPossibleQueenMove(move);
            break;
        }
        case PieceType::King: {
            result = isPossibleKingMove(move);
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

bool Board::isPossiblePawnMove(Move const& move) const {
    Piece pieceAtStart(getPieceAt(move.first));
    Piece pieceAtEnd(getPieceAt(move.second));
    return (pieceAtEnd.isEmpty() && isAPawnNonCaptureMove(move) && isThereNoBlockingPieceInBetweenTheMove(move)) ||
           (!pieceAtEnd.isEmpty() && pieceAtStart.getColor() != pieceAtEnd.getColor() && isAPawnCapture(move));
}

bool Board::isPossibleKnightMove(Move const& move) const {
    return isEndpointEmptyOrHaveDifferentColors(move) && isAnLMove(move);
}

bool Board::isPossibleBishopMove(Move const& move) const {
    return isEndpointEmptyOrHaveDifferentColors(move) && isADiagonalMove(move) &&
           isThereNoBlockingPieceInBetweenTheMove(move);
}

bool Board::isPossibleRookMove(Move const& move) const {
    return isEndpointEmptyOrHaveDifferentColors(move) && isAStraightMove(move) &&
           isThereNoBlockingPieceInBetweenTheMove(move);
}

bool Board::isPossibleQueenMove(Move const& move) const {
    return isEndpointEmptyOrHaveDifferentColors(move) && (isADiagonalMove(move) || isAStraightMove(move)) &&
           isThereNoBlockingPieceInBetweenTheMove(move);
}

bool Board::isPossibleKingMove(Move const& move) const {
    return isPossibleOneKingMove(move) || isPossibleKingCastlingMove(move);
}

bool Board::isPossibleOneKingMove(Move const& move) const {
    return isEndpointEmptyOrHaveDifferentColors(move) && isAOneStepMove(move);
}

bool Board::isPossibleKingCastlingMove(Move const& move) const {
    MovePair kingAndRookCastlingMovePair(getMatchingCastlingKingAndRookMovePair(move));
    Move kingMove(kingAndRookCastlingMovePair.first);
    Move rookMove(kingAndRookCastlingMovePair.second);
    return kingAndRookCastlingMovePair.first == move && isCastlingValid(kingMove, rookMove);
}

bool Board::isAPawnNonCaptureMove(Move const& move) const {
    bool result(false);
    if (move.first.getX() == move.second.getX()) {
        Piece piece(getPieceAt(move.first));
        Coordinate moveDelta = move.second - move.first;
        DeltaRange range = getPawnNonCaptureDeltaRange(move.first, piece.getColor());
        for (CoordinateDataType deltaY = range.interval; deltaY != range.invalidDelta; deltaY += range.interval) {
            if (deltaY == moveDelta.getY()) {
                result = true;
                break;
            }
        }
    }
    return result;
}

bool Board::isAPawnCapture(Move const& move) const {
    Piece piece(getPieceAt(move.first));
    Coordinate moveDelta = move.second - move.first;
    Coordinates pawnCaptureDeltas(getPawnCapturesDeltaCoordinates(piece.getColor()));
    return any_of(pawnCaptureDeltas.cbegin(), pawnCaptureDeltas.cend(), [&moveDelta](Coordinate const& pawnDelta) {
        return moveDelta == pawnDelta;
    });
}

bool Board::isADiagonalMove(Move const& move) const {
    Coordinate moveDelta = move.second - move.first;
    return getAbsoluteValue(moveDelta.getX()) == getAbsoluteValue(moveDelta.getY());
}

bool Board::isAStraightMove(Move const& move) const {
    Coordinate moveDelta = move.second - move.first;
    return (moveDelta.getX() == 0 && moveDelta.getY() != 0) || (moveDelta.getX() != 0 && moveDelta.getY() == 0);
}

bool Board::isAnLMove(Move const& move) const {
    Coordinate moveDelta = move.second - move.first;
    Coordinates lDeltas(getLDeltaCoordinates());
    return any_of(
        lDeltas.cbegin(), lDeltas.cend(), [&moveDelta](Coordinate const& lDelta) { return moveDelta == lDelta; });
}

bool Board::isAOneStepMove(Move const& move) const {
    Coordinate moveDelta = move.second - move.first;
    return moveDelta.getX() >= -1 && moveDelta.getX() <= 1 && moveDelta.getY() >= -1 && moveDelta.getY() <= 1;
}

bool Board::isCastlingValid(Move const& kingMove, Move const& rookMove) const {
    return getPieceAt(kingMove.second).isEmpty() && getPieceAt(rookMove.second).isEmpty() &&
           isThereNoBlockingPieceInBetweenTheMove(kingMove) && isThereNoBlockingPieceInBetweenTheMove(rookMove);
}

bool Board::isEndpointEmptyOrHaveDifferentColors(Move const& move) const {
    Piece pieceAtStart(getPieceAt(move.first));
    Piece pieceAtEnd(getPieceAt(move.second));
    return pieceAtEnd.isEmpty() ||
           (!pieceAtStart.isEmpty() && !pieceAtEnd.isEmpty() && pieceAtStart.getColor() != pieceAtEnd.getColor());
}

bool Board::isThereNoBlockingPieceInBetweenTheMove(Move const& move) const {
    Coordinate moveDelta = move.second - move.first;
    Coordinate oneIncrementDelta(getOneIncrementData(moveDelta.getX()), getOneIncrementData(moveDelta.getY()));
    Coordinate inBetween = move.first + oneIncrementDelta;
    while (isCoordinateWithinTheBoard(inBetween) && move.second != inBetween && getPieceAt(inBetween).isEmpty()) {
        inBetween += oneIncrementDelta;
    }
    return inBetween == move.second;
}

void Board::changePieceMatrixWithMove(Move const& move) {
    m_pieceMatrix.setEntry(
        move.second.getX(), move.second.getY(), m_pieceMatrix.getEntry(move.first.getX(), move.first.getY()));
    m_pieceMatrix.setEntry(move.first.getX(), move.first.getY(), Piece());
}

}  // namespace chess

}  // namespace alba
