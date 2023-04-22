#include <Command/Command.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Command
{

TEST(CommandTest, Test1)
{
    Receiver receiver;
    ConcreteCommand command(receiver);

    Invoker invoker;
    invoker.setCommand(&command);
    invoker.invoke();
    invoker.invokeUndo();
}

}
