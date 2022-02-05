#include "AlbaLocalTimer.hpp"

#include <Common/Time/AlbaDateTime.hpp>

using namespace std;

namespace alba
{

string AlbaLocalTimer::getElapsedTimeDisplayableString() const
{
    AlbaDateTime difference(getDifferenceBetweenTimes());
    return difference.getPrintableStringFormat3();
}

}//namespace alba
