#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <map>
#include <set>

namespace alba
{

namespace algorithm
{

class UndirectedGraphWithVertexToAdjacencyListsMap : public BaseUndirectedGraph
{
public:
    using AdjacencyList = std::set<Vertex>;
    using AdjacencyLists = std::map<Vertex, AdjacencyList>;

    UndirectedGraphWithVertexToAdjacencyListsMap();

    bool isConnected(Vertex const vertex1, Vertex const vertex2) const override;
    unsigned int getNumberOfVertices() const override;
    unsigned int getNumberOfEdges() const override;
    Vertices getAdjacentVerticesAt(Vertex const vertex) const override;
    Vertices getVertices() const override;
    Edges getEdges() const override;
    std::string getDisplayableString() const override;
    void connect(Vertex const vertex1, Vertex const vertex2) override;
    void disconnect(Vertex const vertex1, Vertex const vertex2) override;

private:
    bool isAnyVertexConnectedAtThisVertex(Vertex const vertex) const;
    unsigned int m_numberOfVertices;
    unsigned int m_numberOfEdges;
    AdjacencyLists m_adjacencyLists;
};

}

}
