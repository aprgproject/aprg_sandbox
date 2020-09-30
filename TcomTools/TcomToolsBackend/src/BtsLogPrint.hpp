#pragma once

#include "BtsLogTime.hpp"
#include <iostream>
#include <string>

using std::istream;
using std::ostream;
using std::string;

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
    hardwareAddressState3_HexNumbers,
    BtsTimeState
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
    BtsLogPrint(string const& lineInLogs);
    BtsLogPrint(string const& filename, string const& lineInLogs);
    BtsLogTime getBtsTime() const;
    BtsLogTime getPcTime() const;
    string getHardwareAddress() const;
    string getPrint() const;
    string getPrintWithAllDetails() const;
    void updatePcTimeAndFileNameDetails(BtsLogPrint const& logPrint);
    bool operator<(BtsLogPrint const& btsLogPrintToCompare) const;
    bool operator>(BtsLogPrint const& btsLogPrintToCompare) const;
    bool operator==(BtsLogPrint const& btsLogPrintToCompare) const;
    friend ostream& operator<<(ostream & out, BtsLogPrint const& btsLogPrint);
    friend istream& operator>>(istream & in, BtsLogPrint& btsLogPrint);

private:
    void analyzeLineInLogs(string const& lineInLogs);
    inline void handleUnknownState(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData, int const index, char const character);
    inline void handlePcTimeState1(BtsLogPrintStateMachine::State & state, char const character);
    inline void handlePcTimeState2(BtsLogPrintStateMachine::State & state, char const character);
    inline void handlePcTimeState3(BtsLogPrintStateMachine::State & state, char const character);
    inline void handlePcTimeState4(BtsLogPrintStateMachine::State & state, char const character);
    inline void handlePcTimeState5(BtsLogPrintStateMachine::State & state, char const character);
    inline void handlePcTimeState6(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData, int const index, char const character);
    inline void handleHardWareAddressState1(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData,  char const character);
    inline void handleHardWareAddressState2(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData,  char const character);
    inline void handleHardWareAddressState3(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData, int const index, char const character);
    inline void handleBtsTimeState(BtsLogPrintStateMachine::State & state, BtsLogPrintStateMachine::TransactionData & transactionData, int const index, char const character);

    BtsLogTime m_btsTime;
    BtsLogTime m_pcTime;
    string m_hardwareAddress;
    string m_print;
    string m_fileName;
};

}
