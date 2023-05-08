#include "Board.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
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

bool Board::isEmptyAt(Coordinate const& coordinate) const { return getPieceAt(coordinate).isEmpty(); }

bool Board::isACaptureMove(Move const& move) const { return !isEmptyAt(move.second); }

bool Board::isAPromotionMove(Move const& move) const {
    return PieceType::Pawn == getPieceAt(move.first).getType() &&
           (move.second.getY() == 0 || move.second.getY() == 7) && isAPossibleMove(move);
}

bool Board::isACastlingMove(Move const& move) const {
    MovePair kingAndRookCastlingMovePair(getMatchingCastlingKingAndRookMovePair(move));
    return kingAndRookCastlingMovePair.first == move;
}

bool Board::isAPossibleMove(Move const& move) const { return isPossibleMoveBasedFromPieceType(move); }

bool Board::canBeCaptured(Coordinate const& destination) const {
    Piece piece(getPieceAt(destination));
    bool result(false);
    if (!piece.isEmpty()) {
        PieceColor oppositeColor(getOppositeColor(piece.getColor()));
        result = getDiagonalMovesPossibleToThisDestination(destination, oppositeColor, 1) >= 1 ||
                 getStraightMovesPossibleToThisDestination(destination, oppositeColor, 1) >= 1 ||
                 getKnightMovesPossibleToThisDestination(destination, oppositeColor, 1) >= 1 ||
                 getKingMovesPossibleToThisDestination(destination, oppositeColor, 1) >= 1 ||
                 getPawnReverseCapturesPossibleToThisDestination(destination, oppositeColor, 1) >= 1;
    }
    return result;
}

bool Board::areAnyMovesPossibleToThisDestination(Coordinate const& destination, PieceColor const& color) const {
    Piece piece(getPieceAt(destination));
    return getDiagonalMovesPossibleToThisDestination(destination, color, 1) >= 1 ||
           getStraightMovesPossibleToThisDestination(destination, color, 1) >= 1 ||
           getKnightMovesPossibleToThisDestination(destination, color, 1) >= 1 ||
           getKingMovesPossibleToThisDestination(destination, color, 1) >= 1 ||
           (piece.isEmpty() && getPawnReverseMovesPossibleToThisDestination(destination, color, 1) >= 1) ||
           (!piece.isEmpty() && getPawnReverseCapturesPossibleToThisDestination(destination, color, 1) >= 1);
}

bool Board::hasOnlyOneMovePossibleToThisDestination(Coordinate const& destination, PieceColor const& color) const {
    Piece piece(getPieceAt(destination));
    int numberOfMoves(0);
    numberOfMoves += getDiagonalMovesPossibleToThisDestination(destination, color, 2 - numberOfMoves);
    numberOfMoves += getStraightMovesPossibleToThisDestination(destination, color, 2 - numberOfMoves);
    numberOfMoves += getKnightMovesPossibleToThisDestination(destination, color, 2 - numberOfMoves);
    numberOfMoves += getKingMovesPossibleToThisDestination(destination, color, 2 - numberOfMoves);
    if (piece.isEmpty()) {
        numberOfMoves += getPawnReverseMovesPossibleToThisDestination(destination, color, 2 - numberOfMoves);
    } else {
        numberOfMoves += getPawnReverseCapturesPossibleToThisDestination(destination, color, 2 - numberOfMoves);
    }
    return numberOfMoves == 1;
}

Board::Orientation Board::getOrientation() const { return m_orientation; }

Board::PieceMatrix const& Board::getPieceMatrix() const { return m_pieceMatrix; }

Piece Board::getPieceAt(Coordinate const& coordinate) const {
    Piece result;
    if ((isCoordinateOnBoard(coordinate))) {
        result = m_pieceMatrix.getEntry(coordinate.getX(), coordinate.getY());
    }
    return result;
}

