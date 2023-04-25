#include <Strategy/Strategy.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Strategy {

TEST(StrategyTest, TestForConcreteStrategyA) {
    Context context(make_unique<ConcreteStrategyA>());
    context.contextInterface();
}

TEST(StrategyTest, TestForConcreteStrategyB) {
    Context context(make_unique<ConcreteStrategyB>());
    context.contextInterface();
}

TEST(StrategyTest, TestForConcreteStrategyC) {
    Context context(make_unique<ConcreteStrategyC>());
    context.contextInterface();
}

}  // namespace Strategy
