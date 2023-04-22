#include "KickStart_2020_RoundD_P2_AlienPiano.hpp"

#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2020_RoundD_P2_AlienPiano
{

TEST(KickStart_2020_RoundD_P2_AlienPianoTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "2              " "\n"
            << "5              " "\n"
            << "1 5 100 500 1  " "\n"
            << "8              " "\n"
            << "2 3 4 5 6 7 8 9" "\n"
            << endl;

    main();

    EXPECT_EQ(
                "Case #1: 0" "\n"
                "Case #2: 1" "\n"
                , outputStringStream.str());
}

}

