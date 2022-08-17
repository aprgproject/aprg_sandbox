#include <Common/Container/AlbaContainerHelper.hpp>
#include <Math/Set/MathSet.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

namespace
{
using CharSet = MathSet<char>;using IntegerSet = MathSet<unsigned int>;
using IntegerSets = IntegerSet::MathSets;
IntegerSet::GenerateFunction generateNumbersFromZeroToTen = [](
        IntegerSet::VoidElementFunction const& elementFunction){
    for(unsigned int i=0; i<=10; i++)
    {
        elementFunction(i);
    }
};

CharSet::GenerateFunction generateCharactersFromSmallAToSmallZ = [](
        IntegerSet::VoidElementFunction const& elementFunction)
{
    for(char c='a'; c<='z'; c++)
    {
        elementFunction(c);
    }
};
}

TEST(MathSetTest, NullSetWorks)
{
    IntegerSet nullSet;

    EXPECT_FALSE(nullSet.contains(4));
    EXPECT_TRUE(nullSet.doesNotContain(3));
    EXPECT_EQ("{Null set}", nullSet.getDescription());
    EXPECT_EQ("{...  ...}", nullSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, MathSetCreatedWithRosterListWorks)
{
    IntegerSet::RosterList rosterList{1,2,3,4,5};
    IntegerSet mathSet(rosterList);

    EXPECT_TRUE(mathSet.contains(1));
    EXPECT_FALSE(mathSet.contains(6));
    EXPECT_TRUE(mathSet.doesNotContain(10));
    EXPECT_FALSE(mathSet.doesNotContain(5));
    EXPECT_EQ("{1, 2, 3, 4, 5}", mathSet.getDescription());
    EXPECT_EQ("{... 1, 2, 3, 4, 5 ...}", mathSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, MathSetCreatedWithInitializerListWorks)
{
    IntegerSet mathSet({2,4,6,8,9});

    EXPECT_TRUE(mathSet.contains(2));
    EXPECT_FALSE(mathSet.contains(0));
    EXPECT_TRUE(mathSet.doesNotContain(10));
    EXPECT_FALSE(mathSet.doesNotContain(9));
    EXPECT_EQ("{2, 4, 6, 8, 9}", mathSet.getDescription());
    EXPECT_EQ("{... 2, 4, 6, 8, 9 ...}", mathSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, MathSetCreatedWithASetRuleWorks)
{
    IntegerSet mathSet("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    EXPECT_TRUE(mathSet.contains(2));
    EXPECT_FALSE(mathSet.contains(1));
    EXPECT_TRUE(mathSet.doesNotContain(3));
    EXPECT_FALSE(mathSet.doesNotContain(4));
    EXPECT_EQ("{set of even numbers}", mathSet.getDescription());
    EXPECT_EQ("{... 0, 2, 4, 6, 8, 10 ...}", mathSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, IsASubsetOfWorks)
{
    IntegerSet mathSet1({2,4});
    IntegerSet mathSet2("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    EXPECT_TRUE(mathSet1.isASubsetOf(mathSet2, generateNumbersFromZeroToTen));
    EXPECT_FALSE(mathSet2.isASubsetOf(mathSet1, generateNumbersFromZeroToTen));
}

TEST(MathSetTest, IsASupersetOfWorks)
{
    IntegerSet mathSet1({3,5});
    IntegerSet mathSet2("set of odd numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 1;
    });

    EXPECT_TRUE(mathSet2.isASupersetOf(mathSet1, generateNumbersFromZeroToTen));
    EXPECT_FALSE(mathSet1.isASupersetOf(mathSet2, generateNumbersFromZeroToTen));
}

TEST(MathSetTest, IsDisjointWithWorks)
{
    IntegerSet mathSet1("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });
    IntegerSet mathSet2("set of odd numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 1;
    });
    IntegerSet mathSet3({2,4});

    EXPECT_TRUE(mathSet1.isDisjointWith(mathSet2, generateNumbersFromZeroToTen));
    EXPECT_TRUE(mathSet2.isDisjointWith(mathSet1, generateNumbersFromZeroToTen));
    EXPECT_FALSE(mathSet1.isDisjointWith(mathSet3, generateNumbersFromZeroToTen));
    EXPECT_FALSE(mathSet3.isDisjointWith(mathSet1, generateNumbersFromZeroToTen));
}

TEST(MathSetTest, GetComplementWorks)
{
    IntegerSet mathSet("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    IntegerSet complementSet(mathSet.getComplement());

    EXPECT_FALSE(complementSet.contains(2));
    EXPECT_TRUE(complementSet.contains(5));
    EXPECT_TRUE(complementSet.doesNotContain(4));
    EXPECT_FALSE(complementSet.doesNotContain(7));
    EXPECT_EQ("{complement of {set of even numbers}}", complementSet.getDescription());
    EXPECT_EQ("{... 1, 3, 5, 7, 9 ...}", complementSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, GetUnionWithWorks)
{
    IntegerSet mathSet1({1,2,3});
    IntegerSet mathSet2("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    IntegerSet unionSet(mathSet1.getUnionWith(mathSet2));

    EXPECT_TRUE(unionSet.contains(2));
    EXPECT_FALSE(unionSet.contains(5));
    EXPECT_TRUE(unionSet.doesNotContain(7));
    EXPECT_FALSE(unionSet.doesNotContain(4));
    EXPECT_EQ("{{1, 2, 3} union {set of even numbers}}", unionSet.getDescription());
    EXPECT_EQ("{... 0, 1, 2, 3, 4, 6, 8, 10 ...}", unionSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, GetIntersectionWithWorks)
{
    IntegerSet mathSet1({1,2,3});
    IntegerSet mathSet2("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    IntegerSet intersectionSet(mathSet1.getIntersectionWith(mathSet2));

    EXPECT_TRUE(intersectionSet.contains(2));
    EXPECT_FALSE(intersectionSet.contains(5));
    EXPECT_TRUE(intersectionSet.doesNotContain(7));
    EXPECT_FALSE(intersectionSet.doesNotContain(2));
    EXPECT_EQ("{{1, 2, 3} intersection {set of even numbers}}", intersectionSet.getDescription());
    EXPECT_EQ("{... 2 ...}", intersectionSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, GetDifferenceWithWorks)
{
    IntegerSet mathSet1({1,2,3});
    IntegerSet mathSet2("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    IntegerSet differenceSet(mathSet1.getDifferenceWith(mathSet2));

    EXPECT_TRUE(differenceSet.contains(1));
    EXPECT_FALSE(differenceSet.contains(2));
    EXPECT_TRUE(differenceSet.doesNotContain(2));
    EXPECT_FALSE(differenceSet.doesNotContain(1));
    EXPECT_EQ("{{1, 2, 3} difference {set of even numbers}}", differenceSet.getDescription());
    EXPECT_EQ("{... 1, 3 ...}", differenceSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, GetSubsetsWithWorks)
{
    IntegerSet mathSet({1,2,3});

    IntegerSets actualSubsets(mathSet.getSubsets(generateNumbersFromZeroToTen));

    string actualSubsetsString(containerHelper::getStringFromContents(actualSubsets));
    EXPECT_EQ("{}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}, ", actualSubsetsString);
}

TEST(MathSetTest, GetUnionWorks)
{
    IntegerSet mathSet1({3,4,5});
    IntegerSet mathSet2("set of odd numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 1;
    });

    IntegerSet unionSet(getUnion(mathSet1, mathSet2));

    EXPECT_TRUE(unionSet.contains(3));
    EXPECT_FALSE(unionSet.contains(6));
    EXPECT_TRUE(unionSet.doesNotContain(8));
    EXPECT_FALSE(unionSet.doesNotContain(9));
    EXPECT_EQ("{{3, 4, 5} union {set of odd numbers}}", unionSet.getDescription());
    EXPECT_EQ("{... 1, 3, 4, 5, 7, 9 ...}", unionSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, GetIntersectionWorks)
{
    IntegerSet mathSet1({3,4,5});
    IntegerSet mathSet2("set of odd numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 1;
    });

    IntegerSet intersectionSet(getIntersection(mathSet1, mathSet2));

    EXPECT_TRUE(intersectionSet.contains(3));
    EXPECT_FALSE(intersectionSet.contains(6));
    EXPECT_TRUE(intersectionSet.doesNotContain(4));
    EXPECT_FALSE(intersectionSet.doesNotContain(5));
    EXPECT_EQ("{{3, 4, 5} intersection {set of odd numbers}}", intersectionSet.getDescription());
    EXPECT_EQ("{... 3, 5 ...}", intersectionSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, GetDifferenceWorks)
{
    IntegerSet mathSet1({1,2,3});
    IntegerSet mathSet2("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    IntegerSet differenceSet(getDifference(mathSet1, mathSet2));

    EXPECT_TRUE(differenceSet.contains(1));
    EXPECT_FALSE(differenceSet.contains(2));
    EXPECT_TRUE(differenceSet.doesNotContain(2));
    EXPECT_FALSE(differenceSet.doesNotContain(1));
    EXPECT_EQ("{{1, 2, 3} difference {set of even numbers}}", differenceSet.getDescription());
    EXPECT_EQ("{... 1, 3 ...}", differenceSet.getGeneratedRosterString(generateNumbersFromZeroToTen));
}

TEST(MathSetTest, GetCartesianProductWorks)
{
    IntegerSet mathSet1({1,2});
    CharSet mathSet2({'x','y'});

    MathSet<pair<unsigned int, char>> cartesianProduct(getCartersianProduct(mathSet1, mathSet2, generateNumbersFromZeroToTen, generateCharactersFromSmallAToSmallZ));

    EXPECT_TRUE(cartesianProduct.contains(pair<unsigned int, char>(1,'y')));
    EXPECT_FALSE(cartesianProduct.contains(pair<unsigned int, char>(3,'y')));
    EXPECT_TRUE(cartesianProduct.doesNotContain(pair<unsigned int, char>(2,'z')));
    EXPECT_FALSE(cartesianProduct.doesNotContain(pair<unsigned int, char>(2,'x')));
    EXPECT_EQ("{(1,x), (1,y), (2,x), (2,y)}", cartesianProduct.getDescription());
}

}

}