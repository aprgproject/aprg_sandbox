set(APRG_GRAPH_INCLUDE_DIRECTORIES
    ${APRG_GRAPH_DIR}/src
)

set(APRG_GRAPH_TEST_INCLUDE_DIRECTORIES
    ${APRG_GRAPH_DIR}/tst
)

set(APRG_GRAPH_SOURCES
    ${APRG_GRAPH_DIR}/src/AprgGraph.cpp
    ${APRG_GRAPH_DIR}/src/AprgGraph.hpp
)

set(APRG_GRAPH_TESTS
    ${APRG_GRAPH_DIR}/tst/AprgGraph_unit.cpp
)

set(APRG_GRAPH_SOURCES_AND_TESTS
    ${APRG_GRAPH_SOURCES}
    ${APRG_GRAPH_TESTS}
)
