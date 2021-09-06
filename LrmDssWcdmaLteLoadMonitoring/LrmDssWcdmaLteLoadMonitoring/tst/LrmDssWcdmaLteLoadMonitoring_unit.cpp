#include <LrmDssWcdmaLteLoadMonitoring.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(LrmDssWcdmaLteLoadMonitoringTest, ConsecutiveLowerLoadStateCountIsInitiallyZero)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When

    //Then
    EXPECT_EQ(0U, loadMonitoring.getConsecutiveLowerLoadStateCount());
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, ConsecutiveLowerLoadStateCountCanBeSet){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    //When
    loadMonitoring.setConsecutiveLowerLoadStateCount(10);

    //Then
    EXPECT_EQ(10U, loadMonitoring.getConsecutiveLowerLoadStateCount());
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, CommissioningLoadFactorValuesAreInitiallyZero){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When

    //Then
    EXPECT_EQ(0U, loadMonitoring.getDchLoadFactor());
    EXPECT_EQ(0U, loadMonitoring.getHsdpaAndHsfachLoadFactor());
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, CommissioningLoadFactorValuesCanBeSet){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When
    loadMonitoring.setCommissioningLoadFactorValues(60, 70);
    //Then
    EXPECT_EQ(60U, loadMonitoring.getDchLoadFactor());
    EXPECT_EQ(70U, loadMonitoring.getHsdpaAndHsfachLoadFactor());
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, CommissioningLoadThresholdValuesAreInitiallyZero){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When

    //Then
    EXPECT_EQ(0U, loadMonitoring.getMediumLoadThreshold());
    EXPECT_EQ(0U, loadMonitoring.getHighLoadThreshold());
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, CommissioningLoadFactorThresholdCanBeSet){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    //When
    loadMonitoring.setCommissioningLoadThresholdValues(100, 180);

    //Then
    EXPECT_EQ(100U, loadMonitoring.getMediumLoadThreshold());
    EXPECT_EQ(180U, loadMonitoring.getHighLoadThreshold());
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, LowLoadStateCanBeDeterminedBasedOnCellLoad){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    //When
    loadMonitoring.setCommissioningLoadThresholdValues(100, 180);

    //Then
    EXPECT_EQ(EDssWcdmaLoad_Low, loadMonitoring.getLoadStateFromCellLoad(99));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, MediumLoadStateCanBeDeterminedBasedOnCellLoad)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When
    loadMonitoring.setCommissioningLoadThresholdValues(100, 180);

    //Then
    EXPECT_EQ(EDssWcdmaLoad_Medium, loadMonitoring.getLoadStateFromCellLoad(100));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, HighLoadStateCanBeDeterminedBasedOnCellLoad)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When
    loadMonitoring.setCommissioningLoadThresholdValues(100, 180);

    //Then
    EXPECT_EQ(EDssWcdmaLoad_High, loadMonitoring.getLoadStateFromCellLoad(180));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, CellLoadIsCalculatedAsZeroWhenThereAreNoUsersAndHsFach)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When

    //Then
    EXPECT_EQ(0U, loadMonitoring.calculateCellLoad(0, 0, false));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, DchLoadIsCalculatedAsPartOfCellLoad){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    //When
    loadMonitoring.setCommissioningLoadFactorValues(34, 56);

    //Then
    EXPECT_EQ(918U, loadMonitoring.calculateCellLoad(27, 0, false));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, HsdpaLoadIsCalculatedAsPartOfCellLoad){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    //When
    loadMonitoring.setCommissioningLoadFactorValues(34, 56);

    //Then
    EXPECT_EQ(4704U, loadMonitoring.calculateCellLoad(0, 84, false));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, HsfachIsCalculatedAsPartOfCellLoad){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    //When
    loadMonitoring.setCommissioningLoadFactorValues(34, 56);

    //Then
    EXPECT_EQ(56U, loadMonitoring.calculateCellLoad(0, 0, true));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, CellLoadIsCalculatedCorrectlyWhenAllParametersArePresent) // not TDD but for peace of mind{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    //When
    loadMonitoring.setCommissioningLoadFactorValues(34, 56);

    //Then
    EXPECT_EQ(5678U, loadMonitoring.calculateCellLoad(27, 84, true));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, NextLoadStateIsLowWhenAllInputLoadStatesAreLow){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    //When
    EDssWcdmaLoad currentLoadState = EDssWcdmaLoad_Low;
    EDssWcdmaLoad currentLoadStateOfTheAppliedFilter = EDssWcdmaLoad_Low;
    loadMonitoring.setConsecutiveLowerLoadStateCount(0);

    EXPECT_EQ(EDssWcdmaLoad_Low, loadMonitoring.determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(currentLoadState, currentLoadStateOfTheAppliedFilter));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, NextLoadStateIsHighWhenAllInputLoadStatesAreHigh)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When
    EDssWcdmaLoad currentLoadState = EDssWcdmaLoad_High;
    EDssWcdmaLoad currentLoadStateOfTheAppliedFilter = EDssWcdmaLoad_High;
    loadMonitoring.setConsecutiveLowerLoadStateCount(0);

    EXPECT_EQ(EDssWcdmaLoad_High, loadMonitoring.determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(currentLoadState, currentLoadStateOfTheAppliedFilter));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, ConsecutiveLowerLoadStateCountIsResetToZeroWhenAllInputLoadStatesAreSame)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    loadMonitoring.setConsecutiveLowerLoadStateCount(10);

    //When
    EDssWcdmaLoad currentLoadState = EDssWcdmaLoad_High;
    EDssWcdmaLoad currentLoadStateOfTheAppliedFilter = EDssWcdmaLoad_High;
    loadMonitoring.determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(currentLoadState, currentLoadStateOfTheAppliedFilter);

    EXPECT_EQ(0U, loadMonitoring.getConsecutiveLowerLoadStateCount());
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, ConsecutiveLowerLoadStateCountIsIncrementedWhenCurrentLoadStateIsLowerThanTheLoadOfAppliedFilter){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    loadMonitoring.setConsecutiveLowerLoadStateCount(10);
    //When
    EDssWcdmaLoad currentLoadState = EDssWcdmaLoad_Low;
    EDssWcdmaLoad currentLoadStateOfTheAppliedFilter = EDssWcdmaLoad_High;
    loadMonitoring.determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(currentLoadState, currentLoadStateOfTheAppliedFilter);

    EXPECT_EQ(11U, loadMonitoring.getConsecutiveLowerLoadStateCount());
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, NextLowerLoadStateCanBeDetermined){
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;
    //When

    //Then
    EXPECT_EQ(EDssWcdmaLoad_Low, loadMonitoring.getNextLowerLoadState(EDssWcdmaLoad_Low));
    EXPECT_EQ(EDssWcdmaLoad_Low, loadMonitoring.getNextLowerLoadState(EDssWcdmaLoad_Medium));
    EXPECT_EQ(EDssWcdmaLoad_Medium, loadMonitoring.getNextLowerLoadState(EDssWcdmaLoad_High));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, NextLoadStateIsTheLowerLoadStateOfAppliedFilterWhenFilteringCountIsLessThanNextSavedCount)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When
    EDssWcdmaLoad currentLoadState = EDssWcdmaLoad_Low;
    EDssWcdmaLoad currentLoadStateOfTheAppliedFilter = EDssWcdmaLoad_High;
    loadMonitoring.setConsecutiveLowerLoadStateCount(DSS_WCDMA_LTE_LOAD_STATE_CHANGE_FILTERING_COUNT-2);

    //Then
    EXPECT_EQ(EDssWcdmaLoad_Medium, loadMonitoring.determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(currentLoadState, currentLoadStateOfTheAppliedFilter));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, NextLoadStateIsTheSameLoadStateOfAppliedFilterWhenFilteringCountIsEqualToNextSavedCount)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When
    EDssWcdmaLoad currentLoadState = EDssWcdmaLoad_Low;
    EDssWcdmaLoad currentLoadStateOfTheAppliedFilter = EDssWcdmaLoad_High;
    loadMonitoring.setConsecutiveLowerLoadStateCount(DSS_WCDMA_LTE_LOAD_STATE_CHANGE_FILTERING_COUNT-1);

    //Then
    EXPECT_EQ(EDssWcdmaLoad_High, loadMonitoring.determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(currentLoadState, currentLoadStateOfTheAppliedFilter));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, NextLoadStateIsTheSameLoadStateOfAppliedFilterWhenCurrentLoadStateIsHigherThanLoadStateOfAppliedFilter) //Not TDD but for piece of mind
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When
    EDssWcdmaLoad currentLoadState = EDssWcdmaLoad_High;
    EDssWcdmaLoad currentLoadStateOfTheAppliedFilter = EDssWcdmaLoad_Low;

    //Then
    EXPECT_EQ(EDssWcdmaLoad_High, loadMonitoring.determineLoadStateForTheNextFilterUpdateAndUpdateConsecutiveLowerLoadStateCountIfNeeded(currentLoadState, currentLoadStateOfTheAppliedFilter));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, ConversionOfFilterBandwidthToLoadStateWorks)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When

    //Then
    EXPECT_EQ(EDssWcdmaFilterBandwidth_1200_KHz, loadMonitoring.convertLoadStateToFilterBandwidth(EDssWcdmaLoad_Low));
    EXPECT_EQ(EDssWcdmaFilterBandwidth_600_KHz, loadMonitoring.convertLoadStateToFilterBandwidth(EDssWcdmaLoad_Medium));
    EXPECT_EQ(EDssWcdmaFilterBandwidth_0_KHz, loadMonitoring.convertLoadStateToFilterBandwidth(EDssWcdmaLoad_High));
}

TEST(LrmDssWcdmaLteLoadMonitoringTest, ConversionOfLoadStateToFilterBandwidthWorks)
{
    //Given
    LrmDssWcdmaLteLoadMonitoring loadMonitoring;

    //When

    //Then
    EXPECT_EQ(EDssWcdmaLoad_Low, loadMonitoring.convertFilterBandwidthToLoadState(EDssWcdmaFilterBandwidth_1200_KHz));
    EXPECT_EQ(EDssWcdmaLoad_Medium, loadMonitoring.convertFilterBandwidthToLoadState(EDssWcdmaFilterBandwidth_600_KHz));
    EXPECT_EQ(EDssWcdmaLoad_High, loadMonitoring.convertFilterBandwidthToLoadState(EDssWcdmaFilterBandwidth_0_KHz));
}

}
