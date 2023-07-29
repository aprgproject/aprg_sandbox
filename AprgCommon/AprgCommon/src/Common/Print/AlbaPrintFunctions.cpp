#include "AlbaPrintFunctions.hpp"

#include <iomanip>

using namespace std;

namespace alba {

// put this when std::quoted has string_view definition
// void printParameter(ostream& outputStream, string_view parameter) {
//    outputStream << "string view" << std::quoted(
//        string(parameter));
// }

void printParameter(ostream& outputStream, string const& parameter) { outputStream << std::quoted(parameter); }

void printParameter(ostream& outputStream, char const* const parameter) { outputStream << std::quoted(parameter); }

template <>
void printParameterWithName(ostream& outputStream, string_view, char const* const parameter) {
    // the name is not printing to avoid printing the same string literal twice
    outputStream << R"([")" << parameter << R"("])";
}

}  // namespace alba
