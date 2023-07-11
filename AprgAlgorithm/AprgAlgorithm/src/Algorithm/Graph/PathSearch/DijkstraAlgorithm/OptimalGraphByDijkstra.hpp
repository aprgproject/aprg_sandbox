#pragma once

namespace alba {

namespace algorithm {

template <typename EdgeWeightedDirectedGraph, typename PathSearchUsingDijkstra>
EdgeWeightedDirectedGraph getOptimalDirectedGraph(PathSearchUsingDijkstra const& pathSearch) {
    EdgeWeightedDirectedGraph result;
    for (auto const& [vertex, edgeOrderedByWeight] : pathSearch.getVertexToEdgeWithBestWeightMap()) {
        // remove start vertex because its started there
        if (pathSearch.getStartVertex() != vertex) {
            result.connect(edgeOrderedByWeight.first, edgeOrderedByWeight.second, edgeOrderedByWeight.weight);
        }
    }    return result;
}

}  // namespace algorithm
}  // namespace alba
