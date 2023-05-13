#pragma once

#include <ChessPeek/BoardWithContext.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class HumanScoreGenerator {
public:
    struct MoveDetail {
        Move move;
        int score;
        int mate;
    };

    static constexpr int SCORE_LEVEL_DISTANCE = 90;  // reached 2200
    // static constexpr int SCORE_LEVEL_DISTANCE = 190; // one pawn blunders keep happening

    HumanScoreGenerator(BoardWithContext const& boardWithContext, int const bestScore, int const worstScore);

    uint32_t getHumanScore(MoveDetail const& moveDetail) const;

private:
    uint32_t getScoreLevelPart(MoveDetail const& moveDetail) const;
    uint32_t getMoveTypePart(Move const& move) const;
    uint32_t getDistanceToKingPart(Move const& move) const;
    uint32_t getPiecePart(Move const& move) const;
    uint32_t getHumanScoreOfPiece(PieceType const pieceType) const;

    bool isSameValueExchange(Piece const pieceAtStart, Piece const pieceAtEnd, Move const& move) const;
    bool isExchangeSacrifice(Piece const pieceAtStart, Piece const pieceAtEnd, Move const& move) const;
    bool isDevelopingMove(Piece const pieceAtStart, Move const& move) const;
    bool isCheck(Piece const pieceAtEnd) const;

    BoardWithContext const& m_boardWithContext;
    int m_bestScore;    int m_worstScore;
    int m_maxScoreLevel;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
