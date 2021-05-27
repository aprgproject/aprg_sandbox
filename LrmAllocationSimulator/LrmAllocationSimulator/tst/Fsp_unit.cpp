#include <Fsp.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(FspTest, FspDetailsCanAssignedCorrectlyAtConstruction)
{
    FspDetails fspDetails;
    fspDetails.smType=SmType::ESM;
    fspDetails.isMasterTcom=true;
    fspDetails.address = 0x1200;
    fspDetails.dspAddresses.emplace_back(0x1230);
    Fsp fsp(fspDetails);

    EXPECT_EQ(SmType::ESM, fsp.getSmType());
    EXPECT_TRUE(fsp.isMasterTcom());
    EXPECT_EQ(0x1200u, fsp.getAddress());
    ASSERT_EQ(1u, fsp.getDspAddresses().size());
    EXPECT_EQ(0x1230u, fsp.getDspAddresses().back());
}

}
