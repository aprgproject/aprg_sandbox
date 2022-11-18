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
            auto const& edgeOrderedByWeight(vertexToEdgePair.second);
            result.connect(edgeOrderedByWeight.first, edgeOrderedByWeight.second, edgeOrderedByWeight.weight);
        }
    }
    return result;
}

}

}
