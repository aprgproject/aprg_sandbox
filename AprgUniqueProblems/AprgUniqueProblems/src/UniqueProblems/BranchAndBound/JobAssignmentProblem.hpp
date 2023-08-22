#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <queue>
#include <vector>

namespace alba {

class JobAssignmentProblem {
public:
    using CostMatrix = matrix::AlbaMatrix<int>;
    using Coordinate = std::pair<int, int>;
    using SearchNodeId = int;
    using BoolVector = std::vector<bool>;
    struct SearchNodeDetails {
        SearchNodeId previousNodeId;
        int workerId;
        int jobId;
        BoolVector isJobAssigned;
    };
    struct SearchNode {
        SearchNodeId nodeId;
        int accumulatedCost;
        int minimumPossibleCost;
    };
    struct CostComparator {
        bool operator()(SearchNode const& left, SearchNode const& right) const {
            return left.minimumPossibleCost > right.minimumPossibleCost;
        }
    };
    using SearchNodeIdToDetails = std::vector<SearchNodeDetails>;
    using MinCostPriorityQueue = std::priority_queue<SearchNode, std::vector<SearchNode>, CostComparator>;
    static constexpr SearchNodeId INVALID_NODE_ID = 0;
    static constexpr SearchNodeId START_NODE_ID = 1;

    JobAssignmentProblem(CostMatrix const& costMatrix);

    int getMinimalCostAndPrintAssignments();

private:
    SearchNode createNode(SearchNode const& currentNode, Coordinate const& nextAssignment);
    int getAccumulatedCost(int const workerId, int const jobId, SearchNode const& currentNode) const;
    int getMinimumPossibleCost(int const workerId, int const jobId, BoolVector const& isJobAssigned) const;
    SearchNodeId getNextNodeId();
    void printAssignments(SearchNodeId const nodeId) const;

    CostMatrix m_costMatrix;
    int m_numberOfWorkers;
    int m_numberOfJobs;
    SearchNodeIdToDetails m_nodeIdToDetails;
    SearchNodeId m_nodeId;
};

}  // namespace alba

// -> Let there be N workers and N jobs.
// ---> Any worker can be assigned to perform any job, incurring some cost that may vary depending on the work-job
// assignment.
// ---> It is required to perform all jobs by assigning exactly one worker to each job
// ---> and exactly one job to each agent in such a way that the total cost of the assignment is minimized.
//
// -> Let us explore all approaches for this problem.
// ---> Solution 1: Brute Force
// -----> We generate n! possible job assignments and for each such assignment,
// -----> we compute its total cost and return the less expensive assignment.
// -----> Since the solution is a permutation of the n jobs, its complexity is O(n!).
// ---> Solution 2: Hungarian Algorithm
// -----> The optimal assignment can be found using the Hungarian algorithm.
// -----> The Hungarian algorithm has worst case run-time complexity of O(n^3).
// ---> Solution 3: DFS/BFS on state space tree
// -----> A state space tree is a N-ary tree with property that any path from root to leaf node holds one of many
// solutions to given problem.
// -----> We can perform depth-first search on state space tree and but successive moves can take us away from the goal
// rather than bringing closer.
// -----> The search of state space tree follows leftmost path from the root regardless of initial state.
// -----> An answer node may never be found in this approach. We can also perform a Breadth-first search on state space
// tree.
// -----> But no matter what the initial state is, the algorithm attempts the same sequence of moves like DFS.
// ---> Solution 4: Finding Optimal Solution using Branch and Bound
// -----> The selection rule for the next node in BFS and DFS is “blind”. i.e.
// -----> the selection rule does not give any preference to a node that has a very good chance of getting the search to
// an answer node quickly.
// -----> The search for an optimal solution can often be speeded by using an “intelligent” ranking function,
// -----> also called an approximate cost function to avoid searching in sub-trees that do not contain an optimal
// solution.
// -----> It is similar to BFS-like search but with one major optimization.
// -----> Instead of following FIFO order, we choose a live node with least cost.
// -----> We may not get optimal solution by following node with least promising cost,
// -----> but it will provide very good chance of getting the search to an answer node quickly.
