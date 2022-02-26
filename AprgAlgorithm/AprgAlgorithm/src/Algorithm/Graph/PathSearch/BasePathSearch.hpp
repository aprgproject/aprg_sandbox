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
    using VertexToVertexMap = std::map<Vertex, Vertex>;
    using IsProcessedMap = std::map<Vertex, bool>;

    BasePathSearch(BaseUndirectedGraph const& graph, Vertex const startVertex);

    bool hasPathTo(Vertex const endVertex) const;
    Path getPathTo(Vertex const endVertex) const;
    IsProcessedMap const& getIsProcessedMap();

    virtual void reinitializeStartingFrom(Vertex const startVertex) = 0;
protected:
    void clear();
    BaseUndirectedGraph const& m_graph;
    Vertex m_startVertex;
    VertexToVertexMap m_vertexToPreviousVertexMap;
    IsProcessedMap m_isProcessed;
};

}
}
