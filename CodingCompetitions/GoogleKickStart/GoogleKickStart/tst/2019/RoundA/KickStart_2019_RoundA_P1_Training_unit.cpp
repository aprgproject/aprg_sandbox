#include "KickStart_2019_RoundA_P1_Training.hpp"

#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundA_P1_Training
{

TEST(KickStart_2019_RoundA_P1_TrainingTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "3          " "\n"
            << "4 3        " "\n"
            << "3 1 9 100  " "\n"
            << "6 2        " "\n"
            << "5 5 1 2 3 4" "\n"
            << "5 5        " "\n"
            << "7 7 1 7 7  " "\n"
            << endl;

    main();

    EXPECT_EQ(
                "Case #1: 14" "\n"
                "Case #2: 0" "\n"
                "Case #3: 6" "\n"
                , outputStringStream.str());
}

}


