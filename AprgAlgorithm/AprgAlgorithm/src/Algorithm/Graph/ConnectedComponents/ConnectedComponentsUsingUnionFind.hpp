#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>

namespace alba
{

namespace algorithm
{

class ConnectedComponentsUsingUnionFind : public BaseConnectedComponents
{
public:
    ConnectedComponentsUsingUnionFind(BaseUndirectedGraph const& graph);
    bool isConnected(Vertex const vertex1, Vertex const vertex2) const override;

private:
    void initialize();
    BaseUndirectedGraph const& m_graph;
    UnionFindUsingMap<Vertex> m_unionFind;
};

}

}
