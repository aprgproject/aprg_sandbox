#include "PrintUtilities.hpp"

using namespace std;

namespace alba
{

ostream & operator<<(ostream & out, pair<unsigned int, unsigned int> const& unsignedIntPair)
{
    out << "(";
    out << unsignedIntPair.first;
    out << ",";
    out << unsignedIntPair.second;
    out <<")";
    return out;
}

}
