#include "HumanScoreGenerator.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

HumanScoreGenerator::HumanScoreGenerator(
    BoardWithContext const& boardWithContext, int const worstScore, int const bestScore)
    : m_boardWithContext(boardWithContext),
      m_worstScore(worstScore),
      m_bestScore(bestScore),
      m_highestScoreLevel((m_bestScore - m_worstScore) / getScoreLevelDistance()) {}

HumanScoreGenerator::Score HumanScoreGenerator::getHumanScore(MoveDetail const& moveDetail) const {
    // Format: 0000 0000 0000 0000 SSSS SSSS SSSS HHHH HHHH HHHH MMMM KKKK KKKK CCCC CCCC CCCC

    DataFromExchanges dataFromExchanges(getDataFromExchanges(moveDetail.move));
    return getScoreLevelPart(moveDetail) << 36 | dataFromExchanges.hangingValue << 24 |
           getMoveTypePart(moveDetail.move) << 20 | getDistanceToKingPart(moveDetail.move) << 12 |
           dataFromExchanges.complicatedScore;
}

HumanScoreGenerator::Score HumanScoreGenerator::getScoreLevelPart(MoveDetail const& moveDetail) const {    int scoreLevel = 0;
    if (moveDetail.mate > 0) {
        if (m_bestScore > LOWER_LIMIT_FOR_WINNING) {
            scoreLevel = m_highestScoreLevel;  // put mate as same level as best moves if winning (to be human)        } else {
            scoreLevel = m_highestScoreLevel + 1;  // put it above than highest score level if losing
        }
    } else if (moveDetail.mate < 0) {
        scoreLevel = 0;  // lowest score level (avoid to be mated as much as possible)
    } else {
        scoreLevel = static_cast<HumanScoreGenerator::Score>(
            m_highestScoreLevel - ((m_bestScore - moveDetail.score) / getScoreLevelDistance()));
    }
    return static_cast<HumanScoreGenerator::Score>(clampWithin(scoreLevel, 0, 0xFFF));
}

HumanScoreGenerator::DataFromExchanges HumanScoreGenerator::getDataFromExchanges(Move const& move) const {
    Board const& board(m_boardWithContext.getBoard());
    Piece pieceAtStart = board.getPieceAt(move.first);
    Piece pieceAtEnd = board.getPieceAt(move.second);
    Board boardAfterMove(m_boardWithContext.getBoard());
    boardAfterMove.move(move);

    int hangingValue = isACaptureMove(pieceAtStart, pieceAtEnd) ? -getValueOfPieceType(pieceAtEnd.getType()) : 0;
    int complicatedScore = 0;
    for (int j = 0; j < Board::CHESS_SIDE_SIZE; j++) {
        for (int i = 0; i < Board::CHESS_SIDE_SIZE; i++) {
            Coordinate coordinate{i, j};
            Piece piece(boardAfterMove.getPieceAt(coordinate));
            Exchange exchange(boardAfterMove.getExchangeAt(coordinate));
            if (piece.getColor() == m_boardWithContext.getPlayerColor()) {
                if (exchange.getValue() < 0) {
                    hangingValue += getValueOfPieceType(piece.getType());
                }
            }
            complicatedScore += exchange.getCount();
        }
    }
    hangingValue = 0x8FF - hangingValue;          // reverse sorted and midpoint at 0x8F
    complicatedScore = 0xFFF - complicatedScore;  // reverse sorted

    return DataFromExchanges{
        static_cast<HumanScoreGenerator::Score>(clampWithin(hangingValue, 0, 0xFFF)),
        static_cast<HumanScoreGenerator::Score>(complicatedScore)};
}

