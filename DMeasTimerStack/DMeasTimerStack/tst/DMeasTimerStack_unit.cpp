#include <DMeasTimerStack.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace DMeas;

TEST(TimerStackTest, TestForEmptyTimerStack)
{
    TimerStack timerStack;
    TSfn sampleSfn = 0;
    TimerStack::TimerIndex sampleTimerIndex = 0;
    TimerData sampleTimerData;
    TimeCounter sampleTimeCounter = 0;

    EXPECT_EQ(EBoolean_True, timerStack.mayIPrint());
    EXPECT_EQ(TIMER_INVALID_ITERATOR, timerStack.ARRAY_timers_first(0));
    EXPECT_EQ(nullptr, timerStack.ARRAY_timers_second(0));
    EXPECT_EQ(nullptr, timerStack.timersFindNbccRecovery(0, sampleTimerIndex));
    EXPECT_EQ(EBoolean_False, timerStack.trigExpiredAndRemove(sampleTimerIndex));
    EXPECT_EQ(EBoolean_False, timerStack.preRefresh(sampleSfn));
    EXPECT_EQ(EBoolean_False, timerStack.renewMeasurement(sampleTimerIndex, sampleTimeCounter));
    EXPECT_EQ(EBoolean_False, timerStack.remove(sampleTimerIndex));
    timerStack.initIterator(sampleTimerIndex);
    EXPECT_EQ(EBoolean_False, timerStack.isValidIterator(sampleTimerIndex));
    timerStack.clearUserTimers(0);
    timerStack.removeTimerPrint(TimerType::FreeTimer, 0);
    timerStack.dump(0, 0);
    timerStack.dump();

    EXPECT_EQ(EBoolean_True, timerStack.insert(sampleSfn, sampleTimerData));
    EXPECT_EQ(EBoolean_True, timerStack.insert(sampleSfn, sampleTimerData, sampleTimerIndex));
    EXPECT_EQ(EBoolean_True, timerStack.insertMeasurement(TimerType::FreeTimer, 0, 0, 0, sampleTimerIndex, 0));
}

TEST(TimerStackTest, InsertThenExpireAndRemoveTheTimer)
{
    TimerStack timerStack;
    TSfn sampleSfn = 17;
    TimerData sampleTimerData;
    sampleTimerData.timerType=TimerType::MeasurementInit;
    sampleTimerData.timerValue=20;
    TimerStack::TimerIndex firstTimerIndex = 0;

    EXPECT_EQ(EBoolean_True, timerStack.insert(sampleSfn, sampleTimerData));
    EXPECT_EQ(sampleSfn, timerStack.ARRAY_timers_first(firstTimerIndex));
    TimerData* actualTimerDataPtr = timerStack.ARRAY_timers_second(firstTimerIndex);
    ASSERT_NE(nullptr, actualTimerDataPtr);
    EXPECT_EQ(TimerType::MeasurementInit, actualTimerDataPtr->timerType);
    EXPECT_EQ(sampleSfn, actualTimerDataPtr->timerValue);

    EXPECT_EQ(EBoolean_True, timerStack.trigExpiredAndRemove(firstTimerIndex));
    EXPECT_EQ(0, timerStack.ARRAY_timers_first(firstTimerIndex));
    ASSERT_NE(nullptr, actualTimerDataPtr);
}