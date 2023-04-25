#include "KickStart_2019_RoundD_P1_XOrWhat.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundD_P1_XOrWhat {

TEST(KickStart_2019_RoundD_P1_XOrWhatTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "2            "
                         "\n"
                      << "4 3          "
                         "\n"
                      << "10 21 3 7    "
                         "\n"
                      << "1 13         "
                         "\n"
                      << "0 32         "
                         "\n"
                      << "2 22         "
                         "\n"
                      << "5 1          "
                         "\n"
                      << "14 1 15 20 26"
                         "\n"
                      << "4 26         "
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 4 3 4"
        "\n"
        "Case #2: 4"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2019_RoundD_P1_XOrWhat
