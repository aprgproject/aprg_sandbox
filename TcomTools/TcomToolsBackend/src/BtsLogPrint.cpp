#include "BtsLogPrint.hpp"

#include <String/AlbaStringHelper.hpp>

#include <iostream>

using namespace alba;
using namespace std;

namespace tcomToolsBackend
{

using namespace BtsLogPrintStateMachine;

int const NUMBER_OF_CHARACTER_FOR_FILE = 25;
int const NUMBER_OF_LETTERS_IN_HARDWARE_TYPE = 3;
int const NUMBER_OF_NUMBERS_IN_HARDWARE_TYPE = 4;

BtsLogPrint::BtsLogPrint()
{}

BtsLogPrint::BtsLogPrint(string const& lineInLogs)
{
    analyzeLineInLogs(lineInLogs);
}

BtsLogPrint::BtsLogPrint(string const& filename, string const& lineInLogs)
    : m_fileName(filename)
{
    m_fileName.resize(NUMBER_OF_CHARACTER_FOR_FILE, ' ');
    analyzeLineInLogs(lineInLogs);
}

bool BtsLogPrint::isEmpty() const
{
    return m_btsTime.isEmpty() && m_pcTime.isEmpty();
}

BtsLogTime BtsLogPrint::getBtsTime() const
{
    return m_btsTime;}

BtsLogTime BtsLogPrint::getPcTime() const
{
    return m_pcTime;
}

string BtsLogPrint::getHardwareAddress() const
{
    return m_hardwareAddress;
}

string BtsLogPrint::getPrint() const
{
    return m_print;
}

string BtsLogPrint::getPrintWithAllDetails() const
{
    if(m_pcTime.isEmpty())
    {
        return m_fileName + "|" + m_print;
    }
    return m_fileName + "|" + m_pcTime.getEquivalentStringPcTimeFormat() + " " + m_print;
    //return m_fileName + "|" + m_print;
}

void BtsLogPrint::updatePcTimeAndFileNameDetails(BtsLogPrint const& logPrint)
{
    if(!logPrint.m_pcTime.isEmpty())
    {
        m_pcTime = logPrint.m_pcTime;
        m_fileName = logPrint.m_fileName;
    }
}

bool BtsLogPrint::operator<(BtsLogPrint const& btsLogPrintToCompare) const
{
    bool hasPcTime1 = !m_pcTime.isEmpty();
    bool hasPcTime2 = !btsLogPrintToCompare.m_pcTime.isEmpty();
    bool isStartup1 = m_btsTime.isStartup();
    bool isStartup2 = btsLogPrintToCompare.m_btsTime.isStartup();

    if(hasPcTime1 && hasPcTime2 && (isStartup1 || isStartup2))
    {
        if(m_pcTime == btsLogPrintToCompare.m_pcTime)
        {
            return m_btsTime < btsLogPrintToCompare.m_btsTime;
        }
        return m_pcTime < btsLogPrintToCompare.m_pcTime;
    }
    else
    {
        return m_btsTime < btsLogPrintToCompare.m_btsTime;
    }
    return false;
}

bool BtsLogPrint::operator>(BtsLogPrint const& btsLogPrintToCompare) const
{
    bool hasPcTime1 = !m_pcTime.isEmpty();
    bool hasPcTime2 = !btsLogPrintToCompare.m_pcTime.isEmpty();
    bool isStartup1 = m_btsTime.isStartup();
    bool isStartup2 = btsLogPrintToCompare.m_btsTime.isStartup();

    if(hasPcTime1 && hasPcTime2 && (isStartup1 || isStartup2))
    {
        if(m_pcTime == btsLogPrintToCompare.m_pcTime)
        {
            return m_btsTime > btsLogPrintToCompare.m_btsTime;
        }
        return m_pcTime > btsLogPrintToCompare.m_pcTime;
    }
    else
    {
        return m_btsTime > btsLogPrintToCompare.m_btsTime;
    }
    return false;
}

bool BtsLogPrint::operator==(BtsLogPrint const& btsLogPrintToCompare) const
{
    return m_btsTime == btsLogPrintToCompare.m_btsTime && m_print == btsLogPrintToCompare.m_print;
}

void BtsLogPrint::analyzeLineInLogs(string const& lineInLogs)
{
    State state(State::UnknownState);
    int const length = lineInLogs.length();

    TransactionData transactionData;
    for(int index=0; !transactionData.isBtsTimeSaved && index<length; index++)
    {
        char const character = lineInLogs[index];
        switch(state)
        {
        case State::UnknownState:
            handleUnknownState(state, transactionData, index, character);
            break;
        case State::PcTimeState1_Number:
            handlePcTimeState1(state, character);
            break;
        case State::PcTimeState2_Period:
            handlePcTimeState2(state, character);
            break;
        case State::PcTimeState3_Space:
            handlePcTimeState3(state, character);
            break;
        case State::PcTimeState4_Colon:
            handlePcTimeState4(state, character);
            break;
        case State::PcTimeState5_Colon:
            handlePcTimeState5(state, character);
            break;
        case State::PcTimeState6_Period:
            handlePcTimeState6(state, transactionData, index, character);
            break;
        case State::hardwareAddressState1_Letters:
            handleHardWareAddressState1_Letters(state, transactionData, character);
            break;
        case State::hardwareAddressState2_Dash:
            handleHardWareAddressState2_Dash(state, transactionData, character);
            break;
        case State::hardwareAddressState2_Underscore:
            handleHardWareAddressState2_Underscore(state, transactionData, character);
            break;
        case State::hardwareAddressState3_HexNumbers:
            handleHardWareAddressState3_HexNumbers(state, transactionData, index, character);
            break;
        case State::hardwareAddressState3_Letters:
            handleHardWareAddressState3_Letters(state, transactionData, index, character);
            break;
        case State::BtsTimeState:
            handleBtsTimeState(state, transactionData, index, character);
            break;
        case State::StopCheckingState:
            index = length;
            break;
        default:
            break;
        }
    }

    if(transactionData.isPcTimeSaved)
    {
        m_pcTime.setTimeByTimeStamp(BtsLogTimeType::PcTimeStamp, lineInLogs.substr(transactionData.pcTimeStartIndex, transactionData.pcTimeEndIndex-transactionData.pcTimeStartIndex));
    }
    if(transactionData.isBtsTimeSaved)
    {
        m_btsTime.setTimeByTimeStamp(BtsLogTimeType::BtsTimeStamp, lineInLogs.substr(transactionData.btsTimeStartIndex, transactionData.btsTimeEndIndex-transactionData.btsTimeStartIndex));
    }
    if(transactionData.isHardwareAddressSaved)
    {
        m_hardwareAddress = lineInLogs.substr(transactionData.hardwareAddressStartIndex, transactionData.hardwareAddressEndIndex-transactionData.hardwareAddressStartIndex);
        m_print = lineInLogs.substr(transactionData.hardwareAddressStartIndex, length-transactionData.hardwareAddressStartIndex);
    }
    else
    {
        m_print = lineInLogs;
    }
}

void BtsLogPrint::handleUnknownState(State & state, TransactionData & transactionData, int const index, char const character)
{
    if(!transactionData.isPcTimeSaved && stringHelper::isNumber(character))
    {
        state = State::PcTimeState1_Number;
        transactionData.pcTimeStartIndex = index;
    }
    else if(!transactionData.isHardwareAddressSaved && stringHelper::isLetter(character))
    {
        state = State::hardwareAddressState1_Letters;
        transactionData.hardwareAddressStartIndex = index;
        transactionData.count=1;
    }
    else if(!transactionData.isBtsTimeSaved && '<' == character)
    {
        state = State::BtsTimeState;
        transactionData.btsTimeStartIndex = index+1;
    }
}

void BtsLogPrint::handlePcTimeState1(State & state, char const character)
{
    state = ('.' == character)
            ? State::PcTimeState2_Period
            : stringHelper::isNumber(character)
              ? state
              : State::UnknownState;
}

void BtsLogPrint::handlePcTimeState2(State & state, char const character)
{
    state = (' ' == character)
            ? State::PcTimeState3_Space
            : stringHelper::isNumber(character)
              ? state
              : State::UnknownState;
}

void BtsLogPrint::handlePcTimeState3(State & state, char const character)
{
    state = (':' == character)
            ? State::PcTimeState4_Colon
            : stringHelper::isNumber(character)
              ? state
              : State::UnknownState;
}

void BtsLogPrint::handlePcTimeState4(State & state, char const character)
{
    state = (':' == character)
            ? State::PcTimeState5_Colon
            : stringHelper::isNumber(character)
              ? state
              : State::UnknownState;
}

void BtsLogPrint::handlePcTimeState5(State & state, char const character)
{
    state = ('.' == character)
            ? State::PcTimeState6_Period
            : stringHelper::isNumber(character)
              ? state
              : State::UnknownState;
}

void BtsLogPrint::handlePcTimeState6(State & state, TransactionData & transactionData, int const index, char const character)
{
    if(!stringHelper::isNumber(character))
    {
        state = State::UnknownState;
        transactionData.pcTimeEndIndex = index;
        transactionData.isPcTimeSaved = true;
    }
}

void BtsLogPrint::handleHardWareAddressState1_Letters(State & state, TransactionData & transactionData,  char const character)
{
    if('-' == character && transactionData.count == NUMBER_OF_LETTERS_IN_HARDWARE_TYPE)
    {
        state = State::hardwareAddressState2_Dash;
    }
    else if('_' == character && transactionData.count == NUMBER_OF_LETTERS_IN_HARDWARE_TYPE)
    {
        state = State::hardwareAddressState2_Underscore;
    }
    else if(stringHelper::isLetter(character) && transactionData.count < NUMBER_OF_LETTERS_IN_HARDWARE_TYPE)
    {
        transactionData.count++;
    }
    else
    {
        state = State::UnknownState;
    }
}

void BtsLogPrint::handleHardWareAddressState2_Dash(State & state, TransactionData & transactionData,  char const character)
{
    if(stringHelper::isHexDigit(character))
    {
        state = State::hardwareAddressState3_HexNumbers;
        transactionData.count=1;
    }
    else
    {
        state = State::UnknownState;
    }
}

void BtsLogPrint::handleHardWareAddressState2_Underscore(State & state, TransactionData & transactionData,  char const character)
{
    if(stringHelper::isLetter(character) || stringHelper::isNumber(character))
    {
        state = State::hardwareAddressState3_Letters;
        transactionData.count=1;
    }
    else
    {
        state = State::UnknownState;
    }
}

void BtsLogPrint::handleHardWareAddressState3_HexNumbers(State & state, TransactionData & transactionData, int const index, char const character)
{
    if(stringHelper::isHexDigit(character))
    {
        if(transactionData.count < NUMBER_OF_NUMBERS_IN_HARDWARE_TYPE)
        {
            transactionData.count++;
        }
        else
        {
            state = State::UnknownState;
        }
    }
    else
    {
        state = State::UnknownState;
        if(transactionData.count == NUMBER_OF_NUMBERS_IN_HARDWARE_TYPE)
        {
            transactionData.hardwareAddressEndIndex = index;
            transactionData.isHardwareAddressSaved = true;
        }
    }
}

void BtsLogPrint::handleHardWareAddressState3_Letters(State & state, TransactionData & transactionData, int const index, char const character)
{
    if(stringHelper::isLetter(character) || stringHelper::isNumber(character))
    {
        if(transactionData.count < NUMBER_OF_NUMBERS_IN_HARDWARE_TYPE)
        {
            transactionData.count++;
        }
        else
        {
            state = State::UnknownState;
        }
    }
    else
    {
        state = State::UnknownState;
        if(transactionData.count == NUMBER_OF_NUMBERS_IN_HARDWARE_TYPE)
        {
            transactionData.hardwareAddressEndIndex = index;
            transactionData.isHardwareAddressSaved = true;
        }
    }
}

void BtsLogPrint::handleBtsTimeState(State & state, TransactionData & transactionData, int const index, char const character)
{
    if('>' == character)
    {
        state = State::StopCheckingState;
        transactionData.btsTimeEndIndex = index;
        transactionData.isBtsTimeSaved = true;
    }
}


ostream& operator<<(ostream & out, BtsLogPrint const& btsLogPrint)
{
    bool isExisting(false);
    out << btsLogPrint.m_btsTime << endl;
    out << btsLogPrint.m_pcTime << endl;
    isExisting = !btsLogPrint.m_hardwareAddress.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << btsLogPrint.m_hardwareAddress << endl;
    }
    isExisting = !btsLogPrint.m_print.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << btsLogPrint.m_print << endl;
    }
    isExisting = !btsLogPrint.m_fileName.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << btsLogPrint.m_fileName;
    }
    return out;
}

istream& operator>>(istream & in, BtsLogPrint& btsLogPrint)
{
    bool isExisting(false);
    in >> btsLogPrint.m_btsTime;
    in >> btsLogPrint.m_pcTime;
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, btsLogPrint.m_hardwareAddress);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, btsLogPrint.m_print);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, btsLogPrint.m_fileName);
    }
    return in;
}

}
