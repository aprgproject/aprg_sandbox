#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class CycleDetectionUsingDfs {
public:
    enum class SearchType { Unknown, AllCycles, OneCycle };

    enum class VertexState { NotProcessed, Processing, Processed };

    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Path = typename GraphTypes<Vertex>::Path;
    using Paths = typename GraphTypes<Vertex>::Paths;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using VertexToVertexStateMap = std::map<Vertex, VertexState>;

    CycleDetectionUsingDfs(BaseGraphWithVertex const& graph) : m_graph(graph), m_searchType(SearchType::Unknown) {}

    Paths getAllCycles() {
        initialize();
        m_searchType = SearchType::AllCycles;
        search();
        return m_pathsWithCycle;
    }

    Path getOneCycle() {
        initialize();
        m_searchType = SearchType::OneCycle;
        search();
        Path result;
        if (!m_pathsWithCycle.empty()) {
            result = m_pathsWithCycle.front();
        }
        return result;
    }

private:
    bool hasACycle() const { return !m_pathsWithCycle.empty(); }

    Path getPathWithCycle(Vertex const& secondToTheLastVertex, Vertex const& lastVertex) const {
        bool isSuccessful(true);
        Path reversedPath{lastVertex};
        Vertex currentVertex = secondToTheLastVertex;
        while (currentVertex != lastVertex) {
            reversedPath.emplace_back(currentVertex);
            auto it = m_vertexToPreviousVertexMap.find(currentVertex);
            if (it != m_vertexToPreviousVertexMap.cend()) {
                currentVertex = it->second;
            } else {
                isSuccessful = false;
                break;
            }
        }
        Path result;
        if (isSuccessful) {
            reversedPath.emplace_back(lastVertex);
            result.reserve(reversedPath.size());
            std::copy(reversedPath.crbegin(), reversedPath.crend(), std::back_inserter(result));
        }
        return result;
    }

    void initialize() {
        m_searchType = SearchType::Unknown;
        m_vertexToPreviousVertexMap.clear();
        m_pathsWithCycle.clear();
        initializeVertexStatesMap();
    }

    void initializeVertexStatesMap() {
        for (Vertex const& vertex : m_graph.getVertices()) {
            m_vertexStatesMap[vertex] = VertexState::NotProcessed;
        }
    }

    void search() {
        for (Vertex const& vertex : m_graph.getVertices()) {
            if (VertexState::NotProcessed == m_vertexStatesMap[vertex]) {
                searchUsingDfs(vertex);
            }
        }
    }

    void searchUsingDfs(Vertex const& startVertex) {
        switch (m_graph.getGraphDirectionType()) {
            case GraphDirectionType::Directed: {
                searchUsingDfsWithDirectedGraph(startVertex);
                break;
            }
            case GraphDirectionType::Undirected: {
                searchUsingDfsWithUndirectedGraph(startVertex, startVertex);
                break;
            }
        }
    }

    void searchUsingDfsWithDirectedGraph(Vertex const& startVertex) {
        m_vertexStatesMap[startVertex] = VertexState::Processing;
        for (Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex)) {
            VertexState adjacentVertexState = m_vertexStatesMap[adjacentVertex];
            if (SearchType::OneCycle == m_searchType && hasACycle()) {
                // this check is needed to prune all recursion instances once cycle has been detected
                break;
            } else if (VertexState::NotProcessed == adjacentVertexState) {
                m_vertexToPreviousVertexMap[adjacentVertex] = startVertex;                searchUsingDfsWithDirectedGraph(adjacentVertex);
            } else if (VertexState::Processing == adjacentVertexState) {
                // there is a cycle if adjacent vertex is in processing as well
                m_pathsWithCycle.emplace_back(getPathWithCycle(startVertex, adjacentVertex));            }
        }
        m_vertexStatesMap[startVertex] = VertexState::Processed;
    }

    void searchUsingDfsWithUndirectedGraph(Vertex const& startVertex, Vertex const& previousVertex) {
        m_vertexStatesMap[startVertex] = VertexState::Processing;
        for (Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(startVertex)) {
            VertexState adjacentVertexState = m_vertexStatesMap[adjacentVertex];
            if (SearchType::OneCycle == m_searchType && hasACycle()) {
                // this check is needed to end all recursion instances once cycle has been detected
                break;
            } else if (VertexState::NotProcessed == adjacentVertexState) {
                m_vertexToPreviousVertexMap[adjacentVertex] = startVertex;                searchUsingDfsWithUndirectedGraph(adjacentVertex, startVertex);
            } else if (previousVertex != adjacentVertex && VertexState::Processing == adjacentVertexState) {
                // there is a cycle if adjacent vertex is in processing as well
                // if previous and adjacent are equal then its the same edge (and not technically a cycle)                m_pathsWithCycle.emplace_back(getPathWithCycle(startVertex, adjacentVertex));
            }
        }
        m_vertexStatesMap[startVertex] = VertexState::Processed;
    }

    BaseGraphWithVertex const& m_graph;
    SearchType m_searchType;
    VertexToVertexStateMap m_vertexStatesMap;
    VertexToVertexMap m_vertexToPreviousVertexMap;
    Paths m_pathsWithCycle;
};

// Algorithm
// The idea is to go through the nodes of the graph and always begin a depth-first search at the current node if it has
// not been processed yet. During the searches, the nodes have three possible states:
// -> state 0: the node has not been processed (white)
// -> state 1: the node is under processing (light gray)
// -> state 2: the node has been processed (dark gray)
// 1) Initially, the state of each node is 0.
// 2) When a search reaches a node for the first time, its state becomes 1.
// 3) Finally, after all successors of the node have been processed, its state becomes 2.
// 4) If the graph contains a cycle, we will find this out during the search, because sooner or later we will arrive at
// a node whose state is 1.

// Other analysis:
// Another way to find out whether a graph contains a cycle is to simply calculate the number of nodes and edges in
// every component. If a component contains c nodes and no cycle, it must contain exactly c-1 edges (so it has to be a
// tree). If there are c or more edges, the component surely contains a cycle. This is only for undirected graph?

}  // namespace algorithm

}  // namespace alba
