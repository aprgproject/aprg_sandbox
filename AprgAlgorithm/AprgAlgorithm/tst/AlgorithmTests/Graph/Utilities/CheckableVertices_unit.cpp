#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using CheckableVerticesForTest = CheckableVertices<VertexForTest>;
}  // namespace

TEST(CheckableVerticesTest, IsFoundWorks) {
    CheckableVerticesForTest emptyCheckableVertices;
    CheckableVerticesForTest nonEmptyCheckableVertices;
    nonEmptyCheckableVertices.putVertex(10U);
    nonEmptyCheckableVertices.putVertex(11U);
    nonEmptyCheckableVertices.putVertex(12U);

    EXPECT_FALSE(emptyCheckableVertices.isFound(1U));
    EXPECT_TRUE(nonEmptyCheckableVertices.isFound(10U));
    EXPECT_TRUE(nonEmptyCheckableVertices.isFound(11U));
    EXPECT_TRUE(nonEmptyCheckableVertices.isFound(12U));
    EXPECT_FALSE(nonEmptyCheckableVertices.isFound(9U));
    EXPECT_FALSE(nonEmptyCheckableVertices.isFound(13U));
}

TEST(CheckableVerticesTest, IsNotFoundWorks) {
    CheckableVerticesForTest emptyCheckableVertices;
    CheckableVerticesForTest nonEmptyCheckableVertices;
    nonEmptyCheckableVertices.putVertex(10U);
    nonEmptyCheckableVertices.putVertex(11U);
    nonEmptyCheckableVertices.putVertex(12U);

    EXPECT_TRUE(emptyCheckableVertices.isNotFound(1U));
    EXPECT_FALSE(nonEmptyCheckableVertices.isNotFound(10U));
    EXPECT_FALSE(nonEmptyCheckableVertices.isNotFound(11U));
    EXPECT_FALSE(nonEmptyCheckableVertices.isNotFound(12U));
    EXPECT_TRUE(nonEmptyCheckableVertices.isNotFound(9U));
    EXPECT_TRUE(nonEmptyCheckableVertices.isNotFound(13U));
}

TEST(CheckableVerticesTest, PutVertexWorks) {
    CheckableVerticesForTest checkableVertices;

    checkableVertices.putVertex(10U);
    checkableVertices.putVertex(11U);
    checkableVertices.putVertex(12U);

    EXPECT_TRUE(checkableVertices.isFound(10U));
    EXPECT_TRUE(checkableVertices.isFound(11U));
    EXPECT_TRUE(checkableVertices.isFound(12U));
    EXPECT_FALSE(checkableVertices.isFound(9U));
    EXPECT_FALSE(checkableVertices.isFound(13U));
}

TEST(CheckableVerticesTest, RemoveVertexWorks) {
    CheckableVerticesForTest checkableVertices;
    checkableVertices.putVertex(10U);
    checkableVertices.putVertex(11U);
    checkableVertices.putVertex(12U);

    checkableVertices.removeVertex(9U);
    checkableVertices.removeVertex(12U);

    EXPECT_TRUE(checkableVertices.isFound(10U));
    EXPECT_TRUE(checkableVertices.isFound(11U));
    EXPECT_FALSE(checkableVertices.isFound(12U));
    EXPECT_FALSE(checkableVertices.isFound(9U));
    EXPECT_FALSE(checkableVertices.isFound(13U));
}

TEST(CheckableVerticesTest, ClearWorks) {
    CheckableVerticesForTest checkableVertices;
    checkableVertices.putVertex(10U);
    checkableVertices.putVertex(11U);
    checkableVertices.putVertex(12U);

    checkableVertices.clear();

    EXPECT_FALSE(checkableVertices.isFound(10U));
    EXPECT_FALSE(checkableVertices.isFound(11U));
    EXPECT_FALSE(checkableVertices.isFound(12U));
    EXPECT_FALSE(checkableVertices.isFound(9U));
    EXPECT_FALSE(checkableVertices.isFound(13U));
}

}  // namespace algorithm

}  // namespace alba
