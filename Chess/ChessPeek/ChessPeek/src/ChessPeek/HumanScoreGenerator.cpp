#include "HumanScoreGenerator.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

HumanScoreGenerator::HumanScoreGenerator(
    BoardWithContext const& boardWithContext, int const bestScore, int const worstScore)
    : m_boardWithContext(boardWithContext),
      m_bestScore(bestScore),
      m_worstScore(worstScore),
      m_maxScoreLevel((m_bestScore - m_worstScore) / SCORE_LEVEL_DISTANCE) {}

uint32_t HumanScoreGenerator::getHumanScore(MoveDetail const& moveDetail) const {
    // Format: 0000 SSSS SSSS SSSS TTTT KKKK KKKK PPPP
    return getScoreLevelPart(moveDetail) << 16 | getMoveTypePart(moveDetail.move) << 12 |
           getDistanceToKingPart(moveDetail.move) << 4 | getPiecePart(moveDetail.move);
}

uint32_t HumanScoreGenerator::getScoreLevelPart(MoveDetail const& moveDetail) const {
    if (moveDetail.mate > 0) {
        return m_maxScoreLevel;  // put mate as same level as best moves (to be human)
    } else if (moveDetail.mate < 0) {
        return 0;  // worst score (avoid to be mated as much as possible)
    } else {
        return static_cast<uint32_t>(m_maxScoreLevel - ((m_bestScore - moveDetail.score) / SCORE_LEVEL_DISTANCE)) &
               0xFFF;
    }
}

uint32_t HumanScoreGenerator::getMoveTypePart(Move const& move) const {
    Board const& board(m_boardWithContext.getBoard());
    PieceType pieceAtStart = board.getPieceAt(move.first).getType();
    PieceType pieceAtEnd = board.getPieceAt(move.second).getType();
    if (isSameValueExchange(pieceAtStart, pieceAtEnd)) {
        return 0;  // avoid same value exchanges
    } else if (isDevelopingMove(pieceAtStart, move)) {
        return 3;  // prioritize developing moves
    } else if (isCheck(pieceAtEnd)) {
        return 2;  // prioritize checks to be human
    } else {
        return 1;
    }
}

uint32_t HumanScoreGenerator::getDistanceToKingPart(Move const& move) const {
    Coordinate delta = m_boardWithContext.getOpponentsKingCoordinate() - move.second;
    constexpr int MAX_DISTANCE_SQUARED_IN_BOARD = 98;
    int reverseDistance = MAX_DISTANCE_SQUARED_IN_BOARD - (delta.getX() * delta.getX() + delta.getY() * delta.getY());
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

bool HumanScoreGenerator::isSameValueExchange(PieceType const pieceAtStart, PieceType const pieceAtEnd) const {
    return getValueOfPieceType(pieceAtStart) == getValueOfPieceType(pieceAtEnd);
}

bool HumanScoreGenerator::isDevelopingMove(PieceType const pieceAtStart, Move const& move) const {
    // Note the y axis is reversed so it should be first minus second
    return PieceType::Pawn != pieceAtStart && PieceType::King != pieceAtStart && move.first.getY() >= 3 &&
           move.first.getY() > move.second.getY();
}

bool HumanScoreGenerator::isCheck(PieceType const pieceAtEnd) const { return PieceType::King == pieceAtEnd; }

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
