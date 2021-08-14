#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

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
    Function absoluteValueFunction(abs(Term(-5)));

    EXPECT_EQ("abs", absoluteValueFunction.getFunctionName());
    EXPECT_EQ(Term(-5), getTermConstReferenceFromBaseTerm(absoluteValueFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(5), absoluteValueFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, SineFunctionWorks)
{
    Function sineFunction(sin(Term(getPi())));

    EXPECT_EQ("sin", sineFunction.getFunctionName());
    EXPECT_EQ(Term(getPi()), getTermConstReferenceFromBaseTerm(sineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), sineFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, CosineFunctionWorks)
{
    Function cosineFunction(cos(Term(getPi())));

    EXPECT_EQ("cos", cosineFunction.getFunctionName());
    EXPECT_EQ(Term(getPi()), getTermConstReferenceFromBaseTerm(cosineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(-1), cosineFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, TangentFunctionWorks)
{
    Function tangentFunction(tan(Term(getPi())));

    EXPECT_EQ("tan", tangentFunction.getFunctionName());
    EXPECT_EQ(Term(getPi()), getTermConstReferenceFromBaseTerm(tangentFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), tangentFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, CosecantFunctionWorks)
{
    Function cosecantFunction(csc(Term(getPi()/2)));

    EXPECT_EQ("csc", cosecantFunction.getFunctionName());
    EXPECT_EQ(Term(getPi()/2), getTermConstReferenceFromBaseTerm(cosecantFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(1), cosecantFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, SecantFunctionWorks)
{
    Function secantFunction(sec(Term(getPi())));

    EXPECT_EQ("sec", secantFunction.getFunctionName());
    EXPECT_EQ(Term(getPi()), getTermConstReferenceFromBaseTerm(secantFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(-1), secantFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, CotangentFunctionWorks)
{
    Function cotangentFunction(cot(Term(getPi()/2)));

    EXPECT_EQ("cot", cotangentFunction.getFunctionName());
    EXPECT_EQ(Term(getPi()/2), getTermConstReferenceFromBaseTerm(cotangentFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), cotangentFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcSineFunctionWorks)
{
    Function arcSineFunction(arcsin(Term(1)));

    EXPECT_EQ("arcsin", arcSineFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(arcSineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(getPi()/2), arcSineFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcCosineFunctionWorks)
{
    Function arcCosineFunction(arccos(Term(1)));

    EXPECT_EQ("arccos", arcCosineFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(arcCosineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), arcCosineFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcTangentFunctionWorks)
{
    Function arcTangentFunction(arctan(Term(Constant(0))));

    EXPECT_EQ("arctan", arcTangentFunction.getFunctionName());
    EXPECT_EQ(Term(Constant(0)), getTermConstReferenceFromBaseTerm(arcTangentFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(0), arcTangentFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcCosecantFunctionWorks)
{
    Function arcCosecantFunction(arccsc(Term(1)));

    EXPECT_EQ("arccsc", arcCosecantFunction.getFunctionName());
    EXPECT_EQ(Term(1), getTermConstReferenceFromBaseTerm(arcCosecantFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(getPi()/2), arcCosecantFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcSecantFunctionWorks)
{
    Function arcSecantFunction(arcsec(Term(-1)));

    EXPECT_EQ("arcsec", arcSecantFunction.getFunctionName());
    EXPECT_EQ(Term(-1), getTermConstReferenceFromBaseTerm(arcSecantFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(getPi()), arcSecantFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, ArcCotangentFunctionWorks)
{
    Function arcCotangentFunction(arccot(Term(Constant(0))));

    EXPECT_EQ("arccot", arcCotangentFunction.getFunctionName());
    EXPECT_EQ(Term(Constant(0)), getTermConstReferenceFromBaseTerm(arcCotangentFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(getPi()/2), arcCotangentFunction.performFunctionAndReturnResultIfPossible());
}

TEST(CommonFunctionLibraryTest, SineHarmonicFunctionWorks)
{
    Function sineFunction(sinHarmonic(Term(getPi()), 4, 2, AlbaNumber(getPi()/2)));

    EXPECT_EQ("sinHarmonic", sineFunction.getFunctionName());
    EXPECT_EQ(Term(getPi()), getTermConstReferenceFromBaseTerm(sineFunction.getInputTermConstReference()));
    EXPECT_EQ(AlbaNumber(4), sineFunction.performFunctionAndReturnResultIfPossible());
}

}

}

}