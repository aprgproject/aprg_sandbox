#include "MessageVerifier.hpp"

#include <Common/Messages/Messages.hpp>

using testing::FLAGS_gtest_break_on_failure;

namespace DesignDocumentCreator
{

void MessageVerifier::verifyOneTransportBearerRegisterForCell(GenericMessage const& genericMessage)
{
    ASSERT_EQ(MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG, genericMessage.getMessageName());
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG> tbRegisterMessage(convertGenericToSpecificDynamicArray<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG>(genericMessage));
    STransportBearerRegisterMsg& tbRegisterStaticPayload(tbRegisterMessage.getStaticPayloadReference());
    EXPECT_EQ(100001, tbRegisterStaticPayload.transactionId);
    EXPECT_EQ(100002, tbRegisterStaticPayload.cellId);
    EXPECT_EQ(0, tbRegisterStaticPayload.nbccId);
    ASSERT_EQ(1, tbRegisterStaticPayload.numConnections);
    STransportBearerLocationData& dynamicPayload1(tbRegisterMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(0));
    EXPECT_EQ(EBearerType_ATM, dynamicPayload1.bearerType);
    EXPECT_EQ(100003, dynamicPayload1.transportId);
    EXPECT_EQ(100004, dynamicPayload1.fpLocation.fpId);
    EXPECT_EQ(100005, dynamicPayload1.fpLocation.fpAddress);
    EXPECT_EQ(100006, dynamicPayload1.fpLocation.messagingAddress);
    EXPECT_EQ(100007, dynamicPayload1.messageTypeNumber);
    EXPECT_EQ(100008, dynamicPayload1.ulParameters.maxBitRateInIpPayloadLayer);
    EXPECT_EQ(100009, dynamicPayload1.ulParameters.averageBitRateInIpPayloadLayer);
    EXPECT_EQ(100010, dynamicPayload1.ulParameters.maxSizeOfIpPayloadInOneIpPacket);
    EXPECT_EQ(100011, dynamicPayload1.ulParameters.averageSizeOfIpPayloadInOneIpPacket);
    EXPECT_EQ(EIEPresentType_IEPresentTrue, dynamicPayload1.ulParameters.vlanIdInfo.iePresent);
    EXPECT_EQ(100012, dynamicPayload1.ulParameters.vlanIdInfo.vlanId);
    EXPECT_EQ(100013, dynamicPayload1.oldUlParameters.maxBitRateInIpPayloadLayer);
    EXPECT_EQ(100014, dynamicPayload1.oldUlParameters.averageBitRateInIpPayloadLayer);
    EXPECT_EQ(100015, dynamicPayload1.oldUlParameters.maxSizeOfIpPayloadInOneIpPacket);
    EXPECT_EQ(100016, dynamicPayload1.oldUlParameters.averageSizeOfIpPayloadInOneIpPacket);
    EXPECT_EQ(EIEPresentType_IEPresentTrue, dynamicPayload1.oldUlParameters.vlanIdInfo.iePresent);
    EXPECT_EQ(100017, dynamicPayload1.oldUlParameters.vlanIdInfo.vlanId);
    EXPECT_EQ(0x12, dynamicPayload1.rncEndPoint.ipAddress[0]);
    EXPECT_EQ(0x34, dynamicPayload1.rncEndPoint.ipAddress[1]);
    EXPECT_EQ(0x56, dynamicPayload1.rncEndPoint.ipAddress[2]);
    EXPECT_EQ(0x78, dynamicPayload1.rncEndPoint.ipAddress[3]);
    EXPECT_EQ(100018, dynamicPayload1.rncEndPoint.port);
    EXPECT_EQ(0x12, dynamicPayload1.dsField);
}

void MessageVerifier::verifySuccessfulHwConfigurationResponseMessage(GenericMessage const& genericMessage)
{
    ASSERT_EQ(MessageName::TC_HW_CONFIGURATION_RESP_MSG, genericMessage.getMessageName());
    SpecificStaticMessage<MessageName::TC_HW_CONFIGURATION_RESP_MSG> message(convertGenericToSpecificStatic<MessageName::TC_HW_CONFIGURATION_RESP_MSG>(genericMessage));
    SHwConfigurationResponseMsg& payload(message.getStaticPayloadReference());
    EXPECT_EQ(EStatus_NoError, payload.status);
}

void MessageVerifier::verifyLinkStateResponseMessage(GenericMessage const& genericMessage)
{
    ASSERT_EQ(MessageName::TC_LINK_STATES_RESP_MSG, genericMessage.getMessageName());
    //SpecificStaticMessage<MessageName::TC_LINK_STATES_RESP_MSG> message(convertGenericToSpecificStatic<MessageName::TC_LINK_STATES_RESP_MSG>(genericMessage));
    //SLinkStatesResponseMsg& payload(message.getStaticPayloadReference());
}

void MessageVerifier::verifyTcomDeploymentIndMessage(GenericMessage const& genericMessage)
{
    ASSERT_EQ(MessageName::TC_TCOM_DEPLOYMENT_IND_MSG, genericMessage.getMessageName());
}

}
