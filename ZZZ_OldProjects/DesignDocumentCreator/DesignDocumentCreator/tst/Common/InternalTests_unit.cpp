#include <Common/Components/Components.hpp>
#include <Common/Components/SampleComponent.hpp>
#include <Common/Environment.hpp>
#include <Common/Events/Events.hpp>
#include <Common/Events/OtherEvent.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <gtest/gtest.h>

using namespace DesignDocumentCreator;
using namespace std;

TEST(MessagesTest, SpecificStaticMessageCanBeCreatedWithPayload) {
    SpecificStaticMessage<MessageName::SampleStaticMessage> specificStaticMessage;
    StaticMessageSack& payload(specificStaticMessage.getStaticPayloadReference());
    payload.sampleParameter = 1234;

    EXPECT_EQ(MessageName::SampleStaticMessage, specificStaticMessage.getMessageName());
    EXPECT_EQ(ComponentName::Empty, specificStaticMessage.getSender());
    EXPECT_EQ(ComponentName::Empty, specificStaticMessage.getReceiver());
    EXPECT_EQ(1234, specificStaticMessage.getStaticPayloadReference().sampleParameter);
}

TEST(MessagesTest, SpecificDynamicArrayMessageCanBeCreatedWithPayload) {
    SpecificDynamicArrayMessage<MessageName::SampleDynamicArrayMessage> specificDynamicArrayMessage;
    DynamicArrayMessageSack& staticPayload(specificDynamicArrayMessage.getStaticPayloadReference());
    staticPayload.staticPart.sampleStaticParameter = 1234;
    DynamicArrayPartSack& dynamicFirstContentPayload(
        specificDynamicArrayMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(0));
    dynamicFirstContentPayload.dynamicArrayParameter = 5678;

    EXPECT_EQ(MessageName::SampleDynamicArrayMessage, specificDynamicArrayMessage.getMessageName());
    EXPECT_EQ(ComponentName::Empty, specificDynamicArrayMessage.getSender());
    EXPECT_EQ(ComponentName::Empty, specificDynamicArrayMessage.getReceiver());
    EXPECT_EQ(1234, specificDynamicArrayMessage.getStaticPayloadReference().staticPart.sampleStaticParameter);
    EXPECT_EQ(5678, specificDynamicArrayMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(0).dynamicArrayParameter);
}

TEST(MessagesTest, SpecificDynamicPolymorphicMessageCanBeCreatedWithPayload) {
    SpecificDynamicPolymorphicMessage<MessageName::SampleDynamicPolymorphicMessage, DynamicPolymorphicPartSack>
        specificDynamicPolymorphicMessage;
    DynamicPolymorphicMessageSack& staticPayload(specificDynamicPolymorphicMessage.getStaticPayloadReference());
    staticPayload.staticPart.sampleStaticParameter = 1234;
    DynamicPolymorphicPartSack& dynamicFirstContentPayload(
        specificDynamicPolymorphicMessage.getDynamicPayloadReference());
    dynamicFirstContentPayload.dynamicPolymorphicParameter = 5678;

    EXPECT_EQ(MessageName::SampleDynamicPolymorphicMessage, specificDynamicPolymorphicMessage.getMessageName());
    EXPECT_EQ(ComponentName::Empty, specificDynamicPolymorphicMessage.getSender());
    EXPECT_EQ(ComponentName::Empty, specificDynamicPolymorphicMessage.getReceiver());
    EXPECT_EQ(1234, specificDynamicPolymorphicMessage.getStaticPayloadReference().staticPart.sampleStaticParameter);
    EXPECT_EQ(5678, specificDynamicPolymorphicMessage.getDynamicPayloadReference().dynamicPolymorphicParameter);
}

TEST(MessagesTest, GenericMessageCanBeCreatedWithPayload) {
    StaticMessageSack payload;
    payload.sampleParameter = 5678;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    StaticMessageSack outputPayload(
        *reinterpret_cast<StaticMessageSack*>(genericMessage.getPayloadBufferReference().getBufferPointer()));

    EXPECT_EQ(MessageName::SampleStaticMessage, genericMessage.getMessageName());
    EXPECT_EQ(ComponentName::Empty, genericMessage.getSender());
    EXPECT_EQ(ComponentName::Empty, genericMessage.getReceiver());
    EXPECT_EQ(5678, outputPayload.sampleParameter);
}

