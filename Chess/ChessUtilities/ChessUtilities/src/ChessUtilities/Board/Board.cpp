#include "Board.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <functional>
#include <numeric>
#include <sstream>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace chess {

#define CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED \
    if (static_cast<int>(result.size()) >= maxSize) {             \
        return;                                                   \
    }

#define CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED \
    if (static_cast<int>(result.size()) >= maxSize) {                    \
        break;                                                           \
    }

Board::Board() : m_orientation(BoardOrientation::Unknown), m_pieceGrid{} {}

Board::Board(BoardOrientation const& orientation)
    : m_orientation(orientation), m_pieceGrid(getInitialValues(orientation)) {}

Board::Board(BoardOrientation const& orientation, PieceGrid const& pieceGrid)
    : m_orientation(orientation), m_pieceGrid(pieceGrid) {}

bool Board::operator==(Board const& other) const {
    return m_orientation == other.m_orientation && m_pieceGrid == other.m_pieceGrid;
}

bool Board::operator!=(Board const& other) const { return !operator==(other); }

BoardOrientation Board::getOrientation() const { return m_orientation; }

Board::PieceGrid const& Board::getPieceGrid() const { return m_pieceGrid; }

Moves Board::getMovesFromThis(Coordinate const& startpoint, int const maxSize) const {
    Moves result;
    retrieveMovesFromThis(result, startpoint, maxSize);
    return result;
}

Moves Board::getMovesToThis(Coordinate const& endpoint, PieceColor const& moveColor, int const maxSize) const {
    Moves result;
    retrieveMovesToThis(result, endpoint, moveColor, maxSize);
    return result;
}

Moves Board::getAttacksToThis(Coordinate const& endpoint, PieceColor const& moveColor, int const maxSize) const {
    Moves result;
    retrieveAttacksToThis(result, endpoint, moveColor, maxSize);
    return result;
}

Move Board::getMoveUsingUciNotation(string const& text) const {
    // Source: https://en.wikipedia.org/wiki/Universal_Chess_Interface
    Move result{};
    if (text.size() == 4 || text.size() == 5)  // 5 is for promotion
    {
        result = {
            getCoordinateFromAlgebraicNotation(text.substr(0, 2)),
            getCoordinateFromAlgebraicNotation(text.substr(2, 2))};
    }
    return result;
}

Move Board::getMoveUsingAlgebraicNotation(string const& text, PieceColor const moveColor) const {
    // Source: https://en.wikipedia.org/wiki/Algebraic_text_(chess)
    Move result{};

    CastleType castleType(getCastleTypeWithAlgebraicNotation(text));
    if (CastleType::KingSideCastle == castleType || CastleType::QueenSideCastle == castleType) {
        result = getCastleMove(castleType, moveColor);
    } else {
        result = getNonCastleMoveWithAlgebraicNotation(text, moveColor);
    }
    return result;
}

Coordinate Board::getCoordinateFromAlgebraicNotation(string const& text) const {
    Coordinate result{};
    if (text.size() == 2) {
        char letterChar = tolower(text[0]);
        char numberChar = text[1];
        if (isAToH(letterChar) && is1To8(numberChar)) {
            result = getCorrectCoordinateFromAlgebraicNotation(letterChar - 'a', numberChar - '1');
        }
    }
    return result;
}

Piece Board::getPieceAt(Coordinate const& coordinate) const {
    Piece result;
    if ((isCoordinateWithinTheBoard(coordinate))) {
        result = m_pieceGrid[getGridIndex(coordinate.getX(), coordinate.getY())];
    }
    return result;
}

Exchange Board::getExchangeAt(Coordinate const& coordinate) const {
    enum class ExchangeState { Defended, Attacked };
    constexpr int PAWN_INDEX = 0, KNIGHT_INDEX = 1, BISHOP_INDEX = 2, ROOK_INDEX = 3, QUEEN_INDEX = 4, KING_INDEX = 5,
                  SIZE = 6;
    vector<int> pieceValue{1, 3, 3, 5, 9, 0};
    AttackDefendCounts counts(6, AttackDefendCount{});
    retrievePawnAttackDefendCountToThis(counts[PAWN_INDEX], coordinate);
    retrieveKnightAttackDefendCountToThis(counts[KNIGHT_INDEX], coordinate);
    retrieveDiagonalAttackDefendCountToThis(counts[BISHOP_INDEX], counts[QUEEN_INDEX], coordinate);
    retrieveStraightAttackDefendCountToThis(counts[ROOK_INDEX], counts[QUEEN_INDEX], coordinate);
    retrieveKingOneStepAttackDefendCountToThis(counts[KING_INDEX], coordinate);

    AttackDefendCount totalCount{};
    for (auto const& count : counts) {
        totalCount.attack += count.attack;
        totalCount.defend += count.defend;
    }
    Piece pieceToCapture(getPieceAt(coordinate));
    int pendingPieceValue = getValueOfPieceType(pieceToCapture.getType());
    int exchangeValue = 0;
    int exchangeCount = 0;
    ExchangeState exchangeState{ExchangeState::Defended};
    for (int ai = 0, di = 0; totalCount.attack + totalCount.defend > 0 && ai < SIZE && di < SIZE;) {
        if ((ai == KING_INDEX && totalCount.defend > 0) || (di == KING_INDEX && totalCount.attack > 0)) {
            break;  // king cant counter capture so break loop
        } else if (
            counts[ai].attack > 0 && counts[di].defend > 0 && pieceValue[ai] == pieceValue[di] &&
            pendingPieceValue == pieceValue[ai] && exchangeValue == 0) {
            int sameCount = min(counts[ai].attack, counts[di].defend);
            counts[ai].attack -= sameCount;
            counts[di].defend -= sameCount;
            totalCount.attack -= sameCount;
            totalCount.defend -= sameCount;
            exchangeCount += 2 * sameCount;
        } else if (ExchangeState::Defended == exchangeState) {
            if (counts[ai].attack > 0) {
                exchangeState = ExchangeState::Attacked;
                if ((totalCount.defend > 0 && pendingPieceValue + exchangeValue - pieceValue[ai] >= 0) ||
                    (totalCount.defend == 0 && pendingPieceValue + exchangeValue >= 0)) {
                    exchangeValue -= pendingPieceValue;
                    pendingPieceValue = pieceValue[ai];
                    counts[ai].attack--;
                    totalCount.attack--;
                    exchangeCount++;
                } else {
                    break;  // opponent dont want to exchange
                }
            } else if (counts[ai].attack == 0) {
                ai++;
            }
        } else if (ExchangeState::Attacked == exchangeState) {
            if (counts[di].defend > 0) {
                exchangeState = ExchangeState::Defended;
                if ((totalCount.attack > 0 && pendingPieceValue - exchangeValue - pieceValue[di] >= 0) ||
                    (totalCount.attack == 0 && pendingPieceValue - exchangeValue >= 0)) {
                    exchangeValue += pendingPieceValue;
                    pendingPieceValue = pieceValue[di];
                    counts[di].defend--;
                    totalCount.defend--;
                    exchangeCount++;
                } else {
                    break;  // player dont want to exchange
                }
            } else if (counts[di].defend == 0) {
                di++;
            }
        } else {
            break;
        }
    }
    return Exchange(exchangeValue, exchangeCount);
}

