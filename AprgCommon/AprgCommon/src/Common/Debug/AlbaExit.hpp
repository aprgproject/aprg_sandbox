#pragma once

#include <cstdlib>

namespace alba {

#define ALBA_SUCCESSFUL_EXIT std::exit(EXIT_SUCCESS)  // same with std::exit(0)
#define ALBA_FAILURE_EXIT std::exit(EXIT_FAILURE)  // same with std::exit(1)
//#define ALBA_SUCCESSFUL_QUICK_EXIT std::quick_exit(EXIT_SUCCESS) // no impl in standard?
//#define ALBA_FAILURE_QUICK_EXIT std::quick_exit(EXIT_FAILURE)
#define ALBA_ABORT std::abort()
#define ALBA_TERMINATE std::terminate()

// std::exit
// -> Causes normal program termination to occur.
// -> If exit_code is 0 or EXIT_SUCCESS, an implementation-defined status indicating successful termination is returned.
// ---> If exit_code is EXIT_FAILURE, an implementation-defined status indicating unsuccessful termination is returned.
// ---> In other cases implementation-defined status value is returned.

// std::quick_exit
// Causes normal program termination to occur without completely cleaning the resources.

// std::abort
// -> Causes abnormal program termination unless SIGABRT is being caught by a signal handler passed to std::signal and
// the handler does not return.

// std::terminate
// -> std::terminate() is called by the C++ runtime when the program cannot continue (typically caused by an unhandled
// exception)
// -> In any case, std::terminate calls the currently installed std::terminate_handler. The default
// std::terminate_handler calls std::abort.

}  // namespace alba
