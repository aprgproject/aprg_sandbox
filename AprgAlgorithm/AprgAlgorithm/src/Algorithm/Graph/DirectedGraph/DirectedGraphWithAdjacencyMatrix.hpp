#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <array>

namespace alba {

namespace algorithm {

template <typename Vertex, int MAX_VERTEX_VALUE>
class DirectedGraphWithAdjacencyMatrix : public BaseDirectedGraph<Vertex> {
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using AdjacencyMatrix = matrix::AlbaMatrix<bool>;

    DirectedGraphWithAdjacencyMatrix() : m_numberOfEdges(0), m_adjacencyMatrix(MAX_VERTEX_VALUE, MAX_VERTEX_VALUE) {}

    bool isEmpty() const override { return m_numberOfEdges == 0; }

    bool isDirectlyConnected(Vertex const& vertex1, Vertex const& vertex2) const override {
        return m_adjacencyMatrix.getEntry(vertex1, vertex2);
    }

    int getNumberOfVertices() const override { return getVertices().size(); }

    int getNumberOfEdges() const override { return m_numberOfEdges; }

    Vertices getAdjacentVerticesAt(Vertex const& vertex) const override {
        Vertices result;
        Vertex numberOfRows(m_adjacencyMatrix.getNumberOfRows());
        for (Vertex possibleAdjacentVertex = 0; possibleAdjacentVertex < numberOfRows; possibleAdjacentVertex++) {
            if (isDirectlyConnected(vertex, possibleAdjacentVertex)) {
                result.emplace_back(possibleAdjacentVertex);
            }
        }
        return result;
    }

    Vertices getVertices() const override {
        std::array<bool, MAX_VERTEX_VALUE> isVertexIncluded{};

        Vertex numberOfColumns(m_adjacencyMatrix.getNumberOfColumns());
        Vertex numberOfRows(m_adjacencyMatrix.getNumberOfRows());
        for (Vertex vertex1 = 0; vertex1 < numberOfColumns; vertex1++) {
            for (Vertex vertex2 = 0; vertex2 < numberOfRows; vertex2++) {
                if (isDirectlyConnected(vertex1, vertex2)) {
                    isVertexIncluded[vertex1] = true;
                    isVertexIncluded[vertex2] = true;
                }
            }
        }

        Vertices result;
        for (Vertex vertex = 0; vertex < MAX_VERTEX_VALUE; vertex++) {
            if (isVertexIncluded[vertex]) {
                result.emplace_back(vertex);
            }
        }
        return result;
    }

    Edges getEdges() const override {
        Edges result;
        Vertex numberOfColumns(m_adjacencyMatrix.getNumberOfColumns());
        Vertex numberOfRows(m_adjacencyMatrix.getNumberOfRows());
        for (Vertex vertex1 = 0; vertex1 < numberOfColumns; vertex1++) {
            for (Vertex vertex2 = 0; vertex2 < numberOfRows; vertex2++) {
                if (isDirectlyConnected(vertex1, vertex2)) {
                    result.emplace_back(vertex1, vertex2);
                }
            }
        }
        return result;
    }

    AdjacencyMatrix const& getAdjacencyMatrix() const { return m_adjacencyMatrix; }

    void connect(Vertex const& vertex1, Vertex const& vertex2) override {
        if (!isDirectlyConnected(vertex1, vertex2)) {
            m_numberOfEdges++;
            m_adjacencyMatrix.setEntry(vertex1, vertex2, true);
        }
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override {
        if (isDirectlyConnected(vertex1, vertex2)) {
            m_numberOfEdges--;
            m_adjacencyMatrix.setEntry(vertex1, vertex2, false);
        }
    }

    void clear() override {
        m_numberOfEdges = 0;
        m_adjacencyMatrix.clearAndResize(MAX_VERTEX_VALUE, MAX_VERTEX_VALUE);
    }

protected:
    friend std::ostream& operator<<(std::ostream& out, DirectedGraphWithAdjacencyMatrix const& graph) {
        matrix::AlbaMatrix<std::string> matrixToDisplay(MAX_VERTEX_VALUE + 1, MAX_VERTEX_VALUE + 1);
        matrixToDisplay.setEntry(0, 0, "X");
        for (int i = 0; i < MAX_VERTEX_VALUE; i++) {
            matrixToDisplay.setEntry(i + 1, 0, std::string("[") + stringHelper::convertToString(i) + std::string("]"));
            matrixToDisplay.setEntry(0, i + 1, std::string("[") + stringHelper::convertToString(i) + std::string("]"));
        }
        graph.m_adjacencyMatrix.iterateAllThroughYAndThenX([&](int const x, int const y) {
            matrixToDisplay.setEntry(x + 1, y + 1, stringHelper::convertToString(graph.isDirectlyConnected(x, y)));
        });

        out << "Adjacency " << matrixToDisplay;
        return out;
    }

    int m_numberOfEdges;
    AdjacencyMatrix m_adjacencyMatrix;  // vertex by adjacent matrix
};

}  // namespace algorithm

}  // namespace alba
