#include <State/State.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace State
{

TEST(StateTest, Test1)
{
    Context context;

    context.setState(make_unique<ConcreteStateA>());
    context.request();

    context.setState(make_unique<ConcreteStateB>());
    context.request();
}

}