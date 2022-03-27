#include <Algorithm/Graph/Utilities/ProcessedVertices.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using ProcessedVerticesForTest = ProcessedVertices<VertexForTest>;
}

TEST(ProcessedVerticesTest, IsProcessedWorks)
{
    ProcessedVerticesForTest emptyProcessedVertices;
    ProcessedVerticesForTest nonEmptyprocessedVertices;
    nonEmptyprocessedVertices.putVertexAsProcessed(10U);
    nonEmptyprocessedVertices.putVertexAsProcessed(11U);
    nonEmptyprocessedVertices.putVertexAsProcessed(12U);

    EXPECT_FALSE(emptyProcessedVertices.isProcessed(1U));
    EXPECT_TRUE(nonEmptyprocessedVertices.isProcessed(10U));
    EXPECT_TRUE(nonEmptyprocessedVertices.isProcessed(11U));
    EXPECT_TRUE(nonEmptyprocessedVertices.isProcessed(12U));
    EXPECT_FALSE(nonEmptyprocessedVertices.isProcessed(9U));
    EXPECT_FALSE(nonEmptyprocessedVertices.isProcessed(13U));
}

TEST(ProcessedVerticesTest, IsNotProcessedWorks)
{
    ProcessedVerticesForTest emptyProcessedVertices;
    ProcessedVerticesForTest nonEmptyprocessedVertices;
    nonEmptyprocessedVertices.putVertexAsProcessed(10U);
    nonEmptyprocessedVertices.putVertexAsProcessed(11U);
    nonEmptyprocessedVertices.putVertexAsProcessed(12U);

    EXPECT_TRUE(emptyProcessedVertices.isNotProcessed(1U));
    EXPECT_FALSE(nonEmptyprocessedVertices.isNotProcessed(10U));
    EXPECT_FALSE(nonEmptyprocessedVertices.isNotProcessed(11U));
    EXPECT_FALSE(nonEmptyprocessedVertices.isNotProcessed(12U));
    EXPECT_TRUE(nonEmptyprocessedVertices.isNotProcessed(9U));
    EXPECT_TRUE(nonEmptyprocessedVertices.isNotProcessed(13U));
}

TEST(ProcessedVerticesTest, PutVertexAsProcessedWorks)
{
    ProcessedVerticesForTest processedVertices;

    processedVertices.putVertexAsProcessed(10U);
    processedVertices.putVertexAsProcessed(11U);
    processedVertices.putVertexAsProcessed(12U);

    EXPECT_TRUE(processedVertices.isProcessed(10U));
    EXPECT_TRUE(processedVertices.isProcessed(11U));
    EXPECT_TRUE(processedVertices.isProcessed(12U));
    EXPECT_FALSE(processedVertices.isProcessed(9U));
    EXPECT_FALSE(processedVertices.isProcessed(13U));
}

TEST(ProcessedVerticesTest, ClearWorks)
{
    ProcessedVerticesForTest processedVertices;
    processedVertices.putVertexAsProcessed(10U);
    processedVertices.putVertexAsProcessed(11U);
    processedVertices.putVertexAsProcessed(12U);

    processedVertices.clear();

    EXPECT_FALSE(processedVertices.isProcessed(10U));
    EXPECT_FALSE(processedVertices.isProcessed(11U));
    EXPECT_FALSE(processedVertices.isProcessed(12U));
    EXPECT_FALSE(processedVertices.isProcessed(9U));
    EXPECT_FALSE(processedVertices.isProcessed(13U));
}

}

}
