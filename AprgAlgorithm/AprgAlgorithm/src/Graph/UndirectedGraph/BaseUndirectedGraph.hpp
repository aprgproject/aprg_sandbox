#pragma once

#include <Graph/GraphTypes.hpp>

#include <string>

namespace alba
{

namespace algorithm
{

class BaseUndirectedGraph
{
public:

    virtual unsigned int getNumberOfVertices() const = 0;
    virtual unsigned int getNumberOfEdges() const = 0;
    virtual Vertices getAdjacentVerticesAt(Vertex const vertex) const = 0;
    virtual std::string getDisplayableString() const = 0;

    virtual void connect(Vertex const vertex1, Vertex const vertex2) = 0;
};

}

}
