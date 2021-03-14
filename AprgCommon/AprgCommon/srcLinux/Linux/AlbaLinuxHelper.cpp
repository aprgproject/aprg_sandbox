#include "AlbaLinuxHelper.hpp"

#include <String/AlbaStringHelper.hpp>

#include <cstring>

using namespace std;

namespace alba
{

string AlbaLinuxHelper::getErrorMessage(int const localErrnoCopy)
{
    constexpr unsigned int const MAX_ERROR_CHAR_STRING=256;
    char characterBuffer[MAX_ERROR_CHAR_STRING];
    char const * str = strerror_r(localErrnoCopy, characterBuffer, MAX_ERROR_CHAR_STRING);
    return string(str);
}

}//namespace alba
