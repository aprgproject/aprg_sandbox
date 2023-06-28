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

    using Vertex = int;
    using Color = int;
    using Edge = GraphTypes<Vertex>::Edge;
    using Graph = UndirectedGraphWithListOfEdges<Vertex>;

    AlbaUniformNonDeterministicRandomizer<int> randomizer(0, 1);
    Graph graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(2, 4);
    graph.connect(2, 5);
    graph.connect(3, 4);
    graph.connect(4, 5);
    map<Vertex, Color> vertexToColorMap;

    LasVegasAlgorithm graphColoringAlgorithm = [&]() {
        int numberOfEdgesWithDifferentColors(0);
        do {
            vertexToColorMap.clear();
            for (Vertex const& vertex : graph.getVertices()) {
                vertexToColorMap[vertex] = randomizer.getRandomValue();
            }
            numberOfEdgesWithDifferentColors = 0;
            for (Edge const& edge : graph.getEdges()) {
                if (vertexToColorMap[edge.first] != vertexToColorMap[edge.second]) {
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
