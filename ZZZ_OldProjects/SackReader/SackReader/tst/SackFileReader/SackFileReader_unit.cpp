#include <SackFileReader/SackFileReader.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SackFileReaderTest, DISABLED_Constants) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\DOpenIUBCommonDefs.h)");

    ConstantDetails details(database.getConstantDetails("MAX_NR_OF_CODES"));
    EXPECT_EQ("3GPP 10 Nokia 2.", details.description);
    EXPECT_EQ("2", details.value);

    details = (database.getConstantDetails("MAX_NUM_OF_DELAYED_LINKS_INFO"));
    EXPECT_EQ("Max number of Delayed Links Information", details.description);
    EXPECT_EQ("2", details.value);
}

TEST(SackFileReaderTest, DISABLED_DTechLogDef) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\DTechLogDef.h)");

    ConstantDetails details(database.getConstantDetails("MAX_FILENAME_SIZE"));
    EXPECT_EQ("", details.description);
    EXPECT_EQ("48", details.value);

    details = (database.getConstantDetails("MAX_USERNAME_AND_PASSWORD_SIZE"));
    EXPECT_EQ("", details.description);
    EXPECT_EQ("16", details.value);
}

TEST(SackFileReaderTest, DISABLED_IfAaSysComGw_Defs) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\IfAaSysComGw_Defs.h)");

    ConstantDetails details(database.getConstantDetails("AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN"));
    EXPECT_EQ("", details.description);
    EXPECT_EQ("48", details.value);
}

TEST(SackFileReaderTest, DISABLED_CommentInStructure) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\Oam_Tcom_TestModelService.h)");

    ParameterDetails details(database.getStructureParameterDetails("STestModelSetupReqMsg", "numberOfHsPdsch"));
    EXPECT_EQ("numberOfHsPdsch", details.name);
    EXPECT_EQ("TNumberOfItems", details.type);
    EXPECT_FALSE(details.isAnArray);
    // EXPECT_EQ("indicates how many HS-PDSCH is setup for TM5", details.description); //TooHard

    details = database.getStructureParameterDetails("STestModelSetupReqMsg", "testPattern");
    EXPECT_EQ("testPattern", details.name);
    EXPECT_EQ("ECdmaTestDataPattern", details.type);
    EXPECT_FALSE(details.isAnArray);
    // EXPECT_EQ("indicates what kind of testdata is generated to test channels", details.description); //TooHard
}

TEST(SackFileReaderTest, DISABLED_MessageOamAtmSigFile) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\MessageId_OamAtm.sig)");

    EXPECT_EQ("SAtmHwConfigurationMsg", database.getMessageStructure("OAM_ATM_HW_CONFIGURATION_MSG"));
    EXPECT_EQ(
        "STupcAalmanInternalConfigurationResp",
        database.getMessageStructure("OAM_ATM_TUPC_AALMAN_INTERNAL_CONFIGURATION_RESP_MSG"));
}

TEST(SackFileReaderTest, DISABLED_MessageOamTcomFile) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\MessageId_OamTcom.sig)");

    EXPECT_EQ("SHwConfigurationMsg", database.getMessageStructure("TC_HW_CONFIGURATION_MSG"));
    EXPECT_EQ("SetCellParamResp", database.getMessageStructure("TC_SET_CELL_PARAM_RESP_MSG"));
}

TEST(SackFileReaderTest, DISABLED_OamTupcStructures) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\Oam_Atm.h)");

    ParameterDetails details(database.getStructureParameterDetails("SAtmHwConfigurationMsg", "typeOfConfiguration"));
    EXPECT_EQ("typeOfConfiguration", details.name);
    EXPECT_EQ("EControlUnitType", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);

    details = database.getStructureParameterDetails("SAtmOamCpuStateChangeMsg", "cpuAddress");
    EXPECT_EQ("cpuAddress", details.name);
    EXPECT_EQ("SMessageAddress", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);

    details = database.getStructureParameterDetails("SAtmHwConfigurationMsg", "dynamicData");
    EXPECT_EQ("dynamicData", details.name);
    EXPECT_EQ("TDynamicData", details.type);
    EXPECT_TRUE(details.isAnArray);
    EXPECT_EQ("1", details.arraySize);
    EXPECT_EQ("", details.description);
}

TEST(SackFileReaderTest, DISABLED_OamTcomStructures) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\oam_tcom.h)");

    ParameterDetails details(database.getStructureParameterDetails("SHwConfigurationMsg", "btsomTelecomServiceAddr"));
    EXPECT_EQ("btsomTelecomServiceAddr", details.name);
    EXPECT_EQ("SMessageAddress", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);

    details = database.getStructureParameterDetails("SHwConfigurationMsg", "btsSwVersion");
    EXPECT_EQ("btsSwVersion", details.name);
    EXPECT_EQ("TDynamicData", details.type);
    EXPECT_TRUE(details.isAnArray);
    EXPECT_EQ("1", details.arraySize);
    EXPECT_EQ("", details.description);

    details = database.getStructureParameterDetails("SCellInformationInd", "dssDspAddress");
    EXPECT_EQ("dssDspAddress", details.name);
    EXPECT_EQ("TAaSysComSicad", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("", details.description);
}

TEST(SackFileReaderTest, DISABLED_SWamUnit) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\SWamUnit.h)");

    ParameterDetails details(database.getStructureParameterDetails("SWamUnit", "logUnitAddr"));
    EXPECT_EQ("logUnitAddr", details.name);
    EXPECT_EQ("TBoard", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("logical unit address (e.g. WAM10)", details.description);

    details = database.getStructureParameterDetails("SWamUnit", "numOfFspUnits");
    EXPECT_EQ("numOfFspUnits", details.name);
    EXPECT_EQ("u8", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ(
        "Number of FSP units in System Module. Valid only for EControlUnitType_Fcm2 from Extension System Module in "
        "TC_HW_CONFIGURATION_CHANGE_MSG.",
        details.description);
}

TEST(SackFileReaderTest, DISABLED_EHspaMapping) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\EHspaMapping.h)");

    EnumParameterDetails details(database.getEnumParameterDetails("EHspaMapping", "EHspaMapping_EmptyValue"));
    EXPECT_EQ("EHspaMapping_EmptyValue", details.name);
    EXPECT_EQ("0", details.value);
    EXPECT_EQ("mapping not used", details.description);

    details = database.getEnumParameterDetails("EHspaMapping", "EHspaMapping_SubrackUltra");
    EXPECT_EQ("EHspaMapping_SubrackUltra", details.name);
    EXPECT_EQ("4", details.value);
    EXPECT_EQ("in case of UltraSite", details.description);
}

TEST(SackFileReaderTest, DISABLED_EControlUnitType) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\EControlUnitType.h)");

    EnumParameterDetails details(database.getEnumParameterDetails("EControlUnitType", "EControlUnitType_Fcm"));
    EXPECT_EQ("EControlUnitType_Fcm", details.name);
    EXPECT_EQ("1", details.value);
    EXPECT_EQ("FCM type if Flexi rel 1 platform is used", details.description);

    details = database.getEnumParameterDetails("EControlUnitType", "EControlUnitType_Wspf");
    EXPECT_EQ("EControlUnitType_Wspf", details.name);
    EXPECT_EQ("5", details.value);
    EXPECT_EQ("if EUBB WSPF is control unit", details.description);
}

TEST(SackFileReaderTest, DISABLED_UConfigInfoElement) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\UConfigInfoElement.h)");

    ParameterDetails details(database.getUnionParameterDetails("UConfigInfoElement", "wamUnit"));
    EXPECT_EQ("wamUnit", details.name);
    EXPECT_EQ("SWamUnit", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("WAM info", details.description);

    details = database.getUnionParameterDetails("UConfigInfoElement", "wspUnit");
    EXPECT_EQ("wspUnit", details.name);
    EXPECT_EQ("SWspUnit", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("WSP info", details.description);

    details = database.getUnionParameterDetails("UConfigInfoElement", "rxTxResource");
    EXPECT_EQ("rxTxResource", details.name);
    EXPECT_EQ("SRxTxResource", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("Rx or Tx resource info", details.description);
}

TEST(SackFileReaderTest, DISABLED_UIpMacAddress) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\UIpMacAddress.h)");

    ParameterDetails details(database.getUnionParameterDetails("UIpMacAddress", "ipMacv4"));
    EXPECT_EQ("ipMacv4", details.name);
    EXPECT_EQ("SIpMacAddressV4", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("<TODO>", details.description);

    details = database.getUnionParameterDetails("UIpMacAddress", "ipMacv6");
    EXPECT_EQ("ipMacv6", details.name);
    EXPECT_EQ("SIpMacAddressV6", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("<TODO>", details.description);
}

TEST(SackFileReaderTest, DISABLED_URxAntennaBusParameters) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\URxAntennaBusParameters.h)");

    ParameterDetails details(database.getUnionParameterDetails("URxAntennaBusParameters", "paramsForRfBus"));
    EXPECT_EQ("paramsForRfBus", details.name);
    EXPECT_EQ("SAntennaBusParametersForRfBus", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("Index of R-bus and R-bus Antennas mapped to the current LCR id.", details.description);

    details = database.getUnionParameterDetails("URxAntennaBusParameters", "paramsForRp3");
    EXPECT_EQ("paramsForRp3", details.name);
    EXPECT_EQ("SAntennaPhysicalAddress", details.type);
    EXPECT_FALSE(details.isAnArray);
    EXPECT_EQ("RP3 RX Antenna address information mapped to current LCR ID.", details.description);
}

TEST(SackFileReaderTest, DISABLED_TAichPower) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\TAichPower.h)");

    TypedefDetails details(database.getTypedefDetails("TAichPower"));
    EXPECT_EQ("TAichPower", details.name);
    EXPECT_EQ("i32", details.typedefDerivedName);
    EXPECT_EQ("Definition of Aich power Defined in Iub spec 3.2.0. ch 4.6.4", details.description);
}

TEST(SackFileReaderTest, DISABLED_TSubrackNbr) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\TSubrackNbr.h)");

    TypedefDetails details(database.getTypedefDetails("TSubrackNbr"));
    EXPECT_EQ("TSubrackNbr", details.name);
    EXPECT_EQ("u32", details.typedefDerivedName);
    EXPECT_EQ("", details.description);
}

TEST(SackFileReaderTest, DISABLED_TSubunits) {
    Database database;
    SackFileReader sackFileReader(database);
    sackFileReader.readFile(R"(C:\APRG\SackReader\SackReader\SampleFiles\TSubunits.h)");

    TypedefDetails details(database.getTypedefDetails("TSubunits"));
    EXPECT_EQ("TSubunits", details.name);
    EXPECT_EQ("r32", details.typedefDerivedName);
    EXPECT_EQ("Subunits in floating point format.", details.description);
}

}  // namespace alba
