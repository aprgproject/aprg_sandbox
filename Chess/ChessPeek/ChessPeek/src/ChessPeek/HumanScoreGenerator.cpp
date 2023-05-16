#include "HumanScoreGenerator.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
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

uint32_t HumanScoreGenerator::getHumanScore(MoveDetail const& moveDetail) const {
    // Format: SSSS SSSS HHHH HHHH MMMM KKKK KKKK PPPP

    return getScoreLevelPart(moveDetail) << 24 | getHangingPieceValuePart(moveDetail.move) << 16 |
           getMoveTypePart(moveDetail.move) << 12 | getDistanceToKingPart(moveDetail.move) << 4 |
           getPiecePart(moveDetail.move);
}

uint32_t HumanScoreGenerator::getScoreLevelPart(MoveDetail const& moveDetail) const {
    uint32_t result = 0;
    if (moveDetail.mate > 0) {
        if (m_bestScore > LOWER_LIMIT_FOR_WINNING) {
            result = m_highestScoreLevel;  // put mate as same level as best moves if winning (to be human)
        } else {
            result = m_highestScoreLevel + 1;  // put it above than highest score level if losing
        }
    } else if (moveDetail.mate < 0) {
        result = 0;  // lowest score level (avoid to be mated as much as possible)
    } else {
        result =
            static_cast<uint32_t>(m_highestScoreLevel - ((m_bestScore - moveDetail.score) / getScoreLevelDistance()));
    }
    if (result > 0xFF) {
        result = 0xFF;
    }
    return result;
}

uint32_t HumanScoreGenerator::getHangingPieceValuePart(Move const& move) const {
    Board const& board(m_boardWithContext.getBoard());
    Piece pieceAtStart = board.getPieceAt(move.first);
    Piece pieceAtEnd = board.getPieceAt(move.second);
    Board boardAfterMove(m_boardWithContext.getBoard());
    boardAfterMove.move(move);
    int hangingValue = boardAfterMove.getTotalHangingPieceValue(m_boardWithContext.getPlayerColor());
    if (isACaptureMove(pieceAtStart, pieceAtEnd)) {
        hangingValue -= getValueOfPieceType(pieceAtEnd.getType());
    }
    if (hangingValue < 0) {
        hangingValue = 0;
    }
    if (hangingValue > 0xFF) {
        hangingValue = 0xFF;
    }
    return 0xFF - static_cast<uint32_t>(hangingValue);  // reverse sorted
}

uint32_t HumanScoreGenerator::getMoveTypePart(Move const& move) const {
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

uint32_t HumanScoreGenerator::getDistanceToKingPart(Move const& move) const {
    constexpr int MAX_DISTANCE_SQUARED_IN_BOARD = 98;
    int reverseDistance = MAX_DISTANCE_SQUARED_IN_BOARD - getDistanceToKing(move.second);
    return static_cast<uint32_t>(reverseDistance) & 0xFF;
}

uint32_t HumanScoreGenerator::getPiecePart(Move const& move) const {
    return getHumanScoreOfPiece(m_boardWithContext.getBoard().getPieceAt(move.first).getType()) & 0xF;
}

uint32_t HumanScoreGenerator::getHumanScoreOfPiece(PieceType const pieceType) const {
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
    // Note the y axis is reversed so it should be first minus second
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
