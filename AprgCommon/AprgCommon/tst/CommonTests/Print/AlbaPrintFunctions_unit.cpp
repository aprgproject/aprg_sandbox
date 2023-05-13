#include <Common/Print/AlbaPrintFunctions.hpp>

#include <gtest/gtest.h>

#include <deque>
#include <forward_list>
#include <optional>
#include <queue>
#include <sstream>
#include <stack>#include <unordered_map>
#include <unordered_set>

using namespace std;

namespace alba {

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithItemsThatCanPrint) {
    stringstream ssToVerify;
    int integerToTest = 500;

    printParameterWithName(ssToVerify, "name", integerToTest);
    EXPECT_EQ("name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithPointer) {
    stringstream ssToVerify;
    int integerToTest = 500;

    printParameterWithName(ssToVerify, "name", &integerToTest);
    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithCharacterLiteral) {
    stringstream ssToVerify;

    printParameterWithName(ssToVerify, "name", "ThisIsACharacterLiteralSoNameIsNotIncluded");

    EXPECT_EQ(R"(["ThisIsACharacterLiteralSoNameIsNotIncluded"])", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithUniquePointer) {
    stringstream ssToVerify;
    unique_ptr<int> pointerToTest(make_unique<int>(500));

    printParameterWithName(ssToVerify, "name", pointerToTest);
    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithSharedPointer) {
    stringstream ssToVerify;
    shared_ptr<int> pointerToTest(make_shared<int>(500));

    printParameterWithName(ssToVerify, "name", pointerToTest);
    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithWeakPointer) {
    stringstream ssToVerify;
    shared_ptr<int> sharedPointer(make_shared<int>(500));
    weak_ptr<int> pointerToTest(sharedPointer);

    printParameterWithName(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("name has use count: [1]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithOptional) {
    stringstream ssToVerify;
    optional<int> emptyOptional;
    optional<int> nonEmptyOptional(300);

    printParameterWithName(ssToVerify, "name1", emptyOptional);
    ssToVerify << ", ";
    printParameterWithName(ssToVerify, "name2", nonEmptyOptional);

    EXPECT_EQ("name1 : [empty], name2 : [300]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithPair) {
    stringstream ssToVerify;
    pair<int, char> pairToTest{300, 'A'};

    printParameterWithName(ssToVerify, "name", pairToTest);
    EXPECT_EQ("name : [(300, A)]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithTuple) {
    stringstream ssToVerify;
    tuple<int, string, char> pairToTest{300, "hello", 'A'};

    printParameterWithName(ssToVerify, "name", pairToTest);
    EXPECT_EQ("name : [(300, hello, A)]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithArray) {
    stringstream ssToVerify;
    array<int, 5> vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);
    EXPECT_EQ("name : [{Constant size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithVector) {
    stringstream ssToVerify;
    vector<int> vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);
    EXPECT_EQ("name : [{size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithDeque) {
    stringstream ssToVerify;
    deque<int> vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);
    EXPECT_EQ("name : [{size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithSet) {
    stringstream ssToVerify;
    set<int> vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);
    EXPECT_EQ("name : [{size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithMap) {
    stringstream ssToVerify;
    map<int, char> vectorToTest{{500, 'A'}, {501, 'B'}, {502, 'C'}, {503, 'D'}, {504, 'E'}};

    printParameterWithName(ssToVerify, "name", vectorToTest);
    EXPECT_EQ("name : [{size: 5 | (500, A), (501, B), (502, C), (503, D), (504, E), }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithUnorderedSet) {
    stringstream ssToVerify;
    unordered_set<int> vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);
    EXPECT_EQ("name : [{size: 5 | 504, 503, 502, 501, 500, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithUnorderedMap) {
    stringstream ssToVerify;
    unordered_map<int, char> vectorToTest{{500, 'A'}, {501, 'B'}, {502, 'C'}, {503, 'D'}, {504, 'E'}};

    printParameterWithName(ssToVerify, "name", vectorToTest);
    EXPECT_EQ("name : [{size: 5 | (504, E), (503, D), (502, C), (501, B), (500, A), }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithStack) {
    stringstream ssToVerify;
    stack<int> adapter({1, 2, 3});

    printParameterWithName(ssToVerify, "name", adapter);
    EXPECT_EQ("name : [{adapter: {size: 3 | 1, 2, 3, }}]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithQueue) {
    stringstream ssToVerify;
    queue<int> adapter({1, 2, 3});

    printParameterWithName(ssToVerify, "name", adapter);
    EXPECT_EQ("name : [{adapter: {size: 3 | 1, 2, 3, }}]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithPriorityQueue) {
    stringstream ssToVerify;
    priority_queue<int> adapter;
    adapter.push(1U);
    adapter.push(2U);
    adapter.push(3U);
    printParameterWithName(ssToVerify, "name", adapter);

    EXPECT_EQ("name : [{adapter: {size: 3 | 3, 1, 2, }}]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithForwardList) {
    stringstream ssToVerify;
    forward_list<int> vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);
    EXPECT_EQ("name : [{500, 501, 502, 503, 504, }]", ssToVerify.str());
}

}  // namespace alba
