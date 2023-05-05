#include <Flyweight/Flyweight.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Flyweight {

TEST(FlyweightTest, Test1) {
    FlyweightFactory factory;

    auto firstSharedObjectWith1 = factory.getSharedFlyweight(1);
    firstSharedObjectWith1->operation(10);

    auto secondSharedObjectWith1 = factory.getSharedFlyweight(1);
    secondSharedObjectWith1->operation(20);

    auto sharedObjectWith2 = factory.getSharedFlyweight(2);
    sharedObjectWith2->operation(30);

    auto unsharedObjectWith2 = factory.getUnsharedFlyweight(3);
    unsharedObjectWith2->operation(40);
}

}  // namespace Flyweight