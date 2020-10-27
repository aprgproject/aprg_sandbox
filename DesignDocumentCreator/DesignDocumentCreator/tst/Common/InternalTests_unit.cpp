#include <Common/Components/Components.hpp>
#include <Common/Components/SampleComponent.hpp>
#include <Common/Environment.hpp>
#include <Common/Events/Events.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <gtest/gtest.h>

using namespace DesignDocumentCreator;
using namespace std;

TEST(MessagesTest, SpecificMessageCanBeCreatedWithPayload)
{
    SpecificMessage<MessageName::MESSAGE_SAMPLE> specificMessage;
    SampleSack& payload = specificMessage.getPayloadReference();
    payload.sampleParameter=1234;

    EXPECT_EQ(MessageName::MESSAGE_SAMPLE, specificMessage.getMessageName());
    EXPECT_EQ(ComponentName::EMPTY, specificMessage.getSender());
    EXPECT_EQ(ComponentName::EMPTY, specificMessage.getReceiver());
    EXPECT_EQ(1234, specificMessage.getPayloadReference().sampleParameter);
}

TEST(MessagesTest, GenericMessageCanBeCreatedWithPayload)
{
    SampleSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::MESSAGE_SAMPLE, &payload, sizeof(payload));

    SampleSack outputPayload = *reinterpret_cast<SampleSack*>(genericMessage.getPayloadBufferReference().getBufferPointer());

    EXPECT_EQ(MessageName::MESSAGE_SAMPLE, genericMessage.getMessageName());
    EXPECT_EQ(ComponentName::EMPTY, genericMessage.getSender());
    EXPECT_EQ(ComponentName::EMPTY, genericMessage.getReceiver());
    EXPECT_EQ(5678, outputPayload.sampleParameter);
}

TEST(MessagesTest, GenericMessageCanBeConvertedToSpecific)
{
    SampleSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::MESSAGE_SAMPLE, &payload, sizeof(payload));
    genericMessage.setSender(ComponentName::SampleComponent);
    genericMessage.setReceiver(ComponentName::SampleComponent);

    SpecificMessage<MessageName::MESSAGE_SAMPLE> specificMessage = convertGenericToSpecific<MessageName::MESSAGE_SAMPLE>(genericMessage);

    EXPECT_EQ(MessageName::MESSAGE_SAMPLE, specificMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, specificMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, specificMessage.getReceiver());
    EXPECT_EQ(5678, specificMessage.getPayloadReference().sampleParameter);
}

TEST(MessagesTest, SpecificMessageCanBeConvertedToGeneric)
{
    SpecificMessage<MessageName::MESSAGE_SAMPLE> specificMessage;
    SampleSack& payload = specificMessage.getPayloadReference();
    payload.sampleParameter=1234;
    specificMessage.setSender(ComponentName::SampleComponent);
    specificMessage.setReceiver(ComponentName::SampleComponent);

    GenericMessage genericMessage = convertSpecificToGeneric<MessageName::MESSAGE_SAMPLE>(specificMessage);
    SampleSack outputPayload = *reinterpret_cast<SampleSack*>(genericMessage.getPayloadBufferReference().getBufferPointer());

    EXPECT_EQ(MessageName::MESSAGE_SAMPLE, genericMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getReceiver());
    EXPECT_EQ(1234, outputPayload.sampleParameter);
}

TEST(TimerTest, TimersCanBeCreated)
{
    TimerType type(TimerType::CELL_TIMER);
    TimerId cellId(11111);
    Timer timer(type, cellId);

    EXPECT_EQ(type, timer.getType());
    EXPECT_EQ(cellId, timer.getId());
}

TEST(EventsTest, MessageEventsCanBeCreated)
{
    SampleSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::MESSAGE_SAMPLE, &payload, sizeof(payload));
    Event event(genericMessage);
    SampleSack outputPayload = *reinterpret_cast<SampleSack*>(event.getMessage().getPayloadBufferReference().getBufferPointer());

    EXPECT_EQ(EventType::MessageEvent, event.getType());
    EXPECT_EQ(TimerType::EMPTY, event.getTimer().getType());
    EXPECT_EQ(MessageName::MESSAGE_SAMPLE, event.getMessage().getMessageName());
    EXPECT_EQ(5678, outputPayload.sampleParameter);
}

TEST(EventsTest, TimerEventsCanBeCreated)
{
    TimerType type(TimerType::CELL_TIMER);
    TimerId cellId(11111);
    Timer timer(type, cellId);
    Event event(timer);

    EXPECT_EQ(EventType::TimerEvent, event.getType());
    EXPECT_EQ(MessageName::EMPTY, event.getMessage().getMessageName());
    EXPECT_EQ(type, event.getTimer().getType());
    EXPECT_EQ(cellId, event.getTimer().getId());
}

TEST(ComponentsTest, MessageEventsAreHandledByComponents)
{
    SampleSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::MESSAGE_SAMPLE, &payload, sizeof(payload));
    Event event(genericMessage);

    SampleComponent component;
    component.pushBackEvent(event);
    EXPECT_FALSE(component.isEventQueueEmpty());
    component.handleOneEvent();
    EXPECT_TRUE(component.isEventQueueEmpty());
}

TEST(ComponentsTest, TimerEventsAreHandledByComponents)
{
    TimerType type(TimerType::CELL_TIMER);
    TimerId cellId(11111);
    Timer timer(type, cellId);
    Event event(timer);

    SampleComponent component;
    component.pushBackEvent(event);
    EXPECT_FALSE(component.isEventQueueEmpty());
    component.handleOneEvent();
    EXPECT_TRUE(component.isEventQueueEmpty());
}

TEST(ComponentsTest, SpecificComponentCanBeFetchedFromComponents)
{
    Components components;
    EXPECT_EQ(nullptr, components.getComponentPointer(ComponentName::EMPTY));
    EXPECT_NE(nullptr, components.getComponentPointer(ComponentName::SampleComponent));
}

TEST(EnvironmentTest, SentMessagesAreReceivedByRecipientComponent)
{
    Environment environment;
    SampleSack payload;
    GenericMessage genericMessage(MessageName::MESSAGE_SAMPLE, &payload, sizeof(payload));
    Component* componentPointer(environment.getComponentReference().getComponentPointer(ComponentName::SampleComponent));
    ASSERT_NE(nullptr, componentPointer);

    EXPECT_TRUE(componentPointer->isEventQueueEmpty());
    environment.send(ComponentName::SampleComponent, ComponentName::SampleComponent, genericMessage);

    EXPECT_FALSE(componentPointer->isEventQueueEmpty());
}

TEST(EnvironmentTest, SentMessagesAreExecutedByRecipientComponent)
{
    Environment environment;
    SampleSack payload;
    GenericMessage genericMessage(MessageName::MESSAGE_SAMPLE, &payload, sizeof(payload));
    Component* componentPointer(environment.getComponentReference().getComponentPointer(ComponentName::SampleComponent));
    ASSERT_NE(nullptr, componentPointer);

    EXPECT_TRUE(componentPointer->isEventQueueEmpty());
    environment.send(ComponentName::SampleComponent, ComponentName::SampleComponent, genericMessage);
    environment.execute();

    EXPECT_TRUE(componentPointer->isEventQueueEmpty());
}
