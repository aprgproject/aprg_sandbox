#APRG default flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -std=c17")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++17")
if(WIN32)
    #add -mwindows for windows GUI, do not add for console build
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

message("CMAKE_C_FLAGS are: [${CMAKE_C_FLAGS}]")
message("CMAKE_CXX_FLAGS are: [${CMAKE_CXX_FLAGS}]")

#APRG unique flags
set(APRG_COMPILER_FLAGS_FOR_DEBUG "-g --coverage")
set(APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED "-O3 -DNDEBUG")
set(APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_MIN_SIZE "-Os -DNDEBUG")
set(APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_DEBUG "-O2 -g -DNDEBUG")
set(APRG_LINKER_FLAGS_FOR_RELEASE "-static") # "-static" is needed to make the program work in other deployments (GCC/QT libraries are missing in other deployments)
set(APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP "-static -s")


# Some notes
# Sources:
# --> https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
# --> https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html

# Search Path and Library Linking Flags
# Flag: -l[linalg]
# --> Links to shared library or shared object
# --> Specifically, it links to linalg.dll on Windows, liblinalg.so (on Unix-like oses like Linux, BSD, AIX, …) or linalg.dylib on MacOSX.
# Flag: -L[/path/to/shared-libraries]
# --> Add search path to shared libraries, directory containing *.so, *.dll or *.dlyb files such as libLinearAlgebra.so depending on the current operating system.
# Flag: -I[/path/to/header-files]
# --> Add search path to header files (.h) or (.hpp).
# Flag: -D[FLAG] or -D[FLAG]=VALUE
# --> Pass preprocessor flag #if FLAG ...

# Output file: -o <outputfile>
# --> Example: g++ file.cpp -o file.bin

# Common library flags
# --> -lm - Compiles against the shared library libm (basic math library, mostly C only)
# --> -lpthread - Compile against Posix threads shared library

# Include Path - Directories containing headers files.
# --> -I/path/to/include1 -I/path/to/include2 …

# Compilation flags -D<flag name>
# --> -DCOMPILE_VAR -> Enable flag COMPILE_VAR - It is equivalent to add to the code (#define COMPILE_VAR)
# --> -DDO_SOMETHING=1 - Equivalent to add to the code #define DO_SOMETHING = 1
# --> -DDISABLE_DEPRECATED_FUNCTIONS=0

# Optmization - docs
# --> -O0: No optmization, faster compilation time, better for debugging builds.
# --> -O2, -O3: Higher level of optmization. Slower compile-time, better for production builds.
# --> -OFast: Enables higher level of optmization than (-O3). It enables lots of flags as can be seen src (-ffloat-store, -ffsast-math, -ffinite-math-only, -O3 …)
# --> -finline-functions
# --> -m64
# --> -funroll-loops
# --> -fvectorize
# --> -fprofile-generate

# Misc
# --> -fexceptions -fstack-protector-strong –param=ssp-buffer-size=4
# Special Options
# --> -g: Builds executable with debugging symbols for GDB GNU Debugger or LLDB Clang/LLVM Debugger. It should only be used during development for debugging builds.
# --> -c: Compiler source(s) to object-code (input to linker). This option is better for incremental compilation when using multiple files.
# --> -pie: Builds a dynamically linked position independent executable.
# --> -static-pie: Builds a staticlaly linked position independent executable.
# --> -shared: Build a shared library (.so or .dylib on U*nix-like Oses) or .dll on MS-Windows.
# --> -fno-exceptions: Disable C++ exceptions (it may be better for embedded systems or anything where exceptiions may not be acceptable).
# --> -fno-rtti:  Disable RTTI (Runtime Type Information)
# There many texts around where game and embedded systems developers report that they disable RTTI due to performance concerns.
# --> -fvisibility=hidden: Make library symbols hidden by default, in a similar way to what happens in Windows DLLs
# where exported symbols must have the prefix __declspec(dllexport) or __declspec(dllimport).
# When all symbols are exported by default, it may increase the likelyhood of undefined behavior if there a multiple definitions of same symbol during linking.



# Compiler Flags:

# Flag: "std - Specify the C++ version or ISO standard version"
# --> -std=c++11 (ISO C++11)
# --> -std=c++14 (ISO C++14)
# --> -std=c++1z (ISO C++17)
# --> -std=c++20 (C++20 experimental)
# --> -std=gnu++ (ISO C++ with GNU extensions)

# Flag: "-Wall"
# --> This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning),
# even in conjunction with macros.
# --> This also enables some language-specific warnings described in C++ Dialect Options and Objective-C and Objective-C++ Dialect Options.

# Flag: "-Wextra"
# --> This enables some extra warning flags that are not enabled by -Wall.
# (This option used to be called -W. The older name is still supported, but the newer name is more descriptive.)

# Flag: -Werror
# --> Make all warnings into errors.
# --> Cant use this flags because there are pragma warnings on APRG.

# Flag: "-Wpedantic" or "-pedantic"
# --> Issue all the warnings demanded by strict ISO C and ISO C++; reject all programs that use forbidden extensions,
# and some other programs that do not follow ISO C and ISO C++.
# --> For ISO C, follows the version of the ISO C standard specified by any -std option used.

# Flag: "-g"
# --> Produce debugging information in the operating system’s native format (stabs, COFF, XCOFF, or DWARF). GDB can work with this debugging information.

# Flag: "--coverage"
# --> This option is used to compile and link code instrumented for coverage analysis.
# --> The option is a synonym for -fprofile-arcs -ftest-coverage (when compiling) and -lgcov (when linking).

# Flag: "-O0"
# --> Reduce compilation time and make debugging produce the expected results. This is the default.

# Flag: "-O" or "-O1"
# --> Optimize. Optimizing compilation takes somewhat more time, and a lot more memory for a large function.
# With -O, the compiler tries to reduce code size and execution time, without performing any optimizations that take a great deal of compilation time.
# --> -O turns on the following optimization flags:
# -fauto-inc-dec, -fbranch-count-reg, -fcombine-stack-adjustments, -fcompare-elim, -fcprop-registers, -fdce, -fdefer-pop, -fdelayed-branch, -fdse, -fforward-propagate,
# -fguess-branch-probability, -fif-conversion, -fif-conversion2, -finline-functions-called-once, -fipa-modref, -fipa-profile, -fipa-pure-const, -fipa-reference,
# -fipa-reference-addressable, -fmerge-constants, -fmove-loop-invariants, -fmove-loop-stores, -fomit-frame-pointer, -freorder-blocks, -fshrink-wrap, -fshrink-wrap-separate,
# -fsplit-wide-types, -fssa-backprop, -fssa-phiopt, -ftree-bit-ccp, -ftree-ccp, -ftree-ch, -ftree-coalesce-vars, -ftree-copy-pro, -ftree-dc, -ftree-dominator-opts,
# -ftree-dse, -ftree-forwprop, -ftree-fre, -ftree-phiprop, -ftree-pta, -ftree-scev-cprop, -ftree-sink, -ftree-slsr, -ftree-sra, -ftree-ter, -funit-at-a-time

# Flag: "-O2"
# --> Optimize even more. GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff.
# As compared to -O, this option increases both compilation time and the performance of the generated code.
# -O2 turns on all optimization flags specified by -O1.
# --> It also turns on the following optimization flags:
# -fgcse-after-reload, -fipa-cp-clone, -floop-interchange, -floop-unroll-and-jam, -fpeel-loops, -fpredictive-commoning, -fsplit-loops, -fsplit-paths,
# -ftree-loop-distribution, -ftree-loop-vectorize, -ftree-partial-pre, -ftree-slp-vectorize, -funswitch-loops, -fvect-cost-model, -fvect-cost-model=dynamic,
#- fversion-loops-for-strides

# Flag: "-O3"
# --> Optimize yet more. -O3 turns on all optimizations specified by -O2.
# --> It turns on the following optimization flags:
# -fgcse-after-reload, -fipa-cp-clone, -floop-interchange, -floop-unroll-and-jam, -fpeel-loops, -fpredictive-commoning, -fsplit-loops, -fsplit-paths,
# -ftree-loop-distribution, -ftree-loop-vectorize, -ftree-partial-pre, -ftree-slp-vectorize, -funswitch-loops, -fvect-cost-model, -fvect-cost-model=dynamic,
# -fversion-loops-for-strides

# Flag: "-Os"
# --> Optimize for size. -Os enables all -O2 optimizations except those that often increase code size: "
# -falign-functions, -falign-jumps, -falign-labels  -falign-loops, -fprefetch-loop-arrays  -freorder-blocks-algorithm=st

# Flag: "-DNDEBUG"
# --> disable assertions

# Peformance Optimization Flags
# Flag: "-O0"
# --> Optimization Level 0 (No optimization, default)
# --> Better for debugging builds during development, since it provides faster compile-time.
# Flag: "-O1"
# --> Optimization Level 1
# Flag: "-O2"
# --> Optimization Level 2
# --> Enables (-O1); inline small functions;
# Flag: "-O3"
# --> Optimization Level 3 (Most aggressive optimization, Highest level of optmization and speed)
# --> Problem: Slower compile-time and large binary size.
# --> More function inlining; loop vectorization and SIMD instructions.
# Flag: "-OS"
# --> Code Size Optimization
# --> Enable (-O2), but disable some optimizations flags in order to reduce object-code size.
# Flag: "-Oz"
# --> [CLANG-ONLY] - Optimizes for size even further than (-OS)
# Flag: "-Ofast"
# --> Activate (-O3) optimization disregarding strict standard compliance.
# Flag: "-Og"
# --> Optmizing for debugging.
# -->  Enables all optimization that does not conflicts with debugging. It can be used with the (-g) flag for enabling debugging symbols.



