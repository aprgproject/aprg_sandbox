#pragma once

#include <Algorithm/Graph/GraphTypes.hpp>

#include <string>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class BaseUndirectedGraph
{
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edges = typename GraphTypes<Vertex>::Edges;

    virtual bool hasAnyConnection(Vertex const& vertex) const = 0;
    virtual bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const = 0;
    virtual unsigned int getNumberOfVertices() const = 0;
    virtual unsigned int getNumberOfEdges() const = 0;
    virtual Vertices getAdjacentVerticesAt(Vertex const& vertex) const = 0;
    virtual Vertices getVertices() const = 0;
    virtual Edges getEdges() const = 0;
    virtual std::string getDisplayableString() const = 0;

    virtual void connect(Vertex const& vertex1, Vertex const& vertex2) = 0;
    virtual void disconnect(Vertex const& vertex1, Vertex const& vertex2) = 0;
};

}

}
