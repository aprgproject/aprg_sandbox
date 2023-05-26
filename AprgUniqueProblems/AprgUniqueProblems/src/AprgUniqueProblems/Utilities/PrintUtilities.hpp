#pragma once

#include <ostream>
#include <utility>

namespace alba {

std::ostream& operator<<(std::ostream& out, std::pair<int, int> const& unsignedIntPair);

}