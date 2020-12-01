#include "MessageFactory.hpp"

#include <Common/Messages/Messages.hpp>

namespace DesignDocumentCreator
{

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
    dynamicPayload1.fpLocation.fpId=100004;    dynamicPayload1.fpLocation.fpAddress=100005;
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
