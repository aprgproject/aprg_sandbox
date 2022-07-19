#include "AlbaPrintFunctions.hpp"

using namespace std;

namespace alba
{

template <>
void printParameterWithName(ostream & outputStream, string const&, char const*const parameter)
{
    outputStream << R"([")" << parameter << R"("])";
}

}//namespace alba
