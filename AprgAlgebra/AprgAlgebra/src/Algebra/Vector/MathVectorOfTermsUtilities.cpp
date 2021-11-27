#include "MathVectorOfTermsUtilities.hpp"

#include <Math/Vector/AlbaMathVectorUtilities.hpp>

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

Term getDirectionalDerivativeInTwoDimensions(
        Term const& term,
        ArrayOfStrings<2U> const& coordinateVariables,
        AlbaAngle const& angleOfDirection)
{
    MathVectorOfTwoTerms gradient(getGradient<2U>(term, coordinateVariables));
    MathVectorOfTwoTerms unitDirection(
    {Term(::cos(angleOfDirection.getRadians())), Term(::sin(angleOfDirection.getRadians()))});
    Term result(getDotProduct(gradient, unitDirection));
    simplifyForTermInVector(result);
    return result;
}

Term getDirectionalDerivativeInThreeDimensions(
        Term const& term,
        ArrayOfStrings<3U> const& coordinateVariables,
        MathVectorOfAngles<3U> const& coordinateAngles)
{
    MathVectorOfThreeTerms gradient(getGradient<3U>(term, coordinateVariables));
    MathVectorOfThreeTerms unitDirection(
    {Term(::cos(coordinateAngles.getValueAt(0).getRadians())),
     Term(::cos(coordinateAngles.getValueAt(1).getRadians())),
     Term(::cos(coordinateAngles.getValueAt(2).getRadians()))});
    Term result(getDotProduct(gradient, unitDirection));
    simplifyForTermInVector(result);
    return result;
}

}

}

}
