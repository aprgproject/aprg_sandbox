#include <Common/Macros/AlbaXMacros.hpp>

#include <gtest/gtest.h>

#include <sstream>

using namespace std;

namespace alba
{

TEST(AlbaXMacroTests, OneParameterSampleTest)
{
    stringstream ss;
    //declaration part
#define ALBA_XMACROS_SAMPLE_FUNCTION_WITH_ONE_PARAMETER(parameter) string parameter(#parameter);
    ALBA_XMACROS_SAMPLE_LIST_WITH_ONE_PARAMETER
#undef ALBA_XMACROS_SAMPLE_FUNCTION_WITH_ONE_PARAMETER

    //print part
#define ALBA_XMACROS_SAMPLE_FUNCTION_WITH_ONE_PARAMETER(parameter) ss << #parameter << ": " << (parameter) << endl;
    ALBA_XMACROS_SAMPLE_LIST_WITH_ONE_PARAMETER
#undef ALBA_XMACROS_SAMPLE_FUNCTION_WITH_ONE_PARAMETER

    EXPECT_EQ("parameter1InList: parameter1InList\nparameter2InList: parameter2InList\nparameter3InList: parameter3InList\n", ss.str());
}

}
