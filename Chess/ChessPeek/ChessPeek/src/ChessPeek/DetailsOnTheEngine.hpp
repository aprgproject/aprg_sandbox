#pragma once

#include <ChessUtilities/Board/Board.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class DetailsOnTheEngine {
public:
    DetailsOnTheEngine();
    DetailsOnTheEngine(PieceColor const& playerColor, Board const& board);

    PieceColor getPlayerColor() const;
    Board const& getBoard() const;
    std::string getFenString() const;

    void save(PieceColor const& playerColor, Board const& board);

private:
    PieceColor m_playerColor;
    Board m_board;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
