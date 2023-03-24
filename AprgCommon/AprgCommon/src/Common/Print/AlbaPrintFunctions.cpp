#include "AlbaPrintFunctions.hpp"

using namespace std;

namespace alba
{

void printParameter(ostream & outputStream, string const& parameter)
{
    outputStream << parameter;
}

template <>
void printParameterWithName(ostream & outputStream, string const&, char const*const parameter)
{
    outputStream << R"([")" << parameter << R"("])";
}

}//namespace alba
