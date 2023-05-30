#include "PrintUtilities.hpp"

using namespace std;

namespace alba {

ostream& operator<<(ostream& out, pair<int, int> const& unsignedIntPair) {
    out << "(";
    out << unsignedIntPair.first;
    out << ",";
    out << unsignedIntPair.second;
    out << ")";
    return out;
}

}  // namespace alba
