#include "KickStart_2019_RoundB_P2_EnergyStones.hpp"

#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundB_P2_EnergyStones
{

TEST(KickStart_2019_RoundB_P2_EnergyStonesTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "3        " "\n"
            << "4        " "\n"
            << "20 10 1  " "\n"
            << "5 30 5   " "\n"
            << "100 30 1 " "\n"
            << "5 80 60  " "\n"
            << "3        " "\n"
            << "10 4 1000" "\n"
            << "10 3 1000" "\n"
            << "10 8 1000" "\n"
            << "2        " "\n"
            << "12 300 50" "\n"
            << "5 200 0  " "\n"
            << endl;

    main();

    EXPECT_EQ(
                "Case #1: 105" "\n"
                "Case #2: 8" "\n"
                "Case #3: 500" "\n"
                , outputStringStream.str());
}
}

