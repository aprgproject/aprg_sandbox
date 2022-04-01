#pragma once

#include <Algorithm/Graph/CycleDetection/CycleDetectionUsingDfs.hpp>
#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithRelax.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparisonTemplateType>
class PathSearchUsingBellmanFord : public BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparisonTemplateType>
{
public:
    using Graph = EdgeWeightedGraph;
    using BaseClass = BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparisonTemplateType>;
    using DequeOfVertices = typename GraphTypes<Vertex>::DequeOfVertices;
    using VertexToEdgeWithWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToEdgeWithWeightMap;

    PathSearchUsingBellmanFord(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
        , m_cost(0U)
        , m_hasNegativeCycle(false)
    {
        searchForPath();
    }

private:

    void searchForPath()
    {
        Graph const& graph(this->m_graph);
        unsigned int numberOfVertices(graph.getNumberOfVertices());
        enqueue(this->m_startVertex);
        while(!m_queueOfVertices.empty() && !m_hasNegativeCycle)
        {
            Vertex vertexAtQueue(dequeue());
            this->relaxAt(vertexAtQueue, [&](Vertex const&, Vertex const& destinationVertex, Weight const&)
            {
                if(m_verticesInQueue.isNotFound(destinationVertex))
                {
                    enqueue(destinationVertex);
                }
            },
            [&]()
            {
                if(m_cost++ % numberOfVertices == 0)
                {
                    findNegativeCycle();
                }
            });
        }
    }

    void enqueue(Vertex const& vertex)
    {
        m_queueOfVertices.emplace_back(vertex);
        m_verticesInQueue.putVertex(vertex);
    }

    Vertex dequeue()
    {
        Vertex result;
        if(!m_queueOfVertices.empty())
        {
            result = m_queueOfVertices.front();
            m_queueOfVertices.pop_front();
            m_verticesInQueue.removeVertex(result);
        }
        return result;
    }

    void findNegativeCycle()
    {
        Graph const& graph(this->m_graph);
        VertexToEdgeWithWeightMap const& vertexToEdgeWithUpdatedWeightMap(this->m_vertexToEdgeWithUpdatedWeightMap);
        EdgeWeightedGraph shortestPathTree;
        for(Vertex const& vertex : graph.getVertices())
        {
            auto it = vertexToEdgeWithUpdatedWeightMap.find(vertex);
            if(it != vertexToEdgeWithUpdatedWeightMap.cend())
            {
                shortestPathTree.connect(it->second.first, it->second.second, it->second.weight);
            }
        }
        CycleDetectionUsingDfs<Vertex> cycleDetection(shortestPathTree);
        cycleDetection.checkForCycles();
        m_hasNegativeCycle = cycleDetection.hasCycle();
    }

    unsigned int m_cost;
    bool m_hasNegativeCycle;
    DequeOfVertices m_queueOfVertices;
    CheckableVertices<Vertex> m_verticesInQueue;

};

}

}
