#include <Bridge/Bridge.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Bridge
{

TEST(BridgeTest, Test1)
{
    auto implementatorA = std::make_unique<ConcreteImplementorA>();
    auto implementatorB = std::make_unique<ConcreteImplementorB>();

    unique_ptr<Abstraction> abstraction1 = std::make_unique<RefinedAbstraction>(move(implementatorA));
    abstraction1->operation();

    unique_ptr<Abstraction> abstraction2 = std::make_unique<RefinedAbstraction>(move(implementatorB));
    abstraction2->operation();
}

}
