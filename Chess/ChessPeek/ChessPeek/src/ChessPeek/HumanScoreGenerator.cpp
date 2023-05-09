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
    // Format: 0000 MSSS SSSS SSMM KKKK KKKK YYYY PPPP
    return getMatePart(moveDetail) << 27 | getScoreLevelPart(moveDetail) << 18 | getMovePart(moveDetail.move) << 16 |
           getDistanceToKingPart(moveDetail.move) << 8 | getYForwardCountPart(moveDetail.move) << 4 |
           getPiecePart(moveDetail.move);
}

uint32_t HumanScoreGenerator::getMatePart(MoveDetail const& moveDetail) const {
    // Number of bits for this part: 1
    if (moveDetail.mate > 0) {
        return 1;  // put mate as same level as best move (this is to be human and have an imperfect record on mates)
    } else if (moveDetail.mate < 0) {
        return 0;  // avoid to be mated as much as possible
    } else {
        return 1;
    }
}

uint32_t HumanScoreGenerator::getScoreLevelPart(MoveDetail const& moveDetail) const {
    // Number of bits for this part: 9
    auto result =
        static_cast<uint32_t>(m_maxScoreLevel - ((m_bestScore - moveDetail.score) / SCORE_LEVEL_DISTANCE)) & 0x1FF;
    return result;
}

uint32_t HumanScoreGenerator::getMovePart(Move const& move) const {
    // Number of bits for this part: 2
    Board const& board(m_boardWithContext.getBoard());
    PieceType pieceType1 = board.getPieceAt(move.first).getType();
    PieceType pieceType2 = board.getPieceAt(move.second).getType();
    if (PieceType::King == pieceType2) {
        return 2;  // prioritize checks
    } else if (getValueOfPieceType(pieceType1) == getValueOfPieceType(pieceType2)) {
        return 0;  // avoid same value exchanges
    } else {
        return 1;
    }
}

uint32_t HumanScoreGenerator::getDistanceToKingPart(Move const& move) const {
    // Number of bits for this part: 6
    Coordinate delta = m_boardWithContext.getOpponentsKingCoordinate() - move.second;
    constexpr int MAX_DISTANCE_SQUARED_IN_BOARD = 98;
    int reverseDistance = MAX_DISTANCE_SQUARED_IN_BOARD - (delta.getX() * delta.getX() + delta.getY() * delta.getY());
    return static_cast<uint32_t>(reverseDistance) & 0xFF;
}

uint32_t HumanScoreGenerator::getYForwardCountPart(Move const& move) const {
    // Number of bits for this part: 4
    // Note the y axis is reversed so it should be first minus second
    return static_cast<uint32_t>(7 + move.first.getY() - move.second.getY()) & 0xF;
}

uint32_t HumanScoreGenerator::getPiecePart(Move const& move) const {
    // Number of bits for this part: 4
    return getHumanScoreOfPiece(m_boardWithContext.getBoard().getPieceAt(move.first).getType()) & 0xF;
}

uint32_t HumanScoreGenerator::getHumanScoreOfPiece(PieceType const pieceType) const {
    // Number of bits for this part: 4
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

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
