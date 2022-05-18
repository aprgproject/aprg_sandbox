#include <Common/Print/AlbaPrintFunctions.hpp>

#include <gtest/gtest.h>

#include <deque>
#include <sstream>

using namespace std;

namespace alba
{

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithItemsThatCanPrint)
{
    stringstream ssToVerify;
    unsigned int integerToTest=500U;

    printParameter(ssToVerify, "name", integerToTest);

    EXPECT_EQ("name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithPointer)
{
    stringstream ssToVerify;    unsigned int integerToTest=500U;

    printParameter(ssToVerify, "name", &integerToTest);

    EXPECT_EQ("*name : [500]", ssToVerify.str());}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithCharacterLiteral)
{
    stringstream ssToVerify;

    printParameter(ssToVerify, "name", "ThisIsACharacterLiteralSoNameIsNotIncluded");

    EXPECT_EQ(R"(["ThisIsACharacterLiteralSoNameIsNotIncluded"])", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithUniquePointer)
{
    stringstream ssToVerify;
    unique_ptr<unsigned int> pointerToTest(make_unique<unsigned int>(500U));

    printParameter(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithSharedPointer)
{
    stringstream ssToVerify;
    shared_ptr<unsigned int> pointerToTest(make_shared<unsigned int>(500U));

    printParameter(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithWeakPointer)
{
    stringstream ssToVerify;
    shared_ptr<unsigned int> sharedPointer(make_shared<unsigned int>(500U));
    weak_ptr<unsigned int> pointerToTest(sharedPointer);

    printParameter(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("name has use count: [1]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithPair)
{
    stringstream ssToVerify;
    pair<unsigned int, char> pairToTest{300, 'A'};

    printParameter(ssToVerify, "name", pairToTest);

    EXPECT_EQ("name : [(300, A)]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithArray){
    stringstream ssToVerify;
    array<unsigned int, 5> vectorToTest{500U, 501U, 502U, 503U, 504U};
    printParameter(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [(has size 5):{500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithVector)
{
    stringstream ssToVerify;
    vector<unsigned int> vectorToTest{500U, 501U, 502U, 503U, 504U};

    printParameter(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [(has size 5):{500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithDeque)
{
    stringstream ssToVerify;
    deque<unsigned int> vectorToTest{500U, 501U, 502U, 503U, 504U};

    printParameter(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [(has size 5):{500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithSet)
{
    stringstream ssToVerify;
    set<unsigned int> vectorToTest{500U, 501U, 502U, 503U, 504U};

    printParameter(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [(has size 5):{500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWorksWithMap)
{
    stringstream ssToVerify;
    map<unsigned int, char> vectorToTest{{500U, 'A'}, {501U, 'B'}, {502U, 'C'}, {503U, 'D'}, {504U, 'E'}};

    printParameter(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [(has size 5):{{500:A}, {501:B}, {502:C}, {503:D}, {504:E}, }]", ssToVerify.str());
}

}
