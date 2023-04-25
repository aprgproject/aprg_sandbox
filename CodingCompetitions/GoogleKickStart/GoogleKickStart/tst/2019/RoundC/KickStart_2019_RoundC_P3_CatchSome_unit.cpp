#include "KickStart_2019_RoundC_P3_CatchSome.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundC_P3_CatchSome {

TEST(KickStart_2019_RoundC_P3_CatchSomeTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "3              "
                         "\n"
                      << "4 3            "
                         "\n"
                      << "1 2 4 9        "
                         "\n"
                      << "3 3 2 3        "
                         "\n"
                      << "4 3            "
                         "\n"
                      << "1 2 3 4        "
                         "\n"
                      << "1 8 1 8        "
                         "\n"
                      << "6 6            "
                         "\n"
                      << "4 3 3 1 3 10000"
                         "\n"
                      << "1 2 8 9 5 7    "
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 8"
        "\n"
        "Case #2: 6"
        "\n"
        "Case #3: 10028"
        "\n",
        outputStringStream.str());
}

TEST(KickStart_2019_RoundC_P3_CatchSomeTest, Test2) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "1      "
                         "\n"
                      << "4 3    "
                         "\n"
                      << "4 1 2 9"
                         "\n"
                      << "2 3 3 3"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 8"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2019_RoundC_P3_CatchSome
