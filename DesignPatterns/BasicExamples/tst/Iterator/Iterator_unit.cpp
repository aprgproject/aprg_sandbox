#include <Iterator/Iterator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Iterator
{

TEST(IteratorTest, Test1)
{
    unsigned int size = 5;
    ConcreteAggregate aggregate(size);

    auto it = aggregate.createIterator();
    for (; !it->isDone(); it->gotoNext())
    {
        std::cout << "Item value: " << it->getCurrentItem() << "\n";
    }
}

}