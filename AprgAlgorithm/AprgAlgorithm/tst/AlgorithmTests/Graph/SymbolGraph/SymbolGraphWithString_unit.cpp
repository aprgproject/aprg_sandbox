#include <Algorithm/Graph/SymbolGraph/InvertedMapForSymbolGraph.hpp>
#include <Algorithm/Graph/SymbolGraph/SymbolGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
InvertedMapForSymbolGraph<unsigned int, string> invertedMap;
}

template <>
unsigned int getUniqueVertexIdentifier<unsigned int, string>(string const& object)
{
    return invertedMap.getVertexIdentifierAndAddObjectIfNeeded(object);
}

template <>
void removeUniqueVertexIdentifierIfNeeded<unsigned int, string>(string const& object)
{
    return invertedMap.removeObject(object);
}

namespace
{
using GraphForTest = UndirectedGraphWithListOfEdges<unsigned int>;
using SymbolGraphForTest = SymbolGraph<unsigned int, string, GraphForTest>;
}

TEST(SymbolGraphWithStringTest, ContainsWorksWhenEmpty)
{
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;

    EXPECT_FALSE(symbolGraph.contains("zero"));
    EXPECT_FALSE(symbolGraph.contains("one"));
    EXPECT_FALSE(symbolGraph.contains("two"));
    EXPECT_FALSE(symbolGraph.contains("three"));
}

TEST(SymbolGraphWithStringTest, ContainsWorksWhenNotEmpty)
{
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

TEST(SymbolGraphWithStringTest, GetVertexWorks)
{
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;

    EXPECT_EQ(0U, symbolGraph.getVertex("zero"));
    EXPECT_EQ(1U, symbolGraph.getVertex("one"));
    EXPECT_EQ(2U, symbolGraph.getVertex("two"));
    EXPECT_EQ(3U, symbolGraph.getVertex("three"));
}

TEST(SymbolGraphWithStringTest, GetObjectWorks)
{
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    EXPECT_EQ("zero", symbolGraph.getObject(0U));
    EXPECT_EQ("one", symbolGraph.getObject(1U));
    EXPECT_EQ("two", symbolGraph.getObject(2U));
    EXPECT_TRUE(symbolGraph.getObject(3U).empty());
}

TEST(SymbolGraphWithStringTest, GetGraphWorks)
{
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    GraphForTest::Edges expectedEdges{{0U, 1U}, {0U, 2U}, {1U, 2U}};
    EXPECT_EQ(expectedEdges, symbolGraph.getGraph().getEdges());
}

TEST(SymbolGraphWithStringTest, GetSymbolTableWorks)
{
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    SymbolGraphForTest::SymbolTable expectedSymbolTable{{0U, "zero"}, {1U, "one"}, {2U, "two"}};
    EXPECT_EQ(expectedSymbolTable, symbolGraph.getSymbolTable());
}

TEST(SymbolGraphWithStringTest, ConnectWorks)
{
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    GraphForTest::Edges expectedEdges{{0U, 1U}, {0U, 2U}, {1U, 2U}};
    SymbolGraphForTest::SymbolTable expectedSymbolTable{{0U, "zero"}, {1U, "one"}, {2U, "two"}};
    EXPECT_EQ(expectedEdges, symbolGraph.getGraph().getEdges());
    EXPECT_EQ(expectedSymbolTable, symbolGraph.getSymbolTable());
}

TEST(SymbolGraphWithStringTest, DisconnectWorks)
{
    invertedMap.clear();
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect("zero", "one");
    symbolGraph.connect("zero", "two");
    symbolGraph.connect("one", "two");

    symbolGraph.disconnect("zero", "one");
    symbolGraph.disconnect("zero", "two");

    GraphForTest::Edges expectedEdges{{1U, 2U}};
    SymbolGraphForTest::SymbolTable expectedSymbolTable{{1U, "one"}, {2U, "two"}};
    EXPECT_EQ(expectedEdges, symbolGraph.getGraph().getEdges());
    EXPECT_EQ(expectedSymbolTable, symbolGraph.getSymbolTable());
}

}

}
