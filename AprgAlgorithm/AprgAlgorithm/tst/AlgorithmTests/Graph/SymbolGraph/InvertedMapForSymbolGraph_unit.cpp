#include <Algorithm/Graph/SymbolGraph/InvertedMapForSymbolGraph.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using InvertedMapForTest = InvertedMapForSymbolGraph<int, string>;
}

TEST(InvertedMapForSymbolGraphTest, GetVertexIdentifierAndAddObjectIfNeededWorksWhenAddingVertices) {
    InvertedMapForTest invertedMap;

    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("zero");
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("one");
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("two");

    InvertedMapForTest::ObjectToVertexMap expectedMap{{"zero", 0}, {"one", 1}, {"two", 2}};
    EXPECT_EQ(expectedMap, invertedMap.getObjectToVertexMap());
    EXPECT_TRUE(invertedMap.getUnusedVertices().empty());
}

TEST(InvertedMapForSymbolGraphTest, GetVertexIdentifierAndAddObjectIfNeededWorksWhenReusingVertices) {
    InvertedMapForTest invertedMap;
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("zero");
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("one");
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("two");
    invertedMap.removeObject("zero");
    invertedMap.removeObject("one");

    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("replacement for one");

    InvertedMapForTest::ObjectToVertexMap expectedMap{{"replacement for one", 1}, {"two", 2}};
    InvertedMapForTest::Vertices expectedUnusedVertices{0};
    EXPECT_EQ(expectedMap, invertedMap.getObjectToVertexMap());
    EXPECT_EQ(expectedUnusedVertices, invertedMap.getUnusedVertices());
}

TEST(InvertedMapForSymbolGraphTest, RemoveObjectWorksWhenAddingObjects) {
    InvertedMapForTest invertedMap;
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("zero");
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("one");
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("two");

    invertedMap.removeObject("zero");
    invertedMap.removeObject("one");

    InvertedMapForTest::ObjectToVertexMap expectedMap{{"two", 2}};
    InvertedMapForTest::Vertices expectedUnusedVertices{0, 1};
    EXPECT_EQ(expectedMap, invertedMap.getObjectToVertexMap());
    EXPECT_EQ(expectedUnusedVertices, invertedMap.getUnusedVertices());
}

TEST(InvertedMapForSymbolGraphTest, ClearWorks) {
    InvertedMapForTest invertedMap;
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("zero");
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("one");
    invertedMap.getVertexIdentifierAndAddObjectIfNeeded("two");
    invertedMap.removeObject("zero");
    invertedMap.removeObject("one");

    invertedMap.clear();

    EXPECT_TRUE(invertedMap.getObjectToVertexMap().empty());
    EXPECT_TRUE(invertedMap.getUnusedVertices().empty());
}

}  // namespace algorithm

}  // namespace alba
