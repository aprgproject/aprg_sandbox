#include "TwoSatisfiabilityUsingGraphs.hpp"

#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>
#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>

using namespace alba::algorithm;
using namespace std;

namespace alba {

namespace booleanAlgebra {

TwoSatisfiabilityUsingGraphs::TwoSatisfiabilityUsingGraphs(SatisfiabilityTerms const& satTerms)
    : m_variableNames(createVariableNamesFromSatTerms(satTerms)),
      m_graph(createDirectedGraphBasedFromSatTerms(satTerms)),
      m_connectedComponents(m_graph) {}

bool TwoSatisfiabilityUsingGraphs::hasSolution() const {
    bool isAVariableAndItsNegationConnected =
        any_of(m_variableNames.cbegin(), m_variableNames.cend(), [&](string const& variableName) {
            return m_connectedComponents.isConnected(
                VariableTerm(variableName), VariableTerm::createNegatedVariableTerm(variableName));
        });
    return !isAVariableAndItsNegationConnected;
}

Term TwoSatisfiabilityUsingGraphs::getSolution() const {
    using VertexOrdering = VertexOrderingUsingDfs<VariableTerm>;
    VertexOrdering vertexOrdering(m_graph);
    auto const& variableTermsInOrder(vertexOrdering.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VariableNamesSet processedNames;
    Expression result;
    for (VariableTerm const& variableTerm : variableTermsInOrder) {
        string variableName(variableTerm.getVariableTermName());
        if (processedNames.find(variableName) == processedNames.cend()) {
            result.putTermWithAndOperationIfNeeded(Term(variableTerm));
            processedNames.emplace(variableName);
        } else {
            break;
        }
    }
    result.sort();
    return convertExpressionToSimplestTerm(result);
}

VariableNamesSet TwoSatisfiabilityUsingGraphs::createVariableNamesFromSatTerms(SatisfiabilityTerms const& satTerms) {
    VariableNamesSet result;
    for (SatisfiabilityTerm const& satTerm : satTerms) {
        for (VariableTerm const& variableTerm : satTerm) {
            result.emplace(variableTerm.getVariableTermName());
        }
    }
    return result;
}

TwoSatisfiabilityUsingGraphs::DirectedGraph TwoSatisfiabilityUsingGraphs::createDirectedGraphBasedFromSatTerms(
    SatisfiabilityTerms const& satTerms) {
    DirectedGraph result;
    if (2U == getSatisfiabilityLevel(satTerms))  // 2SAT
    {
        for (SatisfiabilityTerm const& satTerm : satTerms) {
            if (satTerm.size() == 1) {
                result.connect(~satTerm[0], satTerm[0]);
            } else if (satTerm.size() == 2) {
                result.connect(~satTerm[0], satTerm[1]);
                result.connect(~satTerm[1], satTerm[0]);
            }
        }
    }
    return result;
}

}  // namespace booleanAlgebra

}  // namespace alba
