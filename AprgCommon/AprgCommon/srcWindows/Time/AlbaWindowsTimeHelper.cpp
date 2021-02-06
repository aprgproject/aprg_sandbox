#include "AlbaWindowsTimeHelper.hpp"

namespace alba
{

void AlbaWindowsTimeHelper::sleep(unsigned int const milliSeconds)
{
    Sleep(milliSeconds);
}

AlbaDateTime AlbaWindowsTimeHelper::getCurrentDateTime()
{
    SYSTEMTIME currentTime;
    GetSystemTime(&currentTime);
    return convertSystemTimeToAlbaDateTime(currentTime);
}

AlbaDateTime AlbaWindowsTimeHelper::convertSystemTimeToAlbaDateTime(SYSTEMTIME const& systemTime)
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
