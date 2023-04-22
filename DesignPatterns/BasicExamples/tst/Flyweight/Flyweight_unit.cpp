#include <Flyweight/Flyweight.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Flyweight
{

TEST(FlyweightTest, Test1)
{
    FlyweightFactory factory;

    factory.getFlyweight(1).operation();
    factory.getFlyweight(2).operation();

    auto UnsharedFlyweightPointer = std::make_unique<UnsharedConcreteFlyweight>(3);
    UnsharedFlyweightPointer->operation();
}

}