string Board::getAlgebraicNotationOfCoordinate(Coordinate const& coordinate) const {
    string result;
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        result = string{static_cast<char>('a' + coordinate.getX()), static_cast<char>('1' + 7 - coordinate.getY())};
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        result = string{static_cast<char>('a' + 7 - coordinate.getX()), static_cast<char>('1' + coordinate.getY())};
    }
    return result;
}

string Board::getReadableStringOfMove(Move const& move) const {
    stringstream ss;
    ss << getEnumString(getPieceAt(move.first).getType()) << " ";
    ss << getAlgebraicNotationOfCoordinate(move.first) << "->" << getAlgebraicNotationOfCoordinate(move.second);
    return ss.str();
}

string Board::getNotationPartOfFenString() const {
    stringstream ss;
    CoordinateDataType startpoint = (BoardOrientation::BlackUpWhiteDown == m_orientation)   ? 0
                                    : (BoardOrientation::WhiteUpBlackDown == m_orientation) ? 7
                                                                                            : 0;
    CoordinateDataType end = (BoardOrientation::WhiteUpBlackDown == m_orientation)   ? 0
                             : (BoardOrientation::BlackUpWhiteDown == m_orientation) ? 7
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
        int emptyCellsInRank = 0;
        for (CoordinateDataType x = startpoint; loopCondition(x, end); x += interval) {
            Coordinate coordinate(x, y);
            Piece piece(getPieceAt(coordinate));
            if (piece.isEmpty()) {
                emptyCellsInRank++;
            } else {
                if (emptyCellsInRank != 0) {
                    ss << emptyCellsInRank;
                }
                ss << piece.getFenCharacter();
                emptyCellsInRank = 0;
            }
        }
        if (emptyCellsInRank != 0) {
            ss << emptyCellsInRank;
        }
        if (y != end) {
            ss << "/";
        }
    }
    return ss.str();
}

string Board::getCastlingPartOfFenString() const {
    string result;
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
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
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
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
        result = areThereAnyAttacksToThis(endpoint, opponentsColor);
    }
    return result;
}

bool Board::areThereAnyMovesToThis(Coordinate const& endpoint, PieceColor const& moveColor) const {
    return !getMovesToThis(endpoint, moveColor, 1U).empty();
}

bool Board::areThereAnyAttacksToThis(Coordinate const& endpoint, PieceColor const& moveColor) const {
    return !getAttacksToThis(endpoint, moveColor, 1U).empty();
}

bool Board::hasOnlyOneMoveToThis(Coordinate const& endpoint, PieceColor const& moveColor) const {
    auto numberOfMoves = getMovesToThis(endpoint, moveColor, 2U).size();
    return numberOfMoves == 1;
}

int Board::getNumberOfWaysToBlockAttacks(Moves const& attacks, int const maxSize) const {
    int result{};
    if (attacks.size() == 1) {  // multiple attacks cannot be blocked (think about it)
        Move attack = attacks.back();
        Piece attackingPiece = getPieceAt(attack.first);
        if (PieceType::Bishop == attackingPiece.getType() || PieceType::Rook == attackingPiece.getType() ||
            PieceType::Queen == attackingPiece.getType()) {
            PieceColor opponentsColor = getOppositeColor(getPieceAt(attack.first).getColor());
            result = getNumberOfWaysToBlockPath(attack.first, attack.second, opponentsColor, maxSize);
        }
    }
    return result;
}

void Board::setOrientation(BoardOrientation const orientation) { m_orientation = orientation; }

void Board::setPieceAt(Coordinate const& coordinate, Piece const& piece) {
    if ((isCoordinateWithinTheBoard(coordinate))) {
        m_pieceGrid[getGridIndex(coordinate.getX(), coordinate.getY())] = piece;
    }
}

void Board::move(Move const& move) {
    // if (isAPossibleMove(move)) // dont check if its valid to be quicker

    MovePair kingAndRookCastlingMovePair(getMatchingCastlingKingAndRookMovePair(move));
    if (kingAndRookCastlingMovePair.first == move) {
        changePieceGridWithMove(kingAndRookCastlingMovePair.first);
        changePieceGridWithMove(kingAndRookCastlingMovePair.second);
    } else {
        if (isAPawnEnPassantMove(move)) {
            Coordinate opponentPawnLocation{move.second.getX(), move.first.getY()};
            setPieceAt(opponentPawnLocation, Piece());
        }
        changePieceGridWithMove(move);
    }
}

Board::PieceGrid Board::getInitialValues(BoardOrientation const& inputType) const {
    if (BoardOrientation::BlackUpWhiteDown == inputType) {
        return {12, 10, 11, 13, 14, 11, 10, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 4, 2, 3, 5, 6, 3, 2, 4};
    } else if (BoardOrientation::WhiteUpBlackDown == inputType) {
        return {4, 2, 3, 6, 5, 3, 2, 4, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 12, 10, 11, 14, 13, 11, 10, 12};
    } else {
        return {};
    }
}

