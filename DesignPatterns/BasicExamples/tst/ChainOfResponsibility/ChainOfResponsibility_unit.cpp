#include <ChainOfResponsibility/ChainOfResponsibility.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace ChainOfResponsibility
{

TEST(ChainOfResponsibilityTest, Test1)
{
    ConcreteHandler1 handler1;
    handler1.setHandler(make_unique<ConcreteHandler2>());
    handler1.handleRequest();
}

}