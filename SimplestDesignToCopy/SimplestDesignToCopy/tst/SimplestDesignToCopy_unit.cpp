#include <gtest/gtest.h>
#include <SimplestDesignToCopy.hpp>

#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

using namespace alba;
using namespace std;

TEST(SampleTest, DISABLED_SampleTest1)
{
    SimplestDesignToCopy entity;
}

TEST(SampleTest, DISABLED_SampleTest2)
{
    AlbaWindowsPathHandler pathHandler(R"(D:\W\ZZZ_Useless_Logs\RAN2861MegaplexerHang\WiresharkMegaPlexerDump.txt)");
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

TEST(SampleTest, GenerateFeatureSpecificComponentFiles)
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