void Board::retrieveMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Piece pieceAtStart(getPieceAt(startpoint));
    switch (pieceAtStart.getType()) {
        case PieceType::Pawn: {
            retrievePawnMovesFromThis(result, startpoint, maxSize);
            break;
        }
        case PieceType::Knight: {
            retrieveKnightMovesThis(result, startpoint, maxSize);
            break;
        }
        case PieceType::Bishop: {
            retrieveBishopMovesFromThis(result, startpoint, maxSize);
            break;
        }
        case PieceType::Rook: {
            retrieveRookMovesFromThis(result, startpoint, maxSize);
            break;
        }
        case PieceType::Queen: {
            retrieveQueenMovesFromThis(result, startpoint, maxSize);
            break;
        }
        case PieceType::King: {
            retrieveKingMovesFromThis(result, startpoint, maxSize);
            break;
        }
        default: {
            break;
        }
    }
}

void Board::retrievePawnMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    retrievePawnNonCapturesFromThis(result, startpoint, maxSize);
    retrievePawnCapturesFromThis(result, startpoint, maxSize);
}

void Board::retrieveKnightMovesThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Piece pieceAtStart(getPieceAt(startpoint));
    for (Coordinate const& delta : getLDeltaCoordinates()) {
        Coordinate endpoint(startpoint + delta);
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));
            if (pieceAtEnd.isEmpty() || areOpposingColors(pieceAtStart.getColor(), pieceAtEnd.getColor())) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            }
        }
    }
}

void Board::retrieveBishopMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    retrieveDiagonalMovesFromThis(result, startpoint, maxSize);
}

void Board::retrieveRookMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    retrieveStraightMovesFromThis(result, startpoint, maxSize);
}

void Board::retrieveQueenMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    retrieveDiagonalMovesFromThis(result, startpoint, maxSize);
    retrieveStraightMovesFromThis(result, startpoint, maxSize);
}
void Board::retrieveKingMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    retrieveKingOneStepMovesFromThis(result, startpoint, maxSize);
    retrieveKingCastlingMovesFromThis(result, startpoint, maxSize);
}

void Board::retrievePawnNonCapturesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Piece pieceAtStart(getPieceAt(startpoint));
    DeltaRange range = getPawnNonCaptureDeltaRange(startpoint, pieceAtStart.getColor());
    for (CoordinateDataType deltaY = range.interval; deltaY != range.invalidDelta; deltaY += range.interval) {
        Coordinate endpoint(startpoint.getX(), startpoint.getY() + deltaY);
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));
            if (pieceAtEnd.isEmpty()) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            } else {
                break;
            }
        } else {
            break;
        }
    }
}

void Board::retrievePawnCapturesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Piece pieceAtStart(getPieceAt(startpoint));
    for (Coordinate const& delta : getPawnCapturesDeltaCoordinates(pieceAtStart.getColor())) {
        Coordinate endpoint(startpoint + delta);
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));
            if (!pieceAtEnd.isEmpty() && areOpposingColors(pieceAtStart.getColor(), pieceAtEnd.getColor())) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            }
        }
    }
}

void Board::retrieveDiagonalMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    for (Coordinate const& delta : getDiagonalIncrementDeltaCoordinates()) {
        retrieveMovesFromThisByIncrementingDelta(result, startpoint, delta, maxSize);
        CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
    }
}

void Board::retrieveStraightMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    for (Coordinate const& delta : getStraightIncrementDeltaCoordinates()) {
        retrieveMovesFromThisByIncrementingDelta(result, startpoint, delta, maxSize);
        CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
    }
}

void Board::retrieveKingOneStepMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Piece pieceAtStart(getPieceAt(startpoint));
    PieceColor opponentsColor(getOppositeColor(pieceAtStart.getColor()));
    for (Coordinate const& delta : getOneStepDeltaCoordinates()) {
        Coordinate endpoint(startpoint + delta);
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));

            if (!areThereAnyAttacksToThis(endpoint, opponentsColor) &&
                (pieceAtEnd.isEmpty() || areOpposingColors(pieceAtStart.getColor(), pieceAtEnd.getColor()))) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            }
        }
    }
}

void Board::retrieveKingCastlingMovesFromThis(Moves& result, Coordinate const& startpoint, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Piece pieceAtStart(getPieceAt(startpoint));
    for (MovePair const& kingAndRookMovePair : getCastlingKingAndRookMovePairs(pieceAtStart.getColor())) {
        Move const& kingMove(kingAndRookMovePair.first);
        Move const& rookMove(kingAndRookMovePair.second);
        if (isCastlingPossible(kingMove, rookMove)) {
            result.emplace_back(kingMove);
            CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
        }
    }
}

