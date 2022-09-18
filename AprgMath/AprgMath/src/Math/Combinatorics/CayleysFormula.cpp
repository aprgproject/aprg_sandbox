#include "CayleysFormula.hpp"

#include <Common/Math/Helpers/PowerHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

UnsignedInteger getNumberOfLabeledTreesUsingCayleysFormula(UnsignedInteger const& numberOfNodes)
{
    // Cayley’s formula states that there are nn¡2 labeled trees that contain n nodes.
    // The nodes are labeled 1,2,...,n, and two trees are different if either their structure or labeling is different.

    // For example, when n=4, the number of labeled trees is 4^(4-2) = 16.

    // We can derive how Cayley’s formula can be derived using Prüfer codes.
    // A Prüfer code is a sequence of n-2 numbers that describes a labeled tree.
    // The code is constructed by following a process that removes n-2 leaves from the tree.
    // At each step, the leaf with the smallest label is removed, and the label of its only neighbor is added to the code.
    // We can construct a Prüfer code for any tree, and more importantly, the original tree can be reconstructed from a Prüfer code.

    // Hence, the number of labeled trees is equal to the number of Prüfer codes of size n.
    // And the number of Prüfer codes of size n is equal n^(n-2).

    UnsignedInteger result(0);
    if(numberOfNodes >= 2)
    {
        result = getRaiseToPowerForIntegers(numberOfNodes, numberOfNodes-2);
    }
    return result;
}

}

}
