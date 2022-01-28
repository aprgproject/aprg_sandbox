#pragma once

#include <UnionFind/BaseUnionFind.hpp>

namespace alba
{

namespace CommonTestsWithBaseUnionFind
{

using BaseUnionFindForUnsignedInt = BaseUnionFind<unsigned int>;

void performIsConnectedTest(BaseUnionFindForUnsignedInt & unionFind);
void performConnectTest(BaseUnionFindForUnsignedInt & unionFind);
void performConnectTestWithExample1(BaseUnionFindForUnsignedInt & unionFind);

}

}
