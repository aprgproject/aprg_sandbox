#include "BtsLogAnalyzer.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

namespace alba
{

string getStringNumberAfterThisString(string const& mainString, string const& stringToSearch)
{
    string result;
    int firstIndexOfFirstString = mainString.find(stringToSearch);
    if(stringHelper::isNotNpos(firstIndexOfFirstString))
    {
        int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        int lastIndexOfNumber;
        for(lastIndexOfNumber = lastIndexOfFirstString; stringHelper::isNumber(mainString[lastIndexOfNumber]); ++lastIndexOfNumber);
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber-lastIndexOfFirstString);
    }
    return result;
}

void addBtsDelayInformationToContainer(BtsDelayInformationContainer & container, BtsDelayInformation const& delayInformationToAdd)
{
    bool isAdded(false);
    for(BtsDelayInformation & delayInformation : container)
    {
        if(delayInformationToAdd.m_firstComponentString == delayInformation.m_firstComponentString &&
                delayInformationToAdd.m_secondComponentString == delayInformation.m_secondComponentString &&
                delayInformationToAdd.m_firstMessage == delayInformation.m_firstMessage &&
                delayInformationToAdd.m_secondMessage == delayInformation.m_secondMessage)
        {
            delayInformation.m_delay = delayInformation.m_delay + delayInformationToAdd.m_delay;
            delayInformation.m_delayCount++;
            isAdded = true;
            break;
        }
    }
    if(!isAdded)
    {
        container.push_back(delayInformationToAdd);
    }
}

bool isMessageRelated(string const& message1, string const& message2)
{
     return alba::stringHelper::getLevenshteinDistance(message1, message2) < 6;
}

BtsLogTime::BtsLogTime(string const& lineInLogs)
{
    saveTimeFromLineInLogs(lineInLogs);
}

void BtsLogTime::saveTimeFromLineInLogs(string const& lineInLogs)
{
    string timeLog(stringHelper::getStringInBetweenTwoStrings(lineInLogs, "<", ">"));
    vector <int> timeValues;
    string timeValueString;
    bool hasTCharacter(false);

    for(char character: timeLog)
    {
        if(stringHelper::isNumber(character))
        {
            timeValueString += character;
        }
        else
        {
            timeValues.push_back(stringHelper::stringToNumber<int>(timeValueString));
            timeValueString.clear();
            if('T' == character)
            {
                hasTCharacter = true;
            }
        }
    }
    if(!timeValueString.empty())
    {
        timeValues.push_back(stringHelper::stringToNumber<int>(timeValueString));
    }

    if(7 <= timeValues.size() && hasTCharacter)
    {
        m_years = timeValues[0];
        m_months = timeValues[1];
        m_days = timeValues[2];
        m_seconds = timeValues[3]*3600 + timeValues[4]*60 + timeValues[5];
        m_microseconds = timeValues[6];
    }
}


int BtsLogTime::getYears() const
{
    return m_years;
}

int BtsLogTime::getMonths() const
{
    return (int)m_months;
}

int BtsLogTime::getDays() const
{
    return m_days;
}

int BtsLogTime::getHours() const
{
    return m_seconds/3600;
}

int BtsLogTime::getMinutes() const
{
    return (m_seconds/60)%60;
}

int BtsLogTime::getSeconds() const
{
    return m_seconds%60;
}

int BtsLogTime::getTotalSeconds() const
{
    return m_seconds;
}

int BtsLogTime::getMicroSeconds() const
{
    return m_microseconds;
}

string BtsLogTime::getEquivalentString()const
{
    string separator("|");
    stringstream ss;
    ss<<getYears()<<separator<<getMonths()<<separator<<getDays()<<separator<<getHours()<<separator<<getMinutes()<<separator<<setw(2)<<getSeconds()<<separator<<setw(8)<<getMicroSeconds();
    return ss.str();
}

