#include <BtsLogPrint.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <fstream>
#include <vector>

using namespace tcomToolsBackend;
using namespace std;

TEST(BtsLogPrintTest, DefaultConstructorIsEmpty)
{
    BtsLogPrint logPrint;
    EXPECT_TRUE(logPrint.isEmpty());
}

TEST(BtsLogPrintTest, ClearingMakesItEmpty)
{
    BtsLogPrint logPrint("000312 23.09 12:06:04.213  [192.168.255.1]  b5 FSP-120D-1-TCOMexe <2015-09-23T09:06:04.156235Z> BE6 DBG/TCOM/CH, TC_TOAM_POWERLEVEL_REPORT_NOTIFICATION_MSG from 0x120D0156, size: 20 cellId: 1996, averagePowerRxLevel: 65");
    EXPECT_FALSE(logPrint.isEmpty());
    logPrint.clear();
    EXPECT_TRUE(logPrint.isEmpty());
}

TEST(BtsLogPrintTest, PrintFromBtsSyslogsIsUsed)
{
    BtsLogPrint logPrint("000312 23.09 12:06:04.213  [192.168.255.1]  b5 FSP-120D-1-TCOMexe <2015-09-23T09:06:04.156235Z> BE6 DBG/TCOM/CH, TC_TOAM_POWERLEVEL_REPORT_NOTIFICATION_MSG from 0x120D0156, size: 20 cellId: 1996, averagePowerRxLevel: 65");
    BtsLogTime expectedBtsTime(BtsLogTimeType::BtsTimeStamp, "2015-09-23T09:06:04.156235Z");
    BtsLogTime expectedPcTime(BtsLogTimeType::PcTimeStamp, "23.09 12:06:04.213");
    string expectedHardwareType("FSP-120D");
    string expectedPrint("FSP-120D-1-TCOMexe <2015-09-23T09:06:04.156235Z> BE6 DBG/TCOM/CH, TC_TOAM_POWERLEVEL_REPORT_NOTIFICATION_MSG from 0x120D0156, size: 20 cellId: 1996, averagePowerRxLevel: 65");

    EXPECT_EQ(expectedBtsTime, logPrint.getBtsTime());
    EXPECT_EQ(expectedPcTime, logPrint.getPcTime());
    EXPECT_EQ(expectedHardwareType, logPrint.getHardwareAddress());
    EXPECT_EQ(expectedPrint, logPrint.getPrint());
}

TEST(BtsLogPrintTest, PrintFromBtsLogSorterIsUsed)
{
    BtsLogPrint logPrint("SYSLOG_73.LOG            |26.11 07:39:15.009000 FSP-120C-0-TCOMexe <2015-11-26T05:39:14.187399Z> 74 INF/TCOM/G, Received BB_SAMPLE_REPORT_IND_MSG Provider: MasterHsupa, SampleStartSfn: 0, SampledDataVolume: 0, CFs: 0, NumberOfUsers: 0, NumberOfCells: 0");
    BtsLogTime expectedBtsTime(BtsLogTimeType::BtsTimeStamp, "2015-11-26T05:39:14.187399Z");
    BtsLogTime expectedPcTime(BtsLogTimeType::PcTimeStamp, "26.11 07:39:15.009000");
    string expectedHardwareType("FSP-120C");
    string expectedPrint("FSP-120C-0-TCOMexe <2015-11-26T05:39:14.187399Z> 74 INF/TCOM/G, Received BB_SAMPLE_REPORT_IND_MSG Provider: MasterHsupa, SampleStartSfn: 0, SampledDataVolume: 0, CFs: 0, NumberOfUsers: 0, NumberOfCells: 0");

    EXPECT_EQ(expectedBtsTime, logPrint.getBtsTime());
    EXPECT_EQ(expectedPcTime, logPrint.getPcTime());
    EXPECT_EQ(expectedHardwareType, logPrint.getHardwareAddress());
    EXPECT_EQ(expectedPrint, logPrint.getPrint());
}

