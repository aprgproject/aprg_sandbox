#include "KickStart_2019_RoundB_P3_DiverseSubarray.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2019_RoundB_P3_DiverseSubarray {

TEST(KickStart_2019_RoundB_P3_DiverseSubarrayTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "4                            "
                         "\n"
                      << "6 2                          "
                         "\n"
                      << "1 1 4 1 4 4                  "
                         "\n"
                      << "8 1                          "
                         "\n"
                      << "1 2 500 3 4 500 6 7          "
                         "\n"
                      << "10 1                         "
                         "\n"
                      << "100 200 8 8 8 8 8 300 400 100"
                         "\n"
                      << "12 2                         "
                         "\n"
                      << "40 50 1 1 1 60 70 2 2 2 80 90"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 4"
        "\n"
        "Case #2: 6"
        "\n"
        "Case #3: 4"
        "\n"
        "Case #4: 6"
        "\n",
        outputStringStream.str());
}

TEST(KickStart_2019_RoundB_P3_DiverseSubarrayTest, Test2) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "1                            "
                         "\n"
                      << "6 2                          "
                         "\n"
                      << "1 1 4 1 4 4                  "
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 4"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2019_RoundB_P3_DiverseSubarray
