#pragma once

namespace alba {

namespace algorithm {}

}  // namespace alba

// From AlgorithmNotes.txt

// -> Asymptotic Analysis
//
// ---> NOTE: The CLRS book restricts the definitions of functions to be asymptotically non negative, other books just
// use limits on their definitions.
//
// ---> (1) Θ Notation (BIG THETA Notation):// -----> This is for an ASYMPTOTIC TIGHT BOUND.
// -----> Theta notation encloses the function from above and below ("sandwiched").
// -----> This is used for analyzing the GENERAL-CASE (not neccessarily average) complexity of an algorithm.
// -----> Formal definition:// -------> Let g and f be the function from the set of natural numbers to itself.
// -------> The function f is said to be Θ(g), if THERE ARE constants c1,c2>0 and n0>0 such that c1*g(n) ≤ f(n) ≤
// c2*g(n) for all n ≥ n0
// -----> Mathematical Representation:
// -------> Θ(g(n)) = {f(n): THERE EXIST positive constants c1, c2 and n0 such that 0 ≤ c1*g(n) ≤ f(n) ≤ c2*g(n) for all
// n ≥ n0}
// -------> Note: Θ(g) is a set of functions
//
// ---> (2) O Notation (Big Oh Notation):
// -----> This is for an ASYMPTOTIC UPPER BOUND.
// -----> This represents the UPPER BOUND of the running time of an algorithm.
// -----> This is used for the WORST-CASE complexity of an algorithm.
// -----> Formal definition:
// -------> Let g and f be the function from the set of natural numbers to itself.
// -------> The function f is said to be O(g), if THERE ARE constants c>0 and n0>0 such that f(n) ≤ c*g(n) for all n ≥
// n0
// -----> Mathematical Representation:
// -------> O(g(n)) = { f(n): THERE EXIST positive constants c and n0 such that 0 ≤ f(n) ≤ cg(n) for all n ≥ n0 }
//
// ---> (3) Ω Notation (Big Omega Notation):
// -----> This is for an ASYMPTOTIC LOWER BOUND.
// -----> This represents the LOWER BOUND of the running time of an algorithm.
// -----> This is used for the BEST-CASE complexity of an algorithm.
// -----> Formal definition:
// -------> Let g and f be the function from the set of natural numbers to itself.
// -------> The function f is said to be Ω(g), if THERE ARE constants c>0 and n0>0 such that c*g(n) ≤ f(n) for all n ≥
// n0
// -----> Mathematical Representation:
// -------> Ω(g(n)) = { f(n): THERE EXIST positive constants c and n0 such that 0 ≤ cg(n) ≤ f(n) for all n ≥ n0 }
// -------> Note: Θ(g) is a set of functions
//
// ---> (4) o Notation (Small Oh Notation):
// -----> This is for an ASYMPTOTIC UPPER BOUND.
// -----> It also means that its NOT ASYMTOTICALLY TIGHT.
// -----> It also means that its "DOMINATED". (for example f(n) = o(g(n)): f is dominated by g asymptotically).
// -----> This represents the UPPER BOUND of the running time of an algorithm.
// -----> This is used for the WORST-CASE complexity of an algorithm.
// -----> Formal definition:
// -------> Let g and f be the function from the set of natural numbers to itself.
// -------> The function f is said to be o(g), if ANY constant c>0, THERE EXISTS n0>0 such that f(n) < c*g(n) for all n
// ≥ n0
// -----> Mathematical Representation:
// -------> o(g(n)) = { f(n): FOR ANY positive constant c>0, THERE EXISTS a constant n0>0 such that 0 ≤ f(n) < cg(n) for
// all n ≥ n0 }
//
// ---> (3) ω Notation (Small Omega Notation):
// -----> This is for an ASYMPTOTIC LOWER BOUND.
// -----> It also means that its NOT ASYMTOTICALLY TIGHT.
// -----> It also means that it "DOMINATES". (for example f(n) = ω(g(n)): f dominates g asymptotically).
// -----> This represents the LOWER BOUND of the running time of an algorithm.
// -----> This is used for the BEST-CASE complexity of an algorithm.
// -----> Formal definition:
// -------> Let g and f be the function from the set of natural numbers to itself.
// -------> The function f is said to be ω(g), if ANY constant c>0, THERE EXISTS n0>0 such that c*g(n) < f(n) for all n
// ≥ n0
// -----> Mathematical Representation:
// -------> ω(g(n)) = { f(n): FOR ANY positive constant c>0, THERE EXISTS a constant n0>0 such that 0 ≤ c*g(n) < f(n)
// for all n ≥ n0 }
//
// ---> Family of Bachmann–Landau notations
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |  Notation        |  Name                        |  Description |  Formal definition |  Limit definition |
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |  f(n) = o(g(n))  |  Small O; Small Oh           |  f is dominated by g asymptotically |  V k>0 E n0 V n>n0 : |f(n)|
// < k*g(n)                    |  lim n→∞ |f(n)| / g(n) = 0                          | |  f(n) = O(g(n))  |  Big O; Big
// Oh; Big Omicron  |  |f| is bounded above by g (up to constant factor) asymptotically  |  E k>0 E n0 V n>n0 : |f(n)| ≤
// k*g(n)                    |  lim sup n→∞ |f(n)| / g(n) < ∞                      | |  f(n) = Θ(g(n))  |  Big Theta |
// f is bounded both above and below by g asymptotically             |  E k1>0 E k2>0 E n0 V n>n0: k1*g(n) ≤ |f(n)| ≤
// k2*g(n)  |  f(n) = O(g(n)) and f(n) = Ω(g(n)) (Knuth version)  | |  f(n) ~ g(n)     |  On the order of             |
// f is equal to g asymptotically                                    |  V ε>0 E n0 V n>n0 : |(f(n)/g(n))−1| < ε |  lim
// n→∞ f(n) / g(n) = 1                            | |  f(n) = Ω(g(n))  |  Big Omega (Knuth)           |  f is bounded
// below by g asymptotically                            |  E k>0 E n0 V n>n0 : |f(n)| ≥ k*g(n)                    |
// lim inf n→∞ |f(n)| / g(n) > 0                      | |  f(n) = ω(g(n))  |  Small Omega                 |  f dominates
// g asymptotically                                      |  V k>0 E n0 V n>n0 : |f(n)| > k*g(n)                    | lim
// n→∞ |f(n)| / g(n) = ∞                          | |  f(n) = Ω(g(n))  |  Big Omega (number theory)   |  |f| is not
// dominated by g asymptotically                          |  E k>0 V n0 E n>n0 : |f(n)| ≥ k*g(n)                    |
// lim sup n→∞ |f(n)| / g(n) > 0                      |
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// -----> Note: 'V' is acutally '∀' which means "any" or "for all"
// -----> Note: 'E' is acutally '∃' which means "there exists" or "there is at least one" or "for some"
// -----> The limit definitions assume g(n)>0 for sufficiently large n.
// -------> The table is (partly) sorted from smallest to largest, in the sense that o , O , Θ , ~ , (Knuth's version
// of) Ω , ω on functions
// -------> correspond to < , ≤ , ≈ , = ,  ≥ , >  on the real line (the Hardy-Littlewood version of Ω , however, doesn't
// correspond to any such description).
// -----> Computer science uses the big O , big Theta Θ , little o , little omega ω and Knuth's big Omega Ω notations.
// -------> Analytic number theory often uses the big O, small o, Hardy–Littlewood's big Omega Ω (with or without the +,
// − or ± subscripts) and ~ notations.
// -------> The small omega ω notation is not used as often in analysis.
//
// ---> Properties of Asymptotic Notations:
//
// -----> (1) General Properties:
// -------> If f(n) is O(g(n)) then a*f(n) is also O(g(n)), where a is a constant.
// -------> If f(n) is Θ(g(n)) then a*f(n) is also Θ(g(n)), where a is a constant.
// -------> If f(n) is Ω(g(n)) then a*f(n) is also Ω(g(n)), where a is a constant.
// -------> If f(n) is o(g(n)) then a*f(n) is also o(g(n)), where a is a constant.
// -------> If f(n) is ω(g(n)) then a*f(n) is also ω(g(n)), where a is a constant.
// -------> Example:
// ---------> f(n) = 2n²+5 is O(n²)
// ---------> then, 7*f(n) = 7(2n²+5) = 14n²+35 is also O(n²).
//
// -----> (2) Transitive Properties:
// -------> If f(n) is O(g(n)) and g(n) is O(h(n)) then f(n) = O(h(n)).
// -------> If f(n) is Θ(g(n)) and g(n) is Θ(h(n)) then f(n) = Θ(h(n)).
// -------> If f(n) is Ω(g(n)) and g(n) is Ω(h(n)) then f(n) = Ω(h(n)).
// -------> If f(n) is o(g(n)) and g(n) is o(h(n)) then f(n) = o(h(n)).
// -------> If f(n) is ω(g(n)) and g(n) is ω(h(n)) then f(n) = ω(h(n)).
// -------> Example:
// ---------> If f(n) = n, g(n) = n² and h(n)=n³
// ---------> n is O(n²) and n² is O(n³) then, n is O(n³)
//
// -----> (3) Reflexive Properties:
// -------> If f(n) is given then f(n) is O(f(n)).
// -------> If f(n) is given then f(n) is Θ(f(n)).
// -------> If f(n) is given then f(n) is Ω(f(n)).
// -------> Example:
// ---------> f(n) = n² ; O(n²) i.e O(f(n))
//
// -----> (4) Symmetric Properties:
// -------> f(n) is Θ(g(n)) if and only if g(n) is Θ(f(n)).
// -------> This property is only satisfied on the Θ notation.
// -------> Example:
// ---------> If f(n) = n² and g(n) = n²
// ---------> then, f(n) = Θ(n²) and g(n) = Θ(n²)
//
// -----> (5) Transpose Symmetric Properties:
// -------> If f(n) is O(g(n)) then g(n) is Ω(f(n)).
// -------> If f(n) is o(g(n)) then g(n) is ω(f(n)).
// -------> Example:
// ---------> If f(n) = n , g(n) = n²
// ---------> then n is O(n²) and n² is Ω(n)
//
// -------> (6) Some More Properties:
// ---------> 1) If f(n) = O(g(n)) and f(n) = Ω(g(n)) then f(n) = Θ(g(n))
// ---------> 2) If f(n) = O(g(n)) and d(n) = O(e(n))
// ---------> then f(n) + d(n) = O(max(g(n), e(n)))
// ---------> Example:
// -----------> f(n) = n i.e O(n)
// -----------> d(n) = n² i.e O(n²)
// -----------> then f(n) + d(n) = n + n² i.e O(n²)
// ---------> 3) If f(n)=O(g(n)) and d(n)=O(e(n))
// ---------> then f(n) * d(n) = O( g(n) * e(n) )
// ---------> Example:
// -----------> f(n) = n i.e O(n)
// -----------> d(n) = n² i.e O(n²)
// -----------> then f(n) * d(n) = n * n² = n³ i.e O(n³)
// -----------> Note: If  f(n) = O(g(n)) then g(n) = Ω(f(n))
//
// ---> Matters of notation
//
// -----> Equals sign
// -------> The statement "f(x) is O(g(x))" as defined above is usually written as f(x) = O(g(x)). Some consider this to
// be an abuse of notation,
// ---------> since the use of the equals sign could be misleading as it suggests a symmetry that this statement does
// not have.
// ---------> As de Bruijn says, O(x) = O(x2) is true but O(x2) = O(x) is not.[9] Knuth describes such statements as
// "one-way equalities", since if the sides could be reversed,
// ---------> "we could deduce ridiculous things like n = n2 from the identities n = O(n2) and n2 = O(n2)."
// ---------> In another letter, Knuth also pointed out that "the equality sign is not symmetric with respect to such
// notations", as, in this notation,
// ---------> "mathematicians customarily use the = sign as they use the word "is" in English: Aristotle is a man, but a
// man isn't necessarily Aristotle".
// -------> For these reasons, it would be more precise to use set notation and write f(x) ∈ O(g(x)) (read as: "f(x) is
// an element of O(g(x))", or "f(x) is in the set O(g(x))"),
// ---------> thinking of O(g(x)) as the class of all functions h(x) such that |h(x)| ≤ C|g(x)| for some constant C.
// ---------> However, the use of the equals sign is customary.
// -----> Other arithmetic operators
// -------> Big O notation can also be used in conjunction with other arithmetic operators in more complicated
// equations.
// ---------> For example, h(x) + O(f(x)) denotes the collection of functions having the growth of h(x) plus a part
// whose growth is limited to that of f(x). Thus,
// -----------> g(x)=h(x)+O(f(x))
// ---------> expresses the same as
// -----------> g(x)-h(x)=O(f(x))
// -------> Example
// ---------> Suppose an algorithm is being developed to operate on a set of n elements.
// -----------> Its developers are interested in finding a function T(n) that will express how long the algorithm will
// take to run (in some arbitrary measurement of time) in terms of the number of elements in the input set.
// -----------> The algorithm works by first calling a subroutine to sort the elements in the set and then perform its
// own operations.
// -----------> The sort has a known time complexity of O(n2), and after the subroutine runs the algorithm must take an
// additional 55n3 + 2n + 10 steps before it terminates.
// -----------> Thus the overall time complexity of the algorithm can be expressed as T(n) = 55n3 + O(n2). Here the
// terms 2n + 10 are subsumed within the faster-growing O(n2).
// -----------> Again, this usage disregards some of the formal meaning of the "=" symbol, but it does allow one to use
// the big O notation as a kind of convenient placeholder.
// -----> Multiple uses
// -------> In more complicated usage, O(...) can appear in different places in an equation, even several times on each
// side.
// ---------> For example, the following are true for n → ∞ :
// -----------> (n+1)^2 = n^2 + O(n)
// -----------> (n + O(n^(1/2))) * (n + O(log ⁡ n))^2 = n^3 + O(n^(5/2))
// -----------> n^O(1) = O(e^n)
// -------> The meaning of such statements is as follows: for any functions which satisfy each O(·) on the left side,
// ---------> there are some functions satisfying each O(·) on the right side,
// ---------> such that substituting all these functions into the equation makes the two sides equal.
// ---------> For example, the third equation above means: "For any function f(n) = O(1), there is some function g(n) =
// O(en) such that nf(n) = g(n)."
// ---------> In terms of the "set notation" above, the meaning is that the class of functions represented by the left
// side is a subset of the class of functions represented by the right side.
// ---------> In this use the "=" is a formal symbol that unlike the usual use of "=" is not a symmetric relation.
// ---------> Thus for example nO(1) = O(en) does not imply the false statement O(en) = nO(1).
//
// ---> Orders of common functions
//
// -----> Here is a list of classes of functions that are commonly encountered when analyzing the running time of an
// algorithm.
// -------> In each case, c is a positive constant and n increases without bound. The slower-growing functions are
// generally listed first.
// -----------------------------------------------------------------------------------------------
// |  Notation                |  Name                                  |  Example
// -----------------------------------------------------------------------------------------------
// |  O(1)                    |  constant                              |  Determining if a binary number is even or odd;
// Calculating (-1)^n; Using a constant-size lookup table |  O(log log n)            |  double logarithmic |  Average
// number of comparisons spent finding an item using interpolation search in a sorted array of uniformly distributed
// values |  O(log ⁡ n)                |  logarithmic                           |  Finding an item in a sorted array
// with a binary search or a balanced search tree as well as all operations in a binomial heap |  O((log n)^c) and c>1
// |  polylogarithmic                       |  Matrix chain ordering can be solved in polylogarithmic time on a parallel
// random-access machine. |  O(n^c) and 0 < c < 1    |  fractional power                      |  Searching in a kd tree
// |  O(n)                    |  linear                                |  Finding an item in an unsorted list or in an
// unsorted array; adding two n-bit integers by ripple carry |  O(n * log ^{*}n)}       |  n log-star n |  Performing
// triangulation of a simple polygon using Seidel's algorithm, or the union–find algorithm. |  O(n log n) = O(log ⁡
// n!)  |  linearithmic, loglinear, quasilinear  |  Performing a fast Fourier transform; fastest possible comparison
// sort; heapsort and merge sort |  O(n^2)                  |  quadratic                             |  Multiplying two
// n-digit numbers by schoolbook multiplication; simple sorting algorithms, such as bubble sort, selection sort and
// insertion sort; |  O(n^c) and c>1          |  polynomial or algebraic               |  Tree-adjoining grammar
// parsing; maximum matching for bipartite graphs; finding the determinant with LU decomposition |  Ln[α,c] and 0<α<1 |
// L-notation or sub-exponential         |  Factoring a number using the quadratic sieve or number field sieve |  O(c^n)
// and c > 1        |  exponential                           |  Finding the (exact) solution to the travelling salesman
// problem using dynamic programming; determining if two logical statements are equivalent using brute-force search |
// O(n!)                   |  factorial                             |  Solving the travelling salesman problem via
// brute-force search; finding the determinant with Laplace expansion; enumerating all partitions of a set
// -----------------------------------------------------------------------------------------------
// -----> Note that log*⁡ (n) = {0, if n ≤ 1, and 1+log*⁡ (log n) if n>1}
// -----> The statement f(n)=O(n!) is sometimes weakened to f(n)=O(n^n) to derive simpler formulas for asymptotic
// complexity.
// -------> For any k>0 and c>0, O(n^c*(log ⁡ n)^k) is a subset of O(n^(c + ε)) for any ε > 0, so may be considered
// as a polynomial with some bigger order.
