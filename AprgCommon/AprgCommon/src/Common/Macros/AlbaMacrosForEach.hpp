// Inspired by: https://github.com/swansontec/map-macro/blob/master/map.h

#define ALBA_MACROS_FOR_EACH_EVAL0(...) __VA_ARGS__
#define ALBA_MACROS_FOR_EACH_EVAL1(...) ALBA_MACROS_FOR_EACH_EVAL0(ALBA_MACROS_FOR_EACH_EVAL0(ALBA_MACROS_FOR_EACH_EVAL0(__VA_ARGS__)))#define ALBA_MACROS_FOR_EACH_EVAL2(...) ALBA_MACROS_FOR_EACH_EVAL1(ALBA_MACROS_FOR_EACH_EVAL1(ALBA_MACROS_FOR_EACH_EVAL1(__VA_ARGS__)))
#define ALBA_MACROS_FOR_EACH_EVAL3(...) ALBA_MACROS_FOR_EACH_EVAL2(ALBA_MACROS_FOR_EACH_EVAL2(ALBA_MACROS_FOR_EACH_EVAL2(__VA_ARGS__)))
#define ALBA_MACROS_FOR_EACH_EVAL4(...) ALBA_MACROS_FOR_EACH_EVAL3(ALBA_MACROS_FOR_EACH_EVAL3(ALBA_MACROS_FOR_EACH_EVAL3(__VA_ARGS__)))
#define ALBA_MACROS_FOR_EACH_EVAL(...)  ALBA_MACROS_FOR_EACH_EVAL4(ALBA_MACROS_FOR_EACH_EVAL4(ALBA_MACROS_FOR_EACH_EVAL4(__VA_ARGS__)))
#define ALBA_MACROS_FOR_EACH_END(...)
#define ALBA_MACROS_FOR_EACH_OUT
#define ALBA_MACROS_FOR_EACH_COMMA ,

#define ALBA_MACROS_FOR_EACH_GET_END2() 0, ALBA_MACROS_FOR_EACH_END
#define ALBA_MACROS_FOR_EACH_GET_END1(...) ALBA_MACROS_FOR_EACH_GET_END2
#define ALBA_MACROS_FOR_EACH_GET_END(...) ALBA_MACROS_FOR_EACH_GET_END1
#define ALBA_MACROS_FOR_EACH_NEXT0(test, next, ...) next ALBA_MACROS_FOR_EACH_OUT
#define ALBA_MACROS_FOR_EACH_NEXT1(test, next) ALBA_MACROS_FOR_EACH_NEXT0(test, next, 0)
#define ALBA_MACROS_FOR_EACH_NEXT(test, next)  ALBA_MACROS_FOR_EACH_NEXT1(ALBA_MACROS_FOR_EACH_GET_END test, next)

#define ALBA_MACROS_FOR_EACH0(f, x, peek, ...) f(x) ALBA_MACROS_FOR_EACH_NEXT(peek, ALBA_MACROS_FOR_EACH1)(f, peek, __VA_ARGS__)
#define ALBA_MACROS_FOR_EACH1(f, x, peek, ...) f(x) ALBA_MACROS_FOR_EACH_NEXT(peek, ALBA_MACROS_FOR_EACH0)(f, peek, __VA_ARGS__)

#define ALBA_MACROS_FOR_EACH_LIST_NEXT1(test, next) ALBA_MACROS_FOR_EACH_NEXT0(test, ALBA_MACROS_FOR_EACH_COMMA next, 0)
#define ALBA_MACROS_FOR_EACH_LIST_NEXT(test, next)  ALBA_MACROS_FOR_EACH_LIST_NEXT1(ALBA_MACROS_FOR_EACH_GET_END test, next)

#define ALBA_MACROS_FOR_EACH_LIST0(f, x, peek, ...) f(x) ALBA_MACROS_FOR_EACH_LIST_NEXT(peek, ALBA_MACROS_FOR_EACH_LIST1)(f, peek, __VA_ARGS__)
#define ALBA_MACROS_FOR_EACH_LIST1(f, x, peek, ...) f(x) ALBA_MACROS_FOR_EACH_LIST_NEXT(peek, ALBA_MACROS_FOR_EACH_LIST0)(f, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters.
 */
#define ALBA_MACROS_FOR_EACH(f, ...) ALBA_MACROS_FOR_EACH_EVAL(ALBA_MACROS_FOR_EACH1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and
 * inserts commas between the results.
 */
#define ALBA_MACROS_FOR_EACH_WITH_COMMA(f, ...) ALBA_MACROS_FOR_EACH_EVAL(ALBA_MACROS_FOR_EACH_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))



