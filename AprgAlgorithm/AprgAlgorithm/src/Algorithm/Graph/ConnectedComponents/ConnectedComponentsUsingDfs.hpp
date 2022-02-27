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
    ConnectedComponentsUsingDfs(BaseUndirectedGraph const& graph);
    bool isConnected(Vertex const vertex1, Vertex const vertex2) const override;

private:
    void initialize();
    BaseUndirectedGraph const& m_graph;
    VertexToUnsignedIntMap m_vertexToComponentIdMap;
    VertexToBoolMap m_isProcessed;
};

}

}
