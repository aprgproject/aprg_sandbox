#include "JobAssignmentProblem.hpp"

#include <iostream>
#include <utility>

using namespace std;

namespace alba {

JobAssignmentProblem::JobAssignmentProblem(CostMatrix const& costMatrix)
    : m_costMatrix(costMatrix),
      m_numberOfWorkers(m_costMatrix.getNumberOfColumns()),
      m_numberOfJobs(m_costMatrix.getNumberOfRows()),
      m_nodeIdToDetails(),
      m_nodeId(START_NODE_ID) {}

int JobAssignmentProblem::getMinimalCostAndPrintAssignments() {
    int minimalCost{};
    SearchNodeDetails initialDetails{INVALID_NODE_ID, -1, -1, BoolVector(m_numberOfJobs, false)};
    m_nodeIdToDetails.emplace_back(initialDetails);

    // using prioritized queue for branch and bound approach
    MinCostPriorityQueue nodesInMinCost;
    nodesInMinCost.push(SearchNode{INVALID_NODE_ID, 0, 0});
    while (!nodesInMinCost.empty()) {
        SearchNode currentNode(nodesInMinCost.top());
        nodesInMinCost.pop();
        int nextWorkerId = m_nodeIdToDetails[currentNode.nodeId].workerId + 1;
        if (nextWorkerId == m_numberOfWorkers) {
            printAssignments(currentNode.nodeId);
            minimalCost = currentNode.minimumPossibleCost;
            break;
        }
        for (int nextJobId = 0; nextJobId < m_numberOfJobs; nextJobId++) {
            if (!m_nodeIdToDetails[currentNode.nodeId].isJobAssigned[nextJobId]) {
                nodesInMinCost.push(createNode(currentNode, Coordinate{nextWorkerId, nextJobId}));
            }
        }
    }
    return minimalCost;
}

JobAssignmentProblem::SearchNode JobAssignmentProblem::createNode(
    SearchNode const& currentNode, Coordinate const& nextWorkerAndJob) {
    auto const [workerId, jobId] = nextWorkerAndJob;
    SearchNodeId nextNodeId = getNextNodeId();
    m_nodeIdToDetails.emplace_back(
        SearchNodeDetails{currentNode.nodeId, workerId, jobId, m_nodeIdToDetails[currentNode.nodeId].isJobAssigned});
    SearchNodeDetails& nextNodeDetails(m_nodeIdToDetails[nextNodeId]);
    nextNodeDetails.isJobAssigned[jobId] = true;
    int accumulatedCost = getAccumulatedCost(workerId, jobId, currentNode);
    int minimumPossibleCost = accumulatedCost + getMinimumPossibleCost(workerId, jobId, nextNodeDetails.isJobAssigned);
    return SearchNode{nextNodeId, accumulatedCost, minimumPossibleCost};
}

int JobAssignmentProblem::getAccumulatedCost(int const workerId, int const jobId, SearchNode const& currentNode) const {
    return currentNode.accumulatedCost + m_costMatrix.getEntry(workerId, jobId);
}

int JobAssignmentProblem::getMinimumPossibleCost(
    int const workerId, int const jobId, BoolVector const& isJobAssigned) const {
    int cost = 0;
    BoolVector isJobAssignedLocal = isJobAssigned;
    for (int workerIndex = workerId + 1; workerIndex < m_numberOfWorkers; workerIndex++) {
        int minimumCost = INT_MAX, minIndex = -1;
        for (int jobIndex = 0; jobIndex < jobId; jobIndex++) {
            if (!isJobAssignedLocal[jobIndex] && m_costMatrix.getEntry(workerIndex, jobIndex) < minimumCost) {
                minIndex = jobIndex;
                minimumCost = m_costMatrix.getEntry(workerIndex, jobIndex);
            }
        }
        if (minIndex != -1) {
            cost += minimumCost;
            isJobAssignedLocal[minIndex] = true;
        }
    }
    return cost;
}

JobAssignmentProblem::SearchNodeId JobAssignmentProblem::getNextNodeId() { return m_nodeId++; }

void JobAssignmentProblem::printAssignments(SearchNodeId const nodeId) const {
    if (nodeId != INVALID_NODE_ID) {
        SearchNodeDetails const& nodeDetails(m_nodeIdToDetails.at(nodeId));
        printAssignments(nodeDetails.previousNodeId);
        cout << "Assign Worker: [" << nodeDetails.workerId << "] to Job: [" << nodeDetails.jobId << "]\n";
    }
}

}  // namespace alba
