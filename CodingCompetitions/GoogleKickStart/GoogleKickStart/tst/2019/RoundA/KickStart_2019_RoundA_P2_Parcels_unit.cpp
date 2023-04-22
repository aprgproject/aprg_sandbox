#include "KickStart_2019_RoundA_P2_Parcels.hpp"

#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundA_P2_Parcels
{

TEST(KickStart_2019_RoundA_P2_ParcelsTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "3    " "\n"
            << "3 3  " "\n"
            << "101  " "\n"
            << "000  " "\n"
            << "101  " "\n"
            << "1 2  " "\n"
            << "11   " "\n"
            << "5 5  " "\n"
            << "10001" "\n"
            << "00000" "\n"
            << "00000" "\n"
            << "00000" "\n"
            << "10001" "\n"
            << endl;

    main();

    EXPECT_EQ(
                "Case #1: 1" "\n"
                "Case #2: 0" "\n"
                "Case #3: 2" "\n"
                , outputStringStream.str());
}

}


