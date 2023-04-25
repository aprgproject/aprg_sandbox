
#include "AlbaLinuxTimeHelper.hpp"

#include <Common/Time/AlbaDateTimeConstants.hpp>

#include <unistd.h>

namespace alba {

AlbaDateTime convertSystemTimeToAlbaDateTime(struct timespec const& timeSpec) {
    struct tm* timeInformation;
    timeInformation = localtime(&(timeSpec.tv_sec));
    return AlbaDateTime(
        static_cast<unsigned short>(timeInformation->tm_year), static_cast<unsigned char>(timeInformation->tm_mon + 1),
        static_cast<unsigned char>(timeInformation->tm_mday), static_cast<unsigned char>(timeInformation->tm_hour),
        static_cast<unsigned char>(timeInformation->tm_min), static_cast<unsigned char>(timeInformation->tm_sec),
        static_cast<unsigned int>(
            static_cast<double>(timeSpec.tv_nsec) / AlbaDateTimeConstants::NUMBER_OF_NANOSECONDS_IN_A_MICROSECOND));
}

}  // namespace alba
