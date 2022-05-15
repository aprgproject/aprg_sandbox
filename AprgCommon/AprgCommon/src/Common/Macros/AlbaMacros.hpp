#define ALBA_MACROS_COUNT_ARGUMENTS(...) ALBA_MACROS_PP_COUNT_ARGUMENTS_EXPANSION(__VA_ARGS__, ALBA_MACROS_PP_N_REVERSE_SEQUENCE())
#define ALBA_MACROS_PP_COUNT_ARGUMENTS_EXPANSION(...) ALBA_MACROS_PP_GET_COUNT_BASED_FROM_PLACEMENT(__VA_ARGS__)
#define ALBA_MACROS_PP_GET_COUNT_BASED_FROM_PLACEMENT(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30, \
    p31,p32,p33,p34,p35,p36,p37,p38,p39,p40,p41,p42,p43,p44,p45,p46,p47,p48,p49,p50,p51,p52,p53,p54,p55,p56,p57,p58,p59,p60,p61,p62,p63,  N, ...) N
#define ALBA_MACROS_PP_N_REVERSE_SEQUENCE() 63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30, \
    29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0


#define ALBA_MACROS_EXPAND_TO_LITERAL_TEXT(parameter) #parameter
#define ALBA_MACROS_GET_VALUE(parameter) ALBA_MACROS_EXPAND_TO_LITERAL_TEXT(parameter)
#define ALBA_MACROS_DISPLAY_VALUE_PRAGMA_MESSAGE(var) #var "="  ALBA_MACROS_GET_VALUE(var)

#define ALBA_MACROS_GET_STRING_LITERAL(parameter) #parameter // The number-sign or "stringizing" operator.
//#define ALBA_MACROS_GET_CHAR_LITERAL(x) #@x // The charizing operator. Its not supported.
//#define ALBA_MACROS_GET_AS_A_TOKEN(parameter) ##parameter //The double-number-sign or token-pasting operator (##). This needs to be used in the macro.

#define ALBA_MACROS_CASE_ENUM_STRING(parameter) \
    case parameter: \
    return ALBA_MACROS_GET_STRING_LITERAL(parameter);

#define ALBA_MACROS_CASE_ENUM_SHORT_STRING(parameter, shortName) \
    case parameter: \
    return shortName;
