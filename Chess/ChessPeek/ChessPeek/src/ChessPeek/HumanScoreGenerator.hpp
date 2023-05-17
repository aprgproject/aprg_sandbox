#pragma once

#include <ChessPeek/BoardWithContext.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class HumanScoreGenerator {
public:
    using Score = uint64_t;

    struct MoveDetail {
        Move move;
        int mate;
        int score;
    };

    struct DataFromExchanges {
        Score hangingValue;
        Score complicatedScore;
    };

    static constexpr int LOWER_LIMIT_FOR_WINNING = 200;          // x > 200
    static constexpr int LOWER_LIMIT_FOR_SLIGHTLY_BETTER = 100;  // 200 > x > 100
    static constexpr int LOWER_LIMIT_FOR_EQUAL = -100;           // 100 > x > -100
    static constexpr int LOWER_LIMIT_FOR_SLIGHTLY_WORSE = -200;  // -100 > x > -200

    // just lose please
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_WINNING = 190;
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_BETTER = 290;
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_EQUAL = 190;
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_WORSE = 90;
    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_LOSING = 90;

    //    // competitive but not too human
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_WINNING = 90;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_BETTER = 190;  // needs blunders to be human
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_EQUAL = 190;            // needs blunders to be human
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_WORSE = 40;    // try to equalize
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_LOSING = 90;            // just accept that your losing

    //    // good until 2200
    //    static constexpr int SCORE_LEVEL_DISTANCE = 90;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_WINNING = 90;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_BETTER = 190;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_EQUAL = 290;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_SLIGHTLY_WORSE = 140;
    //    static constexpr int SCORE_LEVEL_DISTANCE_WHEN_LOSING = 40;

    HumanScoreGenerator(BoardWithContext const& boardWithContext, int const worstScore, int const bestScore);

    Score getHumanScore(MoveDetail const& moveDetail) const;

private:
    Score getScoreLevelPart(MoveDetail const& moveDetail) const;
    DataFromExchanges getDataFromExchanges(Move const& move) const;
    Score getMoveTypePart(Move const& move) const;
    Score getDistanceToKingPart(Move const& move) const;
    Score getPiecePart(Move const& move) const;
    Score getHumanScoreOfPiece(PieceType const pieceType) const;

    int getDistanceToKing(Coordinate const& coordinate) const;
    int getScoreLevelDistance() const;
    bool isACaptureMove(Piece const pieceAtStart, Piece const pieceAtEnd) const;
    bool isSameValueExchange(Piece const pieceAtStart, Piece const pieceAtEnd) const;
    bool isDevelopingMove(Piece const pieceAtStart, Move const& move) const;
    bool isCastlingMove(Piece const pieceAtStart, Move const& move) const;
    bool isCheck(Piece const pieceAtEnd) const;

    BoardWithContext const& m_boardWithContext;
    int m_worstScore;
    int m_bestScore;
    int m_highestScoreLevel;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
