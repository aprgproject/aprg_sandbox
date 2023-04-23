#include <Common/Print/AlbaPrintFunctions.hpp>

#include <gtest/gtest.h>

#include <deque>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

namespace alba
{

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithItemsThatCanPrint)
{
    stringstream ssToVerify;
    unsigned int integerToTest=500U;

    printParameterWithName(ssToVerify, "name", integerToTest);

    EXPECT_EQ("name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithPointer)
{
    stringstream ssToVerify;
    unsigned int integerToTest=500U;

    printParameterWithName(ssToVerify, "name", &integerToTest);

    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithCharacterLiteral)
{
    stringstream ssToVerify;

    printParameterWithName(ssToVerify, "name", "ThisIsACharacterLiteralSoNameIsNotIncluded");

    EXPECT_EQ(R"(["ThisIsACharacterLiteralSoNameIsNotIncluded"])", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithUniquePointer)
{
    stringstream ssToVerify;
    unique_ptr<unsigned int> pointerToTest(make_unique<unsigned int>(500U));

    printParameterWithName(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithSharedPointer)
{
    stringstream ssToVerify;
    shared_ptr<unsigned int> pointerToTest(make_shared<unsigned int>(500U));

    printParameterWithName(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithWeakPointer)
{
    stringstream ssToVerify;
    shared_ptr<unsigned int> sharedPointer(make_shared<unsigned int>(500U));
    weak_ptr<unsigned int> pointerToTest(sharedPointer);

    printParameterWithName(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("name has use count: [1]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithPair)
{
    stringstream ssToVerify;
    pair<unsigned int, char> pairToTest{300, 'A'};

    printParameterWithName(ssToVerify, "name", pairToTest);

    EXPECT_EQ("name : [(300, A)]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithTuple)
{
    stringstream ssToVerify;
    tuple<unsigned int, string, char> pairToTest{300, "hello", 'A'};

    printParameterWithName(ssToVerify, "name", pairToTest);

    EXPECT_EQ("name : [(300, hello, A)]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithArray){
    stringstream ssToVerify;
    array<unsigned int, 5> vectorToTest{500U, 501U, 502U, 503U, 504U};
    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{Constant size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithVector)
{
    stringstream ssToVerify;
    vector<unsigned int> vectorToTest{500U, 501U, 502U, 503U, 504U};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithDeque)
{
    stringstream ssToVerify;
    deque<unsigned int> vectorToTest{500U, 501U, 502U, 503U, 504U};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithSet)
{
    stringstream ssToVerify;
    set<unsigned int> vectorToTest{500U, 501U, 502U, 503U, 504U};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithMap)
{
    stringstream ssToVerify;
    map<unsigned int, char> vectorToTest{{500U, 'A'}, {501U, 'B'}, {502U, 'C'}, {503U, 'D'}, {504U, 'E'}};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | (500, A), (501, B), (502, C), (503, D), (504, E), }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithUnorderedSet)
{
    stringstream ssToVerify;
    unordered_set<unsigned int> vectorToTest{500U, 501U, 502U, 503U, 504U};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | 504, 503, 502, 501, 500, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithUnorderedMap)
{
    stringstream ssToVerify;
    unordered_map<unsigned int, char> vectorToTest{{500U, 'A'}, {501U, 'B'}, {502U, 'C'}, {503U, 'D'}, {504U, 'E'}};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | (504, E), (503, D), (502, C), (501, B), (500, A), }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithStack)
{
    stringstream ssToVerify;
    stack<unsigned int> adapter({1U, 2U, 3U});

    printParameterWithName(ssToVerify, "name", adapter);

    EXPECT_EQ("name : [{adapter: {size: 3 | 1, 2, 3, }}]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithQueue)
{
    stringstream ssToVerify;
    queue<unsigned int> adapter({1U, 2U, 3U});

    printParameterWithName(ssToVerify, "name", adapter);

    EXPECT_EQ("name : [{adapter: {size: 3 | 1, 2, 3, }}]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithPriorityQueue)
{
    stringstream ssToVerify;
    priority_queue<unsigned int> adapter;
    adapter.push(1U);
    adapter.push(2U);
    adapter.push(3U);

    printParameterWithName(ssToVerify, "name", adapter);

    EXPECT_EQ("name : [{adapter: {size: 3 | 3, 1, 2, }}]", ssToVerify.str());
}

}
