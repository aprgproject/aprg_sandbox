#include "KickStart_2020_RoundG_P4_MergeCards.hpp"

#include <Fake/FakeObjects.hpp>
#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2020_RoundG_P4_MergeCards
{

TEST(KickStart_2020_RoundG_P4_MergeCardsTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "2           " "\n"
            << "3           " "\n"
            << "2 1 10      " "\n"
            << "5           " "\n"
            << "19 3 78 2 31" "\n"
            << endl;

    main();

    EXPECT_EQ(
                "Case #1: 20" "\n"
                "Case #2: 352.3333333" "\n"
                , outputStringStream.str());
}

}

