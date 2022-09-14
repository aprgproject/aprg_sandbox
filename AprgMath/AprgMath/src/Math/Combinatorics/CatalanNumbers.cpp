#include "CatalanNumbers.hpp"

#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

UnsignedInteger getCatalanNumber(UnsignedInteger const n)
{
    // The Catalan number Cn equals the number of valid parenthesis expressions that consist of n left parentheses and n right parentheses.
    // n is the number of parentheses pairs

    // For example, C3 = 5, because we can construct the following parenthesis expressions using three left and right parentheses:
    // • ()()()
    // • (())()
    // • ()(())
    // • ((()))
    // • (()())

    // What is exactly a valid parenthesis expression? The following rules precisely define all valid parenthesis expressions:
    // • An empty parenthesis expression is valid.
    // • If an expression A is valid, then also the expression (A) is valid.
    // • If expressions A and B are valid, then also the expression AB is valid.

    // Another way to characterize valid parenthesis expressions is that if we choose any prefix of such an expression,
    // it has to contain at least as many left parentheses as right parentheses.
    // In addition, the complete expression has to contain an equal number of left and right parentheses.

    // Formula 1(recursive formula): Cn = Summation of [Ci * C(n-i-1)] from i=0 to i=n-1
    // Idea: The sum goes through the ways to divide the expression into two parts such that both parts are valid expressions
    // and the first part is as short as possible but not empty.
    // For any i, the first part contains i+1 pairs of parentheses and the number of expressions is the product of the following values:
    // • Ci: the number of ways to construct an expression using the parentheses of the first part, not counting the outermost parentheses
    // • C(n-i-1): the number of ways to construct an expression using the parentheses of the second part
    // The base case is C0 = 1, because we can construct an empty parenthesis expression using zero pairs of parentheses.
    // Note: Formula 1 might be useful in dynamic programming

    // Formula 2(combination formula): Cn = Combination(2n, n) / n+1
    // Idea: The formula can be explained as follows:
    // There are a total of (2n, n) ways to construct a (not necessarily valid) parenthesis expression that contains n left parentheses and n right parentheses.
    // Let us calculate the number of such expressions that are not valid.
    // If a parenthesis expression is not valid, it has to contain a prefix where the number of right parentheses exceeds the number of left parentheses.
    // The idea is to reverse each parenthesis that belongs to such a prefix.
    // For example, the expression ())()( contains a prefix ()), and after reversing the prefix, the expression becomes )((()(.
    // The resulting expression consists of n+1 left parentheses and n-1 right parentheses.
    // The number of such expressions is (2n, n+1), which equals the number of non-valid parenthesis expressions.
    // Thus, the number of valid parenthesis expressions can be calculated using the formula:
    // -> [number of VALID parenthesis expressions] = [number of parenthesis expressions] - [number of INVALID parenthesis expressions]
    // -> (2n, n) - (2n, n+1) = (2n, n) - (2n, n)*(n/(n+1)) = (2n, n) * (n+1-n)/(n+1) = (2n, n)/n+1

    // Formula 2 is the one implemented below:

    return getNumberOfCombinations<UnsignedInteger>(2*n, n)/(n+1);
}

UnsignedInteger getNumberOfBinaryTrees(UnsignedInteger const numberOfNodes)
{
    // Catalan numbers are also related to trees:
    // • there are Cn binary trees of n nodes
    return getCatalanNumber(numberOfNodes);
}

UnsignedInteger getNumberOfRootedTrees(UnsignedInteger const numberOfNodes)
{
    // Catalan numbers are also related to trees:
    // • there are Cn-1 rooted trees of n nodes
    return getCatalanNumber(numberOfNodes-1);
}

}

}
