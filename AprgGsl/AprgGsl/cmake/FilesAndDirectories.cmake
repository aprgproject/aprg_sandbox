set(APRG_GSL_INCLUDE_DIRECTORIES
    ${APRG_GSL_DIR}/src
)

set(APRG_GSL_TEST_INCLUDE_DIRECTORIES
    ${APRG_GSL_DIR}/tst
)

set(APRG_GSL_SOURCES
    ${APRG_GSL_DIR}/src/Modeling/AprgModeling.cpp
    ${APRG_GSL_DIR}/src/Modeling/AprgModeling.hpp)

set(APRG_GSL_TESTS
    ${APRG_GSL_DIR}/tst/AprgModeling_unit.cpp)

set(APRG_GSL_SOURCES_AND_TESTS
    ${APRG_GSL_SOURCES}
    ${APRG_GSL_TESTS}
)
