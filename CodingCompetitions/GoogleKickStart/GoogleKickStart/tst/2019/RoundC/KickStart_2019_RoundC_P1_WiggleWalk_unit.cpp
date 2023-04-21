#include "KickStart_2019_RoundC_P1_WiggleWalk.hpp"

#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundC_P1_WiggleWalk
{

TEST(KickStart_2019_RoundC_P1_WiggleWalkTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "3          " "\n"
            << "5 3 6 2 3  " "\n"
            << "EEWNS      " "\n"
            << "4 3 3 1 1  " "\n"
            << "SESE       " "\n"
            << "11 5 8 3 4 " "\n"
            << "NEESSWWNESE" "\n"
            << endl;

    main();

    EXPECT_EQ(
                "Case #1: 3 2" "\n"
                "Case #2: 3 3" "\n"
                "Case #3: 3 7" "\n"
                , outputStringStream.str());
}

TEST(KickStart_2019_RoundC_P1_WiggleWalkTest, Test2)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "1          " "\n"
            << "11 5 8 3 4 " "\n"
            << "NEESSWWNESE" "\n"
            << endl;

    main();

    EXPECT_EQ(
                "Case #1: 3 7" "\n"
                , outputStringStream.str());
}
}