void Board::retrieveMovesFromThisByIncrementingDelta(
    Moves& result, Coordinate const& startpoint, Coordinate const& delta, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Coordinate endpoint(startpoint + delta);
    while (true) {
        Piece pieceAtStart(getPieceAt(startpoint));
        if (isCoordinateWithinTheBoard(endpoint)) {
            Piece pieceAtEnd(getPieceAt(endpoint));
            if (pieceAtEnd.isEmpty()) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            } else if (areOpposingColors(pieceAtStart.getColor(), pieceAtEnd.getColor())) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
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

Moves Board::getCandidatesMoves(
    Coordinate const& endpoint, PieceColor const moveColor, PieceType const pieceType) const {
    Moves result;
    Piece pieceAtEnd(getPieceAt(endpoint));
    switch (pieceType) {
        case PieceType::Pawn: {
            if (pieceAtEnd.isEmpty()) {
                retrievePawnReverseNonCapturesToThis(result, endpoint, moveColor, MAX_NUMBER_OF_MOVES);
                retrievePawnEnPassantReverseToThis(result, endpoint, moveColor, MAX_NUMBER_OF_MOVES);
            } else if (areOpposingColors(moveColor, pieceAtEnd.getColor())) {  // capture only
                retrievePawnReverseCapturesToThis(result, endpoint, moveColor, MAX_NUMBER_OF_MOVES);
            }
            break;
        }
        case PieceType::Knight: {
            if (isPieceEmptyOrHasOpposingColors(pieceAtEnd, moveColor)) {  // non capture and capture
                retrieveKnightMovesToThis(result, endpoint, moveColor, MAX_NUMBER_OF_MOVES);
            }
            break;
        }
        case PieceType::Bishop: {
            if (isPieceEmptyOrHasOpposingColors(pieceAtEnd, moveColor)) {  // non capture and capture
                retrieveDiagonalMovesToThis(result, endpoint, moveColor, MAX_NUMBER_OF_MOVES);
            }
            break;
        }
        case PieceType::Rook: {
            if (isPieceEmptyOrHasOpposingColors(pieceAtEnd, moveColor)) {  // non capture and capture
                retrieveStraightMovesToThis(result, endpoint, moveColor, MAX_NUMBER_OF_MOVES);
            }
            break;
        }
        case PieceType::Queen: {
            if (isPieceEmptyOrHasOpposingColors(pieceAtEnd, moveColor)) {  // non capture and capture
                retrieveDiagonalMovesToThis(result, endpoint, moveColor, MAX_NUMBER_OF_MOVES);
                retrieveStraightMovesToThis(result, endpoint, moveColor, MAX_NUMBER_OF_MOVES);
            }
            break;
        }
        case PieceType::King: {
            if (isPieceEmptyOrHasOpposingColors(pieceAtEnd, moveColor)) {  // non capture and capture
                retrieveKingOneStepMovesToThis(result, endpoint, moveColor, MAX_NUMBER_OF_MOVES);
            }
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

void Board::retrieveMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Piece pieceAtEnd(getPieceAt(endpoint));
    if (pieceAtEnd.isEmpty()) {  // non capture only
        retrievePawnReverseNonCapturesToThis(result, endpoint, moveColor, maxSize);
        retrievePawnEnPassantReverseToThis(result, endpoint, moveColor, maxSize);
    } else if (areOpposingColors(moveColor, pieceAtEnd.getColor())) {  // capture only
        retrievePawnReverseCapturesToThis(result, endpoint, moveColor, maxSize);
    }
    if (isPieceEmptyOrHasOpposingColors(pieceAtEnd, moveColor)) {  // non capture and capture
        retrieveAllNonPawnMovesToThis(result, endpoint, moveColor, maxSize);
    }
    // How about castling? It doesnt really make any sense though.
}

void Board::retrieveAttacksToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Piece pieceAtEnd(getPieceAt(endpoint));
    if (isPieceNonEmptyAndHasOpposingColors(pieceAtEnd, moveColor)) {  // capture only
        retrievePawnReverseCapturesToThis(result, endpoint, moveColor, maxSize);
    }
    retrieveAllNonPawnMovesToThis(result, endpoint, moveColor, maxSize);
}

void Board::retrieveAttacksToThisWithNoKingMoves(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Piece pieceAtEnd(getPieceAt(endpoint));
    if (!pieceAtEnd.isEmpty() && areOpposingColors(moveColor, pieceAtEnd.getColor())) {  // capture only
        retrievePawnReverseCapturesToThis(result, endpoint, moveColor, maxSize);
    }
    if (isPieceEmptyOrHasOpposingColors(pieceAtEnd, moveColor)) {  // non capture and capture
        retrieveKnightMovesToThis(result, endpoint, moveColor, maxSize);
        retrieveDiagonalMovesToThis(result, endpoint, moveColor, maxSize);
        retrieveStraightMovesToThis(result, endpoint, moveColor, maxSize);
    }
}

void Board::retrievePawnReverseNonCapturesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    DeltaRange range = getPawnReverseNonCaptureDeltaRange(endpoint, moveColor);
    for (CoordinateDataType deltaY = range.interval; deltaY != range.invalidDelta; deltaY += range.interval) {
        Coordinate startpoint(endpoint.getX(), endpoint.getY() + deltaY);
        Piece pieceAtStart(getPieceAt(startpoint));
        if (moveColor == pieceAtStart.getColor() && PieceType::Pawn == pieceAtStart.getType()) {
            result.emplace_back(startpoint, endpoint);
            CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
        }
    }
}

void Board::retrievePawnReverseCapturesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    for (Coordinate const& delta : getPawnReverseCapturesDeltaCoordinates(moveColor)) {
        Coordinate startpoint = endpoint + delta;
        Piece pieceAtStart(getPieceAt(startpoint));
        if (moveColor == pieceAtStart.getColor() && PieceType::Pawn == pieceAtStart.getType()) {
            result.emplace_back(startpoint, endpoint);
            CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
        }
    }
}

void Board::retrievePawnEnPassantReverseToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == moveColor) {
            if (endpoint.getY() == 2) {
                for (Coordinate const& delta : getPawnReverseCapturesDeltaCoordinates(moveColor)) {
                    Coordinate startpoint = endpoint + delta;
                    Piece pieceAtStart(getPieceAt(startpoint));
                    Piece opponentPawn(getPieceAt({endpoint.getX(), startpoint.getY()}));
                    if (PieceColorAndType::WhitePawn == pieceAtStart.getColorAndType() &&
                        PieceColorAndType::BlackPawn == opponentPawn.getColorAndType()) {
                        result.emplace_back(startpoint, endpoint);
                        CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
                    }
                }
            }
        } else if (PieceColor::Black == moveColor) {
            if (endpoint.getY() == 5) {
                for (Coordinate const& delta : getPawnReverseCapturesDeltaCoordinates(moveColor)) {
                    Coordinate startpoint = endpoint + delta;
                    Piece pieceAtStart(getPieceAt(startpoint));
                    Piece opponentPawn(getPieceAt({endpoint.getX(), startpoint.getY()}));
                    if (PieceColorAndType::BlackPawn == pieceAtStart.getColorAndType() &&
                        PieceColorAndType::WhitePawn == opponentPawn.getColorAndType()) {
                        result.emplace_back(startpoint, endpoint);
                        CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
                    }
                }
            }
        }
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::Black == moveColor) {
            if (endpoint.getY() == 2) {
                for (Coordinate const& delta : getPawnReverseCapturesDeltaCoordinates(moveColor)) {
                    Coordinate startpoint = endpoint + delta;
                    Piece pieceAtStart(getPieceAt(startpoint));
                    Piece opponentPawn(getPieceAt({endpoint.getX(), startpoint.getY()}));
                    if (PieceColorAndType::BlackPawn == pieceAtStart.getColorAndType() &&
                        PieceColorAndType::WhitePawn == opponentPawn.getColorAndType()) {
                        result.emplace_back(startpoint, endpoint);
                        CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
                    }
                }
            }
        } else if (PieceColor::White == moveColor) {
            if (endpoint.getY() == 5) {
                for (Coordinate const& delta : getPawnReverseCapturesDeltaCoordinates(moveColor)) {
                    Coordinate startpoint = endpoint + delta;
                    Piece pieceAtStart(getPieceAt(startpoint));
                    Piece opponentPawn(getPieceAt({endpoint.getX(), startpoint.getY()}));
                    if (PieceColorAndType::WhitePawn == pieceAtStart.getColorAndType() &&
                        PieceColorAndType::BlackPawn == opponentPawn.getColorAndType()) {
                        result.emplace_back(startpoint, endpoint);
                        CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
                    }
                }
            }
        }
    }
}

void Board::retrieveAllNonPawnMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    retrieveKnightMovesToThis(result, endpoint, moveColor, maxSize);
    retrieveDiagonalMovesToThis(result, endpoint, moveColor, maxSize);
    retrieveStraightMovesToThis(result, endpoint, moveColor, maxSize);
    retrieveKingOneStepMovesToThis(result, endpoint, moveColor, maxSize);
}

void Board::retrieveKnightMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    for (Coordinate const& delta : getLDeltaCoordinates()) {
        Coordinate startpoint = endpoint + delta;
        Piece pieceAtStart(getPieceAt(startpoint));
        if (moveColor == pieceAtStart.getColor() && PieceType::Knight == pieceAtStart.getType()) {
            result.emplace_back(startpoint, endpoint);
            CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
        }
    }
}

void Board::retrieveDiagonalMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    for (Coordinate const& delta : getDiagonalIncrementDeltaCoordinates()) {
        Coordinate startpoint = endpoint + delta;
        while (isCoordinateWithinTheBoard(startpoint)) {
            Piece pieceAtStart(getPieceAt(startpoint));
            if (!pieceAtStart.isEmpty()) {
                if (moveColor == pieceAtStart.getColor() &&
                    (PieceType::Bishop == pieceAtStart.getType() || PieceType::Queen == pieceAtStart.getType())) {
                    result.emplace_back(startpoint, endpoint);
                    CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
                }
                break;
            }
            startpoint += delta;
        }
    }
}

void Board::retrieveStraightMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    for (Coordinate const& delta : getStraightIncrementDeltaCoordinates()) {
        Coordinate startpoint = endpoint + delta;
        while (isCoordinateWithinTheBoard(startpoint)) {
            Piece pieceAtStart(getPieceAt(startpoint));
            if (!pieceAtStart.isEmpty()) {
                if (moveColor == pieceAtStart.getColor() &&
                    (PieceType::Rook == pieceAtStart.getType() || PieceType::Queen == pieceAtStart.getType())) {
                    result.emplace_back(startpoint, endpoint);
                    CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
                }
                break;
            }
            startpoint += delta;
        }
    }
}

void Board::retrieveKingOneStepMovesToThis(
    Moves& result, Coordinate const& endpoint, PieceColor const moveColor, int const maxSize) const {
    CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED
    Moves attacksToThisCell;
    retrieveAttacksToThisWithNoKingMoves(attacksToThisCell, endpoint, getOppositeColor(moveColor), 1);
    if (attacksToThisCell.empty()) {
        for (Coordinate const& delta : getOneStepDeltaCoordinates()) {
            Coordinate startpoint = endpoint + delta;
            Piece pieceAtStart(getPieceAt(startpoint));
            if (moveColor == pieceAtStart.getColor() && PieceType::King == pieceAtStart.getType()) {
                result.emplace_back(startpoint, endpoint);
                CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
            }
        }
    }
}

void Board::retrievePawnAttackDefendCountToThis(AttackDefendCount& count, Coordinate const& endpoint) const {
    Piece pieceAtEnd(getPieceAt(endpoint));
    PieceColor sameColor(pieceAtEnd.getColor());
    PieceColor oppositeColor(getOppositeColor(pieceAtEnd.getColor()));
    for (Coordinate const& delta : getPawnReverseCapturesDeltaCoordinates(sameColor)) {
        Coordinate startpoint = endpoint + delta;
        Piece pieceAtStart(getPieceAt(startpoint));
        if (PieceType::Pawn == pieceAtStart.getType() && sameColor == pieceAtStart.getColor()) {
            count.defend++;
        }
    }
    for (Coordinate const& delta : getPawnReverseCapturesDeltaCoordinates(oppositeColor)) {
        Coordinate startpoint = endpoint + delta;
        Piece pieceAtStart(getPieceAt(startpoint));
        if (PieceType::Pawn == pieceAtStart.getType() && oppositeColor == pieceAtStart.getColor()) {
            count.attack++;
        }
    }
}

void Board::retrieveKnightAttackDefendCountToThis(AttackDefendCount& count, Coordinate const& endpoint) const {
    Piece pieceAtEnd(getPieceAt(endpoint));
    PieceColor sameColor(pieceAtEnd.getColor());
    PieceColor oppositeColor(getOppositeColor(pieceAtEnd.getColor()));
    for (Coordinate const& delta : getLDeltaCoordinates()) {
        Coordinate startpoint = endpoint + delta;
        Piece pieceAtStart(getPieceAt(startpoint));
        if (PieceType::Knight == pieceAtStart.getType()) {
            updateAttackDefendCount(count, pieceAtStart.getColor(), sameColor, oppositeColor);
        }
    }
}

void Board::retrieveDiagonalAttackDefendCountToThis(
    AttackDefendCount& bishopCount, AttackDefendCount& queenCount, Coordinate const& endpoint) const {
    Piece pieceAtEnd(getPieceAt(endpoint));
    PieceColor sameColor(pieceAtEnd.getColor());
    PieceColor oppositeColor(getOppositeColor(pieceAtEnd.getColor()));
    for (Coordinate const& delta : getDiagonalIncrementDeltaCoordinates()) {
        Coordinate startpoint = endpoint + delta;
        while (isCoordinateWithinTheBoard(startpoint)) {
            Piece pieceAtStart(getPieceAt(startpoint));
            if (!pieceAtStart.isEmpty()) {
                if (PieceType::Bishop == pieceAtStart.getType()) {
                    updateAttackDefendCount(bishopCount, pieceAtStart.getColor(), sameColor, oppositeColor);
                } else if (PieceType::Queen == pieceAtStart.getType()) {
                    updateAttackDefendCount(queenCount, pieceAtStart.getColor(), sameColor, oppositeColor);
                } else {
                    break;
                }
            }
            startpoint += delta;
        }
    }
}

