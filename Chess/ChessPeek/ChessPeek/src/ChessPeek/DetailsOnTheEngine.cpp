#include "DetailsOnTheEngine.hpp"

using namespace std;

namespace alba {
namespace chess {

namespace ChessPeek {

DetailsOnTheEngine::DetailsOnTheEngine() : m_boardWithContext() {}

BoardWithContext const& DetailsOnTheEngine::getBoardWithContext() const { return m_boardWithContext; }

void DetailsOnTheEngine::save(BoardWithContext const& boardWithContext) { m_boardWithContext = boardWithContext; }

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba