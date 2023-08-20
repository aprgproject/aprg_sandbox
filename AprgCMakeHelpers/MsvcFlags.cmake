set(APRG_COMPILER_COMMON_FLAGS "/nologo /EHsc /W4")
set(APRG_COMPILER_COMMON_C_FLAGS "/std:c17")
set(APRG_COMPILER_COMMON_CPP_FLAGS "/std:c++17")
set(APRG_COMPILER_FLAGS_FOR_DEBUG "/Zi")
set(APRG_COMPILER_FLAGS_FOR_DEBUG_SHOW_PREPROCESSING_RESULT "/EP")
set(APRG_COMPILER_FLAGS_FOR_RELEASE "/GF")

#APRG Common flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_COMMON_FLAGS} ${APRG_COMPILER_COMMON_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_COMMON_FLAGS} ${APRG_COMPILER_COMMON_CPP_FLAGS}")

# Some notes
# Sources:
# -> https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options?view=msvc-170
# -> https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html
# MSVC Native tools:
#    CC = cl.exe
#        C and C++ Compiler - Can compile both C and C++ code depending on the flag. By default it compiles C++ code.
#    rc.exe => Resource Compiler.
#    LD = link.exe
#        C++ Linker.
#    AS = ml
#        Assembler
#    AR = lib
# Compiler: cl.exe
#    /nologo - Suppress microsoft's logo
#    /out:<file.exe> - Set output file name.
#    /EHsc
#    /Zi - Add debugging symbols to the executable
#    /c - Doesn't link generating *.exe or *.dll, it creates only intermedidate object code for further separate linking.
#         It is useful for compiling large code bases where each compilation unit can be compiled separately.
#    /W4 - Set the level of warning to the highest.
#    /entry:<entrypoint> - Set the C/C++ runtime, it can be:
#        mainCRTStartup => calls main(), the entrypoint for console mode apps
#        wmainCRTStartup => calls wmain(), as above but the Unicode version
#        WinMainCRTStartup => calls WinMain(), the entrypoint for native Windows apps
#        wWinMainCRTStartup => calls wWinMain(), as above but the Unicode version
#        _DllMainCRTStartup => Calls DLLMain()
#    /subsystem:<type> - Set the subsystem - default Console, it can be:
#        /subsystem:console - For applications that necessarly runs in the console (aka terminal emulator)
#        /subsystem:windows - Doesn't display the cmd.exe terminal when ones click at the application executable.
#    /TC -> Specify that file name is C source code
#    /TP -> Specify that file name is a C++ source code (default)
#    /MD, /MT, /LD => Run-time library - Indcates that object-code (compiled program) is a DLL.
#    /GF -> (Eliminate Duplicate Strings) - Enables the compiler to create a single copy of identical strings in the program image and in memory during execution.
#                                           This is an optimization called string pooling that can create smaller programs.
#    /E  - Copies preprocessor output to standard output.
#    /EHa - Enable C++ exception handling (with SEH exceptions).
#    /EHc - extern "C" defaults to nothrow.
#    /EHr - Always generate noexcept runtime termination checks.
#    /EHs - Enable C++ exception handling (no SEH exceptions).
#    /EP - Copies preprocessor output to standard output.

