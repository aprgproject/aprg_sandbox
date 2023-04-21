#include <Composite/Composite.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Composite
{

TEST(CompositeTest, Test1)
{
    unsigned int id=1;
    unique_ptr<Component> composite1(make_unique<Composite>()), composite2(make_unique<Composite>()), topComposite(make_unique<Composite>());

    topComposite->add(make_unique<Leaf>(0));
    composite1->add(make_unique<Leaf>(id++));
    composite1->add(make_unique<Leaf>(id++));
    composite2->add(make_unique<Leaf>(id++));
    composite2->add(make_unique<Leaf>(id++));
    topComposite->add(move(composite1));
    topComposite->add(move(composite2));

    topComposite->removeAtIndex(0);

    topComposite->operation();
}

}