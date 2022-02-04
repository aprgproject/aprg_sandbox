#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Functions
{

TEST(CommonFunctionLibraryTest, AbsoluteValueFunctionWorks)
{
    Function absoluteValueFunction(abs(-5));

    EXPECT_EQ("abs", absoluteValueFunction.getFunctionName());
    EXPECT_EQ(Term(-5), getTermConstReferenceFromBaseTerm(absoluteValueFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(5), absoluteValueFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, GreatestIntegerFunctionWorks)
{
    Function greatestIntegerFunctionObject(greatestIntegerFunction(-5.1));

    EXPECT_EQ("greatestIntegerFunction", greatestIntegerFunctionObject.getFunctionName());
    EXPECT_EQ(Term(-5.1), getTermConstReferenceFromBaseTerm(greatestIntegerFunctionObject.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(-5), greatestIntegerFunctionObject.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, SignumFunctionWorks)
{
    Function signumFunctionObject(sgn(-5.1));

    EXPECT_EQ("sgn", signumFunctionObject.getFunctionName());
    EXPECT_EQ(Term(-5.1), getTermConstReferenceFromBaseTerm(signumFunctionObject.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(-1), signumFunctionObject.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, FactorialFunctionWorks)
{
    Function signumFunctionObject(factorial(5));

    EXPECT_EQ("factorial", signumFunctionObject.getFunctionName());
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(signumFunctionObject.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(120), signumFunctionObject.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, FactorialFunctionWorksWhenInputIsZero)
{
    Function signumFunctionObject(factorial(0));

    EXPECT_EQ("factorial", signumFunctionObject.getFunctionName());
    EXPECT_EQ(Term(0), getTermConstReferenceFromBaseTerm(signumFunctionObject.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(1), signumFunctionObject.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, NaturalLogarithmFunctionWorks)
{
    Function naturalLogarithmFunctionObject(ln(5));

    EXPECT_EQ("ln", naturalLogarithmFunctionObject.getFunctionName());
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(naturalLogarithmFunctionObject.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(1.6094379124341), naturalLogarithmFunctionObject.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, LogarithmBase10FunctionWorks)
{
    Function logarithmBase10FunctionObject(log(5));

    EXPECT_EQ("log", logarithmBase10FunctionObject.getFunctionName());
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(logarithmBase10FunctionObject.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0.6989700043360189), logarithmBase10FunctionObject.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, HarmonicNumberFunctionWorks)
{
    Function harmonicNumberFunctionObject(harmonicNumber(5));

    EXPECT_EQ("harmonicNumber", harmonicNumberFunctionObject.getFunctionName());
    EXPECT_EQ(Term(5), getTermConstReferenceFromBaseTerm(harmonicNumberFunctionObject.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber::createFraction(137, 60), harmonicNumberFunctionObject.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, SineFunctionWorks)
{
    Function sineFunction(sin(getPiAsTerm()));

    EXPECT_EQ("sin", sineFunction.getFunctionName());
    EXPECT_EQ(getPiAsTerm(), getTermConstReferenceFromBaseTerm(sineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), sineFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, CosineFunctionWorks)
{
    Function cosineFunction(cos(getPiAsTerm()));

    EXPECT_EQ("cos", cosineFunction.getFunctionName());
    EXPECT_EQ(getPiAsTerm(), getTermConstReferenceFromBaseTerm(cosineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(-1), cosineFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, TangentFunctionWorks)
{
    Function tangentFunction(tan(getPiAsTerm()));

    EXPECT_EQ("tan", tangentFunction.getFunctionName());
    EXPECT_EQ(getPiAsTerm(), getTermConstReferenceFromBaseTerm(tangentFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), tangentFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, CosecantFunctionWorks)
{
    Function cosecantFunction(csc(getPi()/2));

    EXPECT_EQ("csc", cosecantFunction.getFunctionName());
    EXPECT_EQ(Term(getPi()/2), getTermConstReferenceFromBaseTerm(cosecantFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(1), cosecantFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, SecantFunctionWorks)
{
    Function secantFunction(sec(getPiAsTerm()));

    EXPECT_EQ("sec", secantFunction.getFunctionName());
    EXPECT_EQ(getPiAsTerm(), getTermConstReferenceFromBaseTerm(secantFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(-1), secantFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, CotangentFunctionWorks)
{
    Function cotangentFunction(cot(getPi()/2));

    EXPECT_EQ("cot", cotangentFunction.getFunctionName());
    EXPECT_EQ(Term(getPi()/2), getTermConstReferenceFromBaseTerm(cotangentFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), cotangentFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcSineFunctionWorks)
{
    Function arcSineFunction(arcsin(1));

    EXPECT_EQ("arcsin", arcSineFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(arcSineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(getPi()/2), arcSineFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcCosineFunctionWorks)
{
    Function arcCosineFunction(arccos(1));

    EXPECT_EQ("arccos", arcCosineFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(arcCosineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), arcCosineFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcTangentFunctionWorks)
{
    Function arcTangentFunction(arctan(0));

    EXPECT_EQ("arctan", arcTangentFunction.getFunctionName());
    EXPECT_EQ(Term(0), getTermConstReferenceFromBaseTerm(arcTangentFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), arcTangentFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcCosecantFunctionWorks)
{
    Function arcCosecantFunction(arccsc(1));

    EXPECT_EQ("arccsc", arcCosecantFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(arcCosecantFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(getPi()/2), arcCosecantFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcSecantFunctionWorks)
{
    Function arcSecantFunction(arcsec(-1));

    EXPECT_EQ("arcsec", arcSecantFunction.getFunctionName());
    EXPECT_EQ(Term(-1), getTermConstReferenceFromBaseTerm(arcSecantFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(getPi()), arcSecantFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcCotangentFunctionWorks)
{
    Function arcCotangentFunction(arccot(0));

    EXPECT_EQ("arccot", arcCotangentFunction.getFunctionName());
    EXPECT_EQ(Term(0), getTermConstReferenceFromBaseTerm(arcCotangentFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(getPi()/2), arcCotangentFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, HyperbolicSineFunctionWorks)
{
    Function sinhFunction(sinh(1));

    EXPECT_EQ("sinh", sinhFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(sinhFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(1.175201193643801), sinhFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, HyperbolicCosineFunctionWorks)
{
    Function coshFunction(cosh(1));

    EXPECT_EQ("cosh", coshFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(coshFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(1.543080634815244), coshFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, HyperbolicTangentFunctionWorks)
{
    Function tanhFunction(tanh(1));

    EXPECT_EQ("tanh", tanhFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(tanhFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0.7615941559557649), tanhFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, HyperbolicCosecantFunctionWorks)
{
    Function cschFunction(csch(1));

    EXPECT_EQ("csch", cschFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(cschFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0.8509181282393216), cschFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, HyperbolicSecantFunctionWorks)
{
    Function sechFunction(sech(1));

    EXPECT_EQ("sech", sechFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(sechFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0.6480542736638853), sechFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, HyperbolicCotangentFunctionWorks)
{
    Function cothFunction(coth(1));

    EXPECT_EQ("coth", cothFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(cothFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(1.313035285499331), cothFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, SineHarmonicFunctionWorks)
{
    Function sineFunction(sinHarmonic(getPiAsTerm(), 4, 2, AlbaNumber(getPi()/2)));

    EXPECT_EQ("sinHarmonic", sineFunction.getFunctionName());
    EXPECT_EQ(getPiAsTerm(), getTermConstReferenceFromBaseTerm(sineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(4), sineFunction.performFunctionAndReturnResultIfPossible());
}

}

}

}
