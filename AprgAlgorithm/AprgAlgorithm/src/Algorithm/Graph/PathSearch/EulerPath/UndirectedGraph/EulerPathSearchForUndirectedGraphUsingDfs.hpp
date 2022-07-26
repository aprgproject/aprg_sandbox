#pragma once

#include <Algorithm/Graph/PathSearch/EulerPath/UndirectedGraph/BaseEulerPathSearchForUndirectedGraph.hpp>

#include <algorithm>
#include <queue>
#include <stack>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class EulerPathSearchForUndirectedGraphUsingDfs : public BaseEulerPathSearchForUndirectedGraph<Vertex>
{
public:
    using BaseClass = BaseEulerPathSearchForUndirectedGraph<Vertex>;
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Path = typename GraphTypes<Vertex>::Path;
    using SetOfEdges = std::set<Edge>;
    using QueueOfEdges = std::queue<Edge>;
    using StackOfVertices = std::stack<Vertex>;
    using VertexToQueueOfEdgesMap = std::map<Vertex, QueueOfEdges>;

    EulerPathSearchForUndirectedGraphUsingDfs(BaseUndirectedGraphWithVertex const& graph)
        : BaseClass(graph)
        , b_graph(BaseClass::m_graph)
    {}

    Path getEulerCycle() const override
    {
        Path result;
        if(this->hasEulerCycle())
        {
            StackOfVertices eulerPathInStack;
            searchForEulerPathUsingDfs(eulerPathInStack, this->getStartingVertexForEulerCycle());
            putStackOfVerticesOnPath(result, eulerPathInStack);
        }
        return result;
    }
    Path getEulerPath() const override
    {
        Path result;        if(this->hasEulerPath())
        {
            StackOfVertices eulerPathInStack;
            searchForEulerPathUsingDfs(eulerPathInStack, this->getStartingVertexForEulerPath());
            putStackOfVerticesOnPath(result, eulerPathInStack);
        }
        return result;
    }
private:

    void searchForEulerPathUsingDfs(StackOfVertices & eulerPathInStack, Vertex const& startingVertex) const    {
        // This is DFS
        VertexToQueueOfEdgesMap vertexToQueueOfEdgesMap(createVertexToQueueOfEdgesMap());
        StackOfVertices pathToCheck;
        pathToCheck.push(startingVertex);
        SetOfEdges previousEdges;
        while(!pathToCheck.empty())
        {
            Vertex currentVertex(pathToCheck.top());
            pathToCheck.pop();
            auto it = vertexToQueueOfEdgesMap.find(currentVertex);
            // check the most recent vertex if there is a new path
            while(it != vertexToQueueOfEdgesMap.cend() && !it->second.empty()) // traverse to find a continuous path, until a dead end is found
            {
                QueueOfEdges & queueOfEdgesAtVertex(vertexToQueueOfEdgesMap[currentVertex]);
                Edge currentEdge(queueOfEdgesAtVertex.front());
                queueOfEdgesAtVertex.pop();
                if(previousEdges.find(currentEdge) != previousEdges.cend()) // must be a new edge
                {
                    continue;
                }
                previousEdges.emplace(currentEdge);
                pathToCheck.push(currentVertex); // put encountered vertices in path to check
                currentVertex = getTheOtherVertex(currentEdge, currentVertex); // get next vertex based from edge
                it = vertexToQueueOfEdgesMap.find(currentVertex);
            }
            eulerPathInStack.push(currentVertex); // put the most recent "dead end" vertices (vertices with no new edges) on euler path
        }
    }

    VertexToQueueOfEdgesMap createVertexToQueueOfEdgesMap() const
    {
        VertexToQueueOfEdgesMap vertexToQueueOfEdgesMap;
        for(Vertex const& vertex : b_graph.getVertices())
        {
            auto adjacentVertices(b_graph.getAdjacentVerticesAt(vertex));
            for(Vertex const& adjacencyVertex : adjacentVertices)
            {
                if(vertex < adjacencyVertex)
                {
                    vertexToQueueOfEdgesMap[vertex].emplace(Edge(vertex, adjacencyVertex));
                    vertexToQueueOfEdgesMap[adjacencyVertex].emplace(Edge(vertex, adjacencyVertex));
                }
            }
        }
        return vertexToQueueOfEdgesMap;
    }

    void putStackOfVerticesOnPath(Path & result, StackOfVertices & cycle) const
    {
        while(!cycle.empty())
        {
            result.emplace_back(cycle.top());
            cycle.pop();
        }
    }

    Vertex getTheOtherVertex(Edge const& edge, Vertex const& currentVertex) const
    {
        Vertex result;
        if(currentVertex == edge.first)
        {
            result = edge.second;
        }
        else
        {
            result = edge.first;
        }
        return result;
    }
    BaseUndirectedGraphWithVertex const& b_graph;
};

}

}
