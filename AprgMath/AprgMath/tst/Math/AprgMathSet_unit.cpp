#include <Math/AprgMathSet.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SampleTest, NullSetWorks)
{
    AprgMathSet<unsigned int> nullSet;

    EXPECT_FALSE(nullSet.contains(4));
    EXPECT_TRUE(nullSet.doesNotContain(3));
    EXPECT_EQ("{Null set}", nullSet.getDescription());
    EXPECT_EQ("{...  ...}", nullSet.getGeneratedRosterString(
                  [&](AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
                  for(unsigned int i=0; i<=10; i++)
                  {
                      elementFunction(i);
                  }
              }));
}

TEST(SampleTest, MathSetCreatedWithRosterListWorks)
{
    AprgMathSet<unsigned int>::RosterList rosterList{1,2,3,4,5};
    AprgMathSet<unsigned int> mathSet(rosterList);

    EXPECT_TRUE(mathSet.contains(1));
    EXPECT_FALSE(mathSet.contains(6));
    EXPECT_TRUE(mathSet.doesNotContain(10));
    EXPECT_FALSE(mathSet.doesNotContain(5));
    EXPECT_EQ("{1, 2, 3, 4, 5}", mathSet.getDescription());
    EXPECT_EQ("{... 1, 2, 3, 4, 5 ...}", mathSet.getGeneratedRosterString(
                  [&](AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
                  for(unsigned int i=0; i<=10; i++)
                  {
                      elementFunction(i);
                  }
              }));
}

TEST(SampleTest, MathSetCreatedWithInitializerListWorks)
{
    AprgMathSet<unsigned int> mathSet({2,4,6,8,9});

    EXPECT_TRUE(mathSet.contains(2));
    EXPECT_FALSE(mathSet.contains(0));
    EXPECT_TRUE(mathSet.doesNotContain(10));
    EXPECT_FALSE(mathSet.doesNotContain(9));
    EXPECT_EQ("{2, 4, 6, 8, 9}", mathSet.getDescription());
    EXPECT_EQ("{... 2, 4, 6, 8, 9 ...}", mathSet.getGeneratedRosterString(
                  [&](AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
                  for(unsigned int i=0; i<=10; i++)
                  {
                      elementFunction(i);
                  }
              }));
}

TEST(SampleTest, MathSetCreatedWithASetRuleWorks)
{
    AprgMathSet<unsigned int> mathSet("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    EXPECT_TRUE(mathSet.contains(2));
    EXPECT_FALSE(mathSet.contains(1));
    EXPECT_TRUE(mathSet.doesNotContain(3));
    EXPECT_FALSE(mathSet.doesNotContain(4));
    EXPECT_EQ("{set of even numbers}", mathSet.getDescription());
    EXPECT_EQ("{... 0, 2, 4, 6, 8, 10 ...}", mathSet.getGeneratedRosterString(
                  [&](AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
                  for(unsigned int i=0; i<=10; i++)
                  {
                      elementFunction(i);
                  }
              }));
}

TEST(SampleTest, IsASubsetOfWorks)
{
    AprgMathSet<unsigned int> mathSet1({2,4});
    AprgMathSet<unsigned int> mathSet2("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    AprgMathSet<unsigned int>::GenerateFunction generateFunction = [&](
            AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
        for(unsigned int i=0; i<=10; i++)
        {
            elementFunction(i);
        }
    };

    EXPECT_TRUE(mathSet1.isASubsetOf(mathSet2, generateFunction));
    EXPECT_FALSE(mathSet2.isASubsetOf(mathSet1, generateFunction));
}

TEST(SampleTest, IsASupersetOfWorks)
{
    AprgMathSet<unsigned int> mathSet1({3,5});
    AprgMathSet<unsigned int> mathSet2("set of odd numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 1;
    });

    AprgMathSet<unsigned int>::GenerateFunction generateFunction = [&](
            AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
        for(unsigned int i=0; i<=10; i++)
        {
            elementFunction(i);
        }
    };

    EXPECT_TRUE(mathSet2.isASupersetOf(mathSet1, generateFunction));
    EXPECT_FALSE(mathSet1.isASupersetOf(mathSet2, generateFunction));
}

TEST(SampleTest, IsDisjointWithWorks)
{
    AprgMathSet<unsigned int> mathSet1("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });
    AprgMathSet<unsigned int> mathSet2("set of odd numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 1;
    });
    AprgMathSet<unsigned int> mathSet3({2,4});

    AprgMathSet<unsigned int>::GenerateFunction generateFunction = [&](
            AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
        for(unsigned int i=0; i<=10; i++)
        {
            elementFunction(i);
        }
    };

    EXPECT_TRUE(mathSet1.isDisjointWith(mathSet2, generateFunction));
    EXPECT_TRUE(mathSet2.isDisjointWith(mathSet1, generateFunction));
    EXPECT_FALSE(mathSet1.isDisjointWith(mathSet3, generateFunction));
    EXPECT_FALSE(mathSet3.isDisjointWith(mathSet1, generateFunction));
}

