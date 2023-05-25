#include <Algorithm/Graph/SymbolGraph/InvertedMapForSymbolGraph.hpp>
#include <Algorithm/Graph/SymbolGraph/SymbolGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
InvertedMapForSymbolGraph<int, string> invertedMap;
}

template <>
int getUniqueVertexIdentifier<int, string>(string const& object) {
    return invertedMap.getVertexIdentifierAndAddObjectIfNeeded(object);
}

template <>
void removeUniqueVertexIdentifierIfNeeded<int, string>(string const& object) {
    return invertedMap.removeObject(object);
}

namespace {
using GraphForTest = UndirectedGraphWithListOfEdges<int>;
using SymbolGraphForTest = SymbolGraph<int, string, GraphForTest>;
}  // namespace

TEST(SymbolGraphWithStringTest, ContainsWorksWhenEmpty) {
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;

    EXPECT_FALSE(symbolGraph.contains("zero"));
    EXPECT_FALSE(symbolGraph.contains("one"));
    EXPECT_FALSE(symbolGraph.contains("two"));
    EXPECT_FALSE(symbolGraph.contains("three"));
}

TEST(SymbolGraphWithStringTest, ContainsWorksWhenNotEmpty) {
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;

    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    EXPECT_TRUE(symbolGraph.contains("zero"));
    EXPECT_TRUE(symbolGraph.contains("one"));
    EXPECT_TRUE(symbolGraph.contains("two"));
    EXPECT_FALSE(symbolGraph.contains("three"));
}

TEST(SymbolGraphWithStringTest, GetVertexWorks) {
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;

    EXPECT_EQ(0, symbolGraph.getVertex("zero"));
    EXPECT_EQ(1, symbolGraph.getVertex("one"));
    EXPECT_EQ(2, symbolGraph.getVertex("two"));
    EXPECT_EQ(3, symbolGraph.getVertex("three"));
}

TEST(SymbolGraphWithStringTest, GetObjectWorks) {
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    EXPECT_EQ("zero", symbolGraph.getObject(0));
    EXPECT_EQ("one", symbolGraph.getObject(1));
    EXPECT_EQ("two", symbolGraph.getObject(2));
    EXPECT_TRUE(symbolGraph.getObject(3).empty());
}

TEST(SymbolGraphWithStringTest, GetGraphWorks) {
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    GraphForTest::Edges expectedEdges{{0, 1}, {0, 2}, {1, 2}};
    EXPECT_EQ(expectedEdges, symbolGraph.getGraph().getEdges());
}

TEST(SymbolGraphWithStringTest, GetSymbolTableWorks) {
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    SymbolGraphForTest::SymbolTable expectedSymbolTable{{0, "zero"}, {1, "one"}, {2, "two"}};
    EXPECT_EQ(expectedSymbolTable, symbolGraph.getSymbolTable());
}

TEST(SymbolGraphWithStringTest, ConnectWorks) {
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    GraphForTest::Edges expectedEdges{{0, 1}, {0, 2}, {1, 2}};
    SymbolGraphForTest::SymbolTable expectedSymbolTable{{0, "zero"}, {1, "one"}, {2, "two"}};
    EXPECT_EQ(expectedEdges, symbolGraph.getGraph().getEdges());
    EXPECT_EQ(expectedSymbolTable, symbolGraph.getSymbolTable());
}

TEST(SymbolGraphWithStringTest, DisconnectWorks) {
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    symbolGraph.disconnect("zero", "one");
    symbolGraph.disconnect("zero", "two");

    GraphForTest::Edges expectedEdges{{1, 2}};
    SymbolGraphForTest::SymbolTable expectedSymbolTable{{1, "one"}, {2, "two"}};
    EXPECT_EQ(expectedEdges, symbolGraph.getGraph().getEdges());
    EXPECT_EQ(expectedSymbolTable, symbolGraph.getSymbolTable());
}

}  // namespace algorithm

}  // namespace alba
