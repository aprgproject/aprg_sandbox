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
        return "\n"s;
    }
    else
    {
        return ", "s;
    }
}

}

}//namespace alba
