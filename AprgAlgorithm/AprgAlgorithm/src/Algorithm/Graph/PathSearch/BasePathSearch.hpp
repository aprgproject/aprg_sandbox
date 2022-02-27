#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

class BasePathSearch
{
public:

    BasePathSearch(BaseUndirectedGraph const& graph, Vertex const startVertex);

    bool hasPathTo(Vertex const endVertex) const;
    Path getPathTo(Vertex const endVertex) const;
    VertexToBoolMap const& getIsProcessedMap();

    virtual void reinitializeStartingFrom(Vertex const startVertex) = 0;

protected:
    void clear();
    BaseUndirectedGraph const& m_graph;
    Vertex m_startVertex;
    VertexToVertexMap m_vertexToPreviousVertexMap;
    VertexToBoolMap m_isProcessed;
};

}

}
