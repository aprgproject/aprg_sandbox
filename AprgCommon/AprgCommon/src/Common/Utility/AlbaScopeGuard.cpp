#include "AlbaScopeGuard.hpp"

using namespace std;

namespace alba {

AlbaScopeGuard::AlbaScopeGuard(OnExitFunction const& functionParameter) : m_onExitFunction(functionParameter) {}

AlbaScopeGuard::AlbaScopeGuard(OnExitFunction&& functionParameter) : m_onExitFunction(move(functionParameter)) {}

AlbaScopeGuard::~AlbaScopeGuard() noexcept  // destructor/cleanup code should not throw an exception
{
    // put a try catch here to ensure that it will not throw? nah, we dont use exceptions anyway
    m_onExitFunction();
}

}  // namespace alba
