#include "CommonFunctionLibrary.hpp"

#include <BooleanAlgebra/Term/Operators/TermOperators.hpp>

#include <algorithm>

namespace alba {

namespace booleanAlgebra {

// use https://en.wikipedia.org/wiki/List_of_logic_symbols

Term getNegation(Term const& term) {
    // Name: Negation
    // Symbol: '¬', '˜', '!'
    // Read as: "not"
    // Note: The statement ¬A is true if and only if A is false.

    return ~term;
}

Term getConjunction(Term const& term1, Term const& term2) {
    // Name: Logical conjunction
    // Symbol: '∧', '·', '&'
    // Read as: "and"
    // Note: Uses AND logic
    return term1 & term2;
}

Term getInclusiveDisjunction(Term const& term1, Term const& term2) {
    // Name: Logical inclusive disjunction
    // Symbol: '∨', '+', '||'
    // Read as: "or"
    // Note: Uses OR logic
    return term1 | term2;
}

Term getExclusiveDisjunction(Term const& term1, Term const& term2) {
    // Name: Exclusive disjunction
    // Symbol: '⊕', '⊻', '≢'
    // Read as: "xor", "either.... or"
    // Note: Uses XOR logic
    return (term1 & ~term2) | (~term1 & term2);  // Note this is bitwise XOR
}

Term getImplication(Term const& term1, Term const& term2) {
    // Name: Material implication
    // Symbol: '⇒', '→' '⊃'
    // Read as: "implies", "if... then"
    // Note: This is false when A is true and B is false but true otherwise.

    return ~(term1 & ~term2);
}

Term getEquivalence(Term const& term1, Term const& term2) {
    // Name: Material equivalence
    // Symbol: '⇔', '≡', '↔'
    // Read as: "if and only if", "iff", "means the same as"
    // Note: This is true if A and B are both true or both false.
    // Note: Uses XNOR logic

    return (term1 & term2) | (~term1 & ~term2);
}

Term getUniversalQuantification(Terms const& terms, UnaryBooleanFunction const& unaryBooleanFunction) {
    // Name: Universal quantification
    // Symbol: '∀', '()'
    // Read as: "for all", "for any", "for each", "for every"
    // Note: The statement: "∀ x: P(x) or (x) P(x)"
    // -> means P(x) is true for all x.
    // Note: A quantifier connects a logical expression to the elements of a set.

    return std::all_of(terms.cbegin(), terms.cend(), unaryBooleanFunction);
}

Term getExistentialQuantification(Terms const& terms, UnaryBooleanFunction const& unaryBooleanFunction) {
    // Name: Existential quantification
    // Symbol: '∃'
    // Read as: "there exists"
    // Note: The statement: "∃ x: P(x)"
    // -> means there is at least one x such that P(x) is true.
    // Note: A quantifier connects a logical expression to the elements of a set.

    return std::any_of(terms.cbegin(), terms.cend(), unaryBooleanFunction);
}

Term getUniquenessQuantification(Terms const& terms, UnaryBooleanFunction const& unaryBooleanFunction) {
    // Name: Uniqueness quantification
    // Symbol: '∃!'
    // Read as: "there exists exactly one"
    // Note: The statement: "∃! x: P(x)"
    // -> means there is exactly one x such that P(x) is true.
    // Note: A quantifier connects a logical expression to the elements of a set.

    auto it = std::find_if(terms.cbegin(), terms.cend(), unaryBooleanFunction);
    bool result(false);
    if (it != terms.cend()) {
        it++;
        result = std::none_of(it, terms.cend(), unaryBooleanFunction);
    }
    return result;
}

UnaryBooleanFunction getTautology() {
    // Name: Tautology
    // Symbol: '⊤', 'T', '1'
    // The statement ⊤ is unconditionally true.

    return [](Term const&) { return true; };
}

UnaryBooleanFunction getContradiction() {
    // Name: Contradiction
    // Symbol: '⊥', 'F', '0'
    // The statement ⊤ is unconditionally false.

    return [](Term const&) { return false; };
}

// Non codable examples:

// 1)
// Name: Definition
// Symbol: '≔', '≡', ':⇔'
// Read as: "is defined", "such that"
// Note: x ≔ y or x ≡ y means x is defined to be another name for y (but note that ≡ can also mean other things, such as
// congruence).

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

}  // namespace booleanAlgebra

}  // namespace alba
