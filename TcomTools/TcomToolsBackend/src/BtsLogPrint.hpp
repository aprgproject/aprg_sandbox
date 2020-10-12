#pragma once

#include "BtsLogTime.hpp"
#include <iostream>
#include <string>

namespace tcomToolsBackend
{
namespace BtsLogPrintStateMachine
{
enum class State
{
    UnknownState,
    PcTimeState1_Number,
    PcTimeState2_Period,
    PcTimeState3_Space,
    PcTimeState4_Colon,
    PcTimeState5_Colon,
    PcTimeState6_Period,
    hardwareAddressState1_Letters,
    hardwareAddressState2_Dash,
    hardwareAddressState2_Underscore,
    hardwareAddressState3_HexNumbers,
    hardwareAddressState3_Letters,
    BtsTimeState,
    StopCheckingState
};

struct TransactionData
{
    TransactionData()
        : isPcTimeSaved(false)
        , isHardwareAddressSaved(false)
        , isBtsTimeSaved(false)
        , pcTimeStartIndex(0)
        , pcTimeEndIndex(0)
        , hardwareAddressStartIndex(0)
        , hardwareAddressEndIndex(0)
        , btsTimeStartIndex(0)
        , btsTimeEndIndex(0)
        , count(0)
    {}
    bool isPcTimeSaved;
    bool isHardwareAddressSaved;
    bool isBtsTimeSaved;
    int pcTimeStartIndex;
    int pcTimeEndIndex;
    int hardwareAddressStartIndex;
    int hardwareAddressEndIndex;
    int btsTimeStartIndex;
    int btsTimeEndIndex;
    int count;
};

}

class BtsLogPrint
{
public:
    BtsLogPrint();
    BtsLogPrint(std::string const& lineInLogs);
    BtsLogPrint(std::string const& filename, std::string const& lineInLogs);
    BtsLogTime getBtsTime() const;
    BtsLogTime getPcTime() const;
    std::string getHardwareAddress() const;
    std::string getPrint() const;
    std::string getPrintWithAllDetails() const;
    void updatePcTimeAndFileNameDetails(BtsLogPrint const& logPrint);
    bool operator<(BtsLogPrint const& btsLogPrintToCompare) const;
    bool operator>(BtsLogPrint const& btsLogPrintToCompare) const;
    bool operator==(BtsLogPrint const& btsLogPrintToCompare) const;
    friend std::ostream & operator<<(std::ostream & out, BtsLogPrint const& btsLogPrint);
    friend std::istream & operator>>(std::istream & in, BtsLogPrint& btsLogPrint);

private:
    void analyzeLineInLogs(std::string const& lineInLogs);
    inline void handleUnknownState(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData, int const index, char const character);
    inline void handlePcTimeState1(BtsLogPrintStateMachine::State & state, char const character);
    inline void handlePcTimeState2(BtsLogPrintStateMachine::State & state, char const character);    inline void handlePcTimeState3(BtsLogPrintStateMachine::State & state, char const character);
    inline void handlePcTimeState4(BtsLogPrintStateMachine::State & state, char const character);
    inline void handlePcTimeState5(BtsLogPrintStateMachine::State & state, char const character);
    inline void handlePcTimeState6(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData, int const index, char const character);    inline void handleHardWareAddressState1_Letters(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData,  char const character);
    inline void handleHardWareAddressState2_Dash(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData,  char const character);
    inline void handleHardWareAddressState2_Underscore(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData,  char const character);
    inline void handleHardWareAddressState3_HexNumbers(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData, int const index, char const character);
    inline void handleHardWareAddressState3_Letters(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData, int const index, char const character);
    inline void handleBtsTimeState(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData, int const index, char const character);

    BtsLogTime m_btsTime;
    BtsLogTime m_pcTime;
    std::string m_hardwareAddress;
    std::string m_print;
    std::string m_fileName;
};

}