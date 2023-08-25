#include <iostream>
#include <map>
#include <memory>

namespace Interpreter {

// Context
// contains information that's global to the interpreter

class Context {
public:
    void set(std::string const& variable, int const value) { m_variableToValueMap.emplace(variable, value); }

    int getValue(std::string const& variable) const { return m_variableToValueMap.at(variable); }
    // ...

private:
    std::map<std::string, int> m_variableToValueMap;
    // ...
};

// Abstract Expression
// declares an abstract Interpret operation that is common to all nodes
// in the abstract syntax tree

class AbstractExpression {
public:
    virtual ~AbstractExpression() = default;

    virtual int interpret(Context const&) = 0;
    // ...
};

// Terminal Expression
// implements an Interpret operation associated with terminal symbols
// in the grammar (an instance is required for every terminal symbol
// in a sentence)

class TerminalExpression : public AbstractExpression {
public:
    TerminalExpression(std::string const& variable) : m_variable(variable) {}

    int interpret(Context const& context) override { return context.getValue(m_variable); }
    // ...

private:
    std::string m_variable;
    // ...
};

// Nonterminal Expression
// implements an Interpret operation for nonterminal symbols
// in the grammar (one such class is required for every rule in the grammar)

class NonterminalExpression : public AbstractExpression {
public:
    NonterminalExpression(
        std::unique_ptr<AbstractExpression> leftPointer, std::unique_ptr<AbstractExpression> rightPointer)
        : m_leftPointer(move(leftPointer)), m_rightPointer(move(rightPointer)) {}

    int interpret(Context const& context) override {
        // Addition is the interpretation
        return m_leftPointer->interpret(context) + m_rightPointer->interpret(context);
    }
    // ...

private:
    std::unique_ptr<AbstractExpression> m_leftPointer;
    std::unique_ptr<AbstractExpression> m_rightPointer;
    // ...
};

}  // namespace Interpreter

// Interpreter discussion:

// ONE LINE NOTE:
// -> Provide a class (with subclasses) that can be INTERPRETED differently depending on the CONTEXT.

// Intent:
// Given a language, the pattern defines a represention for its grammar along with an
// interpreter that uses the representation to interpret sentences in the language.
// The Interpreter pattern has behavioral purpose and applies to the classes.

// When to use (applicability):
// -> when the grammar is simple (in case of complex grammars, there are better alternatives)
// -> efficiency is not a critical concern

// Consequences:
// -> Its easy to change and extend the grammar.
// ---> Because the pattern uses classes to represent grammar rules, you can use inheritance to change or extend the
// grammar.
// ---> Existing expressions can be modified incrementally, and new expressions can be defined as variations on old
// ones.
// -> Implementing the grammar is easy, too
// ---> Classes defining nodes in the abstract syntax gree have similar implementations.
// ---> These classes are easy to write and often their generation can be automated with a compiler or parser generator.
// -> Complex grammars are hard to maintain
// ---> The Interpreter pattern defines at least one class for every rule in the grammar (grammar rules defined using
// BNF may require multiple classes).
// ---> Hence grammars containing many rules can mitigate the problem (see Implementation).
// ---> But when grammar is very complex, other techniques such as parser or compiler generators are more appropriate.
// -> Adding new ways to interpret expressions
// ---> The Interpreter pattern makes it easier to evaluate an expression in a new way.
// ---> For example, you can support pretty printing or type-checking an expression by defining a new operation on the
// expression classes.
// ---> If you keep creating new ways of interpreting an expression, then consider using the [Visitor] parrent to avoid
// changing the grammar classes.

// Implementation:
// -> Creating the abstract syntax tree.
// ---> The Interpreter pattern doesn't explain how to create an abstract syntax tree.
// ---> In other words, it doesn't address parsing.
// ---> The abstract syntax tree can be created by a table driven parser, by a hand crafted (usually recursive descent)
// parser or directly by the client.
// -> Defining the Interpret operation
// ---> You don't have to define the Interpret operation in the expression classes.
// ---> If its common to create a new interpreter then its better to use the [Visitor] pattern to put Interpret in a
// separate "visitor" object.
// ---> For example, a programming language will have many operations on abstract syntax trees, such as type-checking,
// optimization, code generation, and so on.
// ---> It will be more likely to use a visitor to avoid defining these operations on every grammar class.
// -> Sharing terminal symbols with the Flyweight pattern.
// ---> Grammars whose sentences contain many occurences of a terminal symbol benefit from sharing a single copy of that
// symbol.
// ---> Grammars for computer programs are good examples (each program variable will appear in many places throughout
// the code).
// ---> Terminal nodes generally don't store information about their position in the abstract syntax tree.
// -----> Parent nodes pass them whatever context they need during interpretation.
// -----> Hence there is a distinction between shared (intrinsic) state and passed-in (extrinsic) state, and the
// [Flyweight] pattern applies.

// Related Patterns
// -> [Composite]: The abstract syntax tree is an instance of the [Composite] pattern.
// -> [Flyweight] shows how to share terminal symbols within the abstract syntax tree.
// -> [Iterator]: The interpreter can use an Iterator to traverse the structure.
// -> [Visitor] can be used to maintain the behavior in each node in the abstract syntax tree in one class.
