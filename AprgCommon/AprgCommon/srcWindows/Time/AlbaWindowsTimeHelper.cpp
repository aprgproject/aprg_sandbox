#include "AlbaWindowsTimeHelper.hpp"

namespace alba
{

void sleep(unsigned int const milliSeconds)
{
    Sleep(milliSeconds);
}

AlbaDateTime getCurrentDateTime()
{
    SYSTEMTIME currentTime;
    GetSystemTime(&currentTime);
    return convertSystemTimeToAlbaDateTime(currentTime);
}

AlbaDateTime convertSystemTimeToAlbaDateTime(SYSTEMTIME const& systemTime)
{
    return AlbaDateTime(systemTime.wYear,
                        systemTime.wMonth,
                        systemTime.wDay,
                        systemTime.wHour,
                        systemTime.wMinute,
                        systemTime.wSecond,
                        systemTime.wMilliseconds*1000);
}

}//namespace alba
