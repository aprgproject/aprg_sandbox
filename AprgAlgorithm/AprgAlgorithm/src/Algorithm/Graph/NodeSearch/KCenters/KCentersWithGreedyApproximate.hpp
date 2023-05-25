#pragma once

#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/PathSearchUsingBfsWithDistanceSum.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class KCentersWithGreedyApproximate {
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexToWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToWeightMap;
    using Bfs = PathSearchUsingBfsWithDistanceSum<Vertex, Weight, EdgeWeightedGraph>;

    KCentersWithGreedyApproximate(EdgeWeightedGraph const& graph, Vertex const& startVertex, int const numberOfCenters)
        : m_graph(graph), m_startVertex(startVertex), m_numberOfCenters(numberOfCenters) {
        initialize();
    }

    Vertices const& getFoundCenters() const { return m_foundCenters; }

private:
    void initialize() { traverseWithGreedyApproach(); }

    void traverseWithGreedyApproach() {
        Vertex currentCenter(m_startVertex);  // start vertex is a center
        for (int centerCount = 0; centerCount < m_numberOfCenters; centerCount++) {
            m_foundCenters.emplace_back(currentCenter);
            updateClosestDistances(currentCenter);
            currentCenter = getVertexForMaximumClosestDistance();
        }
    }

    void updateClosestDistances(Vertex const& currentCenter) {
        Bfs bfs(m_graph, {currentCenter});
        for (auto const& endVertexAndDistanceSumPair : bfs.getEndVertexToDistanceSumMap()) {
            Vertex const& vertex(endVertexAndDistanceSumPair.first);
            Weight const& distance(endVertexAndDistanceSumPair.second);
            auto it = m_closestDistanceForVertex.find(vertex);
            if (it != m_closestDistanceForVertex.cend()) {
                it->second = std::min(it->second, distance);
            } else {
                m_closestDistanceForVertex.emplace(vertex, distance);
            }
        }
    }

    Vertex getVertexForMaximumClosestDistance() {
        Vertex result{};
        Weight maximumClosestDistance{};
        for (auto const& vertexAndClosestDistancePair : m_closestDistanceForVertex) {
            if (maximumClosestDistance < vertexAndClosestDistancePair.second) {
                maximumClosestDistance = vertexAndClosestDistancePair.second;
                result = vertexAndClosestDistancePair.first;
            }
        }
        return result;
    }

    EdgeWeightedGraph const& m_graph;
    Vertex const m_startVertex;
    int const m_numberOfCenters;
    VertexToWeightMap m_closestDistanceForVertex;
    Vertices m_foundCenters;
};

}  // namespace algorithm

}  // namespace alba

// Given n cities and distances between every pair of cities, select k cities to place warehouses (or ATMs or Cloud
// Server) such that the maximum distance of a city to a warehouse (or ATM or Cloud Server) is minimized.

// For example consider the following four cities, 0, 1, 2 and 3 and distances between them,
// how do place 2 ATMs among these 4 cities so that the maximum distance of a city to an ATM is minimized.

// There is no polynomial time solution available for this problem as the problem is a known NP-Hard problem.
// There is a polynomial time Greedy approximate algorithm,
// the greedy algorithm provides a solution which is never worse that twice the optimal solution.
// The greedy solution works only if the distances between cities follow Triangular Inequality
// (Distance between two points is always smaller than sum of distances through a third point).

// The 2-Approximate Greedy Algorithm:
// -> Step 1: Choose the first center arbitrarily.
// -> Step 2: Choose remaining k-1 centers using the following criteria.
// ---> Let c1, c2, c3, … ci be the already chosen centers.
// ---> Choose (i+1)’th center by picking the city whi   ch is farthest from already selected centers,
// ---> i.e, the point p which has following value as maximum Min[dist(p, c1), dist(p, c2), dist(p, c3), …. dist(p, ci)]

// Note that the greedy algorithm doesn’t give best solution as this is just an approximate algorithm with bound as
// twice of optimal.

// Proof that the above greedy algorithm is 2 approximate.
// -> Let OPT be the maximum distance of a city from a center in the Optimal solution.
// ---> We need to show that the maximum distance obtained from Greedy algorithm is 2*OPT.
// -> The proof can be done using contradiction.
// ---> a) Assume that the distance from the furthest point to all centers is > 2·OPT.
// ---> b) This means that distances between all centers are also > 2·OPT (otherwise furthest point should be a center).
// ---> c) We have k+1 points with distances > 2·OPT between every pair.
// ---> d) Each point has a center of the optimal solution with distance <= OPT to it.
// ---> e) There exists a pair of points with the same center X in the optimal solution
// --->(pigeonhole principle: k optimal centers, k+1 points)
// ---> f) The distance between them is at most 2·OPT (triangle inequality) which is a contradiction.
