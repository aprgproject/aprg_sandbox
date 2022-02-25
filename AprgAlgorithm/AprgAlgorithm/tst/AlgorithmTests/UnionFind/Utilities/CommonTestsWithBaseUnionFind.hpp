#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithBaseUnionFind
{

using BaseUnionFindForUnsignedInt = BaseUnionFind<unsigned int>;

void performIsConnectedTest(BaseUnionFindForUnsignedInt & unionFind);
void performConnectTest(BaseUnionFindForUnsignedInt & unionFind);
void performConnectTestWithExample1(BaseUnionFindForUnsignedInt & unionFind);
void performConnectTestWithExample2(BaseUnionFindForUnsignedInt & unionFind);

}
}

}