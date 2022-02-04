//#define ALBA_PRINT_OUTPUT_STREAM_FILE_PATH APRG_DIR "/Log.txt" //use this macro for file outputs

#include <Debug/AlbaDebug.hpp>

#include <gtest/gtest.h>

#include <map>

using namespace std;

namespace alba
{

TEST(AlbaDebugTest, DISABLED_PrintTest)
{
    map<unsigned int, char> container{{1U, 'A'}, {5U, 'E'}, {7U, 'G'}, {8U, 'H'}};
    unsigned int singleParameter1=75, singleParameter2=76, singleParameter3=77;

    ALBA_PRINT5("Const char* string literal", container, singleParameter1, singleParameter2, singleParameter3);
}

}
