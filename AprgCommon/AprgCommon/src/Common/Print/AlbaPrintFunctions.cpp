#include "AlbaPrintFunctions.hpp"

using namespace std;

namespace alba {

void printParameter(ostream& outputStream, std::string const& parameter) { outputStream << parameter; }
void printParameter(ostream& outputStream, char const* const parameter) { outputStream << parameter; }

template <>
void printParameterWithName(ostream& outputStream, string_view, char const* const parameter) {
    outputStream << R"([")" << parameter << R"("])";
}

}  // namespace alba