bool BtsLogTime::operator<(BtsLogTime const& btsLogTimeToCompare) const
{
    if(m_years < btsLogTimeToCompare.m_years) return true;
    if(m_years > btsLogTimeToCompare.m_years) return false;
    if(m_months < btsLogTimeToCompare.m_months) return true;
    if(m_months > btsLogTimeToCompare.m_months) return false;
    if(m_days < btsLogTimeToCompare.m_days) return true;
    if(m_days > btsLogTimeToCompare.m_days) return false;
    if(m_seconds < btsLogTimeToCompare.m_seconds) return true;
    if(m_seconds > btsLogTimeToCompare.m_seconds) return false;
    if(m_microseconds < btsLogTimeToCompare.m_microseconds) return true;
    if(m_microseconds > btsLogTimeToCompare.m_microseconds) return false;
    return false;
}

bool BtsLogTime::operator>(BtsLogTime const& btsLogTimeToCompare) const
{
    if(m_years < btsLogTimeToCompare.m_years) return false;
    if(m_years > btsLogTimeToCompare.m_years) return true;
    if(m_months < btsLogTimeToCompare.m_months) return false;
    if(m_months > btsLogTimeToCompare.m_months) return true;
    if(m_days < btsLogTimeToCompare.m_days) return false;
    if(m_days > btsLogTimeToCompare.m_days) return true;
    if(m_seconds < btsLogTimeToCompare.m_seconds) return false;
    if(m_seconds > btsLogTimeToCompare.m_seconds) return true;
    if(m_microseconds < btsLogTimeToCompare.m_microseconds) return false;
    if(m_microseconds > btsLogTimeToCompare.m_microseconds) return true;
    return false;

}

bool BtsLogTime::operator==(BtsLogTime const& btsLogTimeToCompare) const
{
    if(m_years != btsLogTimeToCompare.m_years) return false;
    if(m_months != btsLogTimeToCompare.m_months) return false;
    if(m_days != btsLogTimeToCompare.m_days) return false;
    if(m_seconds != btsLogTimeToCompare.m_seconds) return false;
    if(m_microseconds != btsLogTimeToCompare.m_microseconds) return false;
    return true;
}

BtsLogTime BtsLogTime::operator+(BtsLogTime const& btsLogTime2)
{
    BtsLogTime btsLogTime1(*this);
    btsLogTime1.m_years += btsLogTime2.m_years;
    btsLogTime1.m_months += btsLogTime2.m_months;
    btsLogTime1.m_days += btsLogTime2.m_days;
    btsLogTime1.m_seconds += btsLogTime2.m_seconds;
    btsLogTime1.m_microseconds += btsLogTime2.m_microseconds;
    btsLogTime1.reorganizeOverflowValues();
    return btsLogTime1;
}

BtsLogTime BtsLogTime::operator-(BtsLogTime const& btsLogTime2)
{
    BtsLogTime btsLogTime1(*this);
    btsLogTime1.m_years -= btsLogTime2.m_years;
    btsLogTime1.m_months -= btsLogTime2.m_months;
    btsLogTime1.m_days -= btsLogTime2.m_days;
    btsLogTime1.m_seconds -= btsLogTime2.m_seconds;
    btsLogTime1.m_microseconds -= btsLogTime2.m_microseconds;
    btsLogTime1.reorganizeUnderflowValues();
    return btsLogTime1;
}

void BtsLogTime::reorganizeOverflowValues()
{
    while(m_microseconds >= 1000000)
    {
        m_seconds++;
        m_microseconds -= 1000000;
    }

    while(m_seconds >= 86400)
    {
        m_days++;
        m_seconds -= 86400;
    }
}

void BtsLogTime::reorganizeUnderflowValues()
{
    while(m_microseconds < 0)
    {
        m_seconds--;
        m_microseconds += 1000000;
    }

    while(m_seconds < 0)
    {
        m_days--;
        m_seconds += 86400;
    }
}

BtsDelayInformation::BtsDelayInformation(
        unsigned int nbccId,
        unsigned int transactionId,
        string firstComponentString,
        string secondComponentString,
        string firstMessage,
        string secondMessage,
        BtsLogTime time1,
        BtsLogTime time2)
    : m_nbccId(nbccId)
    , m_transactionId(transactionId)
    , m_firstComponentString(firstComponentString)
    , m_secondComponentString(secondComponentString)
    , m_firstMessage(firstMessage)
    , m_secondMessage(secondMessage)
    , m_delay(time2 - time1)
    , m_delayCount(1)
{}

void BtsDelayInformation::printWithAverage(ostream& outputStream) const
{
    double averageSecondFloat = (double)m_delay.getTotalSeconds()/m_delayCount;
    int averageSeconds = (int)averageSecondFloat;
    int averageMicroSeconds = (int)(((double)averageSecondFloat-averageSeconds)*1000000+((double)m_delay.getMicroSeconds()/m_delayCount));
    outputStream <<"FirstComponent:["<<m_firstComponentString
                <<"]    SecondComponent:["<<m_secondComponentString
               <<"]    FirstMessage:["<<m_firstMessage
              <<"]    SecondMessage:["<<m_secondMessage
             <<"]    TotalDelay:["<<m_delay.getEquivalentString()
            <<"]    DelayCount:["<<m_delayCount
           <<"]    AverageSeconds:["<<averageSeconds
          <<"]    AverageMicroSeconds:["<<averageMicroSeconds
         <<"]"<<endl;
}

void BtsDelayInformation::printWithNbccId(ostream& outputStream) const
{
    outputStream<<m_nbccId<<","<<m_transactionId<<", Seconds:"<<m_delay.getTotalSeconds()<<","<<m_delay.getMicroSeconds()<<endl;
    //outputStream<<"Delay: ["<<m_delay.getEquivalentString()<<"] DelayCount:["<<m_delayCount<<"] "<<"nbccId: "<<setw(6)<<m_nbccId<<" transactionId: "<<setw(10)<<m_transactionId<<" ["<<m_firstComponentString<<"] ["<<m_secondComponentString<<"] ["<<m_firstMessage<<"] ["<<m_secondMessage<<"]"<<endl;
}

BtsLogPrint::BtsLogPrint(){}

BtsLogPrint::BtsLogPrint(string const& lineInLogs)
    : m_isMessagePrint(false){
    m_print = lineInLogs;

    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " INF/"))
    {
        m_printLevel = BtsLogPrintLevel::INF;
        m_componentString = stringHelper::getStringInBetweenTwoStrings(lineInLogs, " INF/", ",");
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " ERR/"))
    {
        m_printLevel = BtsLogPrintLevel::ERR;
        m_componentString = stringHelper::getStringInBetweenTwoStrings(lineInLogs, " ERR/", ",");
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " WRN/"))
    {
        m_printLevel = BtsLogPrintLevel::WRN;
        m_componentString = stringHelper::getStringInBetweenTwoStrings(lineInLogs, " WRN/", ",");
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " VIP/"))
    {
        m_printLevel = BtsLogPrintLevel::VIP;
        m_componentString = stringHelper::getStringInBetweenTwoStrings(lineInLogs, " VIP/", ",");
    }

    if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " BB_"))
    {
        m_isMessagePrint = true;
        m_messageString = string("BB_")+stringHelper::getStringInBetweenTwoStrings(lineInLogs, " BB_", " ");
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " TC_"))
    {
        m_isMessagePrint = true;
        m_messageString = string("TC_")+stringHelper::getStringInBetweenTwoStrings(lineInLogs, " TC_", " ");
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " RLH_"))
    {
        m_isMessagePrint = true;
        m_messageString = string("RLH_")+stringHelper::getStringInBetweenTwoStrings(lineInLogs, " RLH_", " ");
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " CTRL_"))
    {
        m_isMessagePrint = true;
        m_messageString = string("CTRL_")+stringHelper::getStringInBetweenTwoStrings(lineInLogs, " CTRL_", " ");
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " TUP_"))
    {
        m_isMessagePrint = true;
        m_messageString = string("TUP_")+stringHelper::getStringInBetweenTwoStrings(lineInLogs, " TUP_", " ");
    }
}

string BtsLogPrint::getPrint() const
{
    return m_print;
}

string BtsLogPrint::getComponentString() const
{
    return m_componentString;
}

bool BtsLogPrint::isMessagePrint() const
{
    return m_isMessagePrint;
}

string BtsLogPrint::getMessageString() const
{
    return m_messageString;
}

BtsLogUser::BtsLogUser()
{}

void BtsLogUser::addMessagePrint(string const& lineInLogs)
{
    BtsLogPrint btsLogPrint(lineInLogs);
    if(btsLogPrint.isMessagePrint())
    {
        m_prints[BtsLogTime(lineInLogs)] = btsLogPrint;
    }
}

