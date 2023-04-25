#include <Adapter/ClassAdapter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace ClassAdapter {

TEST(ClassAdapterTest, Test1) {
    Target *t = new Adapter();
    t->request();
    delete t;
}

}  // namespace ClassAdapter