TEST(BtsLogPrintTest, PrintFromSnapshotIsUsed)
{
    BtsLogPrint logPrint("a7 FSP-140D-0-TCOMexe <22.10 11:38:33.309447> 83 INF/TCOM/Logger, RLH_TUP_HsdpaDeleteReq: nbccId: 1740, activationMethod: 2, cfn: 56, rcv: 0x14820363");
    BtsLogTime expectedBtsTime(BtsLogTimeType::BtsTimeStamp, "22.10 11:38:33.309447");
    string expectedHardwareType("FSP-140D");
    string expectedPrint("FSP-140D-0-TCOMexe <22.10 11:38:33.309447> 83 INF/TCOM/Logger, RLH_TUP_HsdpaDeleteReq: nbccId: 1740, activationMethod: 2, cfn: 56, rcv: 0x14820363");

    EXPECT_EQ(expectedBtsTime, logPrint.getBtsTime());
    EXPECT_TRUE(logPrint.getPcTime().isEmpty());
    EXPECT_EQ(expectedHardwareType, logPrint.getHardwareAddress());
    EXPECT_EQ(expectedPrint, logPrint.getPrint());
}

TEST(BtsLogPrintTest, PrintFromSctLogsIsUsed)
{
    BtsLogPrint logPrint("00 0x1011-0-ld-linux <2015-05-26T06:00:14.137037Z> 5A03 INF/TCOM/LRM/CCH, Cell waited for this modeChangeResp; cpuId: 0x14500000; cellId: 1");
    BtsLogTime expectedBtsTime(BtsLogTimeType::BtsTimeStamp, "2015-05-26T06:00:14.137037Z");
    string expectedPrint("00 0x1011-0-ld-linux <2015-05-26T06:00:14.137037Z> 5A03 INF/TCOM/LRM/CCH, Cell waited for this modeChangeResp; cpuId: 0x14500000; cellId: 1");

    EXPECT_EQ(expectedBtsTime, logPrint.getBtsTime());
    EXPECT_TRUE(logPrint.getPcTime().isEmpty());
    EXPECT_TRUE(logPrint.getHardwareAddress().empty());
    EXPECT_EQ(expectedPrint, logPrint.getPrint());
}

TEST(BtsLogPrintTest, HardwareTypeIsEmptyWhenInvalidHardwareTypesAreDetected_NotThreeLetters)
{
    BtsLogPrint logPrint("000312 23.09 12:06:04.213  [192.168.255.1]  b5 FSPJ-120D-1-TCOMexe <2015-09-23T09:06:04.156235Z> BE6 DBG/TCOM/CH, TC_TOAM_POWERLEVEL_REPORT_NOTIFICATION_MSG from 0x120D0156, size: 20 cellId: 1996, averagePowerRxLevel: 65");
    BtsLogTime expectedBtsTime(BtsLogTimeType::BtsTimeStamp, "2015-09-23T09:06:04.156235Z");
    BtsLogTime expectedPcTime(BtsLogTimeType::PcTimeStamp, "23.09 12:06:04.213");
    string expectedPrint("000312 23.09 12:06:04.213  [192.168.255.1]  b5 FSPJ-120D-1-TCOMexe <2015-09-23T09:06:04.156235Z> BE6 DBG/TCOM/CH, TC_TOAM_POWERLEVEL_REPORT_NOTIFICATION_MSG from 0x120D0156, size: 20 cellId: 1996, averagePowerRxLevel: 65");

    EXPECT_EQ(expectedBtsTime, logPrint.getBtsTime());
    EXPECT_EQ(expectedPcTime, logPrint.getPcTime());
    EXPECT_TRUE(logPrint.getHardwareAddress().empty());
    EXPECT_EQ(expectedPrint, logPrint.getPrint());
}

TEST(BtsLogPrintTest, HardwareTypeIsEmptyWhenInvalidHardwareTypesAreDetected_NotFourHexDigit)
{
    BtsLogPrint logPrint("000312 23.09 12:06:04.213  [192.168.255.1]  b5 FSP-120DE-1-TCOMexe <2015-09-23T09:06:04.156235Z> BE6 DBG/TCOM/CH, TC_TOAM_POWERLEVEL_REPORT_NOTIFICATION_MSG from 0x120D0156, size: 20 cellId: 1996, averagePowerRxLevel: 65");
    BtsLogTime expectedBtsTime(BtsLogTimeType::BtsTimeStamp, "2015-09-23T09:06:04.156235Z");
    BtsLogTime expectedPcTime(BtsLogTimeType::PcTimeStamp, "23.09 12:06:04.213");
    string expectedPrint("000312 23.09 12:06:04.213  [192.168.255.1]  b5 FSP-120DE-1-TCOMexe <2015-09-23T09:06:04.156235Z> BE6 DBG/TCOM/CH, TC_TOAM_POWERLEVEL_REPORT_NOTIFICATION_MSG from 0x120D0156, size: 20 cellId: 1996, averagePowerRxLevel: 65");

    EXPECT_EQ(expectedBtsTime, logPrint.getBtsTime());
    EXPECT_EQ(expectedPcTime, logPrint.getPcTime());
    EXPECT_TRUE(logPrint.getHardwareAddress().empty());
    EXPECT_EQ(expectedPrint, logPrint.getPrint());
}

TEST(BtsLogPrintTest, RfHardwareTypesAreRecognized)
{
    BtsLogPrint logPrint("027966 17.12 14:10:43.903  [192.168.254.129]  d0 FRM_REL2 <2004-01-01T00:33:46.806457Z> 20088 INF/LTX/RX_VD, RX1: RX_SET_INPUT_ATTENUATOR_REQ attenuator 0 (StatusOk)");
    BtsLogTime expectedBtsTime(BtsLogTimeType::BtsTimeStamp, "2004-01-01T00:33:46.806457Z");
    BtsLogTime expectedPcTime(BtsLogTimeType::PcTimeStamp, "17.12 14:10:43.903");
    string expectedHardwareType("FRM_REL2");
    string expectedPrint("FRM_REL2 <2004-01-01T00:33:46.806457Z> 20088 INF/LTX/RX_VD, RX1: RX_SET_INPUT_ATTENUATOR_REQ attenuator 0 (StatusOk)");

    EXPECT_EQ(expectedBtsTime, logPrint.getBtsTime());
    EXPECT_EQ(expectedPcTime, logPrint.getPcTime());
    EXPECT_EQ(expectedHardwareType, logPrint.getHardwareAddress());
    EXPECT_EQ(expectedPrint, logPrint.getPrint());
}

