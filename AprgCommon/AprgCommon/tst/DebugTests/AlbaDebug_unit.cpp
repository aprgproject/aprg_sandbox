
//#define ALBA_PRINT_OUTPUT_STREAM_FILE_PATH APRG_DIR "/Log.txt" //use this macro for file outputs

#include <Debug/AlbaDebug.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

TEST(AlbaDebugTest, DISABLED_PrintTest)
{
    unsigned int Mark=0,Earvin=0,Alba=0;
    ALBA_PRINT3(Mark, Earvin, Alba);
}
}
