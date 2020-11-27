set(APRG_STATISTICS_INCLUDE_DIRECTORIES
    ${APRG_STATISTICS_DIR}/src
)

set(APRG_STATISTICS_TEST_INCLUDE_DIRECTORIES
    ${APRG_STATISTICS_DIR}/tst
)

set(APRG_STATISTICS_SOURCES
    ${APRG_STATISTICS_DIR}/src/DataSample.hpp
    ${APRG_STATISTICS_DIR}/src/DataStatistics.hpp
    ${APRG_STATISTICS_DIR}/src/FrequencyStatistics.cpp
    ${APRG_STATISTICS_DIR}/src/FrequencyStatistics.hpp
    ${APRG_STATISTICS_DIR}/src/KMeansClustering.cpp
    ${APRG_STATISTICS_DIR}/src/KMeansClustering.hpp

    ${APRG_STATISTICS_DIR}/src/TwoDimensionsStatistics.cpp
    ${APRG_STATISTICS_DIR}/src/TwoDimensionsStatistics.hpp
)
set(APRG_STATISTICS_TESTS
    ${APRG_STATISTICS_DIR}/tst/DataSample_unit.cpp
    ${APRG_STATISTICS_DIR}/tst/DataStatistics_unit.cpp
    ${APRG_STATISTICS_DIR}/tst/FrequencyStatistics_unit.cpp
    ${APRG_STATISTICS_DIR}/tst/KMeansClustering_unit.cpp
    ${APRG_STATISTICS_DIR}/tst/TwoDimensionsStatistics_unit.cpp
)
set(APRG_STATISTICS_SOURCES_AND_TESTS
    ${APRG_STATISTICS_SOURCES}
    ${APRG_STATISTICS_TESTS})
