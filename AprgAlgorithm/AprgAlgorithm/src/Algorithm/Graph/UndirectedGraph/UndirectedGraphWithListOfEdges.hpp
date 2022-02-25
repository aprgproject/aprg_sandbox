#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <set>

namespace alba
{

namespace algorithm
{

class UndirectedGraphWithListOfEdges : public BaseUndirectedGraph
{
public:
    struct EdgeInSet : public Edge
    {
        EdgeInSet(Vertex const vertex1, Vertex const vertex2);
        bool operator<(EdgeInSet const& otherEdge) const;
    };

    using SetOfEdges = std::set<EdgeInSet>;

    UndirectedGraphWithListOfEdges();

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
    SetOfEdges m_edges;
};

}

}
