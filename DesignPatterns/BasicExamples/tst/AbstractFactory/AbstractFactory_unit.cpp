#include <AbstractFactory/AbstractFactory.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace AbstractFactory {

TEST(AbstractFactoryTest, Test1) {
    std::unique_ptr<AbstractFactory> factoryX = make_unique<ConcreteFactoryX>();
    std::unique_ptr<AbstractFactory> factoryY = make_unique<ConcreteFactoryY>();

    std::unique_ptr<ProductA> productAX = factoryX->createProductA();
    std::unique_ptr<ProductB> productBX = factoryX->createProductB();
    std::cout << "ProductAX: " << productAX->getName() << "\n";
    std::cout << "ProductBX: " << productBX->getName() << "\n";

    std::unique_ptr<ProductA> productAY = factoryY->createProductA();
    std::unique_ptr<ProductB> productBY = factoryY->createProductB();
    std::cout << "ProductAY: " << productAY->getName() << "\n";
    std::cout << "ProductBY: " << productBY->getName() << "\n";
}

}  // namespace AbstractFactory