void BtsLogUser::printAll(ostream& outputStream) const
{
    for(auto const& print : m_prints)
    {
        outputStream<<"Time: ["<<print.first.getEquivalentString()<<"] "<<"Component: ["<<print.second.getComponentString()<<"] "<<"Message: ["<<print.second.getMessageString()<<"] ["<<print.second.getPrint()<<"]"<<endl;
    }
}

void BtsLogUser::analyzeDelay()
{
    for (auto it=m_prints.begin(); it!=m_prints.end(); ++it)
    {
        auto it2 = it;
        it2++;
        if(it2!=m_prints.end())
        {
            if(it->second.getMessageString() == "CTRL_RLH_RlSetupReq3G," && it2->second.getMessageString() == "RLH_CTRL_RlSetupResp3G")
            {
                unsigned int transactionId1 = stringHelper::stringToNumber<unsigned int>(getStringNumberAfterThisString(it->second.getPrint(), "transactionId: "));
                unsigned int transactionId2 = stringHelper::stringToNumber<unsigned int>(getStringNumberAfterThisString(it2->second.getPrint(), "transactionId: "));
                if(transactionId1 == transactionId2)
                {
                    BtsDelayInformation delayInformationToAdd(m_nbccId, transactionId1, it->second.getComponentString(), it2->second.getComponentString(), it->second.getMessageString(),  it2->second.getMessageString(), it->first, it2->first);
                    delayInformationToAdd.printWithNbccId(*m_delayListStreamPointer);
                    addBtsDelayInformationToContainer(*m_btsDelayInformationContainerPointer, delayInformationToAdd);

                    m_prints.erase(it, it2);
                    it=m_prints.begin();
                }
            }
        }
    }
}

int BtsLogUser::getNumberPrints() const
{
    return m_prints.size();
}

BtsLogAnalyzer::BtsLogAnalyzer(BtsDelayInformationContainer & container, ostream& delayListStream)
    : m_btsDelayInformationContainer(container)
    , m_delayListStream(delayListStream)
{}

void BtsLogAnalyzer::saveAllMessagePrintsForAllUsers(AlbaWindowsPathHandler const& logPath)
{
    ifstream logStream(logPath.getFullPath());
    if(logStream.is_open())
    {
        AlbaFileReader fileReader(logStream);
        double fileSize = fileReader.getFileSize();
        int previousPercentage = 0;
        while(fileReader.isNotFinished())
        {
            string lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
            if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, " nbccId:"))
            {
                unsigned int nbccId = stringHelper::stringToNumber<unsigned int>(getStringNumberAfterThisString(lineInLogs, " nbccId: "));

                if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "CTRL_RLH_RlSetupReq3G")
                        || stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInLogs, "RLH_CTRL_RlSetupResp3G"))
                {
                    m_users[nbccId].m_nbccId = nbccId;
                    m_users[nbccId].m_btsDelayInformationContainerPointer = &m_btsDelayInformationContainer;
                    m_users[nbccId].m_delayListStreamPointer = &m_delayListStream;
                    m_users[nbccId].addMessagePrint(lineInLogs);
                    if(m_users[nbccId].getNumberPrints()>20)
                    {
                        m_users[nbccId].analyzeDelay();
                    }
                }
            }
            double percentage = 100*(fileReader.getCurrentLocation()/fileSize);
            if((percentage-previousPercentage)>1)
            {
                cout<<"Percent done: "<<percentage<<endl;
                previousPercentage = percentage;
            }
        }
    }
}

void BtsLogAnalyzer::printAllForThisUser(int nbccId, ostream& outputStream) const
{
    m_users.at(nbccId).printAll(outputStream);
}

void BtsLogAnalyzer::printAllUsers(ostream& outputStream) const
{
    for(auto const& user : m_users)
    {
        outputStream<<"NbccId: "<<user.first<<endl;
        user.second.printAll(outputStream);
    }
}

void BtsLogAnalyzer::analyzeForAllUsers()
{
    for(auto & user : m_users)
    {
        user.second.analyzeDelay();
    }
}

}//namespace alba
