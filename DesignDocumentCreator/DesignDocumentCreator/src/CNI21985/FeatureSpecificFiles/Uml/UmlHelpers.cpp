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
    case ComponentName::Dsp:
        result = "DSP";
        break;
    case ComponentName::Oam:
        result = "OAM";
        break;
    case ComponentName::TcomCchhRlh:
        result = "TCOM/RLH/CCHH/HSCH";
        break;
    case ComponentName::TcomToam:
        result = "TCOM/TOAM";
        break;
    case ComponentName::Trsw:
        result = "TRSW/Transport";
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
