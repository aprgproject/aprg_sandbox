macro(PRINT_VARIABLE variable)
    message(STATUS "VARIABLE: [${variable}] contains: [${${variable}}]")
endmacro()

macro(PRINT_STATUS message)
    message(STATUS "STATUS: [${message}]")
endmacro()

macro(PRINT_WARNING message)
    message(WARNING "WARNING: [${message}]")
endmacro()

macro(PRINT_ERROR message)
    message(FATAL_ERROR "FATAL_ERROR: [${message}]")
endmacro()

