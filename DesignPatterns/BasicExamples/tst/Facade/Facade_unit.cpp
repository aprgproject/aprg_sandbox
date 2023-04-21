#include <Facade/Facade.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Facade
{

TEST(FacadeTest, Test1)
{
    Facade *facade = new Facade();

    facade->operation1();
    facade->operation2();
    delete facade;
}

}