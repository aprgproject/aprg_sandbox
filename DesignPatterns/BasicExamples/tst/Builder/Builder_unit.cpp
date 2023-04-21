#include <Builder/Builder.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Builder
{

TEST(BuilderTest, Test1)
{
    Director director(make_unique<ConcreteBuilderX>());
    director.construct();

    Product product1 = director.getProduct();
    std::cout << "1st product parts: " << product1.getProduct() << "\n";

    director.setBuilder(make_unique<ConcreteBuilderY>());
    director.construct();

    Product product2 = director.getProduct();
    std::cout << "2nd product parts: " << product2.getProduct() << "\n";
}

}