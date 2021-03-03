#include <File/AlbaFileReader.hpp>
#include <NsapHelper.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <QuickestWayToProgram.hpp>
#include <String/AlbaStringHelper.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Debug/AlbaDebug.hpp>
#include <stdio.h>

#include <gtest/gtest.h>
#include <windows.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace alba;
using namespace std;



TEST(SampleTest, NSAPCloudPrinting)
{
    u8 mark[4];
    TTransportLayerAddress nsap{
        0x35, 0x00, 0x01, 0x0A,
        0x48, 0xED, 0x8D, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00};
    CommonClassLib::CNsapHelper::convertNsapToIPv4(nsap, mark);

    for(int i=0; i<4; i++)
    {
        cout<<"mark["<<i<<"]: "<<std::dec<<(int)mark[i]<<endl;
    }
}

/*
TEST(SampleTest, Shit)
{
    u32 m_bitContainerForAllocations=1;
    u32 hellomellow = m_bitContainerForAllocations & 0x2;
    cout<<"shouldCellBeAllocatedBasedOnDssKepler start:"<<endl;
    cout<<"shouldCellBeAllocatedBasedOnDssKepler hellomellow: "<<hellomellow<<endl;
    if(m_bitContainerForAllocations & 0x2 != 0)
    {
        cout<<"shouldCellBeAllocatedBasedOnDssKepler true:"<<endl;
    }
    else
    {
        cout<<"shouldCellBeAllocatedBasedOnDssKepler false:"<<endl;
    }

    u32 resultInU32 = m_bitContainerForAllocations & 0x2;
    bool result = resultInU32;
    if(result)
    {
        cout<<"shouldCellBeAllocatedBasedOnDssKepler corrected true:"<<endl;
    }
    else
    {
        cout<<"shouldCellBeAllocatedBasedOnDssKepler corrected false:"<<endl;
    }
}


TEST(SampleTest, CounterOfCounts)
{
    AlbaLocalPathHandler pathHandler(R"(H:\Logs\111_MessagePoolExhaustion\09_09_2018\TC_2_LRM_RL_SETUP_REQ_MSG_queue.log)");
    ifstream queueLogStream(pathHandler.getFullPath());

    map<int, string> highestJumpsQueueLengths;
    map<int, string> highestJumpsMsgQueueingTimes;
    map<int, string> highestJumpsMsgPoolUsages;

    int previousQueueLength(0);
    int previousMsgQueueingTime(0);
    int previousMsgPoolUsage(0);

    if(queueLogStream.is_open())
    {
        AlbaFileReader queueLogFileReader(queueLogStream);

        while(queueLogFileReader.isNotFinished())
        {
            string lineInFile(queueLogFileReader.getLineAndIgnoreWhiteSpaces());
            int queueLength(stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInFile, R"(queueLength: )")));
            int msgQueueingTime(stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInFile, R"(msgQueueingTime: )")));
            int msgPoolUsage(stringHelper::convertStringToNumber<int>(stringHelper::getHexNumberAfterThisString(lineInFile, R"(msgPoolUsage: )")));

            highestJumpsQueueLengths.emplace(queueLength-previousQueueLength, lineInFile);
            highestJumpsMsgQueueingTimes.emplace(msgQueueingTime-previousMsgQueueingTime, lineInFile);
            highestJumpsMsgPoolUsages.emplace(msgPoolUsage-previousMsgPoolUsage, lineInFile);

            previousQueueLength = queueLength;
            previousMsgQueueingTime = msgQueueingTime;
            previousMsgPoolUsage = msgPoolUsage;

            if(highestJumpsQueueLengths.size() > 20)
            {
                highestJumpsQueueLengths.erase(highestJumpsQueueLengths.begin());
            }

            if(highestJumpsMsgQueueingTimes.size() > 20)
            {
                highestJumpsMsgQueueingTimes.erase(highestJumpsMsgQueueingTimes.begin());
            }

            if(highestJumpsMsgPoolUsages.size() > 20)
            {
                highestJumpsMsgPoolUsages.erase(highestJumpsMsgPoolUsages.begin());
            }

        }
    }
    cout<<"highestQueueLengths"<<endl;
    for(pair<int, string> const& printPair: highestJumpsQueueLengths)
    {
        cout<<"queueLengthJump: "<<printPair.first<<" Print: ["<<printPair.second<<"]"<<endl;
    }
    cout<<"highestMsgQueueingTimes"<<endl;
    for(pair<int, string> const& printPair: highestJumpsMsgQueueingTimes)
    {
        cout<<"msgQueueingTimeJump: "<<printPair.first<<" Print: ["<<printPair.second<<"]"<<endl;
    }
    cout<<"highestMsgPoolUsages"<<endl;
    for(pair<int, string> const& printPair: highestJumpsMsgPoolUsages)
    {
        cout<<"msgPoolUsageJump: "<<printPair.first<<" Print: ["<<printPair.second<<"]"<<endl;
    }
}

TEST(SampleTest, MessageIdCounter)
{
    AlbaLocalPathHandler pathHandler(R"(H:\Logs\111_MessagePoolExhaustion\09_09_2018\TC_2_LRM_RL_SETUP_REQ_MSG_queue.log)");
    ifstream queueLogStream(pathHandler.getFullPath());

    map<unsigned int, unsigned int> lastMsgRcvdToCount;
    map<unsigned int, unsigned int> lastMsgSentToCount;
    map<unsigned int, unsigned int> lastInternalMsgToCount;
    map<unsigned int, string> highestMsgQueueingTime;
    map<unsigned int, string> highestQueueLength;

    if(queueLogStream.is_open())
    {
        AlbaFileReader queueLogFileReader(queueLogStream);

        while(queueLogFileReader.isNotFinished())
        {
            string lineInFile(queueLogFileReader.getLineAndIgnoreWhiteSpaces());
            unsigned int lastMsgRcvd(stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getHexNumberAfterThisString(lineInFile, R"(lastMsgRcvd: 0x)")));
            unsigned int lastMsgSent(stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getHexNumberAfterThisString(lineInFile, R"(lastMsgSent: 0x)")));
            unsigned int lastInternalMsg(stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getHexNumberAfterThisString(lineInFile, R"(lastInternalMsg: 0x)")));
            if(lastMsgRcvdToCount.find(lastMsgRcvd) != lastMsgRcvdToCount.cend())
            {
                lastMsgRcvdToCount[lastMsgRcvd]++;
            }
            else
            {
                lastMsgRcvdToCount[lastMsgRcvd]=1;
            }
            if(lastMsgSentToCount.find(lastMsgSent) != lastMsgSentToCount.cend())
            {
                lastMsgSentToCount[lastMsgSent]++;
            }
            else
            {
                lastMsgSentToCount[lastMsgSent]=1;
            }
            if(lastInternalMsgToCount.find(lastInternalMsg) != lastInternalMsgToCount.cend())
            {
                lastInternalMsgToCount[lastInternalMsg]++;
            }
            else
            {
                lastInternalMsgToCount[lastInternalMsg]=1;
            }
        }
    }
    cout<<"lastMsgRcvdToCount"<<endl;
    for(pair<unsigned int, unsigned int> const& printPair: lastMsgRcvdToCount)
    {
        cout<<"MessageId: "<<hex<<printPair.first<<" Count: "<<dec<<printPair.second<<endl;
    }
    cout<<"lastMsgSentToCount"<<endl;
    for(pair<unsigned int, unsigned int> const& printPair: lastMsgSentToCount)
    {
        cout<<"MessageId: "<<hex<<printPair.first<<" Count: "<<dec<<printPair.second<<endl;
    }
    cout<<"lastInternalMsgToCount"<<endl;
    for(pair<unsigned int, unsigned int> const& printPair: lastInternalMsgToCount)
    {
        cout<<"MessageId: "<<hex<<printPair.first<<" Count: "<<dec<<printPair.second<<endl;
    }
}


TEST(SampleTest, ConstTest)
{
    #define GLO_NULL 1
    void * pointer= (void*)GLO_NULL;
    if(pointer==(void*)GLO_NULL)
    {
        cout<<"GLO NULL works! "<<endl;
    }
    if(pointer==nullptr)
    {
        cout<<"nullptr works! "<<endl;
    }
}



class UglyDataType
{
    public:
    unsigned int * uglyPointer; // this is allocated at some point
};
void function1(UglyDataType input)
{
    input.uglyPointer = nullptr; // this will compile
}
void function2(UglyDataType const input) //Since its mandatory to put const for all parameters we will notice the compiler error.
{
    input.uglyPointer = nullptr; // this will not compile
}


TEST(SampleTest, ConstTest)
{
    UglyDataType input;
    function2(input);
}



class SampleClass
{
public:
    SampleClass(unsigned int const sampleParameter)
        : m_sampleParameter(sampleParameter)
    {}
    unsigned int getSampleParameter() const
    {
        return m_sampleParameter;
    }
private:
    unsigned int m_sampleParameter;
};

using SampleClasses = std::vector<SampleClass>;

template <typename T, typename ContainerT, class OperationT>
T sumSample(ContainerT const& container, OperationT const& operation)
{
    return std::accumulate(container.begin(), container.end(), T(),
                           [&operation](T sum, typename ContainerT::value_type const& content)
                           {
                                return sum + (content.*operation)();
    });
//                           boost::bind(std::plus<T>(), 1, boost::bind(operation, 2)));
    //return std::accumulate(container.begin(), container.end(), T(),
                            //std::bind(std::plus<T>(), 1, std::bind(static_cast<typename T()>(OperationT::operation), 2)));
}

TEST(SampleTest, BindingToClassMethod)
{
    SampleClasses sampleContainer;
    sampleContainer.emplace_back(1);
    sampleContainer.emplace_back(2);
    sampleContainer.emplace_back(3);

    EXPECT_EQ(6, sumSample<unsigned int>(sampleContainer, &SampleClass::getSampleParameter));
}

TEST(SampleTest, CompareProfileToLogsInStreamRoutingPoC)
{
    AlbaLocalPathHandler pathHandler(R"(D:\userdata\malba\Desktop\StreamPoC\GSM\WG1_5_GSM_v2.json)");
    ifstream profileStream(pathHandler.getFullPath());

    map<unsigned int, string> ratTypeToAddressMap;
    if(profileStream.is_open())
    {
        AlbaFileReader profileFileReader(profileStream);
        string startString(R"(					")");
        string endString(R"(					},)");
        string axcresblockStartString(R"(				"axcresblock": {)");
        string axcresblockendString(R"(				},)");
        unsigned int axcresblockState=0;
        unsigned int streamState=0;
        unsigned int currentRp3NodeAddress=0;
        string currentRatType;

        while(profileFileReader.isNotFinished())
        {
             string lineInFile(profileFileReader.getLine());
             if(lineInFile.substr(0, axcresblockStartString.length()) == axcresblockStartString)
             {
                 axcresblockState=1;
             }
             else if(lineInFile.substr(0, axcresblockendString.length()) == axcresblockendString)
             {
                 axcresblockState=2;
             }

             if(axcresblockState==1)
             {
                 if(lineInFile.substr(0, startString.length()) == startString)
                 {
                     streamState=1;
                 }
                 else if(lineInFile.substr(0, endString.length()) == endString)
                 {
                     streamState=2;
                 }
             }
             if(streamState==1)
             {
                 if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"("type": ")"))
                 {
                     currentRatType = stringHelper::getStringInBetweenTwoStrings(lineInFile, R"("type": ")", R"(")");
                 }
                 if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"("rp3NodeAddress": )"))
                 {
                     currentRp3NodeAddress = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getStringInBetweenTwoStrings(lineInFile, R"("rp3NodeAddress": )", R"(,)"));
                 }
             }
             else if(streamState==2)
             {
                 //cout<<currentRp3NodeAddress<<"   "<<currentRatType<<endl;
                 ratTypeToAddressMap[currentRp3NodeAddress] = currentRatType;
                 currentRatType="unknown";
                 currentRp3NodeAddress = 0;
             }
        }
    }
}


TEST(SampleTest, CompareProfileToLogsInStreamRoutingPoC)
{
    AlbaLocalPathHandler pathHandler(R"(D:\userdata\malba\Desktop\StreamPoC\GSM\WG1_5_GSM_v2.json)");
    ifstream profileStream(pathHandler.getFullPath());

    map<unsigned int, string> ratTypeToAddressMap;
    if(profileStream.is_open())
    {
        AlbaFileReader profileFileReader(profileStream);
        string startString(R"(					")");
        string endString(R"(					},)");
        string axcresblockStartString(R"(				"axcresblock": {)");
        string axcresblockendString(R"(				},)");
        unsigned int axcresblockState=0;
        unsigned int streamState=0;
        unsigned int currentRp3NodeAddress=0;
        string currentRatType;

        while(profileFileReader.isNotFinished())
        {
             string lineInFile(profileFileReader.getLine());
             if(lineInFile.substr(0, axcresblockStartString.length()) == axcresblockStartString)
             {
                 axcresblockState=1;
             }
             else if(lineInFile.substr(0, axcresblockendString.length()) == axcresblockendString)
             {
                 axcresblockState=2;
             }

             if(axcresblockState==1)
             {
                 if(lineInFile.substr(0, startString.length()) == startString)
                 {
                     streamState=1;
                 }
                 else if(lineInFile.substr(0, endString.length()) == endString)
                 {
                     streamState=2;
                 }
             }
             if(streamState==1)
             {
                 if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"("type": ")"))
                 {
                     currentRatType = stringHelper::getStringInBetweenTwoStrings(lineInFile, R"("type": ")", R"(")");
                 }
                 if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"("rp3NodeAddress": )"))
                 {
                     currentRp3NodeAddress = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getStringInBetweenTwoStrings(lineInFile, R"("rp3NodeAddress": )", R"(,)"));
                 }
             }
             else if(streamState==2)
             {
                 //cout<<currentRp3NodeAddress<<"   "<<currentRatType<<endl;
                 ratTypeToAddressMap[currentRp3NodeAddress] = currentRatType;
                 currentRatType="unknown";
                 currentRp3NodeAddress = 0;
             }
        }
    }
    AlbaLocalPathHandler murrkuLogsPathHandler(R"(D:\userdata\malba\Desktop\StreamPoC\GSM\analyzeMurkkuLogs.txt)");
    ifstream murrkuLogsStream(murrkuLogsPathHandler.getFullPath());

    if(murrkuLogsStream.is_open())
    {
        AlbaFileReader murrkuLogsFileReader(murrkuLogsStream);
        while(murrkuLogsFileReader.isNotFinished())
        {
            string lineInFile(murrkuLogsFileReader.getLineAndIgnoreWhiteSpaces());
            if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"(bbBusAddr: )"))
            {
                 unsigned int rp3NodeAddress(stringHelper::convertStringToNumber<unsigned int>(stringHelper::getStringInBetweenTwoStrings(lineInFile, R"(bbBusAddr: )", R"( )")));
                 //cout<<rp3NodeAddress<<endl;
                 cout<<lineInFile<<"   ["<<ratTypeToAddressMap[rp3NodeAddress]<<"]"<<endl;
            }
        }
    }
}


TEST(SampleTest, SaveGetDifferenceFromGreaterMultipleToCsv)
{
    AlbaLocalPathHandler pathHandler(R"(C:\APRG\GetDifferenceFromGreaterMultipleGraph.txt)");
    ofstream csvFile(pathHandler.getFullPath());

    csvFile<<"size = ["<<endl;
    for(unsigned int multiple = 0; multiple<20; multiple++)
    {
        for(unsigned int number = 0; number<20; number++)
        {
            unsigned int size(mathHelper::getDifferenceFromGreaterMultiple(multiple, number)+mathHelper::getNumberOfMultiplesInclusive(multiple, number));
            csvFile<<size<<" ";
        }
        csvFile<<";"<<endl;
    }
    csvFile<<"]"<<endl;
}

TEST(SampleTest, MessageIds_test)
{
    AlbaLocalPathHandler pathHandler(R"(D:\Branches\trunk\I_Interface\Private\SC_TCOM\Messages\MessageId_TcomTcom.sig)");
    AlbaLocalPathHandler pathHandler2(R"(D:\Branches\trunk\wbts_integration\I_Interface\Application_Env\Wn_Env\Bs_Env\Messages\MessageId_TcomDsp.h)");
    AlbaLocalPathHandler pathHandler3(R"(D:\ZZZ_Logs\PR212221\LRMJairus\MessageHistoryBeforeCorruption.txt)");


    ifstream tcomTcomFile(pathHandler.getFullPath());
    ifstream tcomDspile(pathHandler2.getFullPath());
    ifstream messageMapFile(pathHandler3.getFullPath());


    map<unsigned int, string> messageIds;
    if(tcomTcomFile.is_open())
    {
        AlbaFileReader tcomTcomFileReader(tcomTcomFile);
        while(tcomTcomFileReader.isNotFinished())
        {
            string lineInFile(tcomTcomFileReader.getLineAndIgnoreWhiteSpaces());
            if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "#define"))
            {
                string messageIdString(stringHelper::getStringInBetweenTwoStrings(lineInFile, "(", ")"));
                bool isTcomBasePrintVisible = stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "TC_TCOM_BASE");
                unsigned int messageId = stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getHexNumberAfterThisString(messageIdString, "0x"));
                string messageName = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(stringHelper::getStringInBetweenTwoStrings(lineInFile, "#define", "("));
                if(messageId>0)
                {
                    if(isTcomBasePrintVisible)
                    {
                        messageId = 0x6800+messageId;
                    }
                    //cout<<"isTcomBasePrintVisible"<<isTcomBasePrintVisible<<" messageId: "<<hex<<messageId<<" messageName: "<<dec<<messageName<<endl;
                    messageIds.emplace(messageId, messageName);
                }
            }
        }
    }

    if(tcomDspile.is_open())
    {
        AlbaFileReader tcomDspFileReader(tcomDspile);
        while(tcomDspFileReader.isNotFinished())
        {
            string lineInFile(tcomDspFileReader.getLineAndIgnoreWhiteSpaces());
            if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "#define"))
            {
                string messageIdString(stringHelper::getStringInBetweenTwoStrings(lineInFile, "(", ")"));
                bool isTcomBasePrintVisible = stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "TC_DSP_BASE");
                unsigned int messageId = stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getHexNumberAfterThisString(messageIdString, "0x"));
                string messageName = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(stringHelper::getStringInBetweenTwoStrings(lineInFile, "#define", "("));
                if(messageId>0)
                {
                    if(isTcomBasePrintVisible)
                    {
                        messageId = 0x5000+messageId;
                    }
                    //cout<<"isTcomBasePrintVisible"<<isTcomBasePrintVisible<<" messageId: "<<hex<<messageId<<" messageName: "<<dec<<messageName<<endl;
                    messageIds.emplace(messageId, messageName);
                }
            }
        }
    }

    if(messageMapFile.is_open())
    {
        AlbaFileReader messageMapFileReader(messageMapFile);
        while(messageMapFileReader.isNotFinished())
        {
            string lineInFile(messageMapFileReader.getLineAndIgnoreWhiteSpaces());
            unsigned int messageId = stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getHexNumberAfterThisString(lineInFile, "msgid:0x"));
            unsigned int offset = stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getHexNumberAfterThisString(lineInFile, "off:0x"));
            unsigned int messageSize = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getHexNumberAfterThisString(lineInFile, "msgsize:"));
            unsigned int messagePoolCorruptionAddress = 0x3fdb00;
            int distance = (int)offset+(int)messageSize-(int)messagePoolCorruptionAddress;
            if(messageIds.find(messageId)!= messageIds.end())
            {
                cout<<"distance of the end of the message to corruption: "<<setw(5)<<distance<<", messageId: "<<hex<<messageId<<", messageName: "<<messageIds[messageId] << ", offset+messageSize:0x"<<offset+messageSize<<dec<<endl;
            }
            else
            {
                //cout<<lineInFile<<endl;
            }
        }
    }
}
*/
/*
bool isLeapYear(unsigned int const year)
{
    bool result(true);
    if (year%4 != 0) result = false;
    else if (year%100 != 0) result = true;
    else if (year%400 != 0) result = false;
    return result;
}

unsigned int getMaximumDaysInAMonth(unsigned int const monthIndex, unsigned int const year)
{
    unsigned int maximumDaysOfTheMonth=31;
    if(monthIndex==3 || monthIndex==5 || monthIndex==8 || monthIndex==10)
    {
        maximumDaysOfTheMonth=30;
    }
    else if(monthIndex==1)
    {
        if(isLeapYear(year))
        {
            maximumDaysOfTheMonth=29;
        }
        else
        {
            maximumDaysOfTheMonth=28;
        }
    }
    ALBA_DEBUG_PRINT2(monthIndex, maximumDaysOfTheMonth);
    return maximumDaysOfTheMonth;
}

int getNumberOfLeapYears(unsigned int const year)
{
    int beforeThisYear = year-1;
    //cout<<"beforeThisYear"<<(beforeThisYear/4)<<","<<(beforeThisYear/100)<<","<<(beforeThisYear/400)<<","<<(beforeThisYear/4)+(beforeThisYear/100)<<","<<(beforeThisYear/4)+(beforeThisYear/100)+(beforeThisYear/400)<<(beforeThisYear/4)+(beforeThisYear/100)+(beforeThisYear/400)+1<<endl;
    return (beforeThisYear/4)-(beforeThisYear/100)+(beforeThisYear/400)+1;
}

TEST(SampleTest, DateTimeAlgorithm)
{
    AlbaLocalPathHandler pathHandler(R"(C:\APRG\DateMonthStudy2.csv)");
    ofstream fileOutput(pathHandler.getFullPath());

    fileOutput<<"month,days"<<endl;

    unsigned int numberOfDays=0;
    for(unsigned int month = 0; month<12; month++)
    {
        fileOutput<<month<<","<<(bool)(numberOfDays&2)<<endl;
        numberOfDays+=getMaximumDaysInAMonth(month,1);
    }
}

u32 calculateShiftDelayedSfn(u32 const currentSfn, u32 const calculatedSfn)
{
    const u32 RADIO_FRAME_CYCLE = 4096;
    const u32 MAX_FRAME_NUMBER = 4095;
    const u32 MAX_NUM_OF_TTI = 8;
    const u32 SFN_LOW_LIMIT = 12;
    const u32 SFN_HIGH_LIMIT = 220;

    const u32 limit = (currentSfn + SFN_LOW_LIMIT) % RADIO_FRAME_CYCLE;
    u32 tempSfn = calculatedSfn;
    cout<<"tempSfn"<<tempSfn<<endl;
    cout<<"limit"<<limit<<endl;
    while (tempSfn > limit){
        if (tempSfn < MAX_NUM_OF_TTI){
            break;
        }
        tempSfn = (tempSfn + MAX_NUM_OF_TTI) % RADIO_FRAME_CYCLE;
    }
    cout<<"tempSfn"<<tempSfn<<endl;
    cout<<"limit"<<limit<<endl;
    while (tempSfn < limit){
        if (limit > (MAX_FRAME_NUMBER - MAX_NUM_OF_TTI) && tempSfn < MAX_NUM_OF_TTI){
            cout<<"condition"<<MAX_FRAME_NUMBER-MAX_NUM_OF_TTI<<endl;
            cout<<"tempSfnInside2"<<tempSfn<<endl;
            break;
        }
        cout<<"tempSfnInside"<<tempSfn<<endl;
        tempSfn = (tempSfn + MAX_NUM_OF_TTI) % (RADIO_FRAME_CYCLE);
    }
    cout<<"tempSfn"<<tempSfn<<endl;
    cout<<"limit"<<limit<<endl;
    return tempSfn;
}

u32 calculateShiftDelayedSfnNew(u32 const currentSfn, u32 const calculatedSfn)
{
    const u32 RADIO_FRAME_CYCLE = 4096;
    const u32 MAX_FRAME_NUMBER = 4095;
    const u32 MAX_NUM_OF_TTI = 8;
    const u32 SFN_LOW_LIMIT = 12;
    const u32 SFN_HIGH_LIMIT = 220;

    const u32 limit = (currentSfn + SFN_LOW_LIMIT) % RADIO_FRAME_CYCLE;
    u32 ttiAlignmentValueForCalculatedSfn = calculatedSfn%MAX_NUM_OF_TTI;
    u32 ttiAlignmentValueForLimit  = limit%MAX_NUM_OF_TTI;
    u32 shiftedSfn=0;
    if(ttiAlignmentValueForCalculatedSfn == ttiAlignmentValueForLimit)
    {
        shiftedSfn = limit;
    }
    else if(ttiAlignmentValueForCalculatedSfn > ttiAlignmentValueForLimit)
    {
        shiftedSfn = limit+ttiAlignmentValueForCalculatedSfn-ttiAlignmentValueForLimit;
    }
    else if(ttiAlignmentValueForCalculatedSfn < ttiAlignmentValueForLimit)
    {
        shiftedSfn = limit+ttiAlignmentValueForCalculatedSfn-ttiAlignmentValueForLimit+MAX_NUM_OF_TTI;
    }
    shiftedSfn = shiftedSfn%RADIO_FRAME_CYCLE;
    return shiftedSfn;
}

TEST(SampleTest, RlhBug)
{
    calculateShiftDelayedSfn(4076, 0);

}

TEST(SampleTest, DISABLED_ComparisonOfResultsOfTwoAlgorithms)
{
    AlbaLocalPathHandler pathOfNewAlgorithm(R"(D:\userdata\malba\Desktop\Prontos\PR235148\NewResults.csv)");
    AlbaLocalPathHandler pathOfOldAlgorithm(R"(D:\userdata\malba\Desktop\Prontos\PR235148\OldResults.csv)");

    ifstream newAlgoResultFile(pathOfNewAlgorithm.getFullPath());
    ifstream oldAlgoResultFile(pathOfOldAlgorithm.getFullPath());
    AlbaFileReader newAlgoReader(newAlgoResultFile);
    AlbaFileReader oldAlgoReader(oldAlgoResultFile);

    while(newAlgoReader.isNotFinished() || oldAlgoReader.isNotFinished())
    {
        string lineInFileInNewAlgo(newAlgoReader.getLineAndIgnoreWhiteSpaces());
        string lineInFileInOldAlgo(oldAlgoReader.getLineAndIgnoreWhiteSpaces());
        if(lineInFileInNewAlgo!=lineInFileInOldAlgo)
        {
            cout<<"lineInFileInNewAlgo:["<<lineInFileInNewAlgo<<"]"<<endl;
            cout<<"lineInFileInOldAlgo:["<<lineInFileInOldAlgo<<"]"<<endl;
            //break;
        }
    }
}

TEST(SampleTest, DISABLED_RlhNewLogic)
{
    AlbaLocalPathHandler pathHandler(R"(D:\userdata\malba\Desktop\Prontos\PR235148\NewResults.csv)");
    ofstream fileOutput(pathHandler.getFullPath());

    fileOutput<<"CurrentSfn,CalculatedSfn,ShiftedSfn"<<endl;
    for(u32 currentSfn=0; currentSfn<=4096; currentSfn++)
    {
        for(u32 calculatedSfn=0; calculatedSfn<=4096; calculatedSfn++)
        {
            fileOutput<<currentSfn<<","<<calculatedSfn<<","<<calculateShiftDelayedSfnNew(currentSfn, calculatedSfn)<<endl;
        }
    }
}

TEST(SampleTest, DISABLED_RlhOldLogic)
{
    AlbaLocalPathHandler pathHandler(R"(D:\userdata\malba\Desktop\Prontos\PR235148\OldResults.csv)");
    ofstream fileOutput(pathHandler.getFullPath());

    fileOutput<<"CurrentSfn,CalculatedSfn,ShiftedSfn"<<endl;
    for(u32 currentSfn=0; currentSfn<=4096; currentSfn++)
    {
        for(u32 calculatedSfn=0; calculatedSfn<=4096; calculatedSfn++)
        {
            fileOutput<<currentSfn<<","<<calculatedSfn<<","<<calculateShiftDelayedSfn(currentSfn, calculatedSfn)<<endl;
        }
    }
}


TEST(SampleTest, FilesToFind)
{
    AlbaLocalPathHandler::ListOfPaths files;
    AlbaLocalPathHandler::ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(D:\ZZZ_Logs\PR224369_NEWEST\WBTS17vsWBTS18\WBTS18Second\trace_TUPCexe_Conman_EU_1448_1494233464)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for(string const& file: files)
    {
        AlbaLocalPathHandler filePathHandler(file);
        cout<<R"(./decodeTrace )"<<filePathHandler.getFilenameOnly()<<R"(.log SS_TUPC addr2line)"<<endl;
        cout<<R"(./flameGraph )"<<filePathHandler.getFilenameOnly()<<R"(.log_decode > )"<<filePathHandler.getFilenameOnly()<<R"(.log_flame)"<<endl;
        cout<<R"(cat )"<<filePathHandler.getFilenameOnly()<<R"(.log_flame ~/flamegraphs/FlameGraph-master/stackcollapse-perf.pl | ~/flamegraphs/FlameGraph-master/flamegraph.pl > generatedflamegraphs2/)"<<filePathHandler.getFilenameOnly()<<R"(.svg)"<<endl;
    }
}


TEST(SampleTest, MessageId_TcomTcom_test)
{
    AlbaLocalPathHandler pathHandler(R"(D:\Branches\trunk\I_Interface\Private\SC_TCOM\Messages\MessageId_TcomTcom.sig)");
    AlbaLocalPathHandler pathHandler2(R"(D:\userdata\malba\Desktop\SCTRoutes\MessageId_TcomTcom_xml_format.txt)");
    AlbaLocalPathHandler pathHandler3(R"(D:\userdata\malba\Desktop\SCTRoutes\Unedited\routeList_VM.xml)");
    AlbaLocalPathHandler pathHandler4(R"(D:\userdata\malba\Desktop\SCTRoutes\MessageId_comparison.csv)");

    ifstream tcomTcomFile(pathHandler.getFullPath());
    ifstream routeListFile(pathHandler3.getFullPath());
    ofstream xmlFormattedFile(pathHandler2.getFullPath());
    ofstream messageIdComparisonFile(pathHandler4.getFullPath());

    xmlFormattedFile<<"<messages>"<<endl;

    map<unsigned int, string> tcomTcomMessageIds;
    set<unsigned int> routeListMessageIds;
    if(tcomTcomFile.is_open())
    {
        AlbaFileReader tcomTcomFileReader(tcomTcomFile);
        while(tcomTcomFileReader.isNotFinished())
        {
            string lineInFile(tcomTcomFileReader.getLineAndIgnoreWhiteSpaces());
            if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "#define"))
            {
                string messageIdString(stringHelper::getStringInBetweenTwoStrings(lineInFile, "(", ")"));
                bool isTcomBasePrintVisible = stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "TC_TCOM_BASE");
                unsigned int messageId = stringHelper::convertHexStringToNumber<unsigned int>(stringHelper::getHexNumberAfterThisString(messageIdString, "0x"));
                string messageName = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(stringHelper::getStringInBetweenTwoStrings(lineInFile, "#define", "("));
                if(messageId>0)
                {
                    if(isTcomBasePrintVisible)
                    {
                        messageId = 0x6800+messageId;
                    }
                    cout<<"isTcomBasePrintVisible"<<isTcomBasePrintVisible<<" messageId: "<<messageId<<" messageName: "<<messageName<<endl;
                    tcomTcomMessageIds.emplace(messageId, messageName);
                    xmlFormattedFile<<"\t<message>"<<endl;
                    xmlFormattedFile<<"\t\t<type>"<<messageId<<"</type>"<<endl;
                    xmlFormattedFile<<"\t</message>"<<endl;
                }
            }
        }
    }
    xmlFormattedFile<<"</messages>"<<endl;

    messageIdComparisonFile<<"messageId,isExistInRouteList,isExistInTcomTcom,messageName"<<endl;

    bool isMessageSpace;
    if(routeListFile.is_open())
    {
        AlbaFileReader routeListFileReader(routeListFile);
        while(routeListFileReader.isNotFinished())
        {
            string lineInFile(routeListFileReader.getLineAndIgnoreWhiteSpaces());

            if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "<message>"))
            {
                isMessageSpace=true;
            }

            if(isMessageSpace && stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "<type>"))
            {
                unsigned int messageId = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getStringInBetweenTwoStrings(lineInFile, "<type>", "</type>"));
                if(messageId>0)
                {
                    routeListMessageIds.emplace(messageId);

                }
                //cout<<"messageId:"<<messageId<<endl;
            }

            if(stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "</message>"))
            {
                isMessageSpace=false;
            }
        }
    }
    for(unsigned int i=0; i<0xFFFF; i++)
    {
        bool isExistInRouteList = routeListMessageIds.count(i)>0;
        map<unsigned int, string>::iterator tcomTcomMessageIdIterator = tcomTcomMessageIds.find(i);
        bool isExistInTcomTcom = tcomTcomMessageIdIterator!=tcomTcomMessageIds.end();
        if(!isExistInRouteList !=  !isExistInTcomTcom)
        {
            messageIdComparisonFile<<i<<","<<isExistInRouteList<<","<<isExistInTcomTcom;
            if(isExistInTcomTcom)
            {
                messageIdComparisonFile<<",MessageName:["<<tcomTcomMessageIdIterator->second<<"]";
            }
            messageIdComparisonFile<<endl;
        }
    }
}


TEST(SampleTest, DISABLED_SampleTest1)
{
    QuickestWayToProgram entity;
}

TEST(SampleTest, DISABLED_SampleTest2)
{
    AlbaLocalPathHandler pathHandler(R"(D:\W\ZZZ_Useless_Logs\RAN2861MegaplexerHang\WiresharkMegaPlexerDump.txt)");
    AlbaLocalPathHandler pathHandler2(R"(D:\W\ZZZ_Useless_Logs\RAN2861MegaplexerHang\WiresharkMegaPlexerDumpFixed.txt)");

    ifstream wiresharkDumpFile(pathHandler.getFullPath());
    ofstream wiresharkDumpFileFixed(pathHandler2.getFullPath(), ofstream::binary);
    if(wiresharkDumpFile.is_open())
    {
        AlbaFileReader wiresharkDumpFileReader(wiresharkDumpFile);
        while(wiresharkDumpFileReader.isNotFinished())
        {
            string lineInFile(wiresharkDumpFileReader.getLineAndIgnoreWhiteSpaces());
            string hexDump = lineInFile;
            if(hexDump.length() > 10)
            {
                hexDump = lineInFile.substr(10);
                if(hexDump.length() > 48)
                {
                    hexDump = hexDump.substr(0, 48);
                }
            }
            hexDump = stringHelper::getStringWithoutWhiteSpace(hexDump);

            string byteString;
            int state = 0;
            int count = 0;
            for (char const currentCharacter : hexDump)
            {
                if(state==0)
                {
                    byteString += currentCharacter;
                    state=1;
                }
                else
                {
                    byteString += currentCharacter;
                    unsigned char byteValue = stringHelper::convertHexStringToNumber<unsigned char>(byteString);
                    //cout<<(unsigned int)byteValue<<endl;
                    wiresharkDumpFileFixed<<byteValue;
                    byteString.clear();
                    state=0;
                }
            }
        }
    }
}

TEST(SampleTest, DISABLED_WrcTest)
{
    int power=0xFFFFF205;
    cout.precision(10);
    cout<<"integer:"<<power<<endl;
    cout<<"double:"<<(double)power<<endl;
}

void checkTrace();

void checkTrace()
{
    AlbaLocalPathHandler pathHandler(R"(D:\W\ZZZ_Useless_Logs\RAN2861_slow\PS NRT\1100_MegaPlexer\Ip_10.68.159.157_41786_544_160706_110531.codec.wtbin)");
    ifstream megaplexerStream(pathHandler.getFullPath(), ifstream::binary);
    if(megaplexerStream.is_open())
    {
        char fourBytes[4];
        megaplexerStream.read (fourBytes, 4);
        //cout<<"fourbytes"<<(int)fourBytes[0]<<(int)fourBytes[1]<<(int)fourBytes[2]<<(int)fourBytes[3]<<endl;
        if(!(fourBytes[0]==0x0A && fourBytes[1]==0x0B && fourBytes[2]==0x0C && fourBytes[3]==0x0D))
        {
            cout<<"What the hell is this?"<<megaplexerStream.tellg()<<endl;
        }
        megaplexerStream.read (fourBytes, 4);
        int size = ((unsigned int)fourBytes[0]<<24) | ((unsigned int)fourBytes[1]<<16) | ((unsigned int)fourBytes[2]<<8) | ((unsigned int)fourBytes[3]);
        megaplexerStream.seekg(size-4, ios_base::cur);
        cout<<"size"<<size<<endl;
    }
}

TEST(SampleTest, DISABLED_ConfirmatoryTest)
{
    checkTrace();
}



TEST(SampleTest, DISABLED_VectorAccumulate)
{
    std::vector<int> test ({5, 6, 7, 8});
    std::vector<int> transfer = std::accumulate(test.begin(), test.end(), std::vector<int>{},
                                                [](std::vector<int> const& ref, int a)
    {
            std::vector<int> r(ref);
            r.emplace_back(a);
            return r;
    });
}

TEST(SampleTest, DISABLED_GenerateSupplementarySacksHpp)
{
    AlbaLocalPathHandler currentDirectory(PathInitialValueSource::DetectedLocalPath);
    AlbaLocalPathHandler supplementaryDirectory(currentDirectory.getDirectory()+R"(\SupplementarySacks\)");
    AlbaLocalPathHandler supplementaryHeaderFilePath(currentDirectory.getDirectory()+R"(\SupplementarySacks.hpp)");
    AlbaLocalPathHandler::ListOfPaths files;
    AlbaLocalPathHandler::ListOfPaths directories;
    supplementaryDirectory.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    ofstream supplementaryHeaderFile(supplementaryHeaderFilePath.getFullPath());
    for(string const& file: files)
    {
        AlbaLocalPathHandler filePath(file);
        supplementaryHeaderFile<<"#include <"<<filePath.getFile()<<">"<<endl;
    }
}

TEST(SampleTest, DISABLED_GenerateFeatureSpecificComponentFiles)
{
    AlbaLocalPathHandler currentDirectory(PathInitialValueSource::DetectedLocalPath);
    AlbaLocalPathHandler featureSpecificDirectory(currentDirectory.getDirectory());

    ifstream componentNameFile(featureSpecificDirectory.getFullPath()+"ComponentName.hpp");
    ofstream addComponentFile(featureSpecificDirectory.getFullPath()+"AddComponent.hpp");
    ofstream componentsIncludesFile(featureSpecificDirectory.getFullPath()+"ComponentsIncludes.hpp");
    ofstream convertToStringComponentNameFile(featureSpecificDirectory.getFullPath()+"ConvertToStringComponentName.hpp");

    AlbaFileReader componentNameFileReader(componentNameFile);
    while(componentNameFileReader.isNotFinished())
    {
        string componentName(componentNameFileReader.getLineAndIgnoreWhiteSpaces());
        stringHelper::transformReplaceStringIfFound(componentName, ",", "");
        if(!componentName.empty())
        {
            addComponentFile<<R"(ADD_COMPONENT(ComponentName::)"<<componentName<<", "<<componentName<<")"<<endl;
            componentsIncludesFile<<R"(#include <RAN3374/Components/)"<<componentName<<".hpp"<<endl;
            convertToStringComponentNameFile<<R"(GET_ENUM_STRING(ComponentName::)"<<componentName<<")"<<endl;
        }
    }
}

TEST(SampleTest, DISABLED_CloudPrinting)
{
    char payloadPtr[40];
    int payloadSize=40;
    std::stringstream line;
            line.str("HEX DUMP: ");
            for(int i=0; i<payloadSize; i++)
            {
                char* charPayloadPtr = (char*)payloadPtr;
                unsigned int byte = charPayloadPtr[i]&0xFF;
                line << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte <<" ";
                if(i%32==31)
                {

                    cout<< line.str()<<endl;
                    line.str("HEX DUMP: ");
                }
            }
            if(!line.str().empty())
            {
                cout<< line.str()<<endl;
                line.str("");
            }
}

TEST(SampleTest, DISABLED_NSAPCloudPrinting)
{
    u8 mark[4] = {0xA, 0x45, 0x1A, 0x1A};
    TTransportLayerAddress nsap;
    CommonClassLib::CNsapHelper::convertIPv4toNsap(mark, nsap);

    for(int i=0; i<20; i++)
    {
        cout<<"nsap["<<i<<"]: "<<std::hex<<(int)nsap[i]<<endl;
    }
}

TEST(SampleTest, DISABLED_u32toi32)
{
    typedef unsigned int   u32;
    typedef u32     TCounter;
    typedef  i32 TPowerLevel;

    TPowerLevel           powerLevel1, powerLevel2;
    TCounter test;

    powerLevel1 = -50;
    test = powerLevel1;
    powerLevel2 = test;

    cout<<"PowerLevel1"<<powerLevel1<<"  PowerLevel2"<<powerLevel2<<"  test"<<test<<endl;
}

TEST(SampleTest, DISABLED_RhapsodyShit)
{
    class OMThread
    {
    public:
        int m_param2;
        virtual int getSize(){return sizeof(*this);}
        virtual int execute(){cout<<"OMThread: execute"<<endl;}

    };
    class CMessageReceiver : public OMThread
    {
    public:
        int m_param1;
        int m_param3;
        //virtual int getSize(){return sizeof(*this);}
        virtual int execute(){cout<<"CMessageReceiver: execute"<<endl;}
    };

    const char* name="TCOM_TOAM_EWRP_TASK";
    printf("hello %s\n", name);

    cout<<"CMessageReceiver: "<<sizeof(CMessageReceiver)<<endl;
    cout<<"OMThread: "<<sizeof(OMThread)<<endl;
    OMThread* polyPointer = new CMessageReceiver();
    cout<<"OMThread: "<<sizeof(*polyPointer)<<endl;
    cout<<"OMThread getSize(): "<<polyPointer->getSize()<<endl;

    int size = polyPointer->getSize();
    cout<<"size: "<<size<<endl;
    void* polyPointerVoid = polyPointer;
    void* ccsPointer = malloc(size);
    memcpy(ccsPointer, polyPointer, size);
    printf("polyPointer: %p\n", polyPointer);
    printf("ccsPointer: %p\n", ccsPointer);

    OMThread* staticCastPointer = static_cast<OMThread*>(polyPointerVoid);
    staticCastPointer->execute();
}

TEST(SampleTest, FindThoseIpAddresses)
{
    AlbaLocalPathHandler fileToReadHandler(R"(D:\ZZZ_Logs\NSASampleSnapshots\SampleSnapshots\sorted.log)");
    ifstream fileToReadStream(fileToReadHandler.getFullPath());
    AlbaFileReader fileToRead(fileToReadStream);
    ofstream ipAddressesFile(fileToReadHandler.getDirectory()+"IpAddresses.txt");
    ofstream ipAddressesFile25(fileToReadHandler.getDirectory()+"IpAddresses25.txt");
    while(fileToRead.isNotFinished())
    {
        string lineFromFile(fileToRead.getLineAndIgnoreWhiteSpaces());
        int lineFromFileLength = lineFromFile.length();
        int ipState(0);
        bool isIpAddress(false);
        for (int i = 0; i < lineFromFileLength; ++i)
        {
            //cout <<"printed:["<<lineFromFile[i]<<","<<ipState<<"]"<<endl;
            if(ipState == 0)
            {
                if(stringHelper::isNumber(lineFromFile[i]))
                {
                    ipState = 1;
                }
            }
            else if(ipState == 1)
            {//100
                if(stringHelper::isNumber(lineFromFile[i]))
                {
                    ipState = 1;
                }
                else if(lineFromFile[i]=='.')
                {
                    ipState = 2;
                }
                else
                {
                    ipState = 0;
                }
            }
            else if(ipState == 2)
            {//100.
                if(stringHelper::isNumber(lineFromFile[i]))
                {
                    ipState = 3;
                }
                else
                {
                    ipState = 0;
                }
            }
            else if(ipState == 3)
            {//100.100
                if(stringHelper::isNumber(lineFromFile[i]))
                {
                    ipState = 3;
                }
                else if(lineFromFile[i]=='.')
                {
                    ipState = 4;
                }
                else
                {
                    ipState = 0;
                }
            }
            else if(ipState == 4)
            {//100.100.
                if(stringHelper::isNumber(lineFromFile[i]))
                {
                    ipState = 5;
                }
                else
                {
                    ipState = 0;
                }
            }
            else if(ipState == 5)
            {//100.100.100
                if(stringHelper::isNumber(lineFromFile[i]))
                {
                    ipState = 5;
                }
                else if(lineFromFile[i]=='.')
                {
                    ipState = 6;
                }
                else
                {
                    ipState = 0;
                }
            }
            else if(ipState == 6)
            {//100.100.100.
                if(stringHelper::isNumber(lineFromFile[i]))
                {
                    ipState = 7;
                    isIpAddress = true;
                    break;
                }
                else
                {
                    ipState = 0;
                }
            }
        }
        if(isIpAddress)
        {
            ipAddressesFile << lineFromFile << endl;
            ipAddressesFile25 << lineFromFile.substr(0,25) << endl;
        }
    }
}
*/
