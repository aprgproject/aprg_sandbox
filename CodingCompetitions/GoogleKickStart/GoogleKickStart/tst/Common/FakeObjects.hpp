#pragma once

#include <Common/Container/AlbaSingleton.hpp>

#include <sstream>

namespace alba
{

struct FakeObjects : public alba::AlbaSingleton<FakeObjects>
{
    std::stringstream inputStringStream;
    std::stringstream outputStringStream;
};

}
