#include "AlbaPrintFunctions.hpp"

using namespace std;

namespace alba
{

template <>
void printParameter(ostream & outputStream, string const&, char const*const parameter)
{
    outputStream << R"([")" << parameter << R"("])";
}

}//namespace alba
