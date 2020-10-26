#include <File/AlbaFileReader.hpp>
#include <NsapHelper.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <QuickestWayToProgram.hpp>
#include <String/AlbaStringHelper.hpp>
#include <stdio.h>

#include <gtest/gtest.h>
#include <windows.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace alba;
using namespace std;

TEST(SampleTest, FilesToFind)
{
    AlbaLocalPathHandler::ListOfPaths files;
    AlbaLocalPathHandler::ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(APRG_DIR);
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for(string const& file: files)
    {
        if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(file, ".cpp") || stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(file, ".hpp"))
        {
            vector<string> listOfHeaders;
            AlbaLocalPathHandler pathHandler(file);
            ifstream inputFileStream(pathHandler.getFullPath());
            if(inputFileStream.is_open())
            {
                AlbaFileReader inputFileReader(inputFileStream);
                while(inputFileReader.isNotFinished())
                {
                    string lineInFile(inputFileReader.getLineAndIgnoreWhiteSpaces());
                    if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(lineInFile, "#include") )
                    {
                        listOfHeaders.emplace_back()
                    }
                }
            }
        }
    }
}

/*
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