TEST(MessagesTest, GenericMessageCanBeConvertedToSpecificStatic) {
    StaticMessageSack payload;
    payload.sampleParameter = 5678;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    genericMessage.setSender(ComponentName::SampleComponent);
    genericMessage.setReceiver(ComponentName::SampleComponent);

    SpecificStaticMessage<MessageName::SampleStaticMessage> specificStaticMessage(
        convertGenericToSpecificStatic<MessageName::SampleStaticMessage>(genericMessage));

    EXPECT_EQ(MessageName::SampleStaticMessage, specificStaticMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, specificStaticMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, specificStaticMessage.getReceiver());
    EXPECT_EQ(5678, specificStaticMessage.getStaticPayloadReference().sampleParameter);
}

TEST(MessagesTest, GenericMessageCanBeConvertedToSpecificDynamicArrayToSmallerSpecificMessage) {
    SampleActualDynamicArrayMessageSack payload;
    payload.staticPart.sampleStaticParameter = 1010;
    payload.dynamicPart[0].dynamicArrayParameter = 1111;
    payload.dynamicPart[1].dynamicArrayParameter = 2222;
    payload.dynamicPart[2].dynamicArrayParameter = 3333;
    GenericMessage genericMessage(MessageName::SampleDynamicArrayMessage, &payload, sizeof(payload));
    genericMessage.setSender(ComponentName::SampleComponent);
    genericMessage.setReceiver(ComponentName::SampleComponent);

    SpecificDynamicArrayMessage<MessageName::SampleDynamicArrayMessage> specificDynamicArrayMessage(
        convertGenericToSpecificDynamicArray<MessageName::SampleDynamicArrayMessage>(genericMessage));

    EXPECT_EQ(MessageName::SampleDynamicArrayMessage, specificDynamicArrayMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, specificDynamicArrayMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, specificDynamicArrayMessage.getReceiver());
    EXPECT_EQ(1010, specificDynamicArrayMessage.getStaticPayloadReference().staticPart.sampleStaticParameter);
    EXPECT_EQ(1111, specificDynamicArrayMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(0).dynamicArrayParameter);
    EXPECT_EQ(2222, specificDynamicArrayMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(1).dynamicArrayParameter);
}

TEST(MessagesTest, GenericMessageCanBeConvertedToSpecificDynamicArrayToLargerSpecificMessage) {
    SampleActualDynamicArrayMessageSack payload;
    payload.staticPart.sampleStaticParameter = 1010;
    payload.dynamicPart[0].dynamicArrayParameter = 1111;
    payload.dynamicPart[1].dynamicArrayParameter = 2222;
    payload.dynamicPart[9].dynamicArrayParameter = 3333;
    GenericMessage genericMessage(MessageName::SampleDynamicArrayMessage, &payload, sizeof(payload));
    genericMessage.setSender(ComponentName::SampleComponent);
    genericMessage.setReceiver(ComponentName::SampleComponent);

    SpecificDynamicArrayMessage<MessageName::SampleDynamicArrayMessage> specificDynamicArrayMessage(
        convertGenericToSpecificDynamicArray<MessageName::SampleDynamicArrayMessage>(genericMessage));

    EXPECT_EQ(MessageName::SampleDynamicArrayMessage, specificDynamicArrayMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, specificDynamicArrayMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, specificDynamicArrayMessage.getReceiver());
    EXPECT_EQ(1010, specificDynamicArrayMessage.getStaticPayloadReference().staticPart.sampleStaticParameter);
    EXPECT_EQ(1111, specificDynamicArrayMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(0).dynamicArrayParameter);
    EXPECT_EQ(2222, specificDynamicArrayMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(1).dynamicArrayParameter);
    EXPECT_EQ(3333, specificDynamicArrayMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(9).dynamicArrayParameter);
    specificDynamicArrayMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(10).dynamicArrayParameter = 4444;
}

TEST(MessagesTest, GenericMessageCanBeConvertedToSpecificDynamicPolymorphic) {
    SampleActualDynamicPolymorphicMessageSack payload;
    payload.staticPart.sampleStaticParameter = 0x12345678;
    payload.dynamicPart.dynamicPolymorphicParameter = 0x11111111;
    GenericMessage genericMessage(MessageName::SampleDynamicPolymorphicMessage, &payload, sizeof(payload));
    genericMessage.setSender(ComponentName::SampleComponent);
    genericMessage.setReceiver(ComponentName::SampleComponent);

    SpecificDynamicPolymorphicMessage<MessageName::SampleDynamicPolymorphicMessage, DynamicPolymorphicPartSack>
        specificDynamicPolymorphicMessage(
            convertGenericToSpecificDynamicPolymorphic<
                MessageName::SampleDynamicPolymorphicMessage, DynamicPolymorphicPartSack>(genericMessage));

    EXPECT_EQ(MessageName::SampleDynamicPolymorphicMessage, specificDynamicPolymorphicMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, specificDynamicPolymorphicMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, specificDynamicPolymorphicMessage.getReceiver());
    EXPECT_EQ(
        0x12345678, specificDynamicPolymorphicMessage.getStaticPayloadReference().staticPart.sampleStaticParameter);
    EXPECT_EQ(0x11111111, specificDynamicPolymorphicMessage.getDynamicPayloadReference().dynamicPolymorphicParameter);
}