Moves Board::getPossibleMoves(Coordinate const& start) const {
    Moves result;
    retrievePossibleMovesBasedFromPieceType(result, start);
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

string Board::getFenString() const {
    stringstream resultStream;
    CoordinateDataType start = (Orientation::BlackUpWhiteDown == m_orientation)   ? 0
                               : (Orientation::WhiteUpBlackDown == m_orientation) ? 7
                                                                                  : 0;
    CoordinateDataType end = (Orientation::BlackUpWhiteDown == m_orientation)   ? 7
                             : (Orientation::WhiteUpBlackDown == m_orientation) ? 0
                                                                                : 0;
    AlbaValueRange<CoordinateDataType> yRange(start, end, 1);
    yRange.traverse([&](CoordinateDataType const y) {
        unsigned int emptyCellsInRank = 0;
        AlbaValueRange<CoordinateDataType> xRange(start, end, 1);
        xRange.traverse([&](CoordinateDataType const x) {
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
        });
        if (emptyCellsInRank != 0) {
            resultStream << emptyCellsInRank;
        }
        if (y != end) {
            resultStream << "/";
        }
    });
    return resultStream.str();
}

string Board::getCastlingFenString() const {
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

void Board::setOrientation(Orientation const orientation) { m_orientation = orientation; }

void Board::setPieceAt(Coordinate const& coordinate, Piece const& piece) {
    if ((isCoordinateOnBoard(coordinate))) {
        m_pieceMatrix.setEntry(coordinate.getX(), coordinate.getY(), piece);
    }
}

void Board::move(Move const& move) {
    if (isAPossibleMove(move)) {
        MovePair kingAndRookCastlingMovePair(getMatchingCastlingKingAndRookMovePair(move));
        if (kingAndRookCastlingMovePair.first == move) {
            changePieceMatrixWithMove(kingAndRookCastlingMovePair.first);
            changePieceMatrixWithMove(kingAndRookCastlingMovePair.second);
        } else {
            changePieceMatrixWithMove(move);
        }
    }
}

bool Board::isEndEmptyOrHaveDifferentColors(Move const& move) const {
    Piece start(getPieceAt(move.first));
    Piece end(getPieceAt(move.second));
    return end.isEmpty() || (start.getColor() != end.getColor());
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
    return (pieceAtEnd.isEmpty() && isAPawnMove(move) && doesMoveHasNoBlockingPieceInBetween(move)) ||
           (pieceAtStart.getColor() != pieceAtEnd.getColor() && isAPawnCapture(move));
}

bool Board::isPossibleKnightMove(Move const& move) const {
    return isEndEmptyOrHaveDifferentColors(move) && isAnLMove(move);
}

bool Board::isPossibleBishopMove(Move const& move) const {
    return isEndEmptyOrHaveDifferentColors(move) && isADiagonalMove(move) && doesMoveHasNoBlockingPieceInBetween(move);
}

bool Board::isPossibleRookMove(Move const& move) const {
    return isEndEmptyOrHaveDifferentColors(move) && isAStraightMove(move) && doesMoveHasNoBlockingPieceInBetween(move);
}

bool Board::isPossibleQueenMove(Move const& move) const {
    return isEndEmptyOrHaveDifferentColors(move) && (isADiagonalMove(move) || isAStraightMove(move)) &&
           doesMoveHasNoBlockingPieceInBetween(move);
}

bool Board::isPossibleKingMove(Move const& move) const {
    return isPossibleOneKingMove(move) || isPossibleKingCastlingMove(move);
}

bool Board::isPossibleOneKingMove(Move const& move) const {
    return isEndEmptyOrHaveDifferentColors(move) && isAOneStepMove(move);
}

bool Board::isPossibleKingCastlingMove(Move const& move) const {
    MovePair kingAndRookCastlingMovePair(getMatchingCastlingKingAndRookMovePair(move));
    Move kingMove(kingAndRookCastlingMovePair.first);
    Move rookMove(kingAndRookCastlingMovePair.second);
    return kingAndRookCastlingMovePair.first == move && getPieceAt(kingMove.second).isEmpty() &&
           getPieceAt(rookMove.second).isEmpty() && doesMoveHasNoBlockingPieceInBetween(kingMove) &&
           doesMoveHasNoBlockingPieceInBetween(rookMove);
}

bool Board::isAPawnMove(Move const& move) const {
    Piece piece(getPieceAt(move.first));
    Coordinate moveDelta = move.second - move.first;
    Coordinates possiblePawnMoveDeltas(getPossiblePawnMovesDeltaCoordinates(move.first, piece.getColor()));
    return any_of(
        possiblePawnMoveDeltas.cbegin(), possiblePawnMoveDeltas.cend(),
        [&moveDelta](Coordinate const& possiblePawnDelta) { return moveDelta == possiblePawnDelta; });
}

bool Board::isAPawnCapture(Move const& move) const {
    Piece piece(getPieceAt(move.first));
    Coordinate moveDelta = move.second - move.first;
    Coordinates possiblePawnCaptureDeltas(getPossiblePawnCapturesDeltaCoordinates(piece.getColor()));
    return any_of(
        possiblePawnCaptureDeltas.cbegin(), possiblePawnCaptureDeltas.cend(),
        [&moveDelta](Coordinate const& possiblePawnDelta) { return moveDelta == possiblePawnDelta; });
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

bool Board::doesMoveHasNoBlockingPieceInBetween(Move const& move) const {
    Coordinate moveDelta = move.second - move.first;
    Coordinate oneIncrementDelta(getOneIncrementData(moveDelta.getX()), getOneIncrementData(moveDelta.getY()));
    Coordinate inBetween = move.first + oneIncrementDelta;
    while (isCoordinateOnBoard(inBetween) && move.second != inBetween && getPieceAt(inBetween).isEmpty()) {
        inBetween += oneIncrementDelta;
    }
    return inBetween == move.second;
}

unsigned int Board::getDiagonalMovesPossibleToThisDestination(
    Coordinate const& destination, PieceColor const color, int const maximumCount) const {
    int numberOfMoves(0);
    if (maximumCount > 0) {
        for (Coordinate const& deltaCoordinate : getDiagonalIncrementDeltaCoordinates()) {
            Coordinate runningCoordinate = destination + deltaCoordinate;
            while (isCoordinateOnBoard(runningCoordinate)) {
                Piece piece(getPieceAt(runningCoordinate));
                if (!piece.isEmpty()) {
                    if (color == piece.getColor() &&
                        (PieceType::Bishop == piece.getType() || PieceType::Queen == piece.getType())) {
                        numberOfMoves++;
                    }
                    break;
                }
                runningCoordinate += deltaCoordinate;
            }
            if (numberOfMoves >= maximumCount) {
                break;
            }
        }
    }
    return numberOfMoves;
}

unsigned int Board::getStraightMovesPossibleToThisDestination(
    Coordinate const& destination, PieceColor const color, int const maximumCount) const {
    int numberOfMoves(0);
    if (maximumCount > 0) {
        for (Coordinate const& deltaCoordinate : getStraightIncrementDeltaCoordinates()) {
            Coordinate runningCoordinate = destination + deltaCoordinate;
            while (isCoordinateOnBoard(runningCoordinate)) {
                Piece piece(getPieceAt(runningCoordinate));
                if (!piece.isEmpty()) {
                    if (color == piece.getColor() &&
                        (PieceType::Rook == piece.getType() || PieceType::Queen == piece.getType())) {
                        numberOfMoves++;
                    }
                    break;
                }
                runningCoordinate += deltaCoordinate;
            }
            if (numberOfMoves >= maximumCount) {
                break;
            }
        }
    }
    return numberOfMoves;
}

unsigned int Board::getKnightMovesPossibleToThisDestination(
    Coordinate const& destination, PieceColor const color, int const maximumCount) const {
    int numberOfMoves(0);
    if (maximumCount > 0) {
        for (Coordinate const& deltaCoordinate : getLDeltaCoordinates()) {
            Piece piece(getPieceAt(destination + deltaCoordinate));
            if (color == piece.getColor() && PieceType::Knight == piece.getType()) {
                numberOfMoves++;
                if (numberOfMoves >= maximumCount) {
                    break;
                }
            }
        }
    }
    return numberOfMoves;
}

unsigned int Board::getKingMovesPossibleToThisDestination(
    Coordinate const& destination, PieceColor const color, int const maximumCount) const {
    int numberOfMoves(0);
    if (maximumCount > 0) {
        for (Coordinate const& deltaCoordinate : getOneStepDeltaCoordinates()) {
            Piece piece(getPieceAt(destination + deltaCoordinate));
            if (color == piece.getColor() && PieceType::King == piece.getType()) {
                numberOfMoves++;
                if (numberOfMoves >= maximumCount) {
                    break;
                }
            }
        }
    }
    return numberOfMoves;
}

unsigned int Board::getPawnReverseMovesPossibleToThisDestination(
    Coordinate const& destination, PieceColor const color, int const maximumCount) const {
    int numberOfMoves(0);
    if (maximumCount > 0) {
        for (Coordinate const& deltaCoordinate : getPossiblePawnReverseMovesDeltaCoordinates(destination, color)) {
            Piece piece(getPieceAt(destination + deltaCoordinate));
            if (color == piece.getColor() && PieceType::Pawn == piece.getType()) {
                numberOfMoves++;
                if (numberOfMoves >= maximumCount) {
                    break;
                }
            }
        }
    }
    return numberOfMoves;
}

unsigned int Board::getPawnReverseCapturesPossibleToThisDestination(
    Coordinate const& destination, PieceColor const color, int const maximumCount) const {
    int numberOfMoves(0);
    if (maximumCount > 0) {
        for (Coordinate const& deltaCoordinate : getPossiblePawnReverseCapturesDeltaCoordinates(color)) {
            Piece piece(getPieceAt(destination + deltaCoordinate));
            if (color == piece.getColor() && PieceType::Pawn == piece.getType()) {
                numberOfMoves++;
                if (numberOfMoves >= maximumCount) {
                    break;
                }
            }
        }
    }
    return numberOfMoves;
}

CoordinateDataType Board::getOneIncrementData(CoordinateDataType const coordinateDataType) const {
    return coordinateDataType > 0 ? 1 : coordinateDataType < 0 ? -1 : 0;
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

Coordinates Board::getPossiblePawnMovesDeltaCoordinates(Coordinate const& start, PieceColor const color) const {
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == color) {
            if (6 == start.getY()) {
                return Coordinates{{0, -1}, {0, -2}};
            } else {
                return Coordinates{{0, -1}};
            }
        } else if (PieceColor::Black == color) {
            if (1 == start.getY()) {
                return Coordinates{{0, 1}, {0, 2}};
            } else {
                return Coordinates{{0, 1}};
            }
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == color) {
            if (1 == start.getY()) {
                return Coordinates{{0, 1}, {0, 2}};
            } else {
                return Coordinates{{0, 1}};
            }
        } else if (PieceColor::Black == color) {
            if (6 == start.getY()) {
                return Coordinates{{0, -1}, {0, -2}};
            } else {
                return Coordinates{{0, -1}};
            }
        }
    }
    return {};
}

Coordinates Board::getPossiblePawnReverseMovesDeltaCoordinates(Coordinate const& end, PieceColor const color) const {
    Coordinates result;
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == color) {
            result.emplace_back(0, 1);
            if (4 == end.getY()) {
                result.emplace_back(0, 2);
            }
        } else if (PieceColor::Black == color) {
            result.emplace_back(0, -1);
            if (3 == end.getY()) {
                result.emplace_back(0, -2);
            }
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == color) {
            result.emplace_back(0, -1);
            if (3 == end.getY()) {
                result.emplace_back(0, -2);
            }
        } else if (PieceColor::Black == color) {
            result.emplace_back(0, 1);
            if (4 == end.getY()) {
                result.emplace_back(0, 2);
            }
        }
    }
    return result;
}

