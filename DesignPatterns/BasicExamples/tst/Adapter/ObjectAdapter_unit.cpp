#include <Adapter/ObjectAdapter.hpp>

#include <gtest/gtest.h>

using namespace std;


namespace ObjectAdapter
{

TEST(ObjectAdapterTest, Test1)
{
    Target *t = new Adapter();
    t->request();
    delete t;
}

}
