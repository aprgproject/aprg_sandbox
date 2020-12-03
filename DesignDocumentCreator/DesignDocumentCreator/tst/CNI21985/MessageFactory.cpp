#include "MessageFactory.hpp"

#include <Common/Messages/Messages.hpp>

namespace DesignDocumentCreator
{

GenericMessage MessageFactory::createHwConfigurationMessageForRel3BasedFromLogs()
{
    SpecificStaticMessage<MessageName::OAM_ATM_HW_CONFIGURATION_MSG> hwConfigurationMessage;
    SAtmHwConfigurationMsgFake& payload(hwConfigurationMessage.getPayloadReference());
    payload.typeOfConfiguration = EControlUnitType_Fcm;
    payload.tupConfigurationPresent = EConditional_Present;
    payload.tupConfigurationInfo.ipAddress = 0xc0a8ff10;
    payload.tupConfigurationInfo.minSctpPortIub = 0xc6bf;
    //payload.tupConfigurationInfo.tupAddress = {0x35, 0x00, 0x01, 0x0a, 0x45, 0x5d, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    payload.tupConfigurationInfo.wamNumber = 0x0;
    payload.commisioningParameters.assocMaxRetrans = 0x05;
    payload.commisioningParameters.pathMaxRetrans = 0x05;
    payload.commisioningParameters.pad1 = 0x0;
    payload.commisioningParameters.pad2 = 0x0;
    payload.commisioningParameters.validCookieLife = 0xea60;
    payload.commisioningParameters.cPlaneDscp = 0x0;
    payload.ipMtuSize = 0x05C0;
    payload.numOfWspBoards = 0x12; //18
    payload.numOfFlexiConnections = 0x3;
    for(unsigned int i=0; i<18; i++)
    {
        payload.fspInformation[i].ipAddress = 0;
        payload.fspInformation[i].messageAddress.task = 0x0000;
        payload.fspInformation[i].udpPortMinimum = 0;
        payload.fspInformation[i].udpPortMaximum = 0;
        payload.fspInformation[i].isReady = EBoolean_True;
    }
    payload.fspInformation[0].messageAddress.board = 0x12;
    payload.fspInformation[0].messageAddress.cpu = 0x31;
    payload.fspInformation[0].fspType = EWspType_Nyquist;
    payload.fspInformation[1].messageAddress.board = 0x12;
    payload.fspInformation[1].messageAddress.cpu = 0x51;
    payload.fspInformation[1].fspType = EWspType_Nyquist;
    payload.fspInformation[2].messageAddress.board = 0x12;
    payload.fspInformation[2].messageAddress.cpu = 0x71;
    payload.fspInformation[2].fspType = EWspType_Nyquist;
    payload.fspInformation[3].messageAddress.board = 0x12;
    payload.fspInformation[3].messageAddress.cpu = 0x41;
    payload.fspInformation[3].fspType = EWspType_TurboNyquist;
    payload.fspInformation[4].messageAddress.board = 0x12;
    payload.fspInformation[4].messageAddress.cpu = 0x61;
    payload.fspInformation[4].fspType = EWspType_TurboNyquist;
    payload.fspInformation[5].messageAddress.board = 0x12;
    payload.fspInformation[5].messageAddress.cpu = 0x81;
    payload.fspInformation[5].fspType = EWspType_TurboNyquist;
    payload.fspInformation[6].messageAddress.board = 0x13;
    payload.fspInformation[6].messageAddress.cpu = 0x31;
    payload.fspInformation[6].fspType = EWspType_Nyquist;
    payload.fspInformation[7].messageAddress.board = 0x13;
    payload.fspInformation[7].messageAddress.cpu = 0x51;
    payload.fspInformation[7].fspType = EWspType_Nyquist;
    payload.fspInformation[8].messageAddress.board = 0x13;
    payload.fspInformation[8].messageAddress.cpu = 0x71;
    payload.fspInformation[8].fspType = EWspType_Nyquist;
    payload.fspInformation[9].messageAddress.board = 0x13;
    payload.fspInformation[9].messageAddress.cpu = 0x41;
    payload.fspInformation[9].fspType = EWspType_TurboNyquist;
    payload.fspInformation[10].messageAddress.board = 0x13;
    payload.fspInformation[10].messageAddress.cpu = 0x61;
    payload.fspInformation[10].fspType = EWspType_TurboNyquist;
    payload.fspInformation[11].messageAddress.board = 0x13;
    payload.fspInformation[11].messageAddress.cpu = 0x81;
    payload.fspInformation[11].fspType = EWspType_TurboNyquist;
    payload.fspInformation[12].messageAddress.board = 0x14;
    payload.fspInformation[12].messageAddress.cpu = 0x31;
    payload.fspInformation[12].fspType = EWspType_Nyquist;
    payload.fspInformation[13].messageAddress.board = 0x14;
    payload.fspInformation[13].messageAddress.cpu = 0x51;
    payload.fspInformation[13].fspType = EWspType_Nyquist;
    payload.fspInformation[14].messageAddress.board = 0x14;
    payload.fspInformation[14].messageAddress.cpu = 0x71;
    payload.fspInformation[14].fspType = EWspType_Nyquist;
    payload.fspInformation[15].messageAddress.board = 0x14;
    payload.fspInformation[15].messageAddress.cpu = 0x41;
    payload.fspInformation[15].fspType = EWspType_TurboNyquist;
    payload.fspInformation[16].messageAddress.board = 0x14;
    payload.fspInformation[16].messageAddress.cpu = 0x61;
    payload.fspInformation[16].fspType = EWspType_TurboNyquist;
    payload.fspInformation[17].messageAddress.board = 0x14;
    payload.fspInformation[17].messageAddress.cpu = 0x81;
    payload.fspInformation[17].fspType = EWspType_TurboNyquist;

    payload.flexiConnectionInfo[0].mrsConfigurationInfo.connectionName = EConnectionName_CNBAP;
    payload.flexiConnectionInfo[0].mrsConfigurationInfo.ipAddress = 0xc0a8ff81;
    payload.flexiConnectionInfo[0].mrsConfigurationInfo.udpPort = 0x2335;
    //Dont bother union type zero anyway //payload.flexiConnectionInfo[0].mrsConfigurationInfo.a2ea = 0x0;
    payload.flexiConnectionInfo[0].mrsConfigurationInfo.controlPortId = 0x0;
    payload.flexiConnectionInfo[0].mrsConfigurationInfo.vcType = EServiceCategory_CBR;
    payload.flexiConnectionInfo[0].mrsConfigurationInfo.pcr = 0x0;
    payload.flexiConnectionInfo[0].mrsConfigurationInfo.scr = 0x0;
    payload.flexiConnectionInfo[0].fcmUdpPort = 0x2335;
    payload.flexiConnectionInfo[0].node1.board = 0x59;
    payload.flexiConnectionInfo[0].node1.cpu = 0x12;
    payload.flexiConnectionInfo[0].node1.task = 0x0710;
    payload.flexiConnectionInfo[0].node2.board = 0x12;
    payload.flexiConnectionInfo[0].node2.cpu = 0x0d;
    payload.flexiConnectionInfo[0].node2.task = 0x0152;
    payload.flexiConnectionInfo[0].protocol.type = EProtocolType_NmapGwUdp;
    payload.flexiConnectionInfo[0].protocol.saalUsage = ESaalUsage_Sctp;
    payload.flexiConnectionInfo[0].protocol.mtuSize = 0x1000;
    payload.flexiConnectionInfo[0].protocol.headerFormat = EHeaderFormat_AddRemoveApi;

    payload.flexiConnectionInfo[1].mrsConfigurationInfo.connectionName = EConnectionName_DNBAP;
    payload.flexiConnectionInfo[1].mrsConfigurationInfo.ipAddress = 0xc0a8ff81;
    payload.flexiConnectionInfo[1].mrsConfigurationInfo.udpPort = 0x2333;
    //Dont bother union type zero anyway //payload.flexiConnectionInfo[0].mrsConfigurationInfo.a2ea = 0x0;
    payload.flexiConnectionInfo[1].mrsConfigurationInfo.controlPortId = 0x0;
    payload.flexiConnectionInfo[1].mrsConfigurationInfo.vcType = EServiceCategory_CBR;
    payload.flexiConnectionInfo[1].mrsConfigurationInfo.pcr = 0x0;
    payload.flexiConnectionInfo[1].mrsConfigurationInfo.scr = 0x0;
    payload.flexiConnectionInfo[1].fcmUdpPort = 0x2333;
    payload.flexiConnectionInfo[1].node1.board = 0x59;
    payload.flexiConnectionInfo[1].node1.cpu = 0x12;
    payload.flexiConnectionInfo[1].node1.task = 0x0710;
    payload.flexiConnectionInfo[1].node2.board = 0x12;
    payload.flexiConnectionInfo[1].node2.cpu = 0x0d;
    payload.flexiConnectionInfo[1].node2.task = 0x0152;
    payload.flexiConnectionInfo[1].protocol.type = EProtocolType_NmapGwUdp;
    payload.flexiConnectionInfo[1].protocol.saalUsage = ESaalUsage_Sctp;
    payload.flexiConnectionInfo[1].protocol.mtuSize = 0x1000;
    payload.flexiConnectionInfo[1].protocol.headerFormat = EHeaderFormat_AddRemoveApi;

    payload.flexiConnectionInfo[2].mrsConfigurationInfo.connectionName = EConnectionName_AAL2S;
    payload.flexiConnectionInfo[2].mrsConfigurationInfo.ipAddress = 0xc0a8ff81;
    payload.flexiConnectionInfo[2].mrsConfigurationInfo.udpPort = 0x2334;
    //Dont bother union type zero anyway //payload.flexiConnectionInfo[0].mrsConfigurationInfo.a2ea = 0x0;
    payload.flexiConnectionInfo[2].mrsConfigurationInfo.controlPortId = 0x0;
    payload.flexiConnectionInfo[2].mrsConfigurationInfo.vcType = EServiceCategory_CBR;
    payload.flexiConnectionInfo[2].mrsConfigurationInfo.pcr = 0x0;
    payload.flexiConnectionInfo[2].mrsConfigurationInfo.scr = 0x0;
    payload.flexiConnectionInfo[2].fcmUdpPort = 0x2334;
    payload.flexiConnectionInfo[2].node1.board = 0x10;
    payload.flexiConnectionInfo[2].node1.cpu = 0x12;
    payload.flexiConnectionInfo[2].node1.task = 0x0592;
    payload.flexiConnectionInfo[2].node2.board = 0x12;
    payload.flexiConnectionInfo[2].node2.cpu = 0x0d;
    payload.flexiConnectionInfo[2].node2.task = 0x0331;
    payload.flexiConnectionInfo[2].protocol.type = EProtocolType_NmapGwUdpcp;
    payload.flexiConnectionInfo[2].protocol.saalUsage = ESaalUsage_No;
    payload.flexiConnectionInfo[2].protocol.mtuSize = 0x1000;
    payload.flexiConnectionInfo[2].protocol.headerFormat = EHeaderFormat_AddRemoveApi;

    return convertSpecificStaticToGeneric(hwConfigurationMessage);
}

GenericMessage MessageFactory::createOneTransportBearerRegisterForCell()
{
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG, 1> tbRegisterMessage;
    STransportBearerRegisterMsg& tbRegisterStaticPayload(tbRegisterMessage.getStaticPayloadReference());
    tbRegisterStaticPayload.transactionId = 100001;
    tbRegisterStaticPayload.cellId = 100002;
    tbRegisterStaticPayload.nbccId = 0;
    tbRegisterStaticPayload.numConnections = 1;
    STransportBearerLocationData& dynamicPayload1(tbRegisterMessage.getDynamicPayloadReferenceAt(0));
    dynamicPayload1.bearerType=EBearerType_ATM;
    dynamicPayload1.transportId=100003;
    dynamicPayload1.fpLocation.fpId=100004;
    dynamicPayload1.fpLocation.fpAddress=100005;
    dynamicPayload1.fpLocation.messagingAddress=100006;
    dynamicPayload1.messageTypeNumber=100007;
    dynamicPayload1.ulParameters.maxBitRateInIpPayloadLayer=100008;
    dynamicPayload1.ulParameters.averageBitRateInIpPayloadLayer=100009;
    dynamicPayload1.ulParameters.maxSizeOfIpPayloadInOneIpPacket=100010;
    dynamicPayload1.ulParameters.averageSizeOfIpPayloadInOneIpPacket=100011;
    dynamicPayload1.ulParameters.vlanIdInfo.iePresent=EIEPresentType_IEPresentTrue;
    dynamicPayload1.ulParameters.vlanIdInfo.vlanId=100012;
    dynamicPayload1.oldUlParameters.maxBitRateInIpPayloadLayer=100013;
    dynamicPayload1.oldUlParameters.averageBitRateInIpPayloadLayer=100014;
    dynamicPayload1.oldUlParameters.maxSizeOfIpPayloadInOneIpPacket=100015;
    dynamicPayload1.oldUlParameters.averageSizeOfIpPayloadInOneIpPacket=100016;
    dynamicPayload1.oldUlParameters.vlanIdInfo.iePresent=EIEPresentType_IEPresentTrue;
    dynamicPayload1.oldUlParameters.vlanIdInfo.vlanId=100017;
    dynamicPayload1.rncEndPoint.ipAddress[0]=0x12;
    dynamicPayload1.rncEndPoint.ipAddress[1]=0x34;
    dynamicPayload1.rncEndPoint.ipAddress[2]=0x56;
    dynamicPayload1.rncEndPoint.ipAddress[3]=0x78;
    dynamicPayload1.rncEndPoint.port=100018;
    dynamicPayload1.dsField=0x12;
    return convertSpecificDynamicArrayToGeneric(tbRegisterMessage);
}

}
