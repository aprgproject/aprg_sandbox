#include "AlbaContainerHelper.hpp"

using namespace std;

namespace alba
{

namespace containerHelper
{

string getDelimeterBasedOnFormat(StreamFormat const streamFormat)
{
    if(StreamFormat::File == streamFormat)
    {
        return string("\n");
    }
    else
    {
        return string(", ");
    }
}

}

}//namespace alba
