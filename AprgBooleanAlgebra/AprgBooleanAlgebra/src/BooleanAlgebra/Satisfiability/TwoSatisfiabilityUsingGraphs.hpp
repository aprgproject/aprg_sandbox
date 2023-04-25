#pragma once

#include <Algorithm/Graph/ConnectedComponents/StronglyConnectedComponentsUsingKosarajuSharir.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <BooleanAlgebra/Satisfiability/Utilities.hpp>
#include <BooleanAlgebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba {

namespace booleanAlgebra {

class TwoSatisfiabilityUsingGraphs {
public:
    using DirectedGraph = algorithm::DirectedGraphWithListOfEdges<VariableTerm>;
    using ConnectedComponents = algorithm::StronglyConnectedComponentsUsingKosarajuSharir<VariableTerm>;

    TwoSatisfiabilityUsingGraphs(SatisfiabilityTerms const& satTerms);

    bool hasSolution() const;
    Term getSolution() const;

private:
    VariableNamesSet createVariableNamesFromSatTerms(SatisfiabilityTerms const& satTerms);
    DirectedGraph createDirectedGraphBasedFromSatTerms(SatisfiabilityTerms const& satTerms);

    VariableNamesSet m_variableNames;
    DirectedGraph m_graph;
    ConnectedComponents m_connectedComponents;
};

// A more difficult problem is the 3SAT problem, where each part of the formula is of the form (a|b|c).
// This problem is NP-hard, so no efficient algorithm for solving the problem is known.

}  // namespace booleanAlgebra

}  // namespace alba
