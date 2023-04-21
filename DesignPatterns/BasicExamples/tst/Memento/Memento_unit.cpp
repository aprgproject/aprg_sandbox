#include <Memento/Memento.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Memento
{

TEST(MementoTest, Test1)
{
    CareTaker caretaker;

    caretaker.save(Originator(1));
    caretaker.save(Originator(2));
    caretaker.save(Originator(3));

    Originator originator3 = caretaker.undoAndGetLastOriginator();
    Originator originator2 = caretaker.undoAndGetLastOriginator();
    Originator originator1 = caretaker.undoAndGetLastOriginator();

    caretaker.save(originator3);
    caretaker.save(originator2);
    caretaker.save(originator1);
}

}