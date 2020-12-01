#include <Common/Components/Components.hpp>
#include <Common/Components/SampleComponent.hpp>
#include <Common/Environment.hpp>
#include <Common/Events/Events.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <gtest/gtest.h>

using namespace DesignDocumentCreator;
using namespace std;

TEST(MessagesTest, SpecificStaticMessageCanBeCreatedWithPayload)
{
    SpecificStaticMessage<MessageName::SampleStaticMessage> specificStaticMessage;
    StaticMessageSack& payload = specificStaticMessage.getPayloadReference();
    payload.sampleParameter=1234;

    EXPECT_EQ(MessageName::SampleStaticMessage, specificStaticMessage.getMessageName());
    EXPECT_EQ(ComponentName::Empty, specificStaticMessage.getSender());
    EXPECT_EQ(ComponentName::Empty, specificStaticMessage.getReceiver());
    EXPECT_EQ(1234, specificStaticMessage.getPayloadReference().sampleParameter);
}

TEST(MessagesTest, SpecificDynamicArrayMessageCanBeCreatedWithPayload)
{
    SpecificDynamicArrayMessage<MessageName::SampleDynamicArrayMessage, 5> specificDynamicArrayMessage;
    StaticMessageSack& payload = specificDynamicArrayMessage.getStaticPayloadReference();
    payload.sampleParameter=1234;

    EXPECT_EQ(MessageName::SampleStaticMessage, specificDynamicArrayMessage.getMessageName());
    EXPECT_EQ(ComponentName::Empty, specificDynamicArrayMessage.getSender());
    EXPECT_EQ(ComponentName::Empty, specificDynamicArrayMessage.getReceiver());
    EXPECT_EQ(1234, specificDynamicArrayMessage.getPayloadReference().sampleParameter);
}


TEST(MessagesTest, GenericMessageCanBeCreatedWithPayload)
{
    StaticMessageSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));

    StaticMessageSack outputPayload = *reinterpret_cast<StaticMessageSack*>(genericMessage.getPayloadBufferReference().getBufferPointer());

    EXPECT_EQ(MessageName::SampleStaticMessage, genericMessage.getMessageName());
    EXPECT_EQ(ComponentName::Empty, genericMessage.getSender());
    EXPECT_EQ(ComponentName::Empty, genericMessage.getReceiver());
    EXPECT_EQ(5678, outputPayload.sampleParameter);
}

TEST(MessagesTest, GenericMessageCanBeConvertedToSpecific)
{
    StaticMessageSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    genericMessage.setSender(ComponentName::SampleComponent);
    genericMessage.setReceiver(ComponentName::SampleComponent);

    SpecificStaticMessage<MessageName::SampleStaticMessage> specificStaticMessage = convertGenericToSpecificStatic<MessageName::SampleStaticMessage>(genericMessage);

    EXPECT_EQ(MessageName::SampleStaticMessage, specificStaticMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, specificStaticMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, specificStaticMessage.getReceiver());
    EXPECT_EQ(5678, specificStaticMessage.getPayloadReference().sampleParameter);
}

TEST(MessagesTest, SpecificStaticMessageCanBeConvertedToGeneric)
{
    SpecificStaticMessage<MessageName::SampleStaticMessage> specificStaticMessage;
    StaticMessageSack& payload = specificStaticMessage.getPayloadReference();
    payload.sampleParameter=1234;
    specificStaticMessage.setSender(ComponentName::SampleComponent);
    specificStaticMessage.setReceiver(ComponentName::SampleComponent);

    GenericMessage genericMessage = convertSpecificToGeneric<MessageName::SampleStaticMessage>(specificStaticMessage);
    StaticMessageSack outputPayload = *reinterpret_cast<StaticMessageSack*>(genericMessage.getPayloadBufferReference().getBufferPointer());

    EXPECT_EQ(MessageName::SampleStaticMessage, genericMessage.getMessageName());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getSender());
    EXPECT_EQ(ComponentName::SampleComponent, genericMessage.getReceiver());
    EXPECT_EQ(1234, outputPayload.sampleParameter);}

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
    StaticMessageSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    Event event(genericMessage);
    StaticMessageSack outputPayload = *reinterpret_cast<StaticMessageSack*>(event.getMessage().getPayloadBufferReference().getBufferPointer());

    EXPECT_EQ(EventType::MessageEvent, event.getType());
    EXPECT_EQ(TimerType::EMPTY, event.getTimer().getType());
    EXPECT_EQ(MessageName::SampleStaticMessage, event.getMessage().getMessageName());
    EXPECT_EQ(5678, outputPayload.sampleParameter);
}
TEST(EventsTest, TimerEventsCanBeCreated)
{
    TimerType type(TimerType::CELL_TIMER);
    TimerId cellId(11111);
    Timer timer(type, cellId);
    Event event(timer);

    EXPECT_EQ(EventType::TimerEvent, event.getType());
    EXPECT_EQ(MessageName::Empty, event.getMessage().getMessageName());
    EXPECT_EQ(type, event.getTimer().getType());
    EXPECT_EQ(cellId, event.getTimer().getId());
}

TEST(ComponentsTest, MessageEventsAreHandledByComponents)
{
    StaticMessageSack payload;
    payload.sampleParameter=5678;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    Event event(genericMessage);

    SampleComponent component;    component.pushBackEvent(event);
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
    EXPECT_EQ(nullptr, components.getComponentPointer(ComponentName::Empty));
    EXPECT_NE(nullptr, components.getComponentPointer(ComponentName::SampleComponent));
}

TEST(EnvironmentTest, SentMessagesAreReceivedByRecipientComponent)
{
    Environment environment;
    StaticMessageSack payload;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    Component* componentPointer(environment.getComponentReference().getComponentPointer(ComponentName::SampleComponent));
    ASSERT_NE(nullptr, componentPointer);
    EXPECT_TRUE(componentPointer->isEventQueueEmpty());
    environment.send(ComponentName::SampleComponent, ComponentName::SampleComponent, genericMessage);

    EXPECT_FALSE(componentPointer->isEventQueueEmpty());
}

TEST(EnvironmentTest, SentMessagesAreExecutedByRecipientComponent)
{
    Environment environment;
    StaticMessageSack payload;
    GenericMessage genericMessage(MessageName::SampleStaticMessage, &payload, sizeof(payload));
    Component* componentPointer(environment.getComponentReference().getComponentPointer(ComponentName::SampleComponent));
    ASSERT_NE(nullptr, componentPointer);
    EXPECT_TRUE(componentPointer->isEventQueueEmpty());
    environment.send(ComponentName::SampleComponent, ComponentName::SampleComponent, genericMessage);
    environment.execute();

    EXPECT_TRUE(componentPointer->isEventQueueEmpty());
}