HumanScoreGenerator::Score HumanScoreGenerator::getMoveTypePart(Move const& move) const {
    Board const& board(m_boardWithContext.getBoard());
    Piece pieceAtStart = board.getPieceAt(move.first);
    Piece pieceAtEnd = board.getPieceAt(move.second);
    if (isSameValueExchange(pieceAtStart, pieceAtEnd)) {
        return 0;  // avoid same value exchanges
    } else if (isCastlingMove(pieceAtStart, move)) {
        return 4;  // prioritize checks to be castling
    } else if (isDevelopingMove(pieceAtStart, move)) {
        return 3;  // prioritize developing moves
    } else if (isCheck(pieceAtEnd)) {
        return 2;  // prioritize checks to be human
    } else {
        return 1;
    }
}

HumanScoreGenerator::Score HumanScoreGenerator::getDistanceToKingPart(Move const& move) const {
    constexpr int MAX_DISTANCE_SQUARED_IN_BOARD = 98;
    int reverseDistance = MAX_DISTANCE_SQUARED_IN_BOARD - getDistanceToKing(move.second);
    return static_cast<HumanScoreGenerator::Score>(reverseDistance) & 0xFF;
}

HumanScoreGenerator::Score HumanScoreGenerator::getPiecePart(Move const& move) const {
    return getHumanScoreOfPiece(m_boardWithContext.getBoard().getPieceAt(move.first).getType()) & 0xF;
}

HumanScoreGenerator::Score HumanScoreGenerator::getHumanScoreOfPiece(PieceType const pieceType) const {
    int result{};
    switch (pieceType) {
        case PieceType::Pawn: {
            result = 2;
            break;
        }
        case PieceType::Knight: {
            result = 3;
            break;
        }
        case PieceType::Bishop: {
            result = 4;
            break;
        }
        case PieceType::Rook: {
            result = 5;
            break;
        }
        case PieceType::Queen: {
            result = 6;
            break;
        }
        case PieceType::King: {
            result = 1;
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

int HumanScoreGenerator::getDistanceToKing(Coordinate const& coordinate) const {
    Coordinate deltaToKing = m_boardWithContext.getOpponentsKingCoordinate() - coordinate;
    return (deltaToKing.getX() * deltaToKing.getX() + deltaToKing.getY() * deltaToKing.getY());
}

int HumanScoreGenerator::getScoreLevelDistance() const {
    if (m_bestScore > LOWER_LIMIT_FOR_WINNING) {
        return SCORE_LEVEL_DISTANCE_WHEN_WINNING;
    } else if (m_bestScore > LOWER_LIMIT_FOR_SLIGHTLY_BETTER) {
        return SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_BETTER;
    } else if (m_bestScore > LOWER_LIMIT_FOR_EQUAL) {
        return SCORE_LEVEL_DISTANCE_WHEN_EQUAL;
    } else if (m_bestScore > LOWER_LIMIT_FOR_SLIGHTLY_WORSE) {
        return SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_WORSE;
    } else {
        return SCORE_LEVEL_DISTANCE_WHEN_LOSING;
    }
}

bool HumanScoreGenerator::isACaptureMove(Piece const pieceAtStart, Piece const pieceAtEnd) const {
    return !pieceAtStart.isEmpty() && !pieceAtEnd.isEmpty();
}

bool HumanScoreGenerator::isSameValueExchange(Piece const pieceAtStart, Piece const pieceAtEnd) const {
    return isACaptureMove(pieceAtStart, pieceAtEnd) &&
           getValueOfPieceType(pieceAtStart.getType()) == getValueOfPieceType(pieceAtEnd.getType());
}

bool HumanScoreGenerator::isDevelopingMove(Piece const pieceAtStart, Move const& move) const {
    return PieceType::Pawn != pieceAtStart.getType() && PieceType::King != pieceAtStart.getType() &&
           getDistanceToKing(move.first) > getDistanceToKing(move.second);
}

bool HumanScoreGenerator::isCastlingMove(Piece const pieceAtStart, Move const& move) const {
    return PieceType::King == pieceAtStart.getType() && getPositiveDelta(move.first.getX(), move.second.getX()) == 2;
}

bool HumanScoreGenerator::isCheck(Piece const pieceAtEnd) const { return PieceType::King == pieceAtEnd.getType(); }

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
