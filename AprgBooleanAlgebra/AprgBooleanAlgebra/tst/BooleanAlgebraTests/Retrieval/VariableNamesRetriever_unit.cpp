#include <BooleanAlgebra/Retrieval/VariableNamesRetriever.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace booleanAlgebra {

TEST(VariableNamesRetrieverTest, RetrieveFromTermWorks) {
    VariableNamesRetriever retriever;

    retriever.retrieveFromTerm(Constant(true));
    retriever.retrieveFromTerm(VariableTerm("x"));
    retriever.retrieveFromTerm(createExpressionIfPossible({"a", "&", "b"}));

    VariableNamesSet const& variableNamesSet(retriever.getSavedData());
    ASSERT_EQ(3U, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
    EXPECT_EQ("x", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromConstantWorks) {
    VariableNamesRetriever retriever;

    retriever.retrieveFromConstant(Constant(true));

    VariableNamesSet const& variableNamesSet(retriever.getSavedData());
    EXPECT_TRUE(variableNamesSet.empty());
}

TEST(VariableNamesRetrieverTest, RetrieveFromVariableTermWorks) {
    VariableNamesRetriever retriever;

    retriever.retrieveFromVariableTerm(VariableTerm("x"));

    VariableNamesSet const& variableNamesSet(retriever.getSavedData());
    ASSERT_EQ(1U, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("x", *(it++));
}

TEST(VariableNamesRetrieverTest, RetrieveFromExpressionWorks) {
    VariableNamesRetriever retriever;

    retriever.retrieveFromExpression(createExpressionIfPossible({"a", "&", "b"}));

    VariableNamesSet const& variableNamesSet(retriever.getSavedData());
    ASSERT_EQ(2U, variableNamesSet.size());
    VariableNamesSet::const_iterator it = variableNamesSet.cbegin();
    EXPECT_EQ("a", *(it++));
    EXPECT_EQ("b", *(it++));
}

}  // namespace booleanAlgebra

}  // namespace alba
