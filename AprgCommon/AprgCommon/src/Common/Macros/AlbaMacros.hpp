// Source(for a lot more macros): https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-160

// Standard predefined macros
// NOTE: BEWARE, if this are used in inlined stuffs, this results in ODR violations.
#define ALBA_MACROS_GET_FILE __FILE__
#define ALBA_MACROS_GET_LINE __LINE__
#define ALBA_MACROS_GET_COMPILATION_DATE __DATE__
#define ALBA_MACROS_GET_TIME_OF_TRANSLATION __TIME__
#define ALBA_MACROS_GET_COMPILER_VERSION __cplusplus
// Note: You can use the compilation date as some sort of version control to display when it was compiled.

// Compiler specific predefined macros
// NOTE: BEWARE, if this are used in inlined stuffs, this results in ODR violations.
#define ALBA_MACROS_GET_FUNCTION __FUNCTION__
#define ALBA_MACROS_GET_UNIQUE_COUNTER_VALUE __COUNTER__
// PRETTY_FUNCTION: Same with __FUNCTION_ and includes signature (with template information) as well
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#define ALBA_MACROS_GET_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define ALBA_MACROS_GET_PRETTY_FUNCTION __FUNCSIG__
#else
#define ALBA_MACROS_GET_PRETTY_FUNCTION __FUNCTION__
#endif

// Macro operations
#define ALBA_MACROS_GET_STRING_LITERAL(parameter) #parameter  // The number-sign or "stringizing" operator.
// #define ALBA_MACROS_GET_CHAR_LITERAL(x) #@x // The charizing operator. Its not supported.
// #define ALBA_MACROS_GET_AS_A_TOKEN(parameter) ##parameter //The double-number-sign or token-pasting operator (##).
// Note:
// The token-pasting operator(## operator), is a preprocessor operator in C++ that is used to concatenate two tokens.
// Tokens are individual words or symbols in a C++ program.
// The token-pasting operator can be used to do a variety of things, including:
// 1) Concatenating two identifiers to form a new identifier.
// For example, the expression ##foo##bar would expand to the identifier foobar.
// 2) Concatenating a string literal and an identifier to form a new string literal.
// For example, the expression "hello" ## "world" would expand to the string literal helloworld.
// 3) Concatenating two macro definitions to form a new macro definition.
// For example, the macro definition #define FOO bar and the macro definition
// #define BAR baz could be concatenated to form the macro definition #define FOOBAR barbaz.

// #pragma message macros
#define ALBA_MACROS_VALUE_FOR_PRAGMA_MESSAGE(parameter) ALBA_MACROS_GET_STRING_LITERAL(parameter)#define ALBA_MACROS_PARAMETER_FOR_PRAGMA_MESSAGE(var) #var "=" ALBA_MACROS_VALUE_FOR_PRAGMA_MESSAGE(var)

// Switch case macros
#define ALBA_MACROS_CASE_ENUM_STRING(parameter) \    case parameter:                             \
        return ALBA_MACROS_GET_STRING_LITERAL(parameter);

#define ALBA_MACROS_CASE_ENUM_SHORT_STRING(parameter, shortName) \
    case parameter:                                              \
        return shortName;

// Concatenate macros
#define ALBA_MACROS_CONCATENATE_EXPANSION(first, second) first##second
#define ALBA_MACROS_CONCATENATE(first, second) \
    ALBA_MACROS_CONCATENATE_EXPANSION(         \
        first, second)  // another layer of indirection to expand arguments (example: __COUNTER__)

// Anonymous variable
#define ALBA_MACROS_GET_NAME_WITH_COUNT(prefixOfName) ALBA_MACROS_CONCATENATE(prefixOfName, __COUNTER__)

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
// This works for Clang and GCC only.
// The MSVC (Microsoft Visual C++) compiler has a limitation when it comes to processing preprocessor macros with a
// series of arguments separately. This limitation is due to the way the MSVC compiler handles macro expansion. In the
// C/C++ preprocessor, macros can accept multiple arguments, and each argument can be expanded separately before being
// substituted into the macro body. This is known as argument prescan. It allows macros to work with complex expressions
// and perform operations on individual arguments. However, the MSVC compiler does not perform argument prescan for
// macros by default. Instead, it performs macro expansion in a single pass, treating the entire argument list as a
// single token. This means that the macro body is expanded with the entire series of arguments as a single unit,
// without any separation between the individual arguments.

// Count arguments macros
#define ALBA_MACROS_COUNT_ARGUMENTS(...) \
    ALBA_MACROS_COUNT_ARGUMENTS_EXPANSION(__VA_ARGS__, ALBA_MACROS_COUNT_IN_REVERSE_SEQUENCE())#define ALBA_MACROS_COUNT_ARGUMENTS_EXPANSION(...) ALBA_MACROS_GET_COUNT_BASED_FROM_PLACEMENT(__VA_ARGS__)
#define ALBA_MACROS_GET_COUNT_BASED_FROM_PLACEMENT(                                                                    \
    p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,     \
    p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, p47, \    p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59, p60, p61, p62, p63, N, ...)                            \
    N
#define ALBA_MACROS_COUNT_IN_REVERSE_SEQUENCE()                                                                       \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36,   \
        35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, \
        7, 6, 5, 4, 3, 2, 1, 0
#endif