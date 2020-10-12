#pragma once

#include <AlbaFileReader.hpp>
#include <map>
#include <ostream>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <unordered_map>
#include <vector>

namespace alba
{
class BtsDelayInformation;

typedef std::vector<BtsDelayInformation> BtsDelayInformationContainer;

class BtsLogTime
{
public:    BtsLogTime(string const& lineInLogs);
    int getYears() const;
    int getMonths() const;
    int getDays() const;
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    int getTotalSeconds() const;
    int getMicroSeconds() const;
    string getEquivalentString()const;
    bool operator<(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator>(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator==(BtsLogTime const& btsLogTimeToCompare) const;
    BtsLogTime operator+(BtsLogTime const& btsLogTime);
    BtsLogTime operator-(BtsLogTime const& btsLogTime);
    void reorganizeOverflowValues();
    void reorganizeUnderflowValues();

private:
    void saveTimeFromLineInLogs(string const& lineInLogs);
    int m_years;
    char m_months;
    int m_days;
    int m_seconds;
    int m_microseconds;
};

struct BtsDelayInformation
{
    BtsDelayInformation(
            unsigned int nbccId,
            unsigned int transactionId,
            string firstComponentString,
            string secondComponentString,
            string firstMessage,
            string secondMessage,
            BtsLogTime time1,
            BtsLogTime time2);
    void printWithAverage(std::ostream& outputStream) const;
    void printWithNbccId(std::ostream& outputStream) const;
    unsigned int m_nbccId;
    unsigned int m_transactionId;
    string m_firstComponentString;
    string m_secondComponentString;
    string m_firstMessage;
    string m_secondMessage;
    BtsLogTime m_delay;
    int m_delayCount;
};

enum class BtsLogPrintLevel
{
    ERR,
    WRN,
    INF,
    VIP
};

class BtsLogPrint
{
public:
    BtsLogPrint();
    BtsLogPrint(string const& lineInLogs);
    string getPrint() const;
    string getComponentString() const;
    bool isMessagePrint() const;
    string getMessageString() const;

private:
    string m_print;
    BtsLogPrintLevel m_printLevel;
    string m_componentString;
    bool m_isMessagePrint;
    string m_messageString;
};

class BtsLogUser
{
public:
    BtsLogUser();
    void addMessagePrint(string const& lineInLogs);
    void printAll(std::ostream& outputStream) const;
    void analyzeDelay();
    int getNumberPrints() const;
    unsigned int m_nbccId;
    BtsDelayInformationContainer* m_btsDelayInformationContainerPointer;
    std::ostream* m_delayListStreamPointer;

private:
    std::map<BtsLogTime, BtsLogPrint> m_prints;
};


class BtsLogAnalyzer
{
public:
    BtsLogAnalyzer(BtsDelayInformationContainer & container, std::ostream& delayListStream);
    void saveAllMessagePrintsForAllUsers(AlbaWindowsPathHandler const& logPath);
    void printAllForThisUser(int nbccId, std::ostream& outputStream) const;
    void printAllUsers(std::ostream& outputStream) const;
    void analyzeForAllUsers();

private:
    std::unordered_map<int, BtsLogUser> m_users;
    BtsDelayInformationContainer& m_btsDelayInformationContainer;
    std::ostream& m_delayListStream;
};



}//namespace alba
