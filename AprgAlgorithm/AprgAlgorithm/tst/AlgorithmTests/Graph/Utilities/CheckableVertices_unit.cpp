#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using CheckableVerticesForTest = CheckableVertices<VertexForTest>;
}  // namespace

TEST(CheckableVerticesTest, IsFoundWorks) {
    CheckableVerticesForTest emptyCheckableVertices;
    CheckableVerticesForTest nonEmptyCheckableVertices;
    nonEmptyCheckableVertices.putVertex(10);
    nonEmptyCheckableVertices.putVertex(11);
    nonEmptyCheckableVertices.putVertex(12);

    EXPECT_FALSE(emptyCheckableVertices.isFound(1));
    EXPECT_TRUE(nonEmptyCheckableVertices.isFound(10));
    EXPECT_TRUE(nonEmptyCheckableVertices.isFound(11));
    EXPECT_TRUE(nonEmptyCheckableVertices.isFound(12));
    EXPECT_FALSE(nonEmptyCheckableVertices.isFound(9));
    EXPECT_FALSE(nonEmptyCheckableVertices.isFound(13));
}

TEST(CheckableVerticesTest, IsNotFoundWorks) {
    CheckableVerticesForTest emptyCheckableVertices;
    CheckableVerticesForTest nonEmptyCheckableVertices;
    nonEmptyCheckableVertices.putVertex(10);
    nonEmptyCheckableVertices.putVertex(11);
    nonEmptyCheckableVertices.putVertex(12);

    EXPECT_TRUE(emptyCheckableVertices.isNotFound(1));
    EXPECT_FALSE(nonEmptyCheckableVertices.isNotFound(10));
    EXPECT_FALSE(nonEmptyCheckableVertices.isNotFound(11));
    EXPECT_FALSE(nonEmptyCheckableVertices.isNotFound(12));
    EXPECT_TRUE(nonEmptyCheckableVertices.isNotFound(9));
    EXPECT_TRUE(nonEmptyCheckableVertices.isNotFound(13));
}

TEST(CheckableVerticesTest, PutVertexWorks) {
    CheckableVerticesForTest checkableVertices;

    checkableVertices.putVertex(10);
    checkableVertices.putVertex(11);
    checkableVertices.putVertex(12);

    EXPECT_TRUE(checkableVertices.isFound(10));
    EXPECT_TRUE(checkableVertices.isFound(11));
    EXPECT_TRUE(checkableVertices.isFound(12));
    EXPECT_FALSE(checkableVertices.isFound(9));
    EXPECT_FALSE(checkableVertices.isFound(13));
}

TEST(CheckableVerticesTest, RemoveVertexWorks) {
    CheckableVerticesForTest checkableVertices;
    checkableVertices.putVertex(10);
    checkableVertices.putVertex(11);
    checkableVertices.putVertex(12);

    checkableVertices.removeVertex(9);
    checkableVertices.removeVertex(12);

    EXPECT_TRUE(checkableVertices.isFound(10));
    EXPECT_TRUE(checkableVertices.isFound(11));
    EXPECT_FALSE(checkableVertices.isFound(12));
    EXPECT_FALSE(checkableVertices.isFound(9));
    EXPECT_FALSE(checkableVertices.isFound(13));
}

TEST(CheckableVerticesTest, ClearWorks) {
    CheckableVerticesForTest checkableVertices;
    checkableVertices.putVertex(10);
    checkableVertices.putVertex(11);
    checkableVertices.putVertex(12);

    checkableVertices.clear();

    EXPECT_FALSE(checkableVertices.isFound(10));
    EXPECT_FALSE(checkableVertices.isFound(11));
    EXPECT_FALSE(checkableVertices.isFound(12));
    EXPECT_FALSE(checkableVertices.isFound(9));
    EXPECT_FALSE(checkableVertices.isFound(13));
}

}  // namespace algorithm

}  // namespace alba
