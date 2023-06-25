#include "IsolationOfOneVariableOnEqualityEquations.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Solution/Solver/SolverUsingSubstitution/ReduceEquationsBySubstitution.hpp>

#include <algorithm>

using namespace std;

namespace alba {

namespace algebra {

IsolationOfOneVariableOnEqualityEquations::IsolationOfOneVariableOnEqualityEquations(Equations const& equations)
    : m_equations(equations) {}

void IsolationOfOneVariableOnEqualityEquations::isolateTermWithVariable(
    string const& variableName, Term& termWithVariable, Term& termWithWithoutVariable) const {
    Equations reducedEquations(m_equations);
    reduceEquationsBySubstitution(reducedEquations, {variableName});

    Equations equationsWithVariable;
    Equations equationsWithoutVariable;
    segregateEquationsWithAndWithoutVariable(
        reducedEquations, variableName, equationsWithVariable, equationsWithoutVariable);
    if (!equationsWithVariable.empty()) {
        sortEquationsWithVariable(equationsWithVariable);
        Equation const& selectedEquation(equationsWithVariable[0]);
        IsolationOfOneVariableOnEqualityEquation isolationForVariable(selectedEquation);
        isolationForVariable.isolateTermWithVariable(variableName, termWithVariable, termWithWithoutVariable);
    }}

Term IsolationOfOneVariableOnEqualityEquations::getEquivalentTermByIsolatingAVariable(
    string const& variableName) const {    Term termWithVariable;
    Term termWithWithoutVariable;
    isolateTermWithVariable(variableName, termWithVariable, termWithWithoutVariable);
    return getEquivalentTermByReducingItToAVariable(variableName, termWithVariable, termWithWithoutVariable);
}

void IsolationOfOneVariableOnEqualityEquations::sortEquationsWithVariable(Equations& equationsWithVariable) const {
    stable_sort(
        equationsWithVariable.begin(), equationsWithVariable.end(),
        [](Equation const& equation1, Equation const& equation2) {
            VariableNamesRetriever namesRetriever1;
            VariableNamesRetriever namesRetriever2;
            namesRetriever1.retrieveFromEquation(equation1);
            namesRetriever2.retrieveFromEquation(equation2);
            int size1 = namesRetriever1.getSavedData().size();
            int size2 = namesRetriever2.getSavedData().size();
            bool result(false);
            if (size1 == size2) {
                AlbaNumber degree1(getDegree(equation1));
                AlbaNumber degree2(getDegree(equation2));
                result = degree1 < degree2;
            } else {
                result = size1 < size2;
            }
            return result;
        });
}

}  // namespace algebra

}  // namespace alba
