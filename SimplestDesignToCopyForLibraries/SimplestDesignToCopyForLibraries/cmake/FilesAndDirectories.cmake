set(SIMPLEST_DESIGN_TO_COPY_INCLUDE_DIRECTORIES
    ${SIMPLEST_DESIGN_TO_COPY_DIR}/src
)

set(SIMPLEST_DESIGN_TO_COPY_TEST_INCLUDE_DIRECTORIES
    ${SIMPLEST_DESIGN_TO_COPY_DIR}/tst
)

set(SIMPLEST_DESIGN_TO_COPY_SOURCES
    ${SIMPLEST_DESIGN_TO_COPY_DIR}/src/SimplestDesignToCopyForLibraries.cpp
    ${SIMPLEST_DESIGN_TO_COPY_DIR}/src/SimplestDesignToCopyForLibraries.hpp
)

set(SIMPLEST_DESIGN_TO_COPY_TESTS
    ${SIMPLEST_DESIGN_TO_COPY_DIR}/tst/SimplestDesignToCopyForLibraries_unit.cpp
)

set(SIMPLEST_DESIGN_TO_COPY_SOURCES_AND_TESTS
    ${SIMPLEST_DESIGN_TO_COPY_SOURCES}
    ${SIMPLEST_DESIGN_TO_COPY_TESTS}
)
