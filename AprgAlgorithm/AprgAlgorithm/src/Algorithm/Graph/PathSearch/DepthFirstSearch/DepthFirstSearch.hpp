#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <functional>
#include <map>

namespace alba
{

namespace algorithm
{

class DepthFirstSearch
{
public:
    using TraverseFunction=std::function<void(Path const& path, bool & shouldStop)>;

    DepthFirstSearch(BaseUndirectedGraph const& graph, Vertex const startVertex);

    bool hasPathTo(Vertex const endVertex);
    Path getOrderedPathTo(Vertex const endVertex);

    void reinitializeStartingFrom(Vertex const startVertex);

private:
    void continueTraversal(Vertex const vertex);
    void clear();
    BaseUndirectedGraph const& m_graph;
    Vertex m_startVertex;
    std::map<Vertex, Vertex> m_vertexToNextVertex;
    std::map<Vertex, bool> m_isProcessed;
};

}

}
