#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

class ConnectedComponentsUsingDfs : public BaseConnectedComponents
{
public:
    using VertexToComponentIdMap = std::map<Vertex, unsigned int>;
    using IsProcessedMap = std::map<Vertex, bool>;

    ConnectedComponentsUsingDfs(BaseUndirectedGraph const& graph);
    bool isConnected(Vertex const vertex1, Vertex const vertex2) const override;

private:
    void initialize();
    BaseUndirectedGraph const& m_graph;
    VertexToComponentIdMap m_vertexToComponentIdMap;
    IsProcessedMap m_isProcessed;
};

}

}
