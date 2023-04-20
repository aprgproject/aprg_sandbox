#include "KickStart_2020_RoundB_P1_BikeTour.hpp"

#include <Fake/FakeObjects.hpp>
#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2020_RoundB_P1_BikeTour
{

TEST(KickStart_2020_RoundB_P1_BikeTourTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "4             " "\n"
            << "3             " "\n"
            << "10 20 14      " "\n"
            << "4             " "\n"
            << "7 7 7 7       " "\n"
            << "5             " "\n"
            << "10 90 20 90 10" "\n"
            << "3             " "\n"
            << "10 3 10       " "\n"
            << endl;

    main();

    EXPECT_EQ(
                "Case #1: 1" "\n"
                "Case #2: 0" "\n"
                "Case #3: 2" "\n"
                "Case #4: 0" "\n"
                , outputStringStream.str());
}

}

