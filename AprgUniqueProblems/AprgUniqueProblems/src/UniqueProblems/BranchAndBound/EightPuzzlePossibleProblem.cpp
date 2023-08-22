#include "EightPuzzlePossibleProblem.hpp"

#include <iostream>
#include <utility>

using namespace std;

namespace alba {

EightPuzzlePossibleProblem::EightPuzzlePossibleProblem(
    NumberMatrix const& startMatrix, NumberMatrix const& targetMatrix)
    : m_startMatrix(startMatrix),
      m_targetMatrix(targetMatrix),
      m_sideSize(m_startMatrix.getNumberOfColumns()),
      m_nodeIdToSnapshot(),
      m_nodeId(START_NODE_ID) {
    clearIfInvalid();
}

void EightPuzzlePossibleProblem::printStepsToSolve() {
    Coordinate blankTile(getBlankTile(m_startMatrix));
    PuzzleSnapshot initialSnapshot{INVALID_NODE_ID, blankTile, m_startMatrix};
    m_nodeIdToSnapshot.emplace_back(initialSnapshot);
    // using prioritized queue for branch and bound approach
    MinCostPriorityQueue nodesInMinCost;
    nodesInMinCost.push(createNode(INVALID_NODE_ID, blankTile, -1));
    while (!nodesInMinCost.empty()) {
        SearchNode currentNode(nodesInMinCost.top());
        nodesInMinCost.pop();
        if (currentNode.differenceFromTarget == 0) {
            printSteps(currentNode.nodeId);
            break;
        }
        Coordinate currentBlankTile(m_nodeIdToSnapshot[currentNode.nodeId].blankTile);
        for (int i = 0; i < 4; i++) {
            Coordinate nextBlankTile{currentBlankTile.first + X_OFFSETS[i], currentBlankTile.second + Y_OFFSETS[i]};
            if (isValidCoordinate(nextBlankTile)) {
                nodesInMinCost.push(createNode(currentNode.nodeId, nextBlankTile, currentNode.searchLevel + 1));
            }
        }
    }
}

int EightPuzzlePossibleProblem::getCost(SearchNode const& node) { return node.differenceFromTarget + node.searchLevel; }

void EightPuzzlePossibleProblem::clearIfInvalid() {
    if (m_startMatrix.getNumberOfColumns() != m_startMatrix.getNumberOfRows() ||
        m_targetMatrix.getNumberOfColumns() != m_targetMatrix.getNumberOfRows() ||
        m_startMatrix.getNumberOfColumns() != m_targetMatrix.getNumberOfRows()) {
        clear();
    }
}

void EightPuzzlePossibleProblem::clear() {
    m_startMatrix.clearAndResize(0, 0, {});
    m_targetMatrix.clearAndResize(0, 0, {});
    m_sideSize = 0;
    m_nodeIdToSnapshot.clear();
    m_nodeId = 0;
}

EightPuzzlePossibleProblem::SearchNode EightPuzzlePossibleProblem::createNode(
    SearchNodeId const& currentNodeId, Coordinate const& nextBlankTile, int const nextSearchLevel) {
    SearchNodeId nextNodeId = getNextNodeId();
    m_nodeIdToSnapshot.emplace_back(
        PuzzleSnapshot{currentNodeId, nextBlankTile, m_nodeIdToSnapshot[currentNodeId].numberMatrix});
    PuzzleSnapshot& nextSnapshot(m_nodeIdToSnapshot[nextNodeId]);
    moveTile(nextSnapshot.numberMatrix, m_nodeIdToSnapshot[currentNodeId].blankTile, nextSnapshot.blankTile);
    return SearchNode{nextNodeId, countDifference(nextSnapshot.numberMatrix, m_targetMatrix), nextSearchLevel};
}

void EightPuzzlePossibleProblem::moveTile(
    NumberMatrix& matrix, Coordinate const& previousBlankTile, Coordinate const& nextBlankTile) const {
    swap(
        matrix.getEntryReference(previousBlankTile.first, previousBlankTile.second),
        matrix.getEntryReference(nextBlankTile.first, nextBlankTile.second));
}

EightPuzzlePossibleProblem::SearchNodeId EightPuzzlePossibleProblem::getNextNodeId() { return m_nodeId++; }

bool EightPuzzlePossibleProblem::isValidCoordinate(Coordinate const& coordinate) const {
    return coordinate.first >= 0 && coordinate.first < m_sideSize && coordinate.second >= 0 &&
           coordinate.second < m_sideSize;
}

int EightPuzzlePossibleProblem::countDifference(
    NumberMatrix const& startMatrix, NumberMatrix const& targetMatrix) const {
    int result = 0;
    for (int x = 0; x < m_sideSize; ++x) {
        for (int y = 0; y < m_sideSize; ++y) {
            if (startMatrix.getEntry(x, y) && startMatrix.getEntry(x, y) != targetMatrix.getEntry(x, y)) {
                ++result;
            }
        }
    }
    return result;
}

EightPuzzlePossibleProblem::Coordinate EightPuzzlePossibleProblem::getBlankTile(NumberMatrix const& matrix) const {
    Coordinate result{};
    for (int y = 0; y < m_sideSize; y++) {
        for (int x = 0; x < m_sideSize; x++) {
            if (matrix.getEntry(x, y) == 0) {
                result = Coordinate{x, y};
            }
        }
    }
    return result;
}

void EightPuzzlePossibleProblem::printSteps(SearchNodeId const nodeId) const {
    if (nodeId != INVALID_NODE_ID) {
        PuzzleSnapshot const& snapshot(m_nodeIdToSnapshot.at(nodeId));
        printSteps(snapshot.previousNodeId);
        printMatrix(snapshot.numberMatrix);
    }
}

void EightPuzzlePossibleProblem::printMatrix(NumberMatrix const& numberMatrix) const { cout << numberMatrix << "\n"; }

}  // namespace alba
