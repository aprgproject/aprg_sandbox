#include "UmlHelpers.hpp"

#include <Common/Utils/StringHelpers.hpp>

using namespace std;

namespace DesignDocumentCreator
{

string UmlHelpers::getUmlAlias(ComponentName const componentName)
{
    string result;
    switch(componentName)
    {
    case ComponentName::Oam:
        result = "OAM";
        break;
    case ComponentName::TcomToam:
        result = "TCOM/TOAM";
        break;
    case ComponentName::TupcCm:
        result = "TUPC/CM";
        break;
    case ComponentName::TupcIlm:
        result = "TUPC/ILM";
        break;
    case ComponentName::TupcLom:
        result = "TUPC/LOM";
        break;
    case ComponentName::TupcTbm:
        result = "TUPC/TBM";
        break;
    default:
        result = StringHelpers::convertToString(componentName);
    }
    return result;
}

}