void Board::retrieveStraightAttackDefendCountToThis(
    AttackDefendCount& rookCount, AttackDefendCount& queenCount, Coordinate const& endpoint) const {
    Piece pieceAtEnd(getPieceAt(endpoint));
    PieceColor sameColor(pieceAtEnd.getColor());
    PieceColor oppositeColor(getOppositeColor(pieceAtEnd.getColor()));
    for (Coordinate const& delta : getStraightIncrementDeltaCoordinates()) {
        Coordinate startpoint = endpoint + delta;
        while (isCoordinateWithinTheBoard(startpoint)) {
            Piece pieceAtStart(getPieceAt(startpoint));
            if (!pieceAtStart.isEmpty()) {
                if (PieceType::Rook == pieceAtStart.getType()) {
                    updateAttackDefendCount(rookCount, pieceAtStart.getColor(), sameColor, oppositeColor);
                } else if (PieceType::Queen == pieceAtStart.getType()) {
                    updateAttackDefendCount(queenCount, pieceAtStart.getColor(), sameColor, oppositeColor);
                } else {
                    break;
                }
            }
            startpoint += delta;
        }
    }
}

void Board::retrieveKingOneStepAttackDefendCountToThis(AttackDefendCount& count, Coordinate const& endpoint) const {
    Piece pieceAtEnd(getPieceAt(endpoint));
    PieceColor sameColor(pieceAtEnd.getColor());
    PieceColor oppositeColor(getOppositeColor(pieceAtEnd.getColor()));
    for (Coordinate const& delta : getOneStepDeltaCoordinates()) {
        Coordinate startpoint = endpoint + delta;
        Piece pieceAtStart(getPieceAt(startpoint));
        if (PieceType::King == pieceAtStart.getType()) {
            updateAttackDefendCount(count, pieceAtStart.getColor(), sameColor, oppositeColor);
        }
    }
}

Board::NotationDetailsOfMove Board::determineNotationDetailsOfMove(string const& textInAlgebraicNotation) const {
    NotationDetailsOfMove result{};
    enum class State { LastY, LastX, Capture, FirstY, FirstX, PiecePart, Finish };

    State state(State::LastY);
    for (auto it = textInAlgebraicNotation.crbegin(); it != textInAlgebraicNotation.crend();) {
        char c = *it;
        switch (state) {
            case State::LastY: {
                if (is1To8(c)) {
                    result.lastY = getYInCorrectOrientation(c - '1');
                    state = State::LastX;
                }
                it++;
                break;
            }
            case State::LastX: {
                if (isAToH(c)) {
                    result.lastX = getXInCorrectOrientation(c - 'a');
                    it++;
                }
                state = State::Capture;
                break;
            }
            case State::Capture: {
                if (c == 'x') {
                    it++;
                }
                state = State::FirstY;
                break;
            }
            case State::FirstY: {
                if (is1To8(c)) {
                    result.firstY = getYInCorrectOrientation(c - '1');
                    it++;
                }
                state = State::FirstX;
                break;
            }
            case State::FirstX: {
                if (isAToH(c)) {
                    result.firstX = getXInCorrectOrientation(c - 'a');
                    it++;
                }
                state = State::PiecePart;
                break;
            }
            case State::PiecePart: {
                switch (c) {
                    case 'N':
                        result.pieceType = PieceType::Knight;
                        break;
                    case 'B':
                        result.pieceType = PieceType::Bishop;
                        break;
                    case 'R':
                        result.pieceType = PieceType::Rook;
                        break;
                    case 'Q':
                        result.pieceType = PieceType::Queen;
                        break;
                    case 'K':
                        result.pieceType = PieceType::King;
                        break;
                    default:
                        result.pieceType = PieceType::Pawn;
                        break;
                }
                state = State::Finish;
                break;
            }
            case State::Finish: {
                it = textInAlgebraicNotation.crend();
                break;
            }
        }
    }
    if (result.pieceType == PieceType::Empty) {
        result.pieceType = PieceType::Pawn;
    }
    return result;
}

MovePairs Board::getCastlingKingAndRookMovePairs(PieceColor const moveColor) const {
    MovePairs result;
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::Black == moveColor) {
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
        } else if (PieceColor::White == moveColor) {
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
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == moveColor) {
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
        } else if (PieceColor::Black == moveColor) {
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

Move Board::getCastleMove(CastleType const castleType, PieceColor const moveColor) const {
    Move result{};
    CoordinateDataType rookMoveDistance = CastleType::KingSideCastle == castleType    ? 2
                                          : CastleType::QueenSideCastle == castleType ? 3
                                                                                      : 0;
    MovePairs castlingPairs(getCastlingKingAndRookMovePairs(moveColor));
    for (MovePair const& castlingPair : castlingPairs) {
        Move const& kingMove(castlingPair.first);
        Move const& rookMove(castlingPair.second);
        if (getPositiveDelta(rookMove.first.getX(), rookMove.second.getX()) == rookMoveDistance) {
            result = kingMove;
        }
    }
    return result;
}

Move Board::getNonCastleMoveWithAlgebraicNotation(
    string const& textInAlgebraicNotation, PieceColor const moveColor) const {
    Move result{};
    NotationDetailsOfMove details(determineNotationDetailsOfMove(textInAlgebraicNotation));
    if (details.lastX && details.lastY) {
        // last are prioritized because its reversed
        Coordinate endpoint(details.lastX.value(), details.lastY.value());
        if (details.firstX && details.firstY) {
            Move candidateMove{{details.firstX.value(), details.firstY.value()}, endpoint};
            if (isAPossibleMove(candidateMove)) {
                result = candidateMove;
            }
        } else {
            Moves candidateMoves(getCandidatesMoves(endpoint, moveColor, details.pieceType));
            result = getFirstMoveThatFits(candidateMoves, details.pieceType, details.firstX, details.firstY);
        }
    }
    return result;
}

Move Board::getFirstMoveThatFits(
    Moves const& possibleMoves, PieceType const pieceType, optional<CoordinateDataType> const& xLimitation,
    optional<CoordinateDataType> const& yLimitation) const {
    Move result{};
    for (Move const& possibleMove : possibleMoves) {
        Piece pieceAtStart(getPieceAt(possibleMove.first));
        if (pieceType == pieceAtStart.getType()) {
            if (xLimitation) {
                if (xLimitation.value() == possibleMove.first.getX()) {
                    result = possibleMove;
                    break;
                }
            } else if (yLimitation) {
                if (yLimitation.value() == possibleMove.first.getY()) {
                    result = possibleMove;
                    break;
                }
            } else {
                result = possibleMove;
                break;
            }
        }
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

Board::DeltaRange Board::getPawnNonCaptureDeltaRange(Coordinate const& startpoint, PieceColor const moveColor) const {
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == moveColor) {
            if (6 == startpoint.getY()) {
                return DeltaRange{-1, -3};
            } else {
                return DeltaRange{-1, -2};
            }
        } else if (PieceColor::Black == moveColor) {
            if (1 == startpoint.getY()) {
                return DeltaRange{1, 3};
            } else {
                return DeltaRange{1, 2};
            }
        }
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == moveColor) {
            if (1 == startpoint.getY()) {
                return DeltaRange{1, 3};
            } else {
                return DeltaRange{1, 2};
            }
        } else if (PieceColor::Black == moveColor) {
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
    Coordinate const& endpoint, PieceColor const moveColor) const {
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == moveColor) {
            if (4 == endpoint.getY()) {
                return DeltaRange{1, 3};
            } else {
                return DeltaRange{1, 2};
            }
        } else if (PieceColor::Black == moveColor) {
            if (3 == endpoint.getY()) {
                return DeltaRange{-1, -3};
            } else {
                return DeltaRange{-1, -2};
            }
        }
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == moveColor) {
            if (3 == endpoint.getY()) {
                return DeltaRange{-1, -3};
            } else {
                return DeltaRange{-1, -2};
            }
        } else if (PieceColor::Black == moveColor) {
            if (4 == endpoint.getY()) {
                return DeltaRange{1, 3};
            } else {
                return DeltaRange{1, 2};
            }
        }
    }
    return {};
}

