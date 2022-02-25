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

    DepthFirstSearch(BaseUndirectedGraph const& graph);

    Paths getPathsWithStartPointAndEndPoint(
            Vertex const startVertex,
            Vertex const endVertex);
    Paths getCompletePaths();
    void traverse(
            Vertex const startVertex,
            TraverseFunction const& traverseFunction);

private:
    void continueTraversal(
            Path & path,
            TraverseFunction const& traverseFunction);
    void clear();
    BaseUndirectedGraph const& m_graph;
    std::map<Vertex, bool> m_isProcessed;
};

}

}
