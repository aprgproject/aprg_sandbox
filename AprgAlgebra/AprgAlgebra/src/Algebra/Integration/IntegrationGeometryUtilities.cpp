#include "IntegrationGeometryUtilities.hpp"

#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

Term getAreaInBetweenTwoTermsInAnInterval(
        Term const& lowerTerm,
        Term const& higherTerm,
        string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval)
{
    Term difference(lowerTerm-higherTerm);
    Integration integration(variableName);
    return integration.integrateWithDefiniteValues(difference, lowerValueInInterval, higherValueInInterval);
}

}

}