#  Linker Flags

# Flag: "-Xlinker option"
# --> Pass option as an option to the linker. You can use this to supply system-specific linker options that GCC does not recognize.
# --> If you want to pass an option that takes a separate argument, you must use -Xlinker twice, once for the option and once for the argument.
# For example, to pass -assert definitions, you must write -Xlinker -assert -Xlinker definitions.
# It does not work to write -Xlinker "-assert definitions", because this passes the entire string as a single argument, which is not what the linker expects.
# --> When using the GNU linker, it is usually more convenient to pass arguments to linker options using the option=value syntax than as separate arguments. For example, you can specify -Xlinker -Map=output.map rather than -Xlinker -Map -Xlinker output.map. Other linkers may not support this syntax for command-line options.

# Flag: "-Wl,option"
# --> Pass option as an option to the linker.
# If option contains commas, it is split into multiple options at the commas.
# You can use this syntax to pass an argument to the option. For example, -Wl,-Map,output.map passes -Map output.map to the linker.
# When using the GNU linker, you can also get the same effect with -Wl,-Map=output.map.

# Flag: "-pie"
# --> Produce a dynamically linked position independent executable on targets that support it.
# For predictable results, you must also specify the same set of options used for compilation (-fpie, -fPIE, or model suboptions) when you specify this linker option.

# Flag: "-no-pie"
# --> Don’t produce a dynamically linked position independent executable.

# Flag: "-static-pie"
# --> Produce a static position independent executable on targets that support it.
# A static position independent executable is similar to a static executable, but can be loaded at any address without a dynamic linker. For predictable results, you must also specify the same set of options used for compilation (-fpie, -fPIE, or model suboptions) when you specify this linker option.

# Flag: "-pthread"
# --> Link with the POSIX threads library.
# This option is supported on GNU/Linux targets, most other Unix derivatives, and also on x86 Cygwin and MinGW targets.
# On some targets this option also sets flags for the preprocessor, so it should be used consistently for both compilation and linking.

# Flag: "-r"
# --> Produce a relocatable object as output. This is also known as partial linking.

# Flag: "-rdynamic"
# --> Pass the flag -export-dynamic to the ELF linker, on targets that support it.
# This instructs the linker to add all symbols, not only used ones, to the dynamic symbol table.
# This option is needed for some uses of dlopen or to allow obtaining backtraces from within a program.

# Flag: "-s"
# --> Remove all symbol table and relocation information from the executable.
# --> This is similar to "strip" command in GNU tools.
# --> From stackoverflow:
# ----> What's the equivalent to gcc -s in terms of strip with some of its options?
# ------> They both do the same thing, removing the symbols table completely.
# ------> However, as @JimLewis pointed out strip allows finer control.
# ------> For example, in a relocatable object, strip --strip-unneeded won't remove its global symbols.
# ------> However, strip or strip --strip-all would remove the complete symbols table.
# ----> Which one do you use to reduce the size of executable and speed up its running
# ------> The symbols table is a non-allocable section of the binary.
# ------> This means that it never gets loaded in RAM memory.
# ------> It stores information that can be useful for debugging purporses, for instance, to print out a stacktrace when a crash happens.
# ------> A case where it could make sense to remove the symbols table would be a scenario where you have serious constraints of storage capacity
# ------> (in that regard, gcc -Os -s or make CXXFLAGS="-Os -s" ... is useful as it will result in a smaller slower binary that is also stripped to reduce size further).
# ------> I don't think removing the symbols table would result into a speed gain for the reasons commented.

# Flag: "-static"
# --> On systems that support dynamic linking, this overrides -pie and prevents linking with the shared libraries.
# --> On other systems, this option has no effect.

# Flag: "-shared"
# --> Produce a shared object which can then be linked with other objects to form an executable.
# Not all systems support this option.
# For predictable results, you must also specify the same set of options used for compilation (-fpic, -fPIC, or model suboptions) when you specify this linker option.

