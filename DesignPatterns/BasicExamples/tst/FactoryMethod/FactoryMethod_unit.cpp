#include <FactoryMethod/FactoryMethod.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace FactoryMethod {

TEST(FactoryMethodTest, Test1) {
    unique_ptr<Creator> creator(make_unique<ConcreteCreator>());

    std::unique_ptr<Product> product1 = creator->createProductA();
    std::cout << "Product: " << product1->getName() << "\n";

    std::unique_ptr<Product> product2 = creator->createProductB();
    std::cout << "Product: " << product2->getName() << "\n";
}

}  // namespace FactoryMethod
