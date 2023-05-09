#pragma once

#include <ChessPeek/BoardWithContext.hpp>

namespace alba {
namespace chess {

namespace ChessPeek {
class DetailsOnTheEngine {
public:
    DetailsOnTheEngine();

    BoardWithContext const& getBoardWithContext() const;

    void save(BoardWithContext const& boardWithContext);

private:
    BoardWithContext m_boardWithContext;
};

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba