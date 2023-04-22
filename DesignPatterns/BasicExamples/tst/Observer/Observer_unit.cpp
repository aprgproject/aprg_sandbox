#include <Observer/Observer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Observer
{

TEST(ObserverTest, Test1)
{
    ConcreteObserver observer1( 1 );
    ConcreteObserver observer2( 2 );

    std::cout << "Observer 1 state: " << observer1.getState() << "\n";
    std::cout << "Observer 2 state: " << observer2.getState() << "\n";

    std::unique_ptr<Subject> subject = make_unique<ConcreteSubject>();
    subject->attach( &observer1 );
    subject->attach( &observer2 );

    subject->setState( 10 );
    subject->notify();

    std::cout << "Observer 1 state: " << observer1.getState() << "\n";
    std::cout << "Observer 2 state: " << observer2.getState() << "\n";
}

}
