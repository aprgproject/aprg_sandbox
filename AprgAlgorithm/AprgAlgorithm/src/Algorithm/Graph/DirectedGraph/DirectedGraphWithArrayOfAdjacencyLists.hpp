#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>

#include <array>

namespace alba {

namespace algorithm {

template <typename Vertex, int MAX_VERTEX_VALUE>
class DirectedGraphWithArrayOfAdjacencyLists : public BaseDirectedGraph<Vertex> {
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using AdjacencyList = SetOfVertices;
    using AdjacencyLists = std::array<AdjacencyList, MAX_VERTEX_VALUE>;

    DirectedGraphWithArrayOfAdjacencyLists() : m_numberOfEdges(0), m_adjacencyLists{} {}

    bool isEmpty() const override { return m_numberOfEdges == 0; }

    bool isDirectlyConnected(Vertex const& sourceVertex, Vertex const& destinationVertex) const override {
        AdjacencyList const& adjacencyList(m_adjacencyLists[sourceVertex]);
        return adjacencyList.find(destinationVertex) != adjacencyList.cend();
    }

    int getNumberOfVertices() const override { return getUniqueVertices().size(); }

    int getNumberOfEdges() const override { return m_numberOfEdges; }

    Vertices getAdjacentVerticesAt(Vertex const& vertex) const override {
        AdjacencyList const& adjacencyList(m_adjacencyLists[vertex]);
        return Vertices(adjacencyList.cbegin(), adjacencyList.cend());
    }

    Vertices getVertices() const override {
        SetOfVertices uniqueVertices(getUniqueVertices());
        return Vertices(uniqueVertices.cbegin(), uniqueVertices.cend());
    }

    Edges getEdges() const override {
        Edges result;
        for (Vertex vertex1 = 0; vertex1 < static_cast<Vertex>(m_adjacencyLists.size()); vertex1++) {
            AdjacencyList const& adjacencyList(m_adjacencyLists[vertex1]);
            for (Vertex const& vertex2 : adjacencyList) {
                result.emplace_back(vertex1, vertex2);
            }
        }
        return result;
    }

    void connect(Vertex const& sourceVertex, Vertex const& destinationVertex) override {
        if (!isDirectlyConnected(sourceVertex, destinationVertex)) {
            m_numberOfEdges++;
            m_adjacencyLists[sourceVertex].emplace(destinationVertex);
        }
    }

    void disconnect(Vertex const& sourceVertex, Vertex const& destinationVertex) override {
        if (isDirectlyConnected(sourceVertex, destinationVertex)) {
            m_numberOfEdges--;
            m_adjacencyLists[sourceVertex].erase(destinationVertex);
        }
    }

    void clear() override {
        m_numberOfEdges = 0;
        for (Vertex sourceVertex = 0; sourceVertex < static_cast<Vertex>(m_adjacencyLists.size()); sourceVertex++) {
            m_adjacencyLists[sourceVertex].clear();
        }
    }

protected:
    SetOfVertices getUniqueVertices() const {
        SetOfVertices uniqueVertices;
        for (Vertex sourceVertex = 0; sourceVertex < static_cast<Vertex>(m_adjacencyLists.size()); sourceVertex++) {
            AdjacencyList const& adjacencyList(m_adjacencyLists[sourceVertex]);
            if (!adjacencyList.empty()) {
                uniqueVertices.emplace(sourceVertex);
                std::copy(
                    adjacencyList.cbegin(), adjacencyList.cend(),
                    std::inserter(uniqueVertices, uniqueVertices.cbegin()));
            }
        }
        return uniqueVertices;
    }

    friend std::ostream& operator<<(std::ostream& out, DirectedGraphWithArrayOfAdjacencyLists const& graph) {
        out << "Adjacency Lists: \n";
        for (Vertex vertex = 0; vertex < static_cast<Vertex>(graph.m_adjacencyLists.size()); vertex++) {
            DirectedGraphWithArrayOfAdjacencyLists::AdjacencyList const& adjacencyList(
                graph.m_adjacencyLists[vertex]);
            if (!adjacencyList.empty()) {
                out << "Adjacent with vertex " << vertex << ": {";
                containerHelper::saveContentsToStream(out, adjacencyList, containerHelper::StreamFormat::String);
                out << "} \n";
            }
        }
        return out;
    }

    int m_numberOfEdges;
    AdjacencyLists m_adjacencyLists;
};

}  // namespace algorithm

}  // namespace alba
