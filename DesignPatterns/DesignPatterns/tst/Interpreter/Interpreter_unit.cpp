#include <Interpreter/Interpreter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Interpreter {

TEST(InterpreterTest, Test1) {
    // An example of very simple expression tree
    // that corresponds to expression (A AND B)

    auto a = make_unique<TerminalExpression>("a");
    auto b = make_unique<TerminalExpression>("b");
    auto aPlusB = make_unique<NonterminalExpression>(move(a), move(b));

    Context context;
    context.set("a", 100);
    context.set("b", 20);

    std::cout << context.getValue("a") << " + " << context.getValue("b");
    std::cout << " = " << aPlusB->interpret(context) << "\n";
}

}  // namespace Interpreter
