#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template <class> class ComparatorTemplateType>
class PathSearchUsingFloydWarshall {
public:
    struct PathDetails {
        bool hasAPath;
        Vertex bestInBetweenVertex;
        Weight bestWeight;
    };
    using Graph = EdgeWeightedGraph;
    using Path = typename GraphTypes<Vertex>::Path;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using ListOfVertices = typename GraphTypes<Vertex>::ListOfVertices;
    using ListConstIterator = typename ListOfVertices::const_iterator;
    using EdgeOrderedByWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeOrderedByWeight;
    using PathDetailsMatrix = matrix::AlbaMatrix<PathDetails>;
    using Comparator = ComparatorTemplateType<Weight>;
    PathSearchUsingFloydWarshall(EdgeWeightedGraph const& graph)
        : m_graph(graph), m_pathDetailsMatrix(graph.getNumberOfVertices(), graph.getNumberOfVertices()) {
        searchForBestPaths();    }

    bool hasPathTo(Vertex const& startVertex, Vertex const& endVertex) const {
        bool result(false);
        if (m_pathDetailsMatrix.isInside(startVertex, endVertex)) {
            result = m_pathDetailsMatrix.getEntryConstReference(startVertex, endVertex).hasAPath;
        }
        return result;
    }

    Path getPathTo(Vertex const& startVertex, Vertex const& endVertex) const {
        Path result;
        if (startVertex != endVertex && m_pathDetailsMatrix.isInside(startVertex, endVertex)) {
            PathDetails const& pathDetails(m_pathDetailsMatrix.getEntryConstReference(startVertex, endVertex));
            if (pathDetails.hasAPath) {
                ListOfVertices pathInList{startVertex, endVertex};
                addToPath(pathInList, pathInList.cbegin(), std::prev(pathInList.cend()));
                result.reserve(pathInList.size());
                std::copy(pathInList.cbegin(), pathInList.cend(), std::back_inserter(result));
            }
        }
        return result;
    }

private:
    void addToPath(ListOfVertices& pathInList, ListConstIterator const& startIt, ListConstIterator const& endIt) const {
        if (*startIt != *endIt && m_pathDetailsMatrix.isInside(*startIt, *endIt)) {
            PathDetails const& startToEnd(m_pathDetailsMatrix.getEntryConstReference(*startIt, *endIt));
            if (startToEnd.hasAPath) {
                if (*startIt != startToEnd.bestInBetweenVertex && *endIt != startToEnd.bestInBetweenVertex) {
                    ListConstIterator inbetweenIt = pathInList.insert(endIt, startToEnd.bestInBetweenVertex);
                    PathDetails const& firstToMiddle(
                        m_pathDetailsMatrix.getEntryConstReference(*startIt, startToEnd.bestInBetweenVertex));
                    PathDetails const& middleToSecond(
                        m_pathDetailsMatrix.getEntryConstReference(startToEnd.bestInBetweenVertex, *endIt));
                    if (firstToMiddle.hasAPath && middleToSecond.hasAPath &&
                        firstToMiddle.bestWeight < startToEnd.bestWeight &&
                        middleToSecond.bestWeight < startToEnd.bestWeight) {
                        addToPath(pathInList, startIt, inbetweenIt);
                        addToPath(pathInList, inbetweenIt, endIt);
                    }
                }
            }        }
    }

    void searchForBestPaths() {        initializePathDetailsWithEdgeWeights();
        initializePathDetailsInTheDiagonal();
        checkAllIntermediateVertices();
    }

    void initializePathDetailsWithEdgeWeights() {
        for (EdgeOrderedByWeight const& edgeOrderedByWeight : m_graph.getEdgesWithWeight()) {
            m_pathDetailsMatrix.setEntry(
                edgeOrderedByWeight.first, edgeOrderedByWeight.second,
                {true, edgeOrderedByWeight.first, edgeOrderedByWeight.weight});
        }
    }

    void initializePathDetailsInTheDiagonal() {
        for (Vertex const& vertex : m_graph.getVertices()) {
            PathDetails& diagonalPathDetails(m_pathDetailsMatrix.getEntryReference(vertex, vertex));
            diagonalPathDetails.hasAPath = true;
            diagonalPathDetails.bestInBetweenVertex = vertex;
        }
    }
    void checkAllIntermediateVertices() {
        Vertices vertices(m_graph.getVertices());
        for (Vertex const& inbetweenVertex : vertices) {            for (Vertex const& startVertex : vertices) {
                if (startVertex != inbetweenVertex) {
                    PathDetails& startToIntermediateDetails(
                        m_pathDetailsMatrix.getEntryReference(startVertex, inbetweenVertex));
                    for (Vertex const& endVertex : vertices) {
                        if (endVertex != inbetweenVertex && startVertex != endVertex) {
                            PathDetails& startToEndDetails(
                                m_pathDetailsMatrix.getEntryReference(startVertex, endVertex));
                            PathDetails& intermediateToEndDetails(
                                m_pathDetailsMatrix.getEntryReference(inbetweenVertex, endVertex));
                            if (startToIntermediateDetails.hasAPath && intermediateToEndDetails.hasAPath) {
                                Weight possibleNewWeight =
                                    startToIntermediateDetails.bestWeight + intermediateToEndDetails.bestWeight;
                                if (!startToEndDetails.hasAPath) {
                                    startToEndDetails = {true, inbetweenVertex, possibleNewWeight};
                                } else if (m_comparator(possibleNewWeight, startToEndDetails.bestWeight)) {
                                    startToEndDetails.bestInBetweenVertex = inbetweenVertex;
                                    startToEndDetails.bestWeight = possibleNewWeight;
                                }
                            }                        }
                    }
                }
            }        }
    }

    friend std::ostream& operator<<(std::ostream& out, PathSearchUsingFloydWarshall const& pathSearch) {
        DisplayTable displayTable;
        displayTable.setBorders("-", "|");
        for (unsigned int y = 0; y < pathSearch.m_pathDetailsMatrix.getNumberOfRows(); y++) {
            displayTable.addRow();
            for (unsigned int x = 0; x < pathSearch.m_pathDetailsMatrix.getNumberOfRows(); x++) {
                displayTable.getLastRow().addCell(stringHelper::convertToString(
                    pathSearch.m_pathDetailsMatrix.getEntryConstReference(x, y).hasAPath));
            }
            displayTable.getLastRow().addCell("   ");
            for (unsigned int x = 0; x < pathSearch.m_pathDetailsMatrix.getNumberOfRows(); x++) {
                displayTable.getLastRow().addCell(stringHelper::convertToString(
                    pathSearch.m_pathDetailsMatrix.getEntryConstReference(x, y).bestInBetweenVertex));
            }
            displayTable.getLastRow().addCell("   ");
            for (unsigned int x = 0; x < pathSearch.m_pathDetailsMatrix.getNumberOfRows(); x++) {                displayTable.getLastRow().addCell(stringHelper::convertToString(
                    pathSearch.m_pathDetailsMatrix.getEntryConstReference(x, y).bestWeight));
            }
        }        out << "\n" << displayTable;
        return out;
    }

    Graph const& m_graph;
    Comparator m_comparator;
    PathDetailsMatrix m_pathDetailsMatrix;
};

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template <class> class ComparatorTemplateType>
std::ostream& operator<<(
    std::ostream& out,
    typename PathSearchUsingFloydWarshall<Vertex, Weight, EdgeWeightedGraph, ComparatorTemplateType>::PathDetails const&
        pathDetails) {
    out << pathDetails.hasAPath << "," << pathDetails.bestInBetweenVertex << "," << pathDetails.bestWeight;
    return out;
}
}  // namespace algorithm

}  // namespace alba
// Algorithm in short terms: Use a "adjacent/best weight" matrix to find shortest/longest by checking vertices in
// between vertices.

// The Floyd–Warshall algorithm provides an alternative way to approach the problem of finding best (shortest/longest)
// paths. The algorithm maintains a two-dimensional array that contains distances between the nodes. First, distances
// are calculated only using direct edges between the nodes, and after this, the algorithm reduces distances by using
// intermediate nodes in paths.

// Analysis
// The time complexity of the algorithm is O(n3), because it contains three nested loops that go through the nodes of
// the graph.

// Comments
// Since the implementation of the Floyd–Warshall algorithm is simple,
// the algorithm can be a good choice even if it is only needed to find a single shortest path in the graph.
// However, the algorithm can only be used when the graph is so small that a cubic time complexity is fast enough.
// And the matrix type structure makes it easier to have "start" to "end" path queries

// Other discussions
// The Floyd Warshall Algorithm is for solving the All Pairs Shortest Path problem.
// The problem is to find shortest distances between every pair of vertices in a given edge weighted directed Graph.
// Example:
//
// Input:
//        graph[][] = { {0,   5,  INF, 10},
//                     {INF,  0,  3,  INF},
//                     {INF, INF, 0,   1},
//                     {INF, INF, INF, 0} }
// which represents the following graph
//              10
//        (0)------->(3)
//         |          |UP
//       5 |          |
//         |          | 1
//         |DOWN      |
//        (1)------->(2)
//             3
// Note that the value of graph[i][j] is 0 if i is equal to j
// And graph[i][j] is INF (infinite) if there is no edge from vertex i to j.
//
// Output:
// Shortest distance matrix
//       0      5      8      9
//     INF      0      3      4
//     INF    INF      0      1
//     INF    INF    INF      0

// Floyd Warshall Algorithm
// We initialize the solution matrix same as the input graph matrix as a first step.
// Then we update the solution matrix by considering all vertices as an intermediate vertex.
// The idea is to one by one pick all vertices and updates all shortest paths which include the picked vertex
// as an intermediate vertex in the shortest path.
// When we pick vertex number k as an intermediate vertex,
// we already have considered vertices {0, 1, 2, .. k-1} as intermediate vertices.
// For every pair (i, j) of the source and destination vertices respectively, there are two possible cases.
// -> 1) k is not an intermediate vertex in shortest path from i to j.
// ---> We keep the value of dist[i][j] as it is.
// -> 2) k is an intermediate vertex in shortest path from i to j.
// ---> We update the value of dist[i][j] as dist[i][k] + dist[k][j] if dist[i][j] > dist[i][k] + dist[k][j]

// Time Complexity: O(V^3)
// The above program only prints the shortest distances.
// We can modify the solution to print the shortest paths also by storing the predecessor information in a separate 2D
// matrix. Also, the value of INF can be taken as INT_MAX from limits.h to make sure that we handle maximum possible
// value. When we take INF as INT_MAX, we need to change the if condition in the above program to avoid arithmetic
// overflow. #include
//
// #define INF INT_MAX
// ..........................
// if ( dist[i][k] != INF &&
//      dist[k][j] != INF &&
//      dist[i][k] + dist[k][j] < dist[i][j]
//     )
//  dist[i][j] = dist[i][k] + dist[k][j];
// ...........................
