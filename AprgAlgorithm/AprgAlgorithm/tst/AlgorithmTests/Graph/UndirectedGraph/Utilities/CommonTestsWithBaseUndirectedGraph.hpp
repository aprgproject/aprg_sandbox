#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithBaseUndirectedGraph
{

void performGetNumberOfVerticesTestWhenEmpty(BaseUndirectedGraph & graph);
void performGetNumberOfVerticesTestWhenNotEmpty(BaseUndirectedGraph & graph);
void performGetNumberOfEdgesTestWhenEmpty(BaseUndirectedGraph & graph);
void performGetNumberOfEdgesTestWhenNotEmpty(BaseUndirectedGraph & graph);
void performGetAdjacentVerticesAtTestWhenEmpty(BaseUndirectedGraph & graph);
void performGetAdjacentVerticesAtTestWhenNotEmpty(BaseUndirectedGraph & graph);
void performGetVerticesTestWhenEmpty(BaseUndirectedGraph & graph);
void performGetVerticesTestWhenNotEmpty(BaseUndirectedGraph & graph);
void performGetEdgesTestWhenEmpty(BaseUndirectedGraph & graph);
void performGetEdgesTestWhenNotEmpty(BaseUndirectedGraph & graph);
void performConnectTest(BaseUndirectedGraph & graph);
void performDisconnectTest(BaseUndirectedGraph & graph);
void performComplicatedTest(BaseUndirectedGraph & graph);

}

}

}
