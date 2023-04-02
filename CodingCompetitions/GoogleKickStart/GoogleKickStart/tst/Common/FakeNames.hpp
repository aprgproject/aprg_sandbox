#pragma once

#include <Common/FakeObjects.hpp>

#define main fake_main
#define fake_cin alba::FakeObjects::getInstance().inputStringStream
#define fake_cout alba::FakeObjects::getInstance().outputStringStream
