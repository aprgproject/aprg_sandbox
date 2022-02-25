#include "DepthFirstSearch.hpp"

namespace alba
{

namespace algorithm
{

DepthFirstSearch::DepthFirstSearch(
        BaseUndirectedGraph const& graph)
    : m_graph(graph)
    , m_isProcessed()
{}

Paths DepthFirstSearch::getPathsWithStartPointAndEndPoint(
        Vertex const startVertex,
        Vertex const endVertex)
{
    Paths result;
    traverse(startVertex, [&](Path const& path, bool & shouldStop)
    {
        if(path.back() == endVertex)
        {
            result.emplace_back(path);
            shouldStop = true;
        }
    });
    return result;
}

Paths DepthFirstSearch::getCompletePaths()
{
    Paths result;
    Vertices vertices(m_graph.getVertices());
    for(Vertex startVertex : vertices)
    {
        traverse(startVertex, [&](Path const& path, bool &)
        {
            if(vertices.size() == path.size())
            {
                result.emplace_back(path);
            }
        });
    }
    return result;
}

void DepthFirstSearch::traverse(
        Vertex const startVertex,
        TraverseFunction const& traverseFunction)
{
    clear();
    Path path{startVertex};
    m_isProcessed[startVertex] = true;
    continueTraversal(path, traverseFunction);
}

void DepthFirstSearch::continueTraversal(
        Path & path,
        TraverseFunction const& traverseFunction)
{
    bool shouldStop(false);
    traverseFunction(path, shouldStop);

    if(!shouldStop)
    {
        Vertices adjacentVertices(m_graph.getAdjacentVerticesAt(path.back()));
        for(Vertex const adjacentVertex : adjacentVertices)
        {
            if(!m_isProcessed.at(adjacentVertex))
            {
                path.emplace_back(adjacentVertex);
                m_isProcessed[adjacentVertex] = true;

                continueTraversal(path, traverseFunction);

                path.pop_back();
                m_isProcessed[adjacentVertex] = false;
            }
        }
    }
}


void DepthFirstSearch::clear()
{
    Vertices vertices(m_graph.getVertices());
    for(Vertex const vertex : vertices)
    {
        m_isProcessed[vertex] = false;
    }
}

}

}
