#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Random/LasVegas.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

TEST(LasVegasTest, GraphColoringExample) {
    // Given a graph that contains n nodes and m edges,
    // our task is to find a way to color the nodes of the graph using two colors so that for at least m/2 edges,
    // the endpoints have different colors.

    using Vertex = unsigned int;
    using Color = unsigned int;
    using Edge = GraphTypes<Vertex>::Edge;
    using Graph = UndirectedGraphWithListOfEdges<Vertex>;

    AlbaUniformNonDeterministicRandomizer<unsigned int> randomizer(0, 1);
    Graph graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(2U, 4U);
    graph.connect(2U, 5U);
    graph.connect(3U, 4U);
    graph.connect(4U, 5U);
    map<Vertex, Color> vertexToColorMap;

    LasVegasAlgorithm graphColoringAlgorithm = [&]() {
        unsigned int numberOfEdgesWithDifferentColors(0);
        do {
            vertexToColorMap.clear();
            for (Vertex const& vertex : graph.getVertices()) {
                vertexToColorMap[vertex] = randomizer.getRandomValue();
            }
            numberOfEdgesWithDifferentColors = 0;
            for (Edge const& edge : graph.getEdges()) {
                if (vertexToColorMap.at(edge.first) != vertexToColorMap.at(edge.second)) {
                    numberOfEdgesWithDifferentColors++;
                }
            }
        } while (numberOfEdgesWithDifferentColors >= graph.getNumberOfEdges() / 2);
    };

    performALasVegasAlgorithm(graphColoringAlgorithm);

    EXPECT_EQ(5U, vertexToColorMap.size());
}

}  // namespace algorithm

}  // namespace alba
