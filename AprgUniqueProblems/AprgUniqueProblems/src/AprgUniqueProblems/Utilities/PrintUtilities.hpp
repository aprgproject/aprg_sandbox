#pragma once

#include <ostream>
#include <utility>

namespace alba
{

std::ostream & operator<<(std::ostream & out, std::pair<unsigned int, unsigned int> const& unsignedIntPair);

}
