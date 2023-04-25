#include <MapAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MapAnalyzerTest, AnalyzeWorks) {
    MapAnalyzer mapAnalyzer;

    mapAnalyzer.initialize();
    mapAnalyzer.analyze();
    mapAnalyzer.sortData();

    mapAnalyzer.printResult();
}

}  // namespace alba