# Flag: "-shared-libgcc", "-static-libgcc"
# --> On systems that provide libgcc as a shared library, these options force the use of either the shared or static version, respectively.
# If no shared version of libgcc was built when the compiler was configured, these options have no effect.
# --> There are several situations in which an application should use the shared libgcc instead of the static version.
# The most common of these is when the application wishes to throw and catch exceptions across different shared libraries.
# In that case, each of the libraries as well as the application itself should use the shared libgcc.
# --> Therefore, the G++ driver automatically adds -shared-libgcc whenever you build a shared library or a main executable,
# because C++ programs typically use exceptions, so this is the right thing to do.
# --> If, instead, you use the GCC driver to create shared libraries, you may find that they are not always linked with the shared libgcc.
# If GCC finds, at its configuration time, that you have a non-GNU linker or a GNU linker that does not support option --eh-frame-hdr,
# it links the shared version of libgcc into shared libraries by default.
# Otherwise, it takes advantage of the linker and optimizes away the linking with the shared version of libgcc,
# linking with the static version of libgcc by default.
# This allows exceptions to propagate through such shared libraries, without incurring relocation costs at library load time.
# --> However, if a library or main executable is supposed to throw or catch exceptions, you must link it using the G++ driver,
# or using the option -shared-libgcc, such that it is linked with the shared libgcc.


# Verbose
# --> -Wl,–verbose
# --> -Wl,–print-memory-usage
# Directory which linker will search for libraries (*.so files on Unix; *.dylib on MacOSX and *.dll on Windows)
# --> -L/path/to-directory
# Strip Debug Information
# --> -Wl,-s
# Build Shared Library
# --> -shared
# Set Unix Shared Library SONAME (See)
# --> –Wl,soname,<NAME>
# --> –Wl,soname,libraryname.so.1
# General Format of Linker Options
# --> -Wl,–<OPTION>=<VALUE>
# Windows-only (MINGW)
# --> -Wl,–subsystem,console => Build for console subsystem.
# --> -Wl,–subsystem,windows => Build for winodw subsystem.
# --> -ld3d9 => Link against DirectX (d3d9.dll)
# Windows-only DLL (Dynamic Linked Libraries)
# --> -shared
# --> -Wl,–export-all-symbols
# --> -Wl,–enable-auto-import

# Static link against LibGCC runtime library:
# --> -static-libgcc
# Static link against libstdC++ runtime library:
# --> -static-libstdc++
# Static link against Gfortran (GNU fortran) runtime library.
# --> -static-libgfortran
# Set Unix RPATH (Note Windows does not have rpath)
# --> –Wl,rpath=/path/to/directory1;/path/to/directory2
# Set Unix RPATH to executable current directory.
# --> –Wl,rpath=$ORIGIN
# Change the default dynamic linker (UNIX and Linux)
# --> -Wl,-dynamic-linker,/path/to/linker/ld-linux.so.2.1
# Common Unix Dependencies:
# --> -lpthread => Link against POSIX threads library.
# --> -ldl => Link against libdl library for dlopen(), dlclose(), APIs.
# Exclude Runtime Libraries (gcc docs)
# --> -nostartfiles => "Do not use the standard system startup files when linking. The standard system libraries are used normally, unless -nostdlib, -nolibc, or -nodefaultlibs is used."
# --> -nodefaultlibs => Do not use the standard system libraries when linking.
# --> -nolibc => Do not use the C library or system libraries tightly coupled with it when linking.
# --> -nostdlib => Do not use the standard system startup files or libraries when linking.
# Set heap size
# --> -Wl,–heap,201561
# Stack reserve size
# --> -Wl,–stack,419525
# Generate Linker Map (mostly used for embedded systems)
# --> -Wl,-Map=linker-map.map
# Use a custom linker script (embedded systems)
# --> -Wl,T/path/to/linker-script.ld
# Linker version script
# --> -Wl,–version-script,criptfile
# Eliminate dead-code or unused code for decreasing the program or firmware size (embedded systesm) - (Elinux)
# --> -ffunction-sections -fdata-sections -Wl,–gc-sections
# Miscellaneous
# --> -Wl,–allow-multiple-definition
# --> -fno-keep-inline-dllexport
# --> -Wl,–lager-address-aware
# --> -Wl,–image-base,358612


# Files Generated by the Compiler
# Object Files
# --> *.o -> Generated on *NIX - Linux, MacOSX … by GCC or Clang
# --> *.obj -> Windows
# Binary Native Executable - Object Code
# --> *NIX: Linux, MacOSX, FreeBSD -> Without extension.
# --> Windows: *.exe
# --> *.hex -> Extension of many compiled firmwares generated by embedded systems compilers such as proprietary compilers for Microcontrollers.
# Shared Objects - Shared Libraries
# --> *.dll -> Called dynamic linked libraries on Windows -> libplot.dll
# --> *.so -> Called shared Object on Linux -> libplot.so
# --> *.dylib -> Extension used on MacOSX.
# Static Library
# --> *.a - extension
