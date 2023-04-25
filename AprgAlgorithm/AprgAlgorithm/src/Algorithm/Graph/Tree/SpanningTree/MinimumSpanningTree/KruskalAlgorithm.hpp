#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>
#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>

#include <queue>

namespace alba {

namespace algorithm {

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class KruskalAlgorithm {
public:
    using Graph = EdgeWeightedGraph;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using EdgeOrderedByWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeOrderedByWeight;
    using EdgeOrderedByWeightsPriorityQueue =
        std::priority_queue<EdgeOrderedByWeight, std::deque<EdgeOrderedByWeight>, std::greater<EdgeOrderedByWeight>>;

    KruskalAlgorithm(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : m_graph(graph), m_startVertex(startVertex) {
        searchForMinimumSpanningTree();
    }

    Edges const& getMinimumSpanningTreeEdges() const { return m_minimumSpanningTreeEdges; }

private:
    void searchForMinimumSpanningTree() {
        putAllEdgesToPriorityQueue();
        unsigned int maxNumberOfEdgesInSpanningTree(m_graph.getNumberOfVertices() - 1);
        UnionFindUsingMap<Vertex> unionFind;
        while (!m_edgesInOrder.empty() && m_minimumSpanningTreeEdges.size() < maxNumberOfEdgesInSpanningTree) {
            // traverse all edges (shortest edges first) and add it to MST if vertices are not already connected in the
            // MST (if it does not produce a cycle)
            EdgeOrderedByWeight shortestEdge(m_edgesInOrder.top());
            m_edgesInOrder.pop();
            addEdgeToMstIfVerticesAreNotConnected(unionFind, shortestEdge);
        }
    }

    void putAllEdgesToPriorityQueue() {
        for (Edge const& edge : m_graph.getEdges()) {
            m_edgesInOrder.emplace(edge.first, edge.second, m_graph.getWeight(edge.first, edge.second));
        }
    }

    void addEdgeToMstIfVerticesAreNotConnected(UnionFindUsingMap<Vertex>& unionFind, EdgeOrderedByWeight const& edge) {
        Vertex const& vertex1(edge.first);
        Vertex const& vertex2(edge.second);
        if (!unionFind.isConnected(vertex1, vertex2))  // if its not connected yet, then it does not create a cycle
        {
            unionFind.connect(vertex1, vertex2);
            m_minimumSpanningTreeEdges.emplace_back(createSortedEdge<Vertex, Edge>(vertex1, vertex2));
        }
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    Edges m_minimumSpanningTreeEdges;
    EdgeOrderedByWeightsPriorityQueue m_edgesInOrder;
};

// Algorithm in short terms: Add shortest edges (if does not create a cycle) in the tree

// Proposition: Kruskal's algorithm computes MST.
// Proof:
// -> Kruskal algorithm is a special case of the greedy MST algorithm.
// -> Suppose Kruskal algorithm colors the edge e = v-w black.
// -> Cut = set of vertices connected to v in tree T
// -> No crossing edge is black
// -> No crossing edge has lower weight.

// Proposition: Kruskal's algorithm computes MST in time proportional to E log E (in the worst case).
// Proof:
// -> Time for each part:
// ---> Building the priority queue = 1(frequency) * E(time per operation)
// ---> Deleting the minimum in PQ = E(frequency) * log E(time per operation) -> main part of the running time
// ---> UnionFind connect = V(frequency) * log* V(time per operation)
// ---> UnionFind isConnected = E(frequency) * log* V(time per operation)

// Other discussions:
// In Kruskal’s algorithm, the initial spanning tree only contains the nodes of the graph and does not contain any
// edges. Then the algorithm goes through the edges ordered by their weights, and always adds an edge to the tree if it
// does not create a cycle. The algorithm maintains the components of the tree. Initially, each node of the graph
// belongs to a separate component. Always when an edge is added to the tree, two components are joined. Finally, all
// nodes belong to the same component, and a minimum spanning tree has been found.

// -> Why does this work? Why does the greedy strategy guarantee that we will find a minimum spanning tree?
// ---> Is it possible that a non minimum weight edge of the graph is not included in the spanning tree?
// ---> No, because minimum weight edges are processed first. If there is some connection to vertex V to the MST, it is
// processed first.

// Time Complexity: O(ElogE) or O(ElogV).
// Sorting of edges takes O(ELogE) time. -> NOTE this analysis uses sorting
// After sorting, we iterate through all edges and apply the find-union algorithm.
// The find and union operations can take at most O(LogV) time.
// So overall complexity is O(ELogE + ELogV) time.
// The value of E can be at most O(V2), so O(LogV) is O(LogE) the same.
// Therefore, the overall time complexity is O(ElogE) or O(ElogV)
// NOTE: This is roughly the same as Prim's algorithm.

}  // namespace algorithm

}  // namespace alba
