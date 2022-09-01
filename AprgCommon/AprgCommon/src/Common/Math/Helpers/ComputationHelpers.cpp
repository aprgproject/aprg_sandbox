#include "ComputationHelpers.hpp"

#include <Common/Math/Helpers/ComplexNumberHelpers.hpp>

using namespace std;

namespace alba
{

namespace mathHelper
{

AlbaNumbers getQuadraticRealRoots(
        AlbaNumber const& a,
        AlbaNumber const& b,
        AlbaNumber const& c)
{
    AlbaNumbers result;
    AlbaNumber twoA = a*2;
    AlbaNumber firstPart((-b)/twoA);
    AlbaNumber discriminant((b^2)-(a*c*4));
    if(discriminant >= 0)
    {
        AlbaNumber discriminantSquaredRoot
                = discriminant^(AlbaNumber::createFraction(1, 2));
        AlbaNumber secondPart(discriminantSquaredRoot/twoA);
        result.emplace_back(firstPart + secondPart);
        result.emplace_back(firstPart - secondPart);
    }
    return result;
}

AlbaNumbers getQuadraticRoots(
        RootType const rootType,
        AlbaNumber const& a,
        AlbaNumber const& b,
        AlbaNumber const& c)
{
    AlbaNumbers result;
    AlbaNumber twoA = a*2;
    AlbaNumber firstPart((-b)/twoA);
    AlbaNumber discriminant((b^2)-(a*c*4));
    if(discriminant >= 0)
    {
        AlbaNumber discriminantSquaredRoot
                = discriminant^(AlbaNumber::createFraction(1, 2));
        AlbaNumber secondPart(discriminantSquaredRoot/twoA);
        result.emplace_back(firstPart + secondPart);
        result.emplace_back(firstPart - secondPart);
    }
    else if(RootType::RealAndImaginaryRoots == rootType)
    {
        AlbaComplexNumber<double> discriminantComplex(discriminant.getDouble(), 0.0);
        result.emplace_back(firstPart + createNumberFromComplexNumber(discriminantComplex.getNthRoot(0, 2))/twoA);
        result.emplace_back(firstPart + createNumberFromComplexNumber(discriminantComplex.getNthRoot(1, 2))/twoA);
    }
    return result;
}

}//namespace mathHelper

}//namespace alba
