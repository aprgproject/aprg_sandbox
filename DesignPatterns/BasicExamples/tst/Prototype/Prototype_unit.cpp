#include <Prototype/Prototype.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Prototype
{

TEST(PrototypeTest, Test1)
{
    Client client;
    client.setPrototypeAt(0, make_unique<ConcretePrototypeA>());
    client.setPrototypeAt(1, make_unique<ConcretePrototypeB>());

    auto createdObject1 = client.createBasedFrom(0);
    std::cout << "CreatedObject1: " << createdObject1->getType() << "\n";

    auto createdObject2 = client.createBasedFrom(1);
    std::cout << "CreatedObject2: " << createdObject2->getType() << "\n";
}

}