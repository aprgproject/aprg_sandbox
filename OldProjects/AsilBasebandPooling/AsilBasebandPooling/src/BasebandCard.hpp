#pragma once

#include <Kepler.hpp>

#include <set>
#include <vector>

namespace alba {

class BasebandCard {
public:
    BasebandCard(unsigned char const boardId, KeplerInitializerList const& keplers);
    bool operator<(BasebandCard const& basebandCard) const;
    unsigned char getBoardId() const;
    SetOfKeplers getKeplers() const;

private:
    unsigned char m_boardId;
    SetOfKeplers m_keplers;
};

using BasebandCardInitializerList = std::initializer_list<BasebandCard>;
using SetOfBasebandCards = std::set<BasebandCard>;
using VectorOfBasebandCards = std::vector<BasebandCard>;

}  // namespace alba
