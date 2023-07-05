#pragma once

namespace alba {

namespace algorithm {}

}  // namespace alba

// Master theorem is too hard to code.

// From AlgorithmNotes.txt

// -----> (3) Master Method:
// -------> Master Method is a direct way to get the solution.
// -------> The master method works only for the following type of recurrences or for recurrences that can be
// transformed into the following type.
// ---------> Let a >= 1 and b > 1,
// ---------> and let f(n) be a function,
// ---------> and let T(n) be defined on the non negative integers by the recurrence:
// -----------> T(n) = aT(n/b) + f(n)
// -------> There are following three cases:
// ---------> Case 1: If f(n) = O(n^c) where c < log(b)(a) then T(n) = Θ(n^(log(b)(a)))
// ---------> Case 2: If f(n) = Θ(n^c) where c = log(b)(a) then T(n) = Θ(n^c * lg(n))
// ---------> Case 3: If f(n) = Ω(n^c) where c > log(b)(a) then T(n) = Θ(f(n))
// -------> Stricter definition:
// ---------> Case 1: If f(n) = O( n^(log(b)(a)-e) ) for some constant e>0, then T(n) = Θ( n^(log(b)(a)) )
// ---------> Case 2: If f(n) = Θ( n^(log(b)(a)) ), then T(n) = Θ( n^(log(b)(a))*lg(n) )
// ---------> Case 3: If f(n) = Ω( n^(log(b)(a)+e) ) for some constant e>0
// -----------> and if a*f(n/b) <= c*f(n) for some constant c<1 and all sufficiently large n
// -----------> then T(n) = Θ(f(n))
// -------> How does this work?
// ---------> The master method is mainly derived from the recurrence tree method.
// ---------> If we draw the recurrence tree of T(n) = aT(n/b) + f(n),
// -----------> we can see that the work done at the root is f(n), and work done at all leaves is Θ(n^c) where c is
// log(b)(a).
// ---------> And the height of the recurrence tree is log(b)(n)
// -------> Master Theorem explanation
// ---------> In the recurrence tree method, we calculate the total work done.
// -----------> Case 1: The work done at leaves is polynomially more, then leaves are the dominant part, and our result
// becomes the work done at leaves.
// -----------> Case 2: The work done at leaves and root is asymptotically the same, then our result becomes height
// multiplied by work done at any level.
// -----------> Case 3: The work done at the root is asymptotically more, then our result becomes work done at the root.
// -------> Technicalities:
// ---------> In the first case, not only must f(n) be smaller than n^(log(b)(a)), it must be polynomially smaller.
// ------------> that is, f(n) must be asymptotically smaller than n^(log(b)(a)) by a factor of n^e for some constant
// e>0.
// ---------> In the third case, ont only must f(n) be larger than n^(log(b)(a)),
// ------------> it also must be polynomially larger and in addition satisfy the reularity condition that a*f(n/b) <=
// c*f(n).
// ------------> This condition is safisfied by most of the polynomially bounded functions that we shall encounter.
// -------> Notes:
// ---------> (1) Mote that thre cases do not cover all the possibilities for f(n).
// -----------> There is a gap between cases 1 and 2 when f(n) is smaller than n^(log(b)(a)) but not polynomially
// smaller.
// -----------> Similarly there is a gap between 2 and 3 when f(n) is larger than n^(log(b)(a))  but no polynomially
// larger.
// -----------> If the function f(n) falls into one of these gaps, or if the regularity condition in case 3 fails to
// hold,
// -------------> you cannot use the master theorem to solve the reccurence.
// -----------> For example, the recurrence T(n) = 2T(n/2) + n/log(n) cannot be solved using master method.
// -------------> This is gap between case 1 and 2. There is no e that can satisfies this:
// ---------------> In Case 1, If n/log(n) = O( n^(1-e) ) for some constant e>0
// ---------> (2) Case 2 can be extended for f(n) = Θ( n^c * log(k)(n) )
// -----------> If f(n) = Θ( n^c * log(k)(n) ) for some constant k >= 0 and c = log(b)(a), then T(n) = Θ( n^c *
// log(k+1)(n) )
//
// -------> Examples:
//
// ---------> Remember the form: T(n) = aT(n/b) + f(n)
//
// ---------> Example 1: Merge Sort: T(n) = 2T(n/2) + Θ(n).
// -----------> Its in case 2 because c == log(b)(a) so its 0==log(2)(2) -> 1==1.
// -----------> So T(n) = Θ( n^(log(2)(2)) * lg(n) ) = Θ(n lg(n))
//
// ---------> Example 2: Binary Search: T(n) = T(n/2) + Θ(1).
// -----------> Its in case 2 because c == log(b)(a) so its 0==log(2)(1) -> 0==0.
// -----------> So T(n) = Θ( n^(log(2)(1)) * lg(n) ) = Θ(n^0 lg(n)) = Θ(lg(n))
//
// ---------> Example 3: T(n) = 9T(n/3) + n.
// -----------> Its in case 1 because c < log(b)(a) so its 1<log(3)(9) -> 1<2.
// -----------> So T(n) = Θ( n^(log(3)(9)) )  = Θ(n^2)
//
// ---------> Example 4: T(n) = T(n*2/3) + 1.
// -----------> Its in case 2 because c == log(b)(a) so its 0==log(3/2)(1) -> 0==0.
// -----------> So T(n) = Θ(n^c * lg(n)) = Θ(n^0 * lg(n)) = Θ(lg(n))
//
// ---------> Example 5: T(n) = 3T(n/4) + n lg(n).
// -----------> Although its n lg n, we can use c==1 because its case 3 (the root is asymptotically more) and n < n
// lg(n)
// --------------> It basically satisfies this: I
// ----------------> If f(n) = Ω( n^(log(b)(a)+e) ) for some constant e>0  ->  n lg n == Ω(n^(log(4)(3)+e))  ->  can be
// satisfied with e ~ 0.2
// -----------> Its in case 3 because c > log(b)(a) so its 1>log(4)(3) -> 1>0.792.
// -----------> The regularity condition also holds:
// -------------> if a*f(n/b) <= c*f(n) for some constant c<1 and all sufficiently large n
// -------------> 3*n/4 * lg(n/4) <= c*n*lg(n), let c = 3/4 and the condition holds
// -----------> So T(n) = Θ(f(n)) = Θ(n lg(n))
//
// ---------> Example 6: T(n) = 2T(n/2) + n lg(n).
// -----------> The master method cannot be used because none of the conditions can be satisfied:
// -------------> Case 1: If f(n) = O( n^(log(b)(a)-e) ) for some constant e>0, ->  n lg n == O(n^(1-e))  ->  cannot be
// satisfied
// -------------> Case 2: If f(n) = Θ( n^(log(b)(a)) ), ->  n lg n == Θ(n^(1))  ->  cannot be satisfied
// -------------> Case 3: If f(n) = Ω( n^(log(b)(a)+e) ) for some constant e>0, ->  n lg n == Ω(n^(1+e))  ->  cannot be
// satisfied
//
// ---------> Example 7: Strassen algorithm: T(n) = 7T(n/2) + Θ(n^2).
// -----------> Its in case 1 because c < log(b)(a) so its 2<log(2)(7) -> 2<lg(7).
// -----------> So T(n) = Θ( n^(log(2)(7)) )  = Θ(n^lg(7))
