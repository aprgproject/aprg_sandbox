#include <gtest/gtest.h>
#include <SimplestDesignToCopy.hpp>

#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <NsapHelper.hpp>
#include <stdio.h>

using namespace alba;
using namespace std;
/*
TEST(SampleTest, DISABLED_SampleTest1)
{
    SimplestDesignToCopy entity;}

TEST(SampleTest, DISABLED_SampleTest2)
{    AlbaWindowsPathHandler pathHandler(R"(D:\W\ZZZ_Useless_Logs\RAN2861MegaplexerHang\WiresharkMegaPlexerDump.txt)");
    AlbaWindowsPathHandler pathHandler2(R"(D:\W\ZZZ_Useless_Logs\RAN2861MegaplexerHang\WiresharkMegaPlexerDumpFixed.txt)");

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
    AlbaWindowsPathHandler pathHandler(R"(D:\W\ZZZ_Useless_Logs\RAN2861_slow\PS NRT\1100_MegaPlexer\Ip_10.68.159.157_41786_544_160706_110531.codec.wtbin)");
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

TEST(SampleTest, DISABLED_FilesToFind)
{
    AlbaWindowsPathHandler::ListOfPaths files;
    AlbaWindowsPathHandler::ListOfPaths directories;
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG\gsl\gsl-2.1)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for(string const& file: files)
    {
        cout<<file<<endl;
    }
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
    AlbaWindowsPathHandler currentDirectory(AlbaWindowsPathHandler::InitialValue::PathFromWindows);
    AlbaWindowsPathHandler supplementaryDirectory(currentDirectory.getDirectory()+R"(\SupplementarySacks\)");
    AlbaWindowsPathHandler supplementaryHeaderFilePath(currentDirectory.getDirectory()+R"(\SupplementarySacks.hpp)");
    AlbaWindowsPathHandler::ListOfPaths files;
    AlbaWindowsPathHandler::ListOfPaths directories;
    supplementaryDirectory.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    ofstream supplementaryHeaderFile(supplementaryHeaderFilePath.getFullPath());
    for(string const& file: files)
    {
        AlbaWindowsPathHandler filePath(file);
        supplementaryHeaderFile<<"#include <"<<filePath.getFile()<<">"<<endl;
    }
}

TEST(SampleTest, DISABLED_GenerateFeatureSpecificComponentFiles)
{
    AlbaWindowsPathHandler currentDirectory(AlbaWindowsPathHandler::InitialValue::PathFromWindows);
    AlbaWindowsPathHandler featureSpecificDirectory(currentDirectory.getDirectory());

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
*/

TEST(SampleTest, FindThoseIpAddresses)
{
    AlbaWindowsPathHandler fileToReadHandler(R"(D:\ZZZ_Logs\NSASampleSnapshots\SampleSnapshots\sorted.log)");
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