#include <SackReader.hpp>

#include <gtest/gtest.h>
using namespace alba;
using namespace std;

TEST(SackReaderTest, CheckAllFiles)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    EXPECT_EQ(R"(C:\APRG\SackReader\SackReader\SampleFiles\oam_tcom.h)", sackReader.getFileFullPath("oam_tcom.h"));
}

TEST(SackReaderTest, ReadFile_Constants)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    sackReader.readFile("DOpenIUBCommonDefs.h");

    ConstantDetails details(sackReader.getConstantDetails("MAX_NR_OF_CODES"));
    EXPECT_EQ("3GPP 10 Nokia 2.", details.description);
    EXPECT_EQ("2", details.value);

    details = (sackReader.getConstantDetails("MAX_NUM_OF_DELAYED_LINKS_INFO"));
    EXPECT_EQ("Max number of Delayed Links Information", details.description);
    EXPECT_EQ("2", details.value);
}

TEST(SackReaderTest, ReadFile_MessageOamAtmSigFile)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    sackReader.readFile("MessageId_OamAtm.sig");

    EXPECT_EQ("SAtmHwConfigurationMsg", sackReader.getMessageStructure("OAM_ATM_HW_CONFIGURATION_MSG"));
    EXPECT_EQ("STupcAalmanInternalConfigurationResp", sackReader.getMessageStructure("OAM_ATM_TUPC_AALMAN_INTERNAL_CONFIGURATION_RESP_MSG"));
}

TEST(SackReaderTest, ReadFile_MessageOamTcomFile)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    sackReader.readFile("MessageId_OamTcom.sig");

    EXPECT_EQ("SHwConfigurationMsg", sackReader.getMessageStructure("TC_HW_CONFIGURATION_MSG"));
    EXPECT_EQ("SetCellParamResp", sackReader.getMessageStructure("TC_SET_CELL_PARAM_RESP_MSG"));
}

TEST(SackReaderTest, ReadFile_OamTupcStructures)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    sackReader.readFile("Oam_Atm.h");

    ParameterDetails details(sackReader.getParameterDetails("SAtmHwConfigurationMsg", "typeOfConfiguration"));
    EXPECT_EQ("typeOfConfiguration", details.name);
    EXPECT_EQ("EControlUnitType", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);

    details = sackReader.getParameterDetails("SAtmOamCpuStateChangeMsg", "cpuAddress");
    EXPECT_EQ("cpuAddress", details.name);
    EXPECT_EQ("SMessageAddress", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);

    details = sackReader.getParameterDetails("SAtmHwConfigurationMsg", "dynamicData");
    EXPECT_EQ("dynamicData", details.name);
    EXPECT_EQ("TDynamicData", details.type);
    EXPECT_TRUE(details.isAnArray);
    EXPECT_EQ("1", details.arraySize);
    EXPECT_EQ("", details.description);
}

TEST(SackReaderTest, ReadFile_OamTcomStructures)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    sackReader.readFile("oam_tcom.h");

    ParameterDetails details(sackReader.getParameterDetails("SHwConfigurationMsg", "btsomTelecomServiceAddr"));
    EXPECT_EQ("btsomTelecomServiceAddr", details.name);
    EXPECT_EQ("SMessageAddress", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);

    details = sackReader.getParameterDetails("SHwConfigurationMsg", "btsSwVersion");
    EXPECT_EQ("btsSwVersion", details.name);
    EXPECT_EQ("TDynamicData", details.type);
    EXPECT_TRUE(details.isAnArray);
    EXPECT_EQ("1", details.arraySize);
    EXPECT_EQ("", details.description);

    details = sackReader.getParameterDetails("SCellInformationInd", "dssDspAddress");
    EXPECT_EQ("dssDspAddress", details.name);
    EXPECT_EQ("TAaSysComSicad", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);
}

TEST(SackReaderTest, ReadFile_SWamUnit)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    sackReader.readFile("SWamUnit.h");

    ParameterDetails details(sackReader.getParameterDetails("SWamUnit", "logUnitAddr"));
    EXPECT_EQ("logUnitAddr", details.name);
    EXPECT_EQ("TBoard", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("logical unit address (e.g. WAM10)", details.description);

    details = sackReader.getParameterDetails("SWamUnit", "numOfFspUnits");
    EXPECT_EQ("numOfFspUnits", details.name);
    EXPECT_EQ("u8", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("Number of FSP units in System Module. Valid only for EControlUnitType_Fcm2 from Extension System Module in TC_HW_CONFIGURATION_CHANGE_MSG.", details.description);
}

TEST(SackReaderTest, ReadFile_EHspaMapping)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    sackReader.readFile("EHspaMapping.h");

    EnumParameterDetails details(sackReader.getEnumParameterDetails("EHspaMapping", "EHspaMapping_EmptyValue"));
    EXPECT_EQ("EHspaMapping_EmptyValue", details.name);
    EXPECT_EQ("0", details.value);
    EXPECT_EQ("mapping not used", details.description);

    details = sackReader.getEnumParameterDetails("EHspaMapping", "EHspaMapping_SubrackUltra");
    EXPECT_EQ("EHspaMapping_SubrackUltra", details.name);
    EXPECT_EQ("4", details.value);
    EXPECT_EQ("in case of UltraSite", details.description);

    sackReader.saveDatabaseToFile(R"(C:\APRG\SackReader\SackReader\ReadFile_EHspaMapping.txt)");
}

TEST(SackReaderTest, SaveAndLoadFile_EHspaMapping)
{
    SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader.checkAllFiles();
    sackReader.readFile("EHspaMapping.h");
    sackReader.saveDatabaseToFile(R"(C:\APRG\SackReader\SackReader\TempFiles\ReadFile_EHspaMapping.txt)");
    SackReader sackReader2(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    sackReader2.loadDatabaseFromFile(R"(C:\APRG\SackReader\SackReader\TempFiles\ReadFile_EHspaMapping.txt)");

    EnumParameterDetails details(sackReader2.getEnumParameterDetails("EHspaMapping", "EHspaMapping_EmptyValue"));
    EXPECT_EQ("EHspaMapping_EmptyValue", details.name);
    EXPECT_EQ("0", details.value);
    EXPECT_EQ("mapping not used", details.description);

    details = sackReader2.getEnumParameterDetails("EHspaMapping", "EHspaMapping_SubrackUltra");
    EXPECT_EQ("EHspaMapping_SubrackUltra", details.name);
    EXPECT_EQ("4", details.value);
    EXPECT_EQ("in case of UltraSite", details.description);
}

TEST(RealTest, UpdateTrunkFiles)
{
    SackReader sackReader(R"(D:\Branches\trunk\wbts_integration\I_Interface)");
    //SackReader sackReader(R"(C:\APRG\SackReader\SackReader\SampleFiles)");
    //sackReader.checkAllFiles();
    sackReader.loadDatabaseFromFile(R"(C:\APRG\SackReader\SackReader\TempFiles\Database_05_29_2018.txt)");
    sackReader.loadOamTcomMessage();
    sackReader.saveDatabaseToFile(R"(C:\APRG\SackReader\SackReader\TempFiles\Database_05_30_2018.txt)");
}