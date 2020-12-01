#include "UmlArrow.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <string>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

string UmlArrow::getRedArrow()
{
    return "-[#red]>";
}

string UmlArrow::getBlueArrow()
{
    return "-[#blue]>";
}

string UmlArrow::getGreenArrow()
{
    return "-[#green]>";
}

string UmlArrow::getDarkerGreenArrow()
{
    return "-[#000099]>";
}

string UmlArrow::getBlackArrow()
{
    return "-[#black]>";
}

string UmlArrow::getLostMessageArrow()
{
    return "->x";
}

string UmlArrow::getArrowBaseFromMessageName(string const& messageName)
{
    string result;
    if(isNbapMessage(messageName))
    {
        result = getBlackArrow();
    }
    else if(isTcomInternalMessage(messageName))
    {
        result = getBlueArrow();
    }
    else if(isDspMessage(messageName))
    {
        result = getDarkerGreenArrow();
    }
    else
    {
        result = getGreenArrow();
    }
    return result;
}

}
