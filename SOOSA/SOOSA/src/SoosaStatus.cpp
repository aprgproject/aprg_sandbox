#include "SoosaStatus.hpp"

#include <Macros/AlbaMacros.hpp>

using namespace std;

namespace alba
{

string getString(SoosaStatus const status)
{
    switch(status)
    {
    ALBA_MACROS_CASE_ENUM_STRING(SoosaStatus::AlgorithmError);
    ALBA_MACROS_CASE_ENUM_STRING(SoosaStatus::BitmapError);
    ALBA_MACROS_CASE_ENUM_STRING(SoosaStatus::NoError);
    }
}

}