Coordinates Board::getPossiblePawnCapturesDeltaCoordinates(PieceColor const color) const {
    Coordinates result;
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == color) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        } else if (PieceColor::Black == color) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == color) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        } else if (PieceColor::Black == color) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        }
    }
    return result;
}

Coordinates Board::getPossiblePawnReverseCapturesDeltaCoordinates(PieceColor const color) const {
    Coordinates result;
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == color) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        } else if (PieceColor::Black == color) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == color) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        } else if (PieceColor::Black == color) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        }
    }
    return result;
}

MovePairs Board::getPossibleCastlingKingAndRookMovePairs(PieceColor const color) const {
    MovePairs result;
    if (Board::Orientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::Black == color) {
            Piece pieceAtKing(getPieceAt(Coordinate(4, 0)));
            Piece pieceAtQueenSideRook(getPieceAt(Coordinate(0, 0)));
            Piece pieceAtKingSideRook(getPieceAt(Coordinate(7, 0)));
            if (PieceColorAndType::BlackKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::BlackRook == pieceAtQueenSideRook.getColorAndType()) {
                result.emplace_back(Move{Coordinate(4, 0), Coordinate(2, 0)}, Move{Coordinate(0, 0), Coordinate(3, 0)});
            }
            if (PieceColorAndType::BlackKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::BlackRook == pieceAtKingSideRook.getColorAndType()) {
                result.emplace_back(Move{Coordinate(4, 0), Coordinate(6, 0)}, Move{Coordinate(7, 0), Coordinate(5, 0)});
            }
        } else if (PieceColor::White == color) {
            Piece pieceAtKing(getPieceAt(Coordinate(4, 7)));
            Piece pieceAtQueenSideRook(getPieceAt(Coordinate(0, 7)));
            Piece pieceAtKingSideRook(getPieceAt(Coordinate(7, 7)));
            if (PieceColorAndType::WhiteKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::WhiteRook == pieceAtQueenSideRook.getColorAndType()) {
                result.emplace_back(Move{Coordinate(4, 7), Coordinate(2, 7)}, Move{Coordinate(0, 7), Coordinate(3, 7)});
            }
            if (PieceColorAndType::WhiteKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::WhiteRook == pieceAtKingSideRook.getColorAndType()) {
                result.emplace_back(Move{Coordinate(4, 7), Coordinate(6, 7)}, Move{Coordinate(7, 7), Coordinate(5, 7)});
            }
        }
    } else if (Board::Orientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == color) {
            Piece pieceAtKing(getPieceAt(Coordinate(3, 0)));
            Piece pieceAtQueenSideRook(getPieceAt(Coordinate(0, 0)));
            Piece pieceAtKingSideRook(getPieceAt(Coordinate(7, 0)));
            if (PieceColorAndType::WhiteKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::WhiteRook == pieceAtQueenSideRook.getColorAndType()) {
                result.emplace_back(Move{Coordinate(3, 0), Coordinate(1, 0)}, Move{Coordinate(0, 0), Coordinate(2, 0)});
            }
            if (PieceColorAndType::WhiteKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::WhiteRook == pieceAtKingSideRook.getColorAndType()) {
                result.emplace_back(Move{Coordinate(3, 0), Coordinate(5, 0)}, Move{Coordinate(7, 0), Coordinate(4, 0)});
            }
        } else if (PieceColor::Black == color) {
            Piece pieceAtKing(getPieceAt(Coordinate(3, 7)));
            Piece pieceAtQueenSideRook(getPieceAt(Coordinate(0, 7)));
            Piece pieceAtKingSideRook(getPieceAt(Coordinate(7, 7)));
            if (PieceColorAndType::BlackKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::BlackRook == pieceAtQueenSideRook.getColorAndType()) {
                result.emplace_back(Move{Coordinate(3, 7), Coordinate(1, 7)}, Move{Coordinate(0, 7), Coordinate(2, 7)});
            }
            if (PieceColorAndType::BlackKing == pieceAtKing.getColorAndType() &&
                PieceColorAndType::BlackRook == pieceAtKingSideRook.getColorAndType()) {
                result.emplace_back(Move{Coordinate(3, 7), Coordinate(5, 7)}, Move{Coordinate(7, 7), Coordinate(4, 7)});
            }
        }
    }
    return result;
}

