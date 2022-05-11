//#define ALBA_PRINT_OUTPUT_STREAM_FILE_PATH APRG_DIR "/Log.txt" //use this macro for file outputs

#include <Common/Debug/AlbaDebug.hpp>

#include <gtest/gtest.h>

#include <map>
#include <memory>

using namespace std;

namespace alba
{

TEST(AlbaDebugTest, PrintTest)
{
    unsigned int singleParameter1=75, singleParameter2=75, singleParameter3=75;
    unique_ptr<unsigned int> uniquePointer(make_unique<unsigned int>(695));    unsigned int const* nullPointer = nullptr;
    unsigned int const* rawPointer = uniquePointer.get();
    vector<unsigned int> container1{454, 6, 512, 315};
    map<unsigned int, char> container2{{1U, 'A'}, {5U, 'E'}, {7U, 'G'}, {8U, 'H'}};
    ALBA_PRINT4("Print for single parameters", singleParameter1, singleParameter2, singleParameter3);
    ALBA_PRINT4("Print for pointer", nullPointer, rawPointer, uniquePointer);
    ALBA_PRINT3("Print for containers", container1, container2);

    ALBA_PRINT_MANIPULATE_OUTPUT(std::uppercase);
    ALBA_PRINT_MANIPULATE_OUTPUT(std::hex);
    ALBA_PRINT4("Print for single parameters", singleParameter1, singleParameter2, singleParameter3);
    ALBA_PRINT4("Print for pointer", nullPointer, rawPointer, uniquePointer);
    ALBA_PRINT3("Print for containers", container1, container2);
    ALBA_PRINT_MANIPULATE_OUTPUT(std::dec);
}

}