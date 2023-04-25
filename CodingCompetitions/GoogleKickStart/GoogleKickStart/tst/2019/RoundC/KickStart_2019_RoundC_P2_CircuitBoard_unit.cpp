#include "KickStart_2019_RoundC_P2_CircuitBoard.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundC_P2_CircuitBoard {

TEST(KickStart_2019_RoundC_P2_CircuitBoardTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "3         "
                         "\n"
                      << "1 4 0     "
                         "\n"
                      << "3 1 3 3   "
                         "\n"
                      << "2 3 0     "
                         "\n"
                      << "4 4 5     "
                         "\n"
                      << "7 6 6     "
                         "\n"
                      << "4 5 0     "
                         "\n"
                      << "2 2 4 4 20"
                         "\n"
                      << "8 3 3 3 12"
                         "\n"
                      << "6 6 3 3 3 "
                         "\n"
                      << "1 6 8 6 4 "
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 2"
        "\n"
        "Case #2: 2"
        "\n"
        "Case #3: 6"
        "\n",
        outputStringStream.str());
}

TEST(KickStart_2019_RoundC_P2_CircuitBoardTest, Test2) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "3          "
                         "\n"
                      << "1 4 2      "
                         "\n"
                      << "3 1 3 3    "
                         "\n"
                      << "3 3 2      "
                         "\n"
                      << "0 5 0      "
                         "\n"
                      << "8 12 3     "
                         "\n"
                      << "7 10 1     "
                         "\n"
                      << "4 4 8      "
                         "\n"
                      << "20 10 20 10"
                         "\n"
                      << "10 4 5 20  "
                         "\n"
                      << "20 5 4 10  "
                         "\n"
                      << "10 20 10 20"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 4"
        "\n"
        "Case #2: 3"
        "\n"
        "Case #3: 4"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2019_RoundC_P2_CircuitBoard
