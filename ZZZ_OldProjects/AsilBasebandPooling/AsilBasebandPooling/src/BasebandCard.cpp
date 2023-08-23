#include "BasebandCard.hpp"

#include <iterator>

using namespace std;

namespace alba {

BasebandCard::BasebandCard(unsigned char const boardId, KeplerInitializerList const& keplers) : m_boardId(boardId) {
    copy(keplers.begin(), keplers.end(), inserter(m_keplers, m_keplers.cbegin()));
}

bool BasebandCard::operator<(BasebandCard const& basebandCard) const { return m_boardId < basebandCard.m_boardId; }

unsigned char BasebandCard::getBoardId() const { return m_boardId; }

SetOfKeplers BasebandCard::getKeplers() const { return m_keplers; }

}  // namespace alba
