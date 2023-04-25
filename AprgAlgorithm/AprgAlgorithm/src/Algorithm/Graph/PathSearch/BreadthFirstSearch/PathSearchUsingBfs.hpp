#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithBfsAndDfs.hpp>

#include <deque>
#include <functional>

namespace alba {

namespace algorithm {

template <typename Vertex>
class PathSearchUsingBfs : public BasePathSearchWithBfsAndDfs<Vertex> {
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseClass = BasePathSearchWithBfsAndDfs<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using InitializeDataFunction = std::function<void(Vertices const&)>;
    using UpdateDataFunction = std::function<void(Vertex const&, Vertex const&)>;

    ~PathSearchUsingBfs() =
        default;  // No need for virtual destructor because this class is not destroyed polymorphically.

    PathSearchUsingBfs(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph),
          b_graph(BaseClass::m_graph),
          b_processedVertices(BaseClass::m_processedVertices),
          b_vertexToPreviousVertexMap(BaseClass::m_vertexToPreviousVertexMap),
          m_initializeDataFunction(getEmptyInitializeDataFunction()),
          m_updateDataFunction(getEmptyUpdateDataFunction()) {
        reinitializeStartingFrom({startVertex});
    }

    PathSearchUsingBfs(BaseGraphWithVertex const& graph, Vertices const& startVertices)
        : BaseClass(graph),
          b_graph(BaseClass::m_graph),
          b_processedVertices(BaseClass::m_processedVertices),
          b_vertexToPreviousVertexMap(BaseClass::m_vertexToPreviousVertexMap),
          m_initializeDataFunction(getEmptyInitializeDataFunction()),
          m_updateDataFunction(getEmptyUpdateDataFunction()) {
        reinitializeStartingFrom(startVertices);
    }

    PathSearchUsingBfs(
        BaseGraphWithVertex const& graph, Vertices const& startVertices,
        InitializeDataFunction const& initializeDataFunction, UpdateDataFunction const& updateDataFunction)
        : BaseClass(graph),
          b_graph(BaseClass::m_graph),
          b_processedVertices(BaseClass::m_processedVertices),
          b_vertexToPreviousVertexMap(BaseClass::m_vertexToPreviousVertexMap),
          m_initializeDataFunction(initializeDataFunction),
          m_updateDataFunction(updateDataFunction) {
        reinitializeStartingFrom(startVertices);
    }

    Path getShortestPathTo(Vertex const& endVertex) const { return this->getPathTo(endVertex); }

    void reinitializeStartingFrom(Vertices const& startVertices) {
        clear();
        initializeWithStartVertices(startVertices);
        m_initializeDataFunction(startVertices);
        traverseUsingBfs(startVertices);
    }

private:
    using BaseClass::clear;
    using BaseClass::initializeWithStartVertices;

    void traverseUsingBfs(Vertices const& startVertices) {
        b_processedVertices.putVertices(startVertices);

        std::deque<Vertex> nearestVertices;
        std::copy(startVertices.cbegin(), startVertices.cend(), std::back_inserter(nearestVertices));
        // for multiple-source shortest path so multiple vertices here
        while (!nearestVertices.empty()) {
            Vertex vertex(nearestVertices.back());
            nearestVertices.pop_back();
            for (Vertex const& adjacentVertex : b_graph.getAdjacentVerticesAt(vertex)) {
                if (b_processedVertices.isNotFound(adjacentVertex)) {
                    b_processedVertices.putVertex(adjacentVertex);
                    b_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                    nearestVertices.emplace_front(adjacentVertex);

                    m_updateDataFunction(adjacentVertex, vertex);
                }
            }
        }
    }

    static InitializeDataFunction getEmptyInitializeDataFunction() {
        static InitializeDataFunction emptyInitializeDataFunction = [](Vertices const&) {};
        return emptyInitializeDataFunction;
    }

    static UpdateDataFunction getEmptyUpdateDataFunction() {
        static UpdateDataFunction emptyUpdateDataFunction = [](Vertex const&, Vertex const&) {};
        return emptyUpdateDataFunction;
    }

    BaseGraphWithVertex const& b_graph;
    CheckableVerticesWithVertex& b_processedVertices;
    VertexToVertexMap& b_vertexToPreviousVertexMap;
    InitializeDataFunction m_initializeDataFunction;
    UpdateDataFunction m_updateDataFunction;
};

// Proposition: BFS computes shortest paths (fewest number of edges) from s to all other vertices in a graph in time
// proportional to E+V Proof(correctness): Queue always consists of zero or more vertices of distance k from s, followed
// by zero or more vertices of distance k+1. In short, vertices with distance 1 are first, and then vertices with
// distance 2 and then vertices with distance 3 and so on. Proof(running time): Each vertex connected to s is visited
// once.

// Other analysis:
// Like in depth-first search, the time complexity of breadth-first search is O(n+m),
// where n is the number of nodes and m is the number of edges.
// The algorithm processes each node and edge once.

}  // namespace algorithm

}  // namespace alba
