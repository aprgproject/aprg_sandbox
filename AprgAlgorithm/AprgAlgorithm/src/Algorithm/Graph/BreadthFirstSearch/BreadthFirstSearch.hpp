#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <functional>
#include <map>

namespace alba
{

namespace algorithm
{

class BreadthFirstSearch
{
public:
    using TraverseFunction=std::function<void(Path const& path, bool & shouldStop)>;

    BreadthFirstSearch(BaseUndirectedGraph const& graph, Vertex const startVertex);

    bool hasPathTo(Vertex const endVertex) const;
    Path getShortestPathTo(Vertex const endVertex) const;

    void reinitializeStartingFrom(Vertex const startVertex);

private:
    void clear();
    BaseUndirectedGraph const& m_graph;
    Vertex m_startVertex;
    std::map<Vertex, Vertex> m_vertexToNextVertex;
    std::map<Vertex, bool> m_isProcessed;
};

}

}