Coordinates Board::getPawnCapturesDeltaCoordinates(PieceColor const moveColor) const {
    Coordinates result;
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == moveColor) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        } else if (PieceColor::Black == moveColor) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        }
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == moveColor) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        } else if (PieceColor::Black == moveColor) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        }
    }
    return result;
}

Coordinates Board::getPawnReverseCapturesDeltaCoordinates(PieceColor const moveColor) const {
    Coordinates result;
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        if (PieceColor::White == moveColor) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        } else if (PieceColor::Black == moveColor) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        }
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        if (PieceColor::White == moveColor) {
            result.emplace_back(-1, -1);
            result.emplace_back(1, -1);
        } else if (PieceColor::Black == moveColor) {
            result.emplace_back(-1, 1);
            result.emplace_back(1, 1);
        }
    }
    return result;
}

Coordinate Board::getCoordinateFromGridIndex(int const gridIndex) const {
    return Coordinate{gridIndex % CHESS_SIDE_SIZE, gridIndex / CHESS_SIDE_SIZE};
}

Coordinate Board::getCorrectCoordinateFromAlgebraicNotation(
    CoordinateDataType const x, CoordinateDataType const y) const {
    Coordinate result{};
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        result = Coordinate(x, reverse(y));
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        result = Coordinate(reverse(x), y);
    }
    return result;
}

CoordinateDataType Board::getXInCorrectOrientation(CoordinateDataType const x) const {
    CoordinateDataType result{};
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        result = x;
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        result = reverse(x);
    }
    return result;
}

CoordinateDataType Board::getYInCorrectOrientation(CoordinateDataType const y) const {
    CoordinateDataType result{};
    if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
        result = reverse(y);
    } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
        result = y;
    }
    return result;
}

CoordinateDataType Board::reverse(CoordinateDataType const value) const { return 7 - value; }

CoordinateDataType Board::getOneIncrement(CoordinateDataType const coordinateDataType) const {
    return coordinateDataType > 0 ? 1 : coordinateDataType < 0 ? -1 : 0;
}

Board::CastleType Board::getCastleTypeWithAlgebraicNotation(string const& textInAlgebraicNotation) const {
    return textInAlgebraicNotation == "O-O"     ? CastleType::KingSideCastle
           : textInAlgebraicNotation == "O-O-O" ? CastleType::QueenSideCastle
                                                : CastleType::NotACastle;
}

int Board::getGridIndex(int x, int y) const { return (y * CHESS_SIDE_SIZE) + x; }

int Board::getNumberOfWaysToBlockPath(
    Coordinate const& startpoint, Coordinate const& endpoint, PieceColor const blockingPieceColor,
    int const maxSize) const {
    int result{};
    Coordinate moveDelta = endpoint - startpoint;
    Coordinate oneIncrementDelta(getOneIncrement(moveDelta.getX()), getOneIncrement(moveDelta.getY()));
    Coordinate cellInBetween = startpoint + oneIncrementDelta;
    while (isCoordinateWithinTheBoard(cellInBetween) && endpoint != cellInBetween) {
        cellInBetween += oneIncrementDelta;
        result += getMovesToThis(cellInBetween, blockingPieceColor, maxSize - result).size();
    }
    return result;
}

bool Board::isPieceEmptyOrHasOpposingColors(Piece const& piece, PieceColor const color) const {
    return piece.isEmpty() || areOpposingColors(color, piece.getColor());
}

bool Board::isPieceNonEmptyAndHasOpposingColors(Piece const& piece, PieceColor const color) const {
    return !piece.isEmpty() && areOpposingColors(color, piece.getColor());
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
    return isAPawnNonCaptureMove(move) || isAPawnCapture(move) || isAPawnEnPassantMove(move);
}

bool Board::isPossibleKnightMove(Move const& move) const {
    return isEndpointEmptyOrHaveDifferentColors(move) && isAnLMove(move);
}

bool Board::isPossibleBishopMove(Move const& move) const {
    return isEndpointEmptyOrHaveDifferentColors(move) && isADiagonalMove(move) && isThereNoPieceInBetween(move);
}

bool Board::isPossibleRookMove(Move const& move) const {
    return isEndpointEmptyOrHaveDifferentColors(move) && isAStraightMove(move) && isThereNoPieceInBetween(move);
}

bool Board::isPossibleQueenMove(Move const& move) const {
    return isEndpointEmptyOrHaveDifferentColors(move) && (isADiagonalMove(move) || isAStraightMove(move)) &&
           isThereNoPieceInBetween(move);
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
    return kingAndRookCastlingMovePair.first == move && isCastlingPossible(kingMove, rookMove);
}

