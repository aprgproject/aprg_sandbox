#include <gtest/gtest.h>
#include <Messages/Messages.hpp>

#include <iostream>
#include <string>

using namespace DesignDocumentCreator;
using namespace std;

TEST(MessagesTest, SpecificMessageCanBeCreatedWithPayload)
{
    SpecificMessage<MessageName::MESSAGE_SAMPLE> specificMessage;
    SampleSack& payload = specificMessage.getPayloadReference();
    payload.sampleParameter=1234;
    EXPECT_EQ(1234, specificMessage.getPayloadReference().sampleParameter);
}

TEST(MessagesTest, GenericMessageCanBeCreatedWithPayload)
{
    SampleSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::MESSAGE_SAMPLE, &payload, sizeof(payload));
    SampleSack outputPayload = *reinterpret_cast<SampleSack*>(genericMessage.getPayloadBufferReference().getBufferPointer());
    EXPECT_EQ(5678, outputPayload.sampleParameter);
}

TEST(MessagesTest, GenericMessageCanBeConvertedToSpecific)
{
    SampleSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::MESSAGE_SAMPLE, &payload, sizeof(payload));
    SpecificMessage<MessageName::MESSAGE_SAMPLE> specificMessage = convertGenericToSpecific<MessageName::MESSAGE_SAMPLE>(genericMessage);
    EXPECT_EQ(5678, specificMessage.getPayloadReference().sampleParameter);
}

TEST(MessagesTest, SpecificMessageCanBeConvertedToGeneric)
{
    SpecificMessage<MessageName::MESSAGE_SAMPLE> specificMessage;
    SampleSack& payload = specificMessage.getPayloadReference();
    payload.sampleParameter=1234;
    GenericMessage genericMessage = convertSpecificToGeneric<MessageName::MESSAGE_SAMPLE>(specificMessage);
    SampleSack outputPayload = *reinterpret_cast<SampleSack*>(genericMessage.getPayloadBufferReference().getBufferPointer());
    EXPECT_EQ(1234, outputPayload.sampleParameter);
}
