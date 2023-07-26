#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithBfsAndDfs.hpp>

#include <functional>

namespace alba {

namespace algorithm {

template <typename Vertex>
class PathSearchUsingDfs : public BasePathSearchWithBfsAndDfs<Vertex> {
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using BaseClass = BasePathSearchWithBfsAndDfs<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using VertexToIntMap = typename GraphTypes<Vertex>::VertexToIntMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using InitializeDataFunction = std::function<void(Vertices const&)>;
    using UpdateDataFunction = std::function<void(Vertex const&, Vertex const&)>;

    PathSearchUsingDfs(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : BaseClass(graph),
          b_graph(BaseClass::m_graph),
          b_startVertices(BaseClass::m_startVertices),
          b_processedVertices(BaseClass::m_processedVertices),
          b_vertexToPreviousVertexMap(BaseClass::m_vertexToPreviousVertexMap),
          m_initializeDataFunction(getEmptyInitializeDataFunction()),
          m_updateDataFunction(getEmptyUpdateDataFunction()) {
        reinitializeStartingFrom({startVertex});
    }

    PathSearchUsingDfs(BaseGraphWithVertex const& graph, Vertices const& startVertices)
        : BaseClass(graph),
          b_graph(BaseClass::m_graph),
          b_startVertices(BaseClass::m_startVertices),
          b_processedVertices(BaseClass::m_processedVertices),
          b_vertexToPreviousVertexMap(BaseClass::m_vertexToPreviousVertexMap),
          m_initializeDataFunction(getEmptyInitializeDataFunction()),
          m_updateDataFunction(getEmptyUpdateDataFunction()) {
        reinitializeStartingFrom(startVertices);
    }

    PathSearchUsingDfs(
        BaseGraphWithVertex const& graph, Vertices const& startVertices,
        InitializeDataFunction const& initializeDataFunction, UpdateDataFunction const& updateDataFunction)
        : BaseClass(graph),
          b_graph(BaseClass::m_graph),
          b_startVertices(BaseClass::m_startVertices),
          b_processedVertices(BaseClass::m_processedVertices),
          b_vertexToPreviousVertexMap(BaseClass::m_vertexToPreviousVertexMap),
          m_initializeDataFunction(initializeDataFunction),
          m_updateDataFunction(updateDataFunction) {
        reinitializeStartingFrom(startVertices);
    }

    Path getOrderedPathTo(Vertex const& endVertex) const { return this->getPathTo(endVertex); }

    void reinitializeStartingFrom(Vertices const& startVertices) {
        clear();
        initializeWithStartVertices(startVertices);
        m_initializeDataFunction(startVertices);
        // to maintain order, get the vertices in start vertices (because its sorted)
        for (Vertex const& startVertex : b_startVertices.getVertices()) {
            traverseUsingDfs(startVertex);
        }
    }

private:
    using BaseClass::clear;
    using BaseClass::initializeWithStartVertices;

    void traverseUsingDfs(Vertex const& vertex) {
        b_processedVertices.putVertex(vertex);
        for (Vertex const& adjacentVertex : b_graph.getAdjacentVerticesAt(vertex)) {
            if (b_processedVertices.isNotFound(adjacentVertex)) {
                b_vertexToPreviousVertexMap[adjacentVertex] = vertex;
                m_updateDataFunction(adjacentVertex, vertex);

                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    static InitializeDataFunction getEmptyInitializeDataFunction() {
        static InitializeDataFunction emptyInitializeDataFunction = [](Vertices const&) {};
        return emptyInitializeDataFunction;
    }

    static UpdateDataFunction getEmptyUpdateDataFunction() {
        static UpdateDataFunction noUpdateDataFunction = [](Vertex const&, Vertex const&) {};
        return noUpdateDataFunction;
    }

    BaseGraphWithVertex const& b_graph;
    CheckableVerticesWithVertex& b_startVertices;
    CheckableVerticesWithVertex& b_processedVertices;
    VertexToVertexMap& b_vertexToPreviousVertexMap;
    InitializeDataFunction m_initializeDataFunction;
    UpdateDataFunction m_updateDataFunction;
};

}  // namespace algorithm

}  // namespace alba

// Proposition: DFS marks all vertices connected to s in time proportional to the sum of their degrees
// Proof:
// -> If w is marked, then w is connected to s
// -> If w is connected to s, then w is marked.
// --> If w is unmarked, then consider last edge on a path from s to w that goes from a marked vertex to an unmarked
// one. Proof (running time):
// -> Each vertex connected to s is visited once

// Other analysis:
// The time complexity of depth-first search is O(n+m) where n is the number of nodes and m is the number of edges,
// because the algorithm processes each node and edge once.

// -> Applications:
// ---> Depth-first search (DFS) is an algorithm (or technique) for traversing a graph.
// ---> DFS uses a stack data structure for the traversal.
// ---> A graph can have more than one DFS traversal.
// ---> Following are the problems that use DFS as a building block.
// ---> 1) Detecting cycle in a graph
// -----> A graph has cycle if and only if we see a back edge during DFS.
// -----> So we can run DFS for the graph and check for back edges. (See this for details)
// ---> 2) Path Finding
// -----> We can specialize the DFS algorithm to find a path between two given vertices u and z.
// -----> i) Call DFS(G, u) with u as the start vertex.
// -----> ii) Use a stack S to keep track of the path between the start vertex and the current vertex.
// -----> iii) As soon as destination vertex z is encountered, return the path as the
// -----> contents of the stack
// ---> 3) Topological Sorting
// -----> Topological Sorting is mainly used for scheduling jobs from the given dependencies among jobs.
// -----> In computer science, applications of this type arise in instruction scheduling,
// -----> ordering of formula cell evaluation when recomputing formula values in spreadsheets,
// -----> logic synthesis, determining the order of compilation tasks to perform in makefiles,
// -----> data serialization, and resolving symbol dependencies in linkers.
// ---> 4) To test if a graph is bipartite
// -----> We can augment either BFS or DFS when we first discover a new vertex,
// -----> color it opposite its parents, and for each other edge,
// -----> check it doesn’t link two vertices of the same color.
// -----> The first vertex in any connected component can be red or black!
// -----> See this for details.
// ---> 5) Finding Strongly Connected Components of a graph
// -----> A directed graph is called strongly connected
// -----> if there is a path from each vertex in the graph to every other vertex.
// -----> (See this for DFS-based algo for finding Strongly Connected Components)
// ---> 6) Solving puzzles with only one solution, such as mazes.
// -----> (DFS can be adapted to find all solutions
// -----> to a maze by only including nodes on the current path in the visited set.)