TEST(MessagesTest, SpecificStaticMessageCanBeConvertedToGeneric) {
    SpecificStaticMessage<MessageName::SampleStaticMessage> specificStaticMessage;
    StaticMessageSack& payload(specificStaticMessage.getStaticPayloadReference());
    payload.sampleParameter = 1234;
    specificStaticMessage.setSender(ComponentName::SampleComponent);
    specificStaticMessage.setReceiver(ComponentName::SampleComponent);

    GenericMessage genericMessage(convertSpecificStaticToGeneric(specificStaticMessage));
    StaticMessageSack outputPayload(
        *reinterpret_cast<StaticMessageSack*>(genericMessage.getPayloadBufferReference().getBufferPointer()));

    EXPECT_EQ(MessageName::SampleStaticMessage, genericMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getReceiver());
    EXPECT_EQ(1234, outputPayload.sampleParameter);
}

TEST(MessagesTest, SpecificDynamicArrayMessageCanBeConvertedToGeneric) {
    SpecificDynamicArrayMessage<MessageName::SampleDynamicArrayMessage> specificDynamicArrayMessage;
    DynamicArrayMessageSack& staticPayload(specificDynamicArrayMessage.getStaticPayloadReference());
    staticPayload.staticPart.sampleStaticParameter = 1234;
    DynamicArrayPartSack& dynamicFirstContentPayload(
        specificDynamicArrayMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(0));
    dynamicFirstContentPayload.dynamicArrayParameter = 5678;
    specificDynamicArrayMessage.setSender(ComponentName::SampleComponent);
    specificDynamicArrayMessage.setReceiver(ComponentName::SampleComponent);

    GenericMessage genericMessage(convertSpecificDynamicArrayToGeneric(specificDynamicArrayMessage));

    SampleActualDynamicArrayMessageSack const& messagePayload(
        *reinterpret_cast<SampleActualDynamicArrayMessageSack const*>(
            genericMessage.getPayloadBufferConstReference().getConstantBufferPointer()));
    DynamicArrayPartSack const& dynamicPayload(messagePayload.dynamicPart[0]);
    EXPECT_EQ(MessageName::SampleDynamicArrayMessage, genericMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getReceiver());
    EXPECT_EQ(1234, messagePayload.staticPart.sampleStaticParameter);
    EXPECT_EQ(5678, dynamicPayload.dynamicArrayParameter);
}

TEST(MessagesTest, SpecificDynamicPolymorphicMessageCanBeConvertedToGeneric) {
    SpecificDynamicPolymorphicMessage<MessageName::SampleDynamicPolymorphicMessage, DynamicPolymorphicPartSack>
        specificDynamicPolymorphicMessage;
    DynamicPolymorphicMessageSack& staticPayload(specificDynamicPolymorphicMessage.getStaticPayloadReference());
    staticPayload.staticPart.sampleStaticParameter = 1234;
    DynamicPolymorphicPartSack& dynamicFirstContentPayload(
        specificDynamicPolymorphicMessage.getDynamicPayloadReference());
    dynamicFirstContentPayload.dynamicPolymorphicParameter = 5678;
    specificDynamicPolymorphicMessage.setSender(ComponentName::SampleComponent);
    specificDynamicPolymorphicMessage.setReceiver(ComponentName::SampleComponent);

    GenericMessage genericMessage(convertSpecificDynamicPolymorphicToGeneric(specificDynamicPolymorphicMessage));

    SampleActualDynamicPolymorphicMessageSack const& messagePayload(
        *reinterpret_cast<SampleActualDynamicPolymorphicMessageSack const*>(
            genericMessage.getPayloadBufferConstReference().getConstantBufferPointer()));
    DynamicPolymorphicPartSack const& dynamicPayload(messagePayload.dynamicPart);
    EXPECT_EQ(MessageName::SampleDynamicPolymorphicMessage, genericMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getReceiver());
    EXPECT_EQ(1234, messagePayload.staticPart.sampleStaticParameter);
    EXPECT_EQ(5678, dynamicPayload.dynamicPolymorphicParameter);
}

TEST(TimerTest, TimersCanBeCreated) {
    TimerType type(TimerType::CellTimer);
    TimerId cellId(11111);
    Timer timer(type, cellId);

    EXPECT_EQ(type, timer.getType());
    EXPECT_EQ(cellId, timer.getId());
}

TEST(EventsTest, MessageEventsCanBeCreated) {
    StaticMessageSack payload;
    payload.sampleParameter = 5678;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    Event event(genericMessage);
    StaticMessageSack outputPayload(
        *reinterpret_cast<StaticMessageSack*>(event.getMessage().getPayloadBufferReference().getBufferPointer()));

    EXPECT_EQ(EventType::MessageEvent, event.getType());
    EXPECT_EQ(TimerType::Empty, event.getTimer().getType());
    EXPECT_EQ(MessageName::SampleStaticMessage, event.getMessage().getMessageName());
    EXPECT_EQ(5678, outputPayload.sampleParameter);
}

TEST(EventsTest, TimerEventsCanBeCreated) {
    TimerType type(TimerType::CellTimer);
    TimerId cellId(11111);
    Timer timer(type, cellId);
    Event event(timer);

    EXPECT_EQ(EventType::TimerEvent, event.getType());
    EXPECT_EQ(MessageName::Empty, event.getMessage().getMessageName());
    EXPECT_EQ(type, event.getTimer().getType());
    EXPECT_EQ(cellId, event.getTimer().getId());
}

TEST(EventsTest, OtherEventsCanBeCreated) {
    OtherEvent otherEvent(OtherEventType::MainProcessStartup);
    Event event(otherEvent);

    EXPECT_EQ(EventType::OtherEvent, event.getType());
    EXPECT_EQ(OtherEventType::MainProcessStartup, event.getOtherEvent().getType());
}

TEST(ComponentsTest, MessageEventsAreHandledByComponents) {
    StaticMessageSack payload;
    payload.sampleParameter = 5678;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    Event event(genericMessage);

    SampleComponent component(ComponentName::SampleComponent);
    component.pushBackEvent(event);
    EXPECT_FALSE(component.isEventQueueEmpty());
    component.handleOneEvent();
    EXPECT_TRUE(component.isEventQueueEmpty());
}

TEST(ComponentsTest, TimerEventsAreHandledByComponents) {
    TimerType type(TimerType::CellTimer);
    TimerId cellId(11111);
    Timer timer(type, cellId);
    Event event(timer);

    SampleComponent component(ComponentName::SampleComponent);
    component.pushBackEvent(event);
    EXPECT_FALSE(component.isEventQueueEmpty());
    component.handleOneEvent();
    EXPECT_TRUE(component.isEventQueueEmpty());
}

TEST(ComponentsTest, SpecificComponentCanBeFetchedFromComponents) {
    Components components;
    EXPECT_EQ(nullptr, components.getComponentPointer(ComponentName::Empty));
    EXPECT_NE(nullptr, components.getComponentPointer(ComponentName::SampleComponent));
}

TEST(EnvironmentTest, SentMessagesAreReceivedByRecipientComponent) {
    Environment& environment(Environment::getInstance());
    environment.clear();
    StaticMessageSack payload;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    Component* componentPointer(
        environment.getComponentsReference().getComponentPointer(ComponentName::SampleComponent));
    ASSERT_NE(nullptr, componentPointer);

    EXPECT_TRUE(componentPointer->isEventQueueEmpty());
    environment.send(ComponentName::SampleComponent, ComponentName::SampleComponent, genericMessage);

    EXPECT_FALSE(componentPointer->isEventQueueEmpty());
}

TEST(EnvironmentTest, SentMessagesAreExecutedByRecipientComponent) {
    Environment& environment(Environment::getInstance());
    environment.clear();
    StaticMessageSack payload;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    Component* componentPointer(
        environment.getComponentsReference().getComponentPointer(ComponentName::SampleComponent));
    ASSERT_NE(nullptr, componentPointer);

    EXPECT_TRUE(componentPointer->isEventQueueEmpty());
    environment.send(ComponentName::SampleComponent, ComponentName::SampleComponent, genericMessage);
    environment.execute();

    EXPECT_TRUE(componentPointer->isEventQueueEmpty());
}
