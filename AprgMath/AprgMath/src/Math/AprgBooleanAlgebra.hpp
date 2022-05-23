#pragma once

#include <algorithm>
#include <functional>
#include <vector>

namespace alba
{

namespace BooleanAlgebra
{

// use https://en.wikipedia.org/wiki/List_of_logic_symbols

template <typename DataType> using Predicate = std::function<bool(DataType const&)>;
template <typename DataType> using Container = std::vector<DataType>;

bool getNegation(bool const value)
{
    // Name: Negation
    // Symbol: '¬', '˜', '!'
    // Read as: "not"
    // Note: The statement ¬A is true if and only if A is false.

    return !value;
}

bool getConjunction(bool const value1, bool const value2)
{
    // Name: Logical conjunction
    // Symbol: '∧', '·', '&'
    // Read as: "and"
    // Note: Uses AND logic
    return value1 && value2;
}

bool getInclusiveDisjunction(bool const value1, bool const value2)
{
    // Name: Logical inclusive disjunction
    // Symbol: '∨', '+', '||'
    // Read as: "or"
    // Note: Uses OR logic
    return value1 || value2;
}

bool getExclusiveDisjunction(bool const value1, bool const value2)
{
    // Name: Exclusive disjunction
    // Symbol: '⊕', '⊻', '≢'
    // Read as: "xor", "either.... or"
    // Note: Uses XOR logic
    return value1 ^ value2; // Note this is bitwise XOR
}

bool getImplication(bool const value1, bool const value2)
{
    // Name: Material implication
    // Symbol: '⇒', '→' '⊃'
    // Read as: "implies", "if... then"
    // Note: This is false when A is true and B is false but true otherwise.

    bool result(true);
    if(value1)
    {
        result = value2;
    }
    return result;
}

bool getEquivalence(bool const value1, bool const value2)
{
    // Name: Material equivalence
    // Symbol: '⇔', '≡', '↔'
    // Read as: "if and only if", "iff", "means the same as"
    // Note: This is true if A and B are both true or both false.

    return value1==value2;
}

template<typename DataType>
bool getUniversalQuantification(Container<DataType> const& elements, Predicate<DataType> const& predicate)
{
    // Name: Universal quantification
    // Symbol: '∀', '()'
    // Read as: "for all", "for any", "for each", "for every"
    // Note: The statement: "∀ x: P(x) or (x) P(x)"
    // -> means P(x) is true for all x.
    // Note: A quantifier connects a logical expression to the elements of a set.

    return std::all_of(elements.cbegin(), elements.cend(), predicate);
}

template<typename DataType>
bool getExistentialQuantification(Container<DataType> const& elements, Predicate<DataType> const& predicate)
{
    // Name: Existential quantification
    // Symbol: '∃'
    // Read as: "there exists"
    // Note: The statement: "∃ x: P(x)"
    // -> means there is at least one x such that P(x) is true.
    // Note: A quantifier connects a logical expression to the elements of a set.

    return std::any_of(elements.cbegin(), elements.cend(), predicate);
}

template<typename DataType>
bool getUniquenessQuantification(Container<DataType> const& elements, Predicate<DataType> const& predicate)
{
    // Name: Uniqueness quantification
    // Symbol: '∃!'
    // Read as: "there exists exactly one"
    // Note: The statement: "∃! x: P(x)"
    // -> means there is exactly one x such that P(x) is true.
    // Note: A quantifier connects a logical expression to the elements of a set.

    auto it = std::find_if(elements.cbegin(), elements.cend(), predicate);
    bool result(false);
    if(it != elements.cend())
    {
        it++;
        result = std::none_of(it, elements.cend(), predicate);
    }
    return result;
}

template<typename DataType>
Predicate<DataType> getTautology()
{
    // Name: Tautology
    // Symbol: '⊤', 'T', '1'
    // The statement ⊤ is unconditionally true.

    return [](DataType const&)
    {
        return true;
    };
}

template<typename DataType>
Predicate<DataType> getContradiction()
{
    // Name: Contradiction
    // Symbol: '⊥', 'F', '0'
    // The statement ⊤ is unconditionally false.

    return [](DataType const&)
    {
        return false;
    };
}

// Non codable examples:

// 1)
// Name: Definition
// Symbol: '≔', '≡', ':⇔'
// Read as: "is defined", "such that"
// Note: x ≔ y or x ≡ y means x is defined to be another name for y (but note that ≡ can also mean other things, such as congruence).

// 2)
// Name: Precedence Grouping
// Symbol: ( )
// Read as: "parentheses", "brackets"
// Note: Perform the operations inside the parentheses first.

// 3)
// Name: Turnstile
// Symbol: ⊢
// Read as: "proves"
// Note: x ⊢ y means x proves (syntactically entails) y

// 4)
// Name: Double turnstile
// Symbol: ⊨
// Read as: "models"
// Note: x ⊨ y means x models (semantically entails) y


}

}
