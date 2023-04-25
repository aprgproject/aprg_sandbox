#pragma once

#include <functional>

namespace alba {

class AlbaScopeGuard {
public:
    using OnExitFunction = std::function<void(void)>;

    AlbaScopeGuard(OnExitFunction const& functionParameter);
    AlbaScopeGuard(OnExitFunction&& functionParameter);
    ~AlbaScopeGuard() noexcept;

private:
    OnExitFunction m_onExitFunction;
};

}  // namespace alba
