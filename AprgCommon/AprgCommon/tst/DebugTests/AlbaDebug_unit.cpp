//#define ALBA_PRINT_OUTPUT_STREAM_FILE_PATH APRG_DIR "/Log.txt" //use this macro for file outputs

#include <Debug/AlbaDebug.hpp>

#include <gtest/gtest.h>

#include <map>

using namespace std;

namespace alba{

TEST(AlbaDebugTest, DISABLED_PrintTest)
{    unsigned int Mark=0,Earvin=0,Alba=0;

    ALBA_PRINT3(Mark, Earvin, Alba);
}

TEST(AlbaDebugTest, DISABLED_PrintContainerTest)
{
    map<unsigned int, char> container{{1U, 'A'}, {5U, 'E'}, {7U, 'G'}, {8U, 'H'}};

    ALBA_PRINT_CONTAINER(container);
}

}