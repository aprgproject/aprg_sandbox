
// Source: https://en.cppreference.com/w/cpp/types/size_t
// Construct: std::size_t
// 
// std::size_t is the unsigned integer type of the result of the sizeof operator as well as the sizeof... operator and the alignof operator (since C++11).
// 
// Notes:
// -> std::size_t can store the maximum size of a theoretically possible object of any type (including array).
// -> A type whose size cannot be represented by std::size_t is ill-formed (since C++14) 
// -> On many platforms (an exception is systems with segmented addressing) std::size_t can safely store the value of any non-member pointer, in which case it is synonymous with std::uintptr_t.
// -> 
// -> std::size_t is commonly used for array indexing and loop counting. 
// -> Programs that use other types, such as unsigned int, for array indexing may fail on, e.g. 64-bit systems when the index exceeds UINT_MAX or if it relies on 32-bit modular arithmetic.
// -> When indexing C++ containers, such as std::string, std::vector, etc, the appropriate type is the member typedef size_type provided by such containers. It is usually defined as a synonym for std::size_t.
// 
// Example:
// -> int main()
// -> {
// ->     std::array<std::size_t,10> a;
// ->     std::size_t i{};
// ->  
// ->     for (i = 0; i != a.size(); ++i)
// ->         std::cout << (a[i] = i) << ' ';
// ->     std::cout << "│ i = " << i << '\n';
// ->  
// ->     for (i = a.size()-1; i < a.size(); --i)
// ->         std::cout << a[i] << ' ';
// ->     std::cout << "│ i = " << i << '\n';
// -> }




// Source: https://en.cppreference.com/w/cpp/types/offsetof
// Construct: offsetof
// 
// The macro offsetof expands to an integral constant expression of type std::size_t, the value of which is the offset, in bytes, 
// from the beginning of an object of specified type to its specified subobject, including padding if any.
// Given an object o of type type and static storage duration, o.member shall be an lvalue constant expression that refers to a subobject of o. 
// Otherwise, the behavior is undefined. 
// Particularly, if member is a static data member, a bit-field, or a member function, the behavior is undefined.
// If type is not a PODType (until C++11)standard layout type (since C++11), the behavior is undefined (until C++17) use of the offsetof macro is conditionally-supported (since C++17).
// The expression offsetof(type, member) is never type-dependent and it is value-dependent if and only if type is dependent.
// 
// Example:
// -> #include <iostream>
// -> #include <cstddef>
// -> struct S {
// ->     char   m0;
// ->     double m1;
// ->     short  m2;
// ->     char   m3;
// -> //  private: int z; // warning: 'S' is a non-standard-layout type
// -> };
// -> int main()
// -> {
// ->     std::cout
// ->         << "offset of char   m0 = " << offsetof(S, m0) << '\n'
// ->         << "offset of double m1 = " << offsetof(S, m1) << '\n'
// ->         << "offset of short  m2 = " << offsetof(S, m2) << '\n'
// ->         << "offset of char   m3 = " << offsetof(S, m3) << '\n';
// -> }




// Source: https://en.cppreference.com/w/cpp/language/alignas
// Construct: alignas
// 
// alignas specifier (since C++11)
// 
// Specifies the alignment requirement of a type or an object.
// 
// Syntax:
// alignas( expression ) 		
// alignas( type-id ) 		
// alignas( pack ... ) 		
// 1) alignas(expression) must be an integral constant expression that evaluates to zero, or to a valid value for an alignment or extended alignment.
// 2) Equivalent to alignas(alignof(type))
// 3) Equivalent to multiple alignas specifiers applied to the same declaration, one for each member of the parameter pack, which can be either type or non-type parameter pack.
// 
// Explanation:
// The alignas specifier may be applied to:
// 
//     the declaration or definition of a class/struct/union or enumeration;
//     the declaration of a non-bitfield class data member;
//     the declaration of a variable, except that it cannot be applied to the following:
//         a function parameter;
//         the exception parameter of a catch clause. 
// 
// The object or the type declared by such a declaration will have its alignment requirement equal to the strictest (largest) non-zero expression
// of all alignas specifiers used in the declaration, unless it would weaken the natural alignment of the type.
// 
// If the strictest (largest) alignas on a declaration is weaker than the alignment it would have without any alignas specifiers 
// (that is, weaker than its natural alignment or weaker than alignas on another declaration of the same object or type), the program is ill-formed:
// 
// struct alignas(8) S {};
// struct alignas(1) U { S s; }; // error: alignment of U would have been 8 without alignas(1)
// 
// Invalid non-zero alignments, such as alignas(3) are ill-formed.
// 
// Valid non-zero alignments that are weaker than another alignas on the same declaration are ignored.
// 
// alignas(0) is always ignored. 
// 
// Example:
// -> // every object of type struct_float will be aligned to alignof(float) boundary
// -> // (usually 4):
// -> struct alignas(float) struct_float
// -> {
// ->     // your definition here
// -> };
// ->  
// -> // every object of type sse_t will be aligned to 32-byte boundary:
// -> struct alignas(32) sse_t
// -> {
// ->     float sse_data[4];
// -> };
// ->  
// -> // the array "cacheline" will be aligned to 64-byte boundary:
// -> alignas(64) char cacheline[64];
// ->  
// ->  
// -> #include <iostream>
// -> int main()
// -> {
// ->     struct default_aligned { float data[4]; } a, b, c;
// ->     sse_t x, y, z;
// ->  
// ->     std::cout
// ->         << "alignof(struct_float) = " << alignof(struct_float) << '\n'
// ->         << "sizeof(sse_t) = " << sizeof(sse_t) << '\n'
// ->         << "alignof(sse_t) = " << alignof(sse_t) << '\n'
// ->         << "alignof(cacheline) = " << alignof(alignas(64) char[64]) << '\n'
// ->         << std::hex << std::showbase
// ->         << "&a: " << &a << '\n'
// ->         << "&b: " << &b << '\n'
// ->         << "&c: " << &c << '\n'
// ->         << "&x: " << &x << '\n'
// ->         << "&y: " << &y << '\n'
// ->         << "&z: " << &z << '\n';
// -> }




// Source: https://en.cppreference.com/w/cpp/language/alignof
// Construct: alignof
// 
// alignof operator (since C++11)
// Queries alignment requirements of a type
//
// Syntax:
// alignof( type-id ) 	
// Returns a value of type std::size_t.
// 
// Explanation:
// Returns the alignment, in bytes, required for any instance of the type indicated by type-id, which is either complete object type, an array type whose element type is complete, or a reference type to one of those types.
// 
// If the type is reference type, the operator returns the alignment of referenced type; if the type is array type, alignment requirement of the element type is returned. 
// 
// Example:
// -> #include <iostream>
// ->  
// -> struct Foo {
// ->     int   i;
// ->     float f;
// ->     char  c;
// -> };
// ->  
// -> // Note: `alignas(alignof(long double))` below can be simplified to simply 
// -> // `alignas(long double)` if desired.
// -> struct alignas(alignof(long double)) Foo2 {
// ->     // put your definition here
// -> }; 
// ->  
// -> struct Empty {};
// ->  
// -> struct alignas(64) Empty64 {};
// ->  
// -> int main()
// -> {
// ->     std::cout << "Alignment of"  "\n"
// ->         "- char             : " << alignof(char)    << "\n"
// ->         "- pointer          : " << alignof(int*)    << "\n"
// ->         "- class Foo        : " << alignof(Foo)     << "\n"
// ->         "- class Foo2       : " << alignof(Foo2)    << "\n"
// ->         "- empty class      : " << alignof(Empty)   << "\n"
// ->         "- alignas(64) Empty: " << alignof(Empty64) << "\n";
// -> }




// Source: https://en.cppreference.com/w/cpp/types/alignment_of
// Construct: alignment_of
// 
// std::alignment_of
// 		
// template< class T >
// struct alignment_of;
// 		(since C++11)
// 
// Provides the member constant value equal to the alignment requirement of the type T, as if obtained by an alignof expression. 
// If T is an array type, returns the alignment requirements of the element type. 
// If T is a reference type, returns the alignment requirements of the type referred to.
// 
// If alignof(T) is not a valid expression, the behavior is undefined.
// 
// The behavior of a program that adds specializations for alignment_of or alignment_of_v (since C++17) is undefined. 
// 
// Example:
// -> #include <cstdint>
// -> #include <iostream>
// -> #include <type_traits>
// ->  
// -> struct A {};
// -> struct B {
// ->     std::int8_t p;
// ->     std::int16_t q;
// -> };
// ->  
// -> int main()
// -> {
// ->     std::cout << std::alignment_of<A>::value << ' ';
// ->     std::cout << std::alignment_of<B>::value << ' ';
// ->     std::cout << std::alignment_of<int>() << ' '; // alt syntax
// ->     std::cout << std::alignment_of_v<double> << '\n'; // c++17 alt syntax
// -> }


