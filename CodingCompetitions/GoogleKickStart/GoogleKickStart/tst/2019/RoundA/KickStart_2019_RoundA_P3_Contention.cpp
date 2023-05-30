// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundA_P3_Contention.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <climits>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_RoundA_P3_Contention {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

using Interval = pair<int, int>;
using Intervals = vector<Interval>;

int getMinimumSeats(Intervals const& bookings) {
    int minimumNewSeats = 0;
    Interval accumulatedInterval;
    bool isFirst(true);
    for (Interval const& booking : bookings) {
        if (isFirst) {
            accumulatedInterval = booking;
            minimumNewSeats = booking.second - booking.first + 1;
            isFirst = false;
        } else {
            int newSeats = 0;
            if (booking.first < accumulatedInterval.first) {
                newSeats += min(booking.second + 1, accumulatedInterval.first) - booking.first;
                accumulatedInterval.first = booking.first;
            }
            if (accumulatedInterval.second < booking.second) {
                newSeats += booking.second - max(booking.first - 1, accumulatedInterval.second);
                accumulatedInterval.second = booking.second;
            }
            minimumNewSeats = min(minimumNewSeats, newSeats);
        }
    }
    return minimumNewSeats;
}

int getMinimumSeatsFromLeftToRight(Intervals& bookings) {
    sort(bookings.begin(), bookings.end(), [](Interval const& interval1, Interval const& interval2) {
        if (interval1.first == interval2.first) {
            return interval1.second < interval2.second;
        } else {
            return interval1.first > interval2.first;
        }
    });
    return getMinimumSeats(bookings);
}

int getMinimumSeatsFromRightToLeft(Intervals& bookings) {
    sort(bookings.begin(), bookings.end(), [](Interval const& interval1, Interval const& interval2) {
        if (interval1.second == interval2.second) {
            return interval1.first > interval2.first;
        } else {
            return interval1.second < interval2.second;
        }
    });
    return getMinimumSeats(bookings);
}

void runTestCase(int const testCaseNumber) {
    int numberOfSeats, numberOfBookings;
    my_cin >> numberOfSeats >> numberOfBookings;
    Intervals bookings;
    for (int y = 0; y < numberOfBookings; ++y) {
        int leftIndex, rightIndex;
        my_cin >> leftIndex >> rightIndex;
        bookings.emplace_back(leftIndex, rightIndex);
    }

    int maximumOfMinimumSeats = max(getMinimumSeatsFromLeftToRight(bookings), getMinimumSeatsFromRightToLeft(bookings));
    // Why maximumOfMinimumSeats?
    // What is the largest integer k where there exists an order that you can enter the bookings into the system,
    // such that each booking is assigned at least k seats?

    my_cout << "Case #" << testCaseNumber << ": " << maximumOfMinimumSeats << '\n';
}

/*

Code of top scorer:

int numberOfSeats, numberOfBookings;
vector<Interval> bookings;
vector<int> val;

bool isWithinTheLimit(int minimumSeatsLimit)
{
    val.assign(bookings.size(), 0);
    set<Interval> setOfIntervals;
    int last = 0;
    int cur = 0;
    for (auto const& booking : bookings)
    {
        int left = booking.first, right = booking.second;
        while (!setOfIntervals.empty())
        {
            auto it = setOfIntervals.begin();
            if (it->first <= left)
            {
                val[it->second] += max(it->first - last, 0);
                last = max(last, it->first);
                setOfIntervals.erase(it);
            }
            else
                break;
        }

        if (last < left)
        {
            if (!setOfIntervals.empty())
            {
                val[setOfIntervals.begin()->second] += left - last;
            }
            last = left;
        }

        Interval now(right, cur++);
        setOfIntervals.insert(now);
        auto it = setOfIntervals.lower_bound(now);
        if (it == setOfIntervals.begin())
            continue;
        --it;
        while (1)
        {
            if (val[it->second] >= minimumSeatsLimit)
            {
                if (it == setOfIntervals.begin())
                {
                    setOfIntervals.erase(it);
                    break;
                }
                else
                {
                    auto bef = it;
                    --it;
                    setOfIntervals.erase(bef);
                }
            }
            else
                break;
        }
    }


    while (!setOfIntervals.empty())
    {
        auto it = setOfIntervals.begin();
        val[it->second] += max(it->first - last, 0);
        last = max(last, it->first);
        setOfIntervals.erase(it);
    }

    // cerr << last << endl;
    bool ret = 1;
    // cerr << " cek " << x << endl;
    int w = 0;
    for (int u : val)
    {
        if (u < minimumSeatsLimit)
        {
            ret = 0;
        }
        // cerr << u << " " << seg[w].first << " " << seg[w].second << endl;
        ++w;
    }
    return ret;
}

void runTestCase(int const testCaseNumber)
{
    my_cin >> numberOfSeats >> numberOfBookings;
    bookings.resize(numberOfBookings);
    int lo = 0, hi = numberOfSeats;
    for (int i = 0; i < numberOfBookings; ++i) {
        int l, r;
        my_cin >> l >> r;
        --l;
        bookings[i] = {l, r};
        hi = min(hi, r-l);
    }
    sort(bookings.begin(), bookings.end());
    while (lo < hi)
    {
        int mid = (lo + hi + 1) >> 1;
        if (isWithinTheLimit(mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    my_cout << "Case #" << testCaseNumber << ": " << hi << '\n';
}
*/

void runAllTestCases() {
    int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++) {
        runTestCase(testCaseNumber);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
}  // namespace KickStart_2019_RoundA_P3_Contention
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
