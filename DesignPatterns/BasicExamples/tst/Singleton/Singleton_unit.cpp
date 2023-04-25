#include <Singleton/Singleton.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Singleton {

TEST(SingletonTest, Test1) {
    Singleton::getInstance().tellSomething();

    Singleton::restartInstance();

    Singleton::getInstance().tellSomething();
}

}  // namespace Singleton
