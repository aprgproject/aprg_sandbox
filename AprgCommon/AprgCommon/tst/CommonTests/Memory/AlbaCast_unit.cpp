#include <Common/Memory/AlbaCast.hpp>

#include <gtest/gtest.h>

#include <cstdint>

using namespace std;

namespace alba
{

TEST(AlbaCastTest, GetFloatingPointMemoryRepresentationWorks)
{
    EXPECT_EQ(0ULL, (getFloatingPointMemoryRepresentation<double, uint64_t>(0.)));
    EXPECT_EQ(4611686018427387904ULL, (getFloatingPointMemoryRepresentation<double, uint64_t>(2.)));
    EXPECT_EQ(4653144502051863213ULL, (getFloatingPointMemoryRepresentation<double, uint64_t>(1234.5678)));
}

}
