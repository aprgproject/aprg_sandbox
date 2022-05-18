#pragma once

#include <Algorithm/Graph/ConnectedComponents/ConnectedComponentsUsingDfs.hpp>
#include <Algorithm/Graph/PathSearch/EulerCircuitAndPath/BaseEulerPathSearch.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <algorithm>
namespace alba
{

namespace algorithm
{

template <typename Vertex>
class FleuryAlgorithm : public BaseEulerPathSearch<Vertex>
{
public:
    using BaseClass = BaseEulerPathSearch<Vertex>;
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using EdgeWithVertexComparison = typename GraphTypes<Vertex>::EdgeWithVertexComparison;
    using SetOfEdges = typename GraphTypes<Vertex>::SetOfEdges;
    using GraphToManipulate = UndirectedGraphWithListOfEdges<Vertex>;

    FleuryAlgorithm(BaseUndirectedGraphWithVertex const& graph)
        : BaseClass(graph)
    {}

    Path getEulerCircuit() const override
    {
        // Fleury’s Algorithm
        // 1. Start at any vertex if finding an Euler circuit. If finding an Euler path, start at one of the two vertices with odd degree.
        // 2. Choose any edge leaving your current vertex, provided deleting that edge will not separate the graph into two disconnected sets of edges.        // 3. Add that edge to your circuit, and delete it from the graph.
        // 4. Continue until you’re done.

        Path result;
        Edges originalEdges(this->m_graph.getEdges());
        if(!originalEdges.empty())
        {
            // start at the vertices of the first edge            searchForEulerPath(result, originalEdges.front().first, originalEdges);
        }
        return result;
    }

    Path getEulerPath() const override
    {
        Path result;
        Edges originalEdges(this->m_graph.getEdges());
        if(!originalEdges.empty())
        {
            // check graph for starting vertex
            searchForEulerPath(result, this->getStartingVertexForEulerPath(), originalEdges);
        }
        return result;
    }
private:

    bool isGraphStillConnectedWithoutOneEdge(GraphToManipulate const& graph, Edge const& edgeToDelete) const    {
        GraphToManipulate graphWithDeletedEdge(graph);
        graphWithDeletedEdge.disconnect(edgeToDelete.first, edgeToDelete.second);
        ConnectedComponentsUsingDfs<Vertex> connectedComponents(graphWithDeletedEdge);
        return connectedComponents.getNumberOfComponentIds() <= 1;
    }

    GraphToManipulate createGraphToManipulate(Edges const& originalEdges) const
    {
        GraphToManipulate graphToManipulate;        for(Edge const& originalEdge: originalEdges)
        {
            graphToManipulate.connect(originalEdge.first, originalEdge.second);
        }
        return graphToManipulate;
    }

    void putEulerEdgesOnPath(Path & result, Edges const& edgesInEulerCircuit) const
    {
        result.emplace_back(edgesInEulerCircuit.front().first);
        for(Edge const& edge : edgesInEulerCircuit)
        {
            result.emplace_back(edge.second);
        }
    }

    void searchForEulerPath(Path & result, Vertex const& startVertex, Edges const& originalEdges) const
    {
        GraphToManipulate graphToManipulate(createGraphToManipulate(originalEdges));
        SetOfEdges & currentEdges(graphToManipulate.getSetOfEdgesReference());
        Edges edgesInEulerCircuit;
        bool isComplete(true);
        Edge edgeToDelete(startVertex, startVertex);
        while(!currentEdges.empty())
        {
            auto nextEdgeToDeleteIt = std::find_if(currentEdges.cbegin(), currentEdges.cend(), [&](Edge const& currentEdge)
            {
                return  edgeToDelete.second == currentEdge.first
                    && isGraphStillConnectedWithoutOneEdge(graphToManipulate, edgeToDelete);  // THIS IS COSTLY!
            });
            if(nextEdgeToDeleteIt != currentEdges.cend())
            {                edgeToDelete = *nextEdgeToDeleteIt;
                edgesInEulerCircuit.emplace_back(edgeToDelete);
                currentEdges.erase(EdgeWithVertexComparison(edgeToDelete.first, edgeToDelete.second));
                currentEdges.erase(EdgeWithVertexComparison(edgeToDelete.second, edgeToDelete.first));            }
            else
            {
                isComplete = false;
                break;
            }
        }
        if(isComplete)
        {
            putEulerEdgesOnPath(result, edgesInEulerCircuit);
        }
    }
};

}
}