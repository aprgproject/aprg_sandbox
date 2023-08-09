#pragma once

#include <Algorithm/Graph/PathSearch/EulerCircuitAndPath/BaseEulerPathSearch.hpp>

#include <algorithm>
#include <queue>
#include <stack>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class EulerPathSearchUsingDfs : public BaseEulerPathSearch<Vertex>
{
public:
    using BaseClass = BaseEulerPathSearch<Vertex>;
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Path = typename GraphTypes<Vertex>::Path;
    using SetOfEdges = std::set<Edge>;
    using QueueOfEdges = std::queue<Edge>;
    using StackOfVertices = std::stack<Vertex>;
    using VertexToQueueOfEdgesMap = std::map<Vertex, QueueOfEdges>;

    EulerPathSearchUsingDfs(BaseUndirectedGraphWithVertex const& graph)
        : BaseClass(graph)
    {}

    Path getEulerCircuit() const override
    {
        Path result;
        if(this->hasEulerCircuit())
        {
            StackOfVertices eulerPathInStack;
            searchForEulerPath(eulerPathInStack, this->getStartingVertexForEulerCircuit());
            if(eulerPathInStack.size() == this->m_graph.getNumberOfVertices()+1)
            {
                putStackOfVerticesOnPath(result, eulerPathInStack);
            }
        }
        return result;
    }

    Path getEulerPath() const override
    {
        Path result;
        if(this->hasEulerPath())
        {
            StackOfVertices eulerPathInStack;
            searchForEulerPath(eulerPathInStack, this->getStartingVertexForEulerPath());
            if(eulerPathInStack.size() == this->m_graph.getNumberOfVertices())
            {
                putStackOfVerticesOnPath(result, eulerPathInStack);
            }
        }
        return result;
    }

private:

    void searchForEulerPath(StackOfVertices & eulerPathInStack, Vertex const& startingVertex) const
    {
        VertexToQueueOfEdgesMap vertexToQueueOfEdgesMap(createVertexToQueueOfEdgesMap());
        StackOfVertices verticesToProcess;
        verticesToProcess.push(startingVertex);
        SetOfEdges checkableEdges;
        while(!verticesToProcess.empty())
        {
            Vertex currentVertex(verticesToProcess.top());
            verticesToProcess.pop();
            auto it = vertexToQueueOfEdgesMap.find(currentVertex);
            while(it != vertexToQueueOfEdgesMap.cend() && !it->second.empty())
            {
                QueueOfEdges & queueOfEdgesAtVertex(vertexToQueueOfEdgesMap[currentVertex]);
                Edge currentEdge(queueOfEdgesAtVertex.front());
                queueOfEdgesAtVertex.pop();
                if(checkableEdges.find(currentEdge) != checkableEdges.cend())
                {
                    continue;
                }
                checkableEdges.emplace(currentEdge);
                verticesToProcess.push(currentVertex); // put encountered vertices as vertices to process
                currentVertex = getTheOtherVertex(currentEdge, currentVertex); // get next vertex based from edge
                it = vertexToQueueOfEdgesMap.find(currentVertex);
            }
            eulerPathInStack.push(currentVertex);
        }
    }

    VertexToQueueOfEdgesMap createVertexToQueueOfEdgesMap() const
    {
        VertexToQueueOfEdgesMap vertexToQueueOfEdgesMap;
        for(Vertex const& vertex : this->m_graph.getVertices())
        {
            auto adjacentVertices(this->m_graph.getAdjacentVerticesAt(vertex));
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
};

}

}