MovePair Board::getMatchingCastlingKingAndRookMovePair(Move const& kingMoveThatShouldMatch) const {
    MovePair result{};
    Piece pieceAtKing(getPieceAt(kingMoveThatShouldMatch.first));
    MovePairs kingAndRookMovePairs(getPossibleCastlingKingAndRookMovePairs(pieceAtKing.getColor()));
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

void Board::retrievePossibleMovesBasedFromPieceType(Moves& result, Coordinate const& start) const {
    Piece piece(getPieceAt(start));
    switch (piece.getType()) {
        case PieceType::Pawn: {
            retrievePossiblePawnMoves(result, start);
            break;
        }
        case PieceType::Knight: {
            retrievePossibleKnightMoves(result, start);
            break;
        }
        case PieceType::Bishop: {
            retrievePossibleBishopMoves(result, start);
            break;
        }
        case PieceType::Rook: {
            retrievePossibleRookMoves(result, start);
            break;
        }
        case PieceType::Queen: {
            retrievePossibleQueenMoves(result, start);
            break;
        }
        case PieceType::King: {
            retrievePossibleKingMoves(result, start);
            break;
        }
        default: {
            break;
        }
    }
}

void Board::retrievePossiblePawnMoves(Moves& result, Coordinate const& start) const {
    Piece piece(getPieceAt(start));
    for (Coordinate const& deltaCoordinate : getPossiblePawnMovesDeltaCoordinates(start, piece.getColor())) {
        addMoveToListOfMoves(result, Move(start, start + deltaCoordinate));
    }
}

void Board::retrievePossibleKnightMoves(Moves& result, Coordinate const& start) const {
    for (Coordinate const& deltaCoordinate : getLDeltaCoordinates()) {
        addMoveToListOfMoves(result, Move(start, start + deltaCoordinate));
    }
}

void Board::retrievePossibleBishopMoves(Moves& result, Coordinate const& start) const {
    for (Coordinate const& deltaCoordinate : getDiagonalIncrementDeltaCoordinates()) {
        retrievePossibleMovesByIncrements(result, start, deltaCoordinate);
    }
}

void Board::retrievePossibleRookMoves(Moves& result, Coordinate const& start) const {
    for (Coordinate const& deltaCoordinate : getStraightIncrementDeltaCoordinates()) {
        retrievePossibleMovesByIncrements(result, start, deltaCoordinate);
    }
}

void Board::retrievePossibleQueenMoves(Moves& result, Coordinate const& start) const {
    retrievePossibleBishopMoves(result, start);
    retrievePossibleRookMoves(result, start);
}

void Board::retrievePossibleKingMoves(Moves& result, Coordinate const& start) const {
    retrievePossibleOneKingMoves(result, start);
    retrievePossibleKingCastlingMoves(result, start);
}

void Board::retrievePossibleOneKingMoves(Moves& result, Coordinate const& start) const {
    for (Coordinate const& deltaCoordinate : getOneStepDeltaCoordinates()) {
        addMoveToListOfMoves(result, Move(start, start + deltaCoordinate));
    }
}

void Board::retrievePossibleKingCastlingMoves(Moves& result, Coordinate const& start) const {
    Piece piece(getPieceAt(start));
    for (MovePair const& kingAndRookMovePair : getPossibleCastlingKingAndRookMovePairs(piece.getColor())) {
        if (kingAndRookMovePair.first.first == start) {
            addMoveToListOfMoves(result, kingAndRookMovePair.first);
        }
    }
}

void Board::retrievePossibleMovesByIncrements(
    Moves& result, Coordinate const& start, Coordinate const& increment) const {
    Coordinate end(start + increment);
    while (true) {
        Piece pieceAtStart(getPieceAt(start));
        Piece pieceAtEnd(getPieceAt(end));
        if (!isCoordinateOnBoard(end)) {
            break;
        } else if (pieceAtEnd.isEmpty()) {
            addMoveToListOfMoves(result, Move(start, end));
        } else if (pieceAtStart.getColor() != pieceAtEnd.getColor()) {
            addMoveToListOfMoves(result, Move(start, end));
            break;
        } else {
            break;
        }
        end = end + increment;
    }
}

void Board::addMoveToListOfMoves(Moves& moves, Move const& move) const {
    if (isValidMove(move)) {
        if (isEndEmptyOrHaveDifferentColors(move)) {
            moves.emplace_back(move);
        }
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

void Board::changePieceMatrixWithMove(Move const& move) {
    m_pieceMatrix.setEntry(
        move.second.getX(), move.second.getY(), m_pieceMatrix.getEntry(move.first.getX(), move.first.getY()));
    m_pieceMatrix.setEntry(move.first.getX(), move.first.getY(), Piece());
}

}  // namespace chess

}  // namespace alba
