#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

#include <string>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BaseGraph
{
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edges = typename GraphTypes<Vertex>::Edges;

    virtual bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const = 0;
    virtual GraphDirectionType getGraphDirectionType() const = 0;
    virtual unsigned int getNumberOfVertices() const = 0;
    virtual unsigned int getNumberOfEdges() const = 0;
    virtual Vertices getAdjacentVerticesAt(Vertex const& vertex) const = 0;
    virtual Vertices getVertices() const = 0;
    virtual Edges getEdges() const = 0;
    virtual std::string getDisplayableString() const = 0;

    virtual void connect(Vertex const& sourceVertex, Vertex const& destinationVertex) = 0;
    virtual void disconnect(Vertex const& sourceVertex, Vertex const& destinationVertex) = 0;
    virtual void clear() = 0;
};

}

}
