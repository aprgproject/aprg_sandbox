#include <Monomial.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(MonomialTest, MonomialsAreConstructedCorrectly)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial::VariablesToExponentsMap variablesToExponents{{"i", -7}};
    Monomial monomial3(23, variablesToExponents);

    EXPECT_DOUBLE_EQ(0, monomial1.getConstantConstReference().getDouble());
    ASSERT_TRUE(monomial1.getVariablesToExponentsMapConstReference().empty());

    EXPECT_DOUBLE_EQ(-54, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap1.size());
    EXPECT_DOUBLE_EQ(6, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-1.25, variableMap1.at("y").getDouble());

    EXPECT_DOUBLE_EQ(23, monomial3.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial3.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(-7, variableMap2.at("i").getDouble());
}

TEST(MonomialTest, CombineVariableExponentMapByMultiplicationWorks)
{
    Monomial::VariablesToExponentsMap variableMap1{{"x", 7}, {"y", 8}};
    Monomial::VariablesToExponentsMap variableMap2{{"x", 1}, {"y", -8}};
    Monomial::VariablesToExponentsMap variableMap3{{"z", 5}};

    Monomial::VariablesToExponentsMap variableMapToVerify1(Monomial::combineVariableExponentMapByMultiplication(variableMap1, variableMap2));
    Monomial::VariablesToExponentsMap variableMapToVerify2(Monomial::combineVariableExponentMapByMultiplication(variableMap1, variableMap3));

    ASSERT_EQ(2u, variableMapToVerify1.size());
    EXPECT_DOUBLE_EQ(8, variableMapToVerify1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(0, variableMapToVerify1.at("y").getDouble());
    ASSERT_EQ(3u, variableMapToVerify2.size());
    EXPECT_DOUBLE_EQ(7, variableMapToVerify2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(8, variableMapToVerify2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(5, variableMapToVerify2.at("z").getDouble());
}

TEST(MonomialTest, CombineVariableExponentMapByDivisionWorks)
{
    Monomial::VariablesToExponentsMap variableMap1{{"x", 7}, {"y", 8}};
    Monomial::VariablesToExponentsMap variableMap2{{"x", 1}, {"y", 8}};
    Monomial::VariablesToExponentsMap variableMap3{{"z", 5}};

    Monomial::VariablesToExponentsMap variableMapToVerify1(Monomial::combineVariableExponentMapByDivision(variableMap1, variableMap2));
    Monomial::VariablesToExponentsMap variableMapToVerify2(Monomial::combineVariableExponentMapByDivision(variableMap1, variableMap3));

    ASSERT_EQ(2u, variableMapToVerify1.size());
    EXPECT_DOUBLE_EQ(6, variableMapToVerify1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(0, variableMapToVerify1.at("y").getDouble());
    ASSERT_EQ(3u, variableMapToVerify2.size());
    EXPECT_DOUBLE_EQ(7, variableMapToVerify2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(8, variableMapToVerify2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(-5, variableMapToVerify2.at("z").getDouble());
}

TEST(MonomialTest, EqualityOperatorWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(-234, {{"x", 6}, {"y", -1.25}});
    Monomial monomial4(-54, {{"x", 6}});
    Monomial monomial5(-54, {{"x", 6}, {"y", -1.25}});

    EXPECT_TRUE(monomial1==monomial1);
    EXPECT_FALSE(monomial1==monomial2);
    EXPECT_TRUE(monomial2==monomial2);
    EXPECT_FALSE(monomial2==monomial3);
    EXPECT_FALSE(monomial2==monomial4);
    EXPECT_TRUE(monomial2==monomial5);
}

TEST(MonomialTest, IsZeroFunctionWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(0, {{"x", 6}, {"y", -1.25}});
    Monomial monomial4(23, {});

    EXPECT_TRUE(monomial1.isZero());
    EXPECT_FALSE(monomial2.isZero());
    EXPECT_TRUE(monomial3.isZero());
    EXPECT_FALSE(monomial4.isZero());
}

TEST(MonomialTest, IsConstantOnlyFunctionWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(23, {});

    EXPECT_TRUE(monomial1.isConstantOnly());
    EXPECT_FALSE(monomial2.isConstantOnly());
    EXPECT_TRUE(monomial3.isConstantOnly());
}

TEST(MonomialTest, IsVariableOnlyFunctionWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(-54, {{"x", 6}});
    Monomial monomial4(-54, {{"x", 1}});
    Monomial monomial5(0, {{"x", 1}});
    Monomial monomial6(1, {{"x", 1}});

    EXPECT_FALSE(monomial1.isVariableOnly());
    EXPECT_FALSE(monomial2.isVariableOnly());
    EXPECT_FALSE(monomial3.isVariableOnly());
    EXPECT_FALSE(monomial4.isVariableOnly());
    EXPECT_FALSE(monomial5.isVariableOnly());
    EXPECT_TRUE(monomial6.isVariableOnly());
}

TEST(MonomialTest, GetFirstVariableNameFunctionWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x1", 6}, {"y1", -1.25}});
    Monomial monomial3(-54, {{"x2", 6}});
    Monomial monomial4(-54, {{"x3", 1}});
    Monomial monomial5(0, {{"x4", 1}});
    Monomial monomial6(1, {{"x5", 1}});
    Monomial monomial7(1, {});

    EXPECT_TRUE(monomial1.getFirstVariableName().empty());
    EXPECT_EQ("x1", monomial2.getFirstVariableName());
    EXPECT_EQ("x2", monomial3.getFirstVariableName());
    EXPECT_EQ("x3", monomial4.getFirstVariableName());
    EXPECT_EQ("x4", monomial5.getFirstVariableName());
    EXPECT_EQ("x5", monomial6.getFirstVariableName());
    EXPECT_TRUE(monomial7.getFirstVariableName().empty());
}

TEST(MonomialTest, GetDisplayableStringWorks)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(-54, {{"x", 6}});
    Monomial monomial4(-54, {{"x", 1}});
    Monomial monomial5(0, {{"x", 1}});
    Monomial monomial6(1, {{"x", 1}});
    Monomial monomial7(1, {});

    EXPECT_EQ("0", monomial1.getDisplayableString());
    EXPECT_EQ("-54|x^6||y^-1.25|", monomial2.getDisplayableString());
    EXPECT_EQ("-54|x^6|", monomial3.getDisplayableString());
    EXPECT_EQ("-54|x^1|", monomial4.getDisplayableString());
    EXPECT_EQ("0|x^1|", monomial5.getDisplayableString());
    EXPECT_EQ("1|x^1|", monomial6.getDisplayableString());
    EXPECT_EQ("1", monomial7.getDisplayableString());
}

TEST(MonomialTest, SimplifyWorks)
{
    Monomial monomial1;
    Monomial monomial2(6, {});
    Monomial monomial3(1, {{"x", 1}});
    Monomial monomial4(10, {{"x", 0}});
    Monomial monomial5(58, {{"x", 7}, {"y", 0}});

    monomial1.simplify();
    monomial2.simplify();
    monomial3.simplify();
    monomial4.simplify();
    monomial5.simplify();

    EXPECT_DOUBLE_EQ(0, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(6, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());
    EXPECT_DOUBLE_EQ(1, monomial3.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomial3.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap3.size());
    EXPECT_DOUBLE_EQ(1, variableMap3.at("x").getDouble());
    EXPECT_DOUBLE_EQ(10, monomial4.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap4(monomial4.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap4.empty());
    EXPECT_DOUBLE_EQ(58, monomial5.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap5(monomial5.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap5.size());
    EXPECT_DOUBLE_EQ(7, variableMap5.at("x").getDouble());
}

TEST(MonomialTest, MultiplyNumberWorks)
{
    Monomial monomial1(16, {{"x", 5}});
    Monomial monomial2(20, {{"x", 7}});

    monomial1.multiplyNumber(3);
    monomial2.multiplyNumber(5);

    EXPECT_DOUBLE_EQ(48, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(5, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(100, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(7, variableMap2.at("x").getDouble());
}

TEST(MonomialTest, RaiseToPowerNumberWorks)
{
    Monomial monomial(3, {{"x", 1}, {"y", 2}, {"z", 3}});

    monomial.raiseToPowerNumber(3);

    EXPECT_DOUBLE_EQ(27, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(3u, variableMap.size());
    EXPECT_DOUBLE_EQ(3, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(6, variableMap.at("y").getDouble());
    EXPECT_DOUBLE_EQ(9, variableMap.at("z").getDouble());
}

TEST(MonomialTest, MultiplyMonomialWorks)
{
    Monomial monomial1(16, {{"x", 5}});
    Monomial monomial2(20, {{"x", 7}});

    monomial1.multiplyMonomial(Monomial(8, {{"x", 3}}));
    monomial2.multiplyMonomial(Monomial(8, {{"y", 4}}));

    EXPECT_DOUBLE_EQ(128, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(8, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(160, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(7, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("y").getDouble());
}

TEST(MonomialTest, DivideMonomialWorks)
{
    Monomial monomial1(16, {{"x", 5}});
    Monomial monomial2(20, {{"x", 7}});

    monomial1.divideMonomial(Monomial(8, {{"x", 3}}));
    monomial2.divideMonomial(Monomial(8, {{"y", 4}}));

    EXPECT_DOUBLE_EQ(2, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(2, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(2.5, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(7, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-4, variableMap2.at("y").getDouble());
}

TEST(MonomialTest, SettingANewConstantWorks)
{
    Monomial monomial;
    EXPECT_DOUBLE_EQ(0, monomial.getConstantConstReference().getDouble());

    monomial.setConstant(512);
    EXPECT_DOUBLE_EQ(512, monomial.getConstantConstReference().getDouble());
}

TEST(MonomialTest, PuttingANewVariableWithExponentWorks)
{
    Monomial monomial;
    ASSERT_TRUE(monomial.getVariablesToExponentsMapConstReference().empty());

    monomial.putVariableWithExponent("i", 62);
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(62, variableMap.at("i").getDouble());
}

TEST(MonomialTest, PuttingASetOfNewVariablesWithExponentWorks)
{
    Monomial monomial;
    ASSERT_TRUE(monomial.getVariablesToExponentsMapConstReference().empty());

    monomial.putVariablesWithExponents({{"j", -4}, {"k", -0.75}});
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(-4, variableMap.at("j").getDouble());
    EXPECT_DOUBLE_EQ(-0.75, variableMap.at("k").getDouble());
}

}

}
