#include "BaseTerm.hpp"

using namespace std;

namespace alba
{

namespace equation
{

BaseTerm::BaseTerm()
{}

BaseTerm::~BaseTerm()
{}

string BaseTerm::getDisplayableString() const
{
    return "[BaseTermDisplayableString]";
}

string BaseTerm::getDebugString() const
{
    return "[BaseTermDebugString]";
}

ostream & operator<<(ostream & out, BaseTerm const& baseTerm)
{
    out << baseTerm.getDisplayableString();
    return out;
}
}

}