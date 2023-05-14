#pragma once

#include <ChessUtilities/Board/BoardValue.hpp>

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace alba {

namespace chess {

namespace ChessPeek {

class Book {
public:
    struct MoveDetail {
        std::string move;
        int winPercentage;
    };

    using MoveDetails = std::vector<MoveDetail>;
    struct LineDetail {
        std::string nameOfLine;
        PieceColor colorToMove;
        int totalNumberOfGames;
        MoveDetails nextMoves;
    };
    using LineDetailOptional = std::optional<LineDetail>;

    size_t getSize() const;
    LineDetailOptional getLine(Board const& board) const;
    void saveDatabaseTo(std::string const& path) const;

    void clear();
    void addLine(Board const& board, LineDetail const& lineDetail);
    void loadDatabaseFrom(std::string const& path);
private:
    std::map<BoardValue, LineDetail> m_boardToLineDetail;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
