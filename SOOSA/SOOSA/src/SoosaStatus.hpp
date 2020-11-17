#pragma once

#include <string>

namespace alba
{

enum class SoosaStatus
{
    BitmapError,
    AlgorithmError,
    NoError
};

std::string getString(SoosaStatus const status);

}