TEST(SampleTest, GetComplementWorks)
{
    AprgMathSet<unsigned int> mathSet("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    AprgMathSet<unsigned int> complementSet(mathSet.getComplement());

    EXPECT_FALSE(complementSet.contains(2));
    EXPECT_TRUE(complementSet.contains(5));
    EXPECT_TRUE(complementSet.doesNotContain(4));
    EXPECT_FALSE(complementSet.doesNotContain(7));
    EXPECT_EQ("{complement of {set of even numbers}}", complementSet.getDescription());
    EXPECT_EQ("{... 1, 3, 5, 7, 9 ...}", complementSet.getGeneratedRosterString(
                  [&](AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
                  for(unsigned int i=0; i<=10; i++)
                  {
                      elementFunction(i);
                  }
              }));
}

TEST(SampleTest, GetUnionWithWorks)
{
    AprgMathSet<unsigned int> mathSet1({1,2,3});
    AprgMathSet<unsigned int> mathSet2("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    AprgMathSet<unsigned int> unionSet(mathSet1.getUnionWith(mathSet2));

    EXPECT_TRUE(unionSet.contains(2));
    EXPECT_FALSE(unionSet.contains(5));
    EXPECT_TRUE(unionSet.doesNotContain(7));
    EXPECT_FALSE(unionSet.doesNotContain(4));
    EXPECT_EQ("{{1, 2, 3} union {set of even numbers}}", unionSet.getDescription());
    EXPECT_EQ("{... 0, 1, 2, 3, 4, 6, 8, 10 ...}", unionSet.getGeneratedRosterString(
                  [&](AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
                  for(unsigned int i=0; i<=10; i++)
                  {
                      elementFunction(i);
                  }
              }));
}

TEST(SampleTest, GetUnionWorks)
{
    AprgMathSet<unsigned int> mathSet1({3,4,5});
    AprgMathSet<unsigned int> mathSet2("set of odd numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 1;
    });

    AprgMathSet<unsigned int> unionSet(getUnion(mathSet1, mathSet2));

    EXPECT_TRUE(unionSet.contains(3));
    EXPECT_FALSE(unionSet.contains(6));
    EXPECT_TRUE(unionSet.doesNotContain(8));
    EXPECT_FALSE(unionSet.doesNotContain(9));
    EXPECT_EQ("{{3, 4, 5} union {set of odd numbers}}", unionSet.getDescription());
    EXPECT_EQ("{... 1, 3, 4, 5, 7, 9 ...}", unionSet.getGeneratedRosterString(
                  [&](AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
                  for(unsigned int i=0; i<=10; i++)
                  {
                      elementFunction(i);
                  }
              }));
}

TEST(SampleTest, GetIntersectionWithWorks)
{
    AprgMathSet<unsigned int> mathSet1({1,2,3});
    AprgMathSet<unsigned int> mathSet2("set of even numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 0;
    });

    AprgMathSet<unsigned int> intersectionSet(mathSet1.getIntersectionWith(mathSet2));

    EXPECT_TRUE(intersectionSet.contains(2));
    EXPECT_FALSE(intersectionSet.contains(5));
    EXPECT_TRUE(intersectionSet.doesNotContain(7));
    EXPECT_FALSE(intersectionSet.doesNotContain(2));
    EXPECT_EQ("{{1, 2, 3} intersection {set of even numbers}}", intersectionSet.getDescription());
    EXPECT_EQ("{... 2 ...}", intersectionSet.getGeneratedRosterString(
                  [&](AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
                  for(unsigned int i=0; i<=10; i++)
                  {
                      elementFunction(i);
                  }
              }));
}

TEST(SampleTest, GetIntersectionWorks)
{
    AprgMathSet<unsigned int> mathSet1({3,4,5});
    AprgMathSet<unsigned int> mathSet2("set of odd numbers", [](unsigned int const& elementToCheck)
    {
        return elementToCheck % 2 == 1;
    });

    AprgMathSet<unsigned int> intersectionSet(getIntersection(mathSet1, mathSet2));

    EXPECT_TRUE(intersectionSet.contains(3));
    EXPECT_FALSE(intersectionSet.contains(6));
    EXPECT_TRUE(intersectionSet.doesNotContain(4));
    EXPECT_FALSE(intersectionSet.doesNotContain(5));
    EXPECT_EQ("{{3, 4, 5} intersection {set of odd numbers}}", intersectionSet.getDescription());
    EXPECT_EQ("{... 3, 5 ...}", intersectionSet.getGeneratedRosterString(
                  [&](AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
                  for(unsigned int i=0; i<=10; i++)
                  {
                      elementFunction(i);
                  }
              }));
}

TEST(SampleTest, GetCartesianWorks)
{
    AprgMathSet<unsigned int> mathSet1({1,2});
    AprgMathSet<char> mathSet2({'x','y'});

    AprgMathSet<unsigned int>::GenerateFunction generateFunction1 = [&](
            AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
        for(unsigned int i=0; i<=10; i++)
        {
            elementFunction(i);
        }
    };

    AprgMathSet<char>::GenerateFunction generateFunction2 = [&](
            AprgMathSet<unsigned int>::VoidElementFunction const& elementFunction)
    {
        for(char c='a'; c<='z'; c++)
        {
            elementFunction(c);
        }
    };

    AprgMathSet<pair<unsigned int, char>> cartesianProduct(getCarterisianProduct(mathSet1, mathSet2, generateFunction1, generateFunction2));

    EXPECT_TRUE(cartesianProduct.contains(pair<unsigned int, char>(1,'y')));
    EXPECT_FALSE(cartesianProduct.contains(pair<unsigned int, char>(3,'y')));
    EXPECT_TRUE(cartesianProduct.doesNotContain(pair<unsigned int, char>(2,'z')));
    EXPECT_FALSE(cartesianProduct.doesNotContain(pair<unsigned int, char>(2,'x')));
    EXPECT_EQ("{(1,x), (1,y), (2,x), (2,y)}", cartesianProduct.getDescription());
}

}
