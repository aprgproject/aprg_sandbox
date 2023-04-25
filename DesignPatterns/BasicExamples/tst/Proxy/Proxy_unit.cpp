#include <Proxy/Proxy.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Proxy {

TEST(ProxyTest, Test1) {
    Proxy *proxy = new Proxy();
    proxy->request();

    delete proxy;
}

}  // namespace Proxy
