#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

namespace algebra {

class SimplexSolver {
public:
    using SimplexMatrix = matrix::AlbaMatrix<AlbaNumber>;
    using SimplexMatrixData = matrix::AlbaMatrixData<AlbaNumber>;

    SimplexSolver(Equations const& constraints, Polynomial const& objectiveFunction);

    bool isOptimized() const;
    AlbaNumber getOptimizedObjectiveValue() const;
    Equations getSolutionEquations() const;

private:
    void intialize(Equations const& constraints, Polynomial const& objectiveFunction);
    void solve();
    void processConstraints(
        Equations const& constraints, Polynomials& constraintsInStandardForm,
        VariableNamesRetriever& inputVariablesRetriever, std::set<int>& indicesWithSlackVariables);
    void saveInputVariables(VariableNamesSet const& inputVariableNames);
    void initializeSimplexTable(
        Polynomial const& objectiveFunction, Polynomials const& constraintsInStandardForm,
        VariableNamesSet const& inputVariableNames, std::set<int> const& indicesWithSlackVariables);
    SimplexMatrix m_simplexTable;
    VariableNames m_inputVariables;
};
}  // namespace algebra

}  // namespace alba