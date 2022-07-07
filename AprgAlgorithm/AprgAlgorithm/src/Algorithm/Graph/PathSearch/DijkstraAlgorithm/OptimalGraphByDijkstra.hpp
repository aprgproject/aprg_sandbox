#pragma once

namespace alba
{

namespace algorithm
{

template <typename EdgeWeightedDirectedGraph, typename PathSearchUsingDijkstra>
EdgeWeightedDirectedGraph getOptimalDirectedGraph(PathSearchUsingDijkstra const& pathSearch)
{
    EdgeWeightedDirectedGraph result;
    for(auto const& vertexToEdgePair: pathSearch.getVertexToEdgeWithBestWeightMap())
    {
        if(pathSearch.getStartVertex() != vertexToEdgePair.first) // remove start vertex because its started there
        {
            auto const& edgeWithWeight(vertexToEdgePair.second);
            result.connect(edgeWithWeight.first, edgeWithWeight.second, edgeWithWeight.weight);
        }
    }
    return result;
}

}

}
