#include "MathVectorOfTermsUtilities.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

namespace VectorUtilities
{

void simplifyForTermInVector(Term & term)
{
    Simplification::simplifyTermByFactoringToNonDoubleFactorsToACommonDenominator(term);
    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

Term getDyOverDx(
        MathVectorOfTwoTerms const& termVector,
        string const& variableName)
{
    MathVectorOfTwoTerms derivative(differentiate<2U>(termVector, variableName));
    Term result(derivative.getValueAt(1)/derivative.getValueAt(0));
    result.simplify();
    return result;
}

}

}

}
