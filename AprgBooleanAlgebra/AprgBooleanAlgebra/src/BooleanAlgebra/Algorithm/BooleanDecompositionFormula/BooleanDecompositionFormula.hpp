// -> THEOREM. If f(x, y, z) is a Boolean function of three variables, 
// ---> then it can be decomposed into the form g(x, y) ^ zh(x, y), 
// ---> where g and h are Boolean functions of two variables.
// 
// -> Proof [Ditlow]. f(x, y, z) can be expressed as a sum of minterms, 
// ---> and then and z can be factored out of their terms, giving
// -----> f(x, y, z) = z'&f0(x, y) + z&f1(x, y)
// -> Because the operands to “+” cannot both be 1, the "or" can be replaced with "exclusive or", giving
// -----> f(x, y, z) = z'&f0(x, y) ^ z&f1(x, y)
// -----> f(x, y, z) = (1^z)&f0(x, y) ^ z&f1(x, y)
// -----> f(x, y, z) = f0(x, y) ^ z&f0(x, y) ^ z&f1(x, y)
// -----> f(x, y, z) = f0(x, y) ^ z&(f0(x, y) ^ f1(x, y))
// ---> where we have twice used the identity (a^b) & c = ac ^ bc.
// -> This is in the required form with g(x, y) = f0(x, y) and h(x, y) = f0(x, y) ^ f1(x, y). 
// ---> f0(x, y), incidentally, is f(x, y, z) with z = 0, and f1(x, y) is f(x, y, z) with z = 1.
// 
// -> COROLLARY. If a computer’s instruction set includes an instruction for each of the 16 Boolean functions of two variables, 
// ---> then any Boolean function of three variables can be implemented with FOUR (or fewer) instructions.
// -> One instruction implements g(x, y), another implements h(x, y), and these are combined with "and" and "exclusive or".
// 
// -> Example: Consider the Boolean function that is 1 if exactly two of x, y, and z are 1:
// ---> f(x, y, z) = xyz' + xy'z + x'yz
// -> Before proceeding, the interested reader might like to try to implement f with four instructions, without using the theorem.
// ---> From the proof of the theorem:
// -----> f(x, y, z) = z'&f0(x, y) + z&f1(x, y)
// ---> So from the example:
// -----> f(x, y, z) = xyz' + (xy' + x'y)z
// -----> f0(x, y) = xy
// -----> f1(x, y) = xy' + x'y
// -----> f(x, y, z) = f0(x, y)&z' + f1(x, y)&z
// ---> At the end of the proof:
// -----> f(x, y, z) = f0(x, y) ^ z&(f0(x, y) ^ f1(x, y))
// -----> f(x, y, z) = xy ^ z&(xy ^ (xy' + x'y))
// ---> Using the truth table this reduces to: xy ^ (xy' + x'y):  x+y
// -----> f(x, y, z) = xy ^ z(x+y)