TEST(BtsLogPrintTest, OperatorLessThanWorksWhenHigherBtsTimeIsCompared)
{
    BtsLogPrint printWithNoPcTimeDuringLowerBtsStartupTime("FCT-1011-3-BTSOMex <1990-01-01T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithNoPcTimeDuringLowerBtsRuntimeTime("FCT-1011-3-BTSOMex <2015-05-26T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringLowerBtsStartupTime("000009 23.09 12:01:01.222  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringLowerBtsRuntimeTime("000009 23.09 12:01:01.222  [192.168.255.1]  19 FCT-1011-3-BTSOMex <2015-05-26T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");

    BtsLogPrint printWithNoPcTimeDuringHigherBtsStartupTime("FCT-1011-3-BTSOMex <1990-01-01T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithNoPcTimeDuringHigherBtsRuntimeTime("FCT-1011-3-BTSOMex <2015-05-26T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringHigherBtsStartupTime("000009 23.09 12:01:01.111  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringHigherBtsRuntimeTime("000009 23.09 12:01:01.111  [192.168.255.1]  19 FCT-1011-3-BTSOMex <2015-05-26T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");

    EXPECT_TRUE(printWithNoPcTimeDuringLowerBtsStartupTime < printWithNoPcTimeDuringHigherBtsStartupTime);
    EXPECT_TRUE(printWithNoPcTimeDuringLowerBtsStartupTime < printWithNoPcTimeDuringHigherBtsRuntimeTime);
    EXPECT_TRUE(printWithNoPcTimeDuringLowerBtsStartupTime < printWithPcTimeDuringHigherBtsStartupTime);
    EXPECT_TRUE(printWithNoPcTimeDuringLowerBtsStartupTime < printWithPcTimeDuringHigherBtsRuntimeTime);

    EXPECT_FALSE(printWithNoPcTimeDuringLowerBtsRuntimeTime < printWithNoPcTimeDuringHigherBtsStartupTime);
    EXPECT_TRUE(printWithNoPcTimeDuringLowerBtsRuntimeTime < printWithNoPcTimeDuringHigherBtsRuntimeTime);
    EXPECT_FALSE(printWithNoPcTimeDuringLowerBtsRuntimeTime < printWithPcTimeDuringHigherBtsStartupTime);
    EXPECT_TRUE(printWithNoPcTimeDuringLowerBtsRuntimeTime < printWithPcTimeDuringHigherBtsRuntimeTime);

    EXPECT_TRUE(printWithPcTimeDuringLowerBtsStartupTime < printWithNoPcTimeDuringHigherBtsStartupTime);
    EXPECT_TRUE(printWithPcTimeDuringLowerBtsStartupTime < printWithNoPcTimeDuringHigherBtsRuntimeTime);
    EXPECT_FALSE(printWithPcTimeDuringLowerBtsStartupTime < printWithPcTimeDuringHigherBtsStartupTime);
    EXPECT_FALSE(printWithPcTimeDuringLowerBtsStartupTime < printWithPcTimeDuringHigherBtsRuntimeTime);

    EXPECT_FALSE(printWithPcTimeDuringLowerBtsRuntimeTime < printWithNoPcTimeDuringHigherBtsStartupTime);
    EXPECT_TRUE(printWithPcTimeDuringLowerBtsRuntimeTime < printWithNoPcTimeDuringHigherBtsRuntimeTime);
    EXPECT_FALSE(printWithPcTimeDuringLowerBtsRuntimeTime < printWithPcTimeDuringHigherBtsStartupTime);
    EXPECT_TRUE(printWithPcTimeDuringLowerBtsRuntimeTime < printWithPcTimeDuringHigherBtsRuntimeTime);
}

TEST(BtsLogPrintTest, OperatorLessThanWorksWhenLowerBtsTimeIsCompared)
{
    BtsLogPrint printWithNoPcTimeDuringLowerBtsStartupTime("FCT-1011-3-BTSOMex <1990-01-01T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithNoPcTimeDuringLowerBtsRuntimeTime("FCT-1011-3-BTSOMex <2015-05-26T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringLowerBtsStartupTime("000009 23.09 12:01:01.222  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringLowerBtsRuntimeTime("000009 23.09 12:01:01.222  [192.168.255.1]  19 FCT-1011-3-BTSOMex <2015-05-26T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");

    BtsLogPrint printWithNoPcTimeDuringHigherBtsStartupTime("FCT-1011-3-BTSOMex <1990-01-01T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithNoPcTimeDuringHigherBtsRuntimeTime("FCT-1011-3-BTSOMex <2015-05-26T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringHigherBtsStartupTime("000009 23.09 12:01:01.111  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringHigherBtsRuntimeTime("000009 23.09 12:01:01.111  [192.168.255.1]  19 FCT-1011-3-BTSOMex <2015-05-26T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");

    EXPECT_FALSE(printWithNoPcTimeDuringHigherBtsStartupTime < printWithNoPcTimeDuringLowerBtsStartupTime);
    EXPECT_TRUE(printWithNoPcTimeDuringHigherBtsStartupTime < printWithNoPcTimeDuringLowerBtsRuntimeTime);
    EXPECT_FALSE(printWithNoPcTimeDuringHigherBtsStartupTime < printWithPcTimeDuringLowerBtsStartupTime);
    EXPECT_TRUE(printWithNoPcTimeDuringHigherBtsStartupTime < printWithPcTimeDuringLowerBtsRuntimeTime);

    EXPECT_FALSE(printWithNoPcTimeDuringHigherBtsRuntimeTime < printWithNoPcTimeDuringLowerBtsStartupTime);
    EXPECT_FALSE(printWithNoPcTimeDuringHigherBtsRuntimeTime < printWithNoPcTimeDuringLowerBtsRuntimeTime);
    EXPECT_FALSE(printWithNoPcTimeDuringHigherBtsRuntimeTime < printWithPcTimeDuringLowerBtsStartupTime);
    EXPECT_FALSE(printWithNoPcTimeDuringHigherBtsRuntimeTime < printWithPcTimeDuringLowerBtsRuntimeTime);

    EXPECT_FALSE(printWithPcTimeDuringHigherBtsStartupTime < printWithNoPcTimeDuringLowerBtsStartupTime);
    EXPECT_TRUE(printWithPcTimeDuringHigherBtsStartupTime < printWithNoPcTimeDuringLowerBtsRuntimeTime);
    EXPECT_TRUE(printWithPcTimeDuringHigherBtsStartupTime < printWithPcTimeDuringLowerBtsStartupTime);
    EXPECT_TRUE(printWithPcTimeDuringHigherBtsStartupTime < printWithPcTimeDuringLowerBtsRuntimeTime);

    EXPECT_FALSE(printWithPcTimeDuringHigherBtsRuntimeTime < printWithNoPcTimeDuringLowerBtsStartupTime);
    EXPECT_FALSE(printWithPcTimeDuringHigherBtsRuntimeTime < printWithNoPcTimeDuringLowerBtsRuntimeTime);
    EXPECT_TRUE(printWithPcTimeDuringHigherBtsRuntimeTime < printWithPcTimeDuringLowerBtsStartupTime);
    EXPECT_FALSE(printWithPcTimeDuringHigherBtsRuntimeTime < printWithPcTimeDuringLowerBtsRuntimeTime);
}

TEST(BtsLogPrintTest, OperatorGreaterThanWorksWhenLowerBtsTimeIsCompared)
{
    BtsLogPrint printWithNoPcTimeDuringLowerBtsStartupTime("FCT-1011-3-BTSOMex <1990-01-01T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithNoPcTimeDuringLowerBtsRuntimeTime("FCT-1011-3-BTSOMex <2015-05-26T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringLowerBtsStartupTime("000009 23.09 12:01:01.222  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringLowerBtsRuntimeTime("000009 23.09 12:01:01.222  [192.168.255.1]  19 FCT-1011-3-BTSOMex <2015-05-26T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");

    BtsLogPrint printWithNoPcTimeDuringHigherBtsStartupTime("FCT-1011-3-BTSOMex <1990-01-01T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithNoPcTimeDuringHigherBtsRuntimeTime("FCT-1011-3-BTSOMex <2015-05-26T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringHigherBtsStartupTime("000009 23.09 12:01:01.111  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringHigherBtsRuntimeTime("000009 23.09 12:01:01.111  [192.168.255.1]  19 FCT-1011-3-BTSOMex <2015-05-26T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");

    EXPECT_TRUE(printWithNoPcTimeDuringHigherBtsStartupTime > printWithNoPcTimeDuringLowerBtsStartupTime);
    EXPECT_FALSE(printWithNoPcTimeDuringHigherBtsStartupTime > printWithNoPcTimeDuringLowerBtsRuntimeTime);
    EXPECT_TRUE(printWithNoPcTimeDuringHigherBtsStartupTime > printWithPcTimeDuringLowerBtsStartupTime);
    EXPECT_FALSE(printWithNoPcTimeDuringHigherBtsStartupTime > printWithPcTimeDuringLowerBtsRuntimeTime);

    EXPECT_TRUE(printWithNoPcTimeDuringHigherBtsRuntimeTime > printWithNoPcTimeDuringLowerBtsStartupTime);
    EXPECT_TRUE(printWithNoPcTimeDuringHigherBtsRuntimeTime > printWithNoPcTimeDuringLowerBtsRuntimeTime);
    EXPECT_TRUE(printWithNoPcTimeDuringHigherBtsRuntimeTime > printWithPcTimeDuringLowerBtsStartupTime);
    EXPECT_TRUE(printWithNoPcTimeDuringHigherBtsRuntimeTime > printWithPcTimeDuringLowerBtsRuntimeTime);

    EXPECT_TRUE(printWithPcTimeDuringHigherBtsStartupTime > printWithNoPcTimeDuringLowerBtsStartupTime);
    EXPECT_FALSE(printWithPcTimeDuringHigherBtsStartupTime > printWithNoPcTimeDuringLowerBtsRuntimeTime);
    EXPECT_FALSE(printWithPcTimeDuringHigherBtsStartupTime > printWithPcTimeDuringLowerBtsStartupTime);
    EXPECT_FALSE(printWithPcTimeDuringHigherBtsStartupTime > printWithPcTimeDuringLowerBtsRuntimeTime);

    EXPECT_TRUE(printWithPcTimeDuringHigherBtsRuntimeTime > printWithNoPcTimeDuringLowerBtsStartupTime);
    EXPECT_TRUE(printWithPcTimeDuringHigherBtsRuntimeTime > printWithNoPcTimeDuringLowerBtsRuntimeTime);
    EXPECT_FALSE(printWithPcTimeDuringHigherBtsRuntimeTime > printWithPcTimeDuringLowerBtsStartupTime);
    EXPECT_TRUE(printWithPcTimeDuringHigherBtsRuntimeTime > printWithPcTimeDuringLowerBtsRuntimeTime);
}

TEST(BtsLogPrintTest, OperatorGreaterThanWorksWhenHigherBtsTimeIsCompared)
{
    BtsLogPrint printWithNoPcTimeDuringLowerBtsStartupTime("FCT-1011-3-BTSOMex <1990-01-01T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithNoPcTimeDuringLowerBtsRuntimeTime("FCT-1011-3-BTSOMex <2015-05-26T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringLowerBtsStartupTime("000009 23.09 12:01:01.222  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringLowerBtsRuntimeTime("000009 23.09 12:01:01.222  [192.168.255.1]  19 FCT-1011-3-BTSOMex <2015-05-26T01:01:01.111111Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");

    BtsLogPrint printWithNoPcTimeDuringHigherBtsStartupTime("FCT-1011-3-BTSOMex <1990-01-01T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithNoPcTimeDuringHigherBtsRuntimeTime("FCT-1011-3-BTSOMex <2015-05-26T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringHigherBtsStartupTime("000009 23.09 12:01:01.111  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint printWithPcTimeDuringHigherBtsRuntimeTime("000009 23.09 12:01:01.111  [192.168.255.1]  19 FCT-1011-3-BTSOMex <2015-05-26T01:01:01.222222Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");

    EXPECT_FALSE(printWithNoPcTimeDuringLowerBtsStartupTime > printWithNoPcTimeDuringHigherBtsStartupTime);
    EXPECT_FALSE(printWithNoPcTimeDuringLowerBtsStartupTime > printWithNoPcTimeDuringHigherBtsRuntimeTime);
    EXPECT_FALSE(printWithNoPcTimeDuringLowerBtsStartupTime > printWithPcTimeDuringHigherBtsStartupTime);
    EXPECT_FALSE(printWithNoPcTimeDuringLowerBtsStartupTime > printWithPcTimeDuringHigherBtsRuntimeTime);

    EXPECT_TRUE(printWithNoPcTimeDuringLowerBtsRuntimeTime > printWithNoPcTimeDuringHigherBtsStartupTime);
    EXPECT_FALSE(printWithNoPcTimeDuringLowerBtsRuntimeTime > printWithNoPcTimeDuringHigherBtsRuntimeTime);
    EXPECT_TRUE(printWithNoPcTimeDuringLowerBtsRuntimeTime > printWithPcTimeDuringHigherBtsStartupTime);
    EXPECT_FALSE(printWithNoPcTimeDuringLowerBtsRuntimeTime > printWithPcTimeDuringHigherBtsRuntimeTime);

    EXPECT_FALSE(printWithPcTimeDuringLowerBtsStartupTime > printWithNoPcTimeDuringHigherBtsStartupTime);
    EXPECT_FALSE(printWithPcTimeDuringLowerBtsStartupTime > printWithNoPcTimeDuringHigherBtsRuntimeTime);
    EXPECT_TRUE(printWithPcTimeDuringLowerBtsStartupTime > printWithPcTimeDuringHigherBtsStartupTime);
    EXPECT_TRUE(printWithPcTimeDuringLowerBtsStartupTime > printWithPcTimeDuringHigherBtsRuntimeTime);

    EXPECT_TRUE(printWithPcTimeDuringLowerBtsRuntimeTime > printWithNoPcTimeDuringHigherBtsStartupTime);
    EXPECT_FALSE(printWithPcTimeDuringLowerBtsRuntimeTime > printWithNoPcTimeDuringHigherBtsRuntimeTime);
    EXPECT_TRUE(printWithPcTimeDuringLowerBtsRuntimeTime > printWithPcTimeDuringHigherBtsStartupTime);
    EXPECT_FALSE(printWithPcTimeDuringLowerBtsRuntimeTime > printWithPcTimeDuringHigherBtsRuntimeTime);
}

TEST(BtsLogPrintTest, OperatorEqualityWorksAsExpectedBasedOnBtsTime)
{
    BtsLogPrint logPrint1("000009 23.09 12:08:04.251  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T00:00:16.700634Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint logPrint2("000009 23.09 12:08:04.251  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T00:00:16.700634Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint logPrint3("FCT-1011-3-BTSOMex <1990-01-01T00:00:16.700634Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint differentTimePrint4("FCT-1011-3-BTSOMex <2004-01-01T00:00:17.856856> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");

    EXPECT_TRUE(logPrint1==logPrint2);
    EXPECT_TRUE(logPrint1==logPrint3);
    EXPECT_FALSE(differentTimePrint4==logPrint1);
    EXPECT_FALSE(differentTimePrint4==logPrint2);
    EXPECT_FALSE(differentTimePrint4==logPrint3);
}

TEST(BtsLogPrintTest, OperatorEqualityWorksAsExpectedBasedPrint)
{
    BtsLogPrint logPrint1("000009 23.09 12:08:04.251  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T00:00:16.700634Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a print");
    BtsLogPrint differentPrint2("000009 23.09 12:08:04.251  [192.168.255.1]  19 FCT-1011-3-BTSOMex <1990-01-01T00:00:16.700634Z> 2F9 INF/SUBSYSTEM/SUBCOMPONENT, This is a different print");

    EXPECT_FALSE(differentPrint2==logPrint1);
}

TEST(BtsLogPrintTest, SyslogAndSnapshotPrintStartupComparisonTest)
{
    BtsLogPrint logPrint1("022712 09.11 15:32:45.246  [192.168.255.129]  90 FCT-1011-0-HWRSwDl <2004-01-01T00:01:33.827322Z> 3C0 WRN/HWA/SWDL, 1");
    BtsLogPrint logPrint2("9b FCT-1011-0-HWRSwDl <2004-01-01T00:01:34.533125Z> 3C0 WRN/HWA/SWDL, 2");

    EXPECT_TRUE(logPrint1<logPrint2);
    EXPECT_FALSE(logPrint1>logPrint2);
}

TEST(BtsLogPrintTest, SyslogAndSnapshotPrintRuntimeComparisonTest)
{
    BtsLogPrint logPrint1("022712 09.11 15:32:45.246  [192.168.255.129]  90 FCT-1011-0-HWRSwDl <2015-01-01T00:01:33.827322Z> 3C0 WRN/HWA/SWDL, 1");
    BtsLogPrint logPrint2("9b FCT-1011-0-HWRSwDl <2015-01-01T00:01:34.533125Z> 3C0 WRN/HWA/SWDL, 2");

    EXPECT_TRUE(logPrint1<logPrint2);
    EXPECT_FALSE(logPrint1>logPrint2);
}

TEST(BtsLogPrintTest, SortingTestWithAndWithoutPcTime)
{
    vector<BtsLogPrint> logPrints;
    logPrints.emplace_back("022712 09.11 15:32:45.246  [192.168.255.129]  90 FCT-1011-0-HWRSwDl <2015-01-01T00:01:33.827322Z> 3C0 WRN/HWA/SWDL, 1");
    logPrints.emplace_back("022723 09.11 15:32:45.948  [192.168.255.129]  9b FCT-1011-0-HWRSwDl <2015-01-01T00:01:34.533125Z> 3C0 WRN/HWA/SWDL, 2");
    logPrints.emplace_back("90 FCT-1011-0-HWRSwDl <2015-01-01T00:01:33.827322Z> 3C0 WRN/HWA/SWDL, 1");
    logPrints.emplace_back("9b FCT-1011-0-HWRSwDl <2015-01-01T00:01:34.533125Z> 3C0 WRN/HWA/SWDL, 2");

    sort(logPrints.begin(), logPrints.end());

    EXPECT_EQ(4u, logPrints.size());
    EXPECT_EQ("FCT-1011-0-HWRSwDl <2015-01-01T00:01:33.827322Z> 3C0 WRN/HWA/SWDL, 1", logPrints[0].getPrint());
    EXPECT_EQ("FCT-1011-0-HWRSwDl <2015-01-01T00:01:33.827322Z> 3C0 WRN/HWA/SWDL, 1", logPrints[1].getPrint());
    EXPECT_EQ("FCT-1011-0-HWRSwDl <2015-01-01T00:01:34.533125Z> 3C0 WRN/HWA/SWDL, 2", logPrints[2].getPrint());
    EXPECT_EQ("FCT-1011-0-HWRSwDl <2015-01-01T00:01:34.533125Z> 3C0 WRN/HWA/SWDL, 2", logPrints[3].getPrint());
}

TEST(BtsLogPrintTest, SortingTestWithAndWithoutPcTime2)
{
    vector<BtsLogPrint> logPrints;
    logPrints.emplace_back("022712 09.11 15:32:45.246  [192.168.255.129]  90 FCT-1011-0-HWRSwDl <2015-01-01T00:01:33.827322Z> 3C0 WRN/HWA/SWDL, validateSrioWrite, [0x1331] ddal_rio_copy_from() failed");
    logPrints.emplace_back("022723 09.11 15:32:45.948  [192.168.255.129]  9b FCT-1011-0-HWRSwDl <2015-01-01T00:01:35.533125Z> 3C0 WRN/HWA/SWDL, validateSrioWrite, [0x1331] ddal_rio_copy_from() failed");
    logPrints.emplace_back("90 FCT-1011-0-HWRSwDl <2015-01-01T00:01:34.827322Z> 3C0 WRN/HWA/SWDL, validateSrioWrite, [0x1331] ddal_rio_copy_from() failed");
    logPrints.emplace_back("9b FCT-1011-0-HWRSwDl <2015-01-01T00:01:36.533125Z> 3C0 WRN/HWA/SWDL, validateSrioWrite, [0x1331] ddal_rio_copy_from() failed");

    sort(logPrints.begin(), logPrints.end());

    EXPECT_EQ(4u, logPrints.size());
    EXPECT_EQ("FCT-1011-0-HWRSwDl <2015-01-01T00:01:33.827322Z> 3C0 WRN/HWA/SWDL, validateSrioWrite, [0x1331] ddal_rio_copy_from() failed", logPrints[0].getPrint());
    EXPECT_EQ("FCT-1011-0-HWRSwDl <2015-01-01T00:01:34.827322Z> 3C0 WRN/HWA/SWDL, validateSrioWrite, [0x1331] ddal_rio_copy_from() failed", logPrints[1].getPrint());
    EXPECT_EQ("FCT-1011-0-HWRSwDl <2015-01-01T00:01:35.533125Z> 3C0 WRN/HWA/SWDL, validateSrioWrite, [0x1331] ddal_rio_copy_from() failed", logPrints[2].getPrint());
    EXPECT_EQ("FCT-1011-0-HWRSwDl <2015-01-01T00:01:36.533125Z> 3C0 WRN/HWA/SWDL, validateSrioWrite, [0x1331] ddal_rio_copy_from() failed", logPrints[3].getPrint());
}

TEST(BtsLogPrintTest, DISABLED_InputStreamWorks)
{
    ifstream inputFileStream(APRG_DIR R"(TcomTools\TcomToolsBackend\tst\ProblemFiles\BLOCK_701.txt)");
    int count(0);
    while(inputFileStream.good())
    {
        BtsLogPrint logPrint;
        inputFileStream>>logPrint;
        count++;
    }
    EXPECT_EQ(1001, count);
}