bool Board::isAPawnNonCaptureMove(Move const& move) const {
    bool result(false);
    if (move.first.getX() == move.second.getX()) {
        Piece pieceAtStart(getPieceAt(move.first));
        Piece pieceAtEnd(getPieceAt(move.second));
        if (pieceAtEnd.isEmpty() && isThereNoPieceInBetween(move)) {
            Coordinate moveDelta = move.second - move.first;
            DeltaRange range = getPawnNonCaptureDeltaRange(move.first, pieceAtStart.getColor());
            for (CoordinateDataType deltaY = range.interval; deltaY != range.invalidDelta; deltaY += range.interval) {
                if (deltaY == moveDelta.getY()) {
                    result = true;
                    break;
                }
            }
        }
    }
    return result;
}

bool Board::isAPawnCapture(Move const& move) const {
    bool result(false);
    Piece pieceAtStart(getPieceAt(move.first));
    Piece pieceAtEnd(getPieceAt(move.second));
    Coordinate moveDelta = move.second - move.first;
    if (!pieceAtEnd.isEmpty() && areOpposingColors(pieceAtStart.getColor(), pieceAtEnd.getColor())) {
        Coordinates pawnCaptureDeltas(getPawnCapturesDeltaCoordinates(pieceAtStart.getColor()));
        result = any_of(
            pawnCaptureDeltas.cbegin(), pawnCaptureDeltas.cend(),
            [&moveDelta](Coordinate const& pawnDelta) { return moveDelta == pawnDelta; });
    }
    return result;
}

bool Board::isAPawnEnPassantMove(Move const& move) const {
    bool result(false);
    Piece pieceAtStart(getPieceAt(move.first));
    Piece pieceAtEnd(getPieceAt(move.second));
    if (pieceAtEnd.isEmpty() && getPositiveDelta(move.first.getX(), move.second.getX()) == 1) {
        if (BoardOrientation::BlackUpWhiteDown == m_orientation) {
            if (PieceColor::White == pieceAtStart.getColor()) {
                if (move.first.getY() == 3 && move.first.getY() - move.second.getY() == 1) {
                    Piece opponentPawn(getPieceAt({move.second.getX(), move.first.getY()}));
                    result = opponentPawn.getColorAndType() == PieceColorAndType::BlackPawn;
                }
            } else if (PieceColor::Black == pieceAtStart.getColor()) {
                if (move.first.getY() == 4 && move.second.getY() - move.first.getY() == 1) {
                    Piece opponentPawn(getPieceAt({move.second.getX(), move.first.getY()}));
                    result = opponentPawn.getColorAndType() == PieceColorAndType::WhitePawn;
                }
            }
        } else if (BoardOrientation::WhiteUpBlackDown == m_orientation) {
            if (PieceColor::Black == pieceAtStart.getColor()) {
                if (move.first.getY() == 3 && move.first.getY() - move.second.getY() == 1) {
                    Piece opponentPawn(getPieceAt({move.second.getX(), move.first.getY()}));
                    result = opponentPawn.getColorAndType() == PieceColorAndType::WhitePawn;
                }
            } else if (PieceColor::White == pieceAtStart.getColor()) {
                if (move.first.getY() == 4 && move.second.getY() - move.first.getY() == 1) {
                    Piece opponentPawn(getPieceAt({move.second.getX(), move.first.getY()}));
                    result = opponentPawn.getColorAndType() == PieceColorAndType::BlackPawn;
                }
            }
        }
    }
    return result;
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

bool Board::isCastlingPossible(Move const& kingMove, Move const& rookMove) const {
    return getPieceAt(kingMove.second).isEmpty() && getPieceAt(rookMove.second).isEmpty() &&
           !canBeCaptured(kingMove.first) && isSafeToCastleInBetween(kingMove.first, rookMove.first);
}

bool Board::isEndpointEmptyOrHaveDifferentColors(Move const& move) const {
    Piece pieceAtStart(getPieceAt(move.first));
    Piece pieceAtEnd(getPieceAt(move.second));
    return pieceAtEnd.isEmpty() || (!pieceAtStart.isEmpty() && !pieceAtEnd.isEmpty() &&
                                    areOpposingColors(pieceAtStart.getColor(), pieceAtEnd.getColor()));
}

bool Board::isThereNoPieceInBetween(Move const& move) const {
    return doesAllCellsInBetweenSatisfyTheCondition(
        move.first, move.second, [&](Coordinate const& cellInBetween) { return getPieceAt(cellInBetween).isEmpty(); });
}

bool Board::isSafeToCastleInBetween(Coordinate const& startpoint, Coordinate const& endpoint) const {
    PieceColor opponentsColor = getOppositeColor(getPieceAt(startpoint).getColor());
    return doesAllCellsInBetweenSatisfyTheCondition(startpoint, endpoint, [&](Coordinate const& cellInBetween) {
        return getPieceAt(cellInBetween).isEmpty() && !areThereAnyAttacksToThis(cellInBetween, opponentsColor);
    });
}

bool Board::doesAllCellsInBetweenSatisfyTheCondition(
    Coordinate const& startpoint, Coordinate const& endpoint, CoordinateCondition const& condition) const {
    Coordinate moveDelta = endpoint - startpoint;
    Coordinate oneIncrementDelta(getOneIncrement(moveDelta.getX()), getOneIncrement(moveDelta.getY()));
    Coordinate cellInBetween = startpoint + oneIncrementDelta;
    while (isCoordinateWithinTheBoard(cellInBetween) && endpoint != cellInBetween && condition(cellInBetween)) {
        cellInBetween += oneIncrementDelta;
    }
    return cellInBetween == endpoint;
}

void Board::updateAttackDefendCount(
    Board::AttackDefendCount& count, PieceColor const pieceColor, PieceColor const sameColor,
    PieceColor oppositeColor) const {
    if (sameColor == pieceColor) {
        count.defend++;
    } else if (oppositeColor == pieceColor) {
        count.attack++;
    }
}

void Board::changePieceGridWithMove(Move const& move) {
    setPieceAt(move.second, getPieceAt(move.first));
    setPieceAt(move.first, {});
}

#undef CHESS_UTILITIES_BOARD_QUICK_BREAK_IN_LOOP_IF_MAX_SIZE_IS_REACHED
#undef CHESS_UTILITIES_BOARD_QUICK_RETURN_IF_MAX_SIZE_IS_REACHED

}  // namespace chess

}  // namespace alba
