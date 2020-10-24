set(APRG_ALGORITHM_INCLUDE_DIRECTORIES
    ${APRG_ALGORITHM_DIR}/src
)

set(APRG_ALGORITHM_SOURCES
    ${APRG_ALGORITHM_DIR}/src/GrepStringEvaluator/AlbaGrepStringEvaluator.cpp
    ${APRG_ALGORITHM_DIR}/src/GrepStringEvaluator/AlbaGrepStringEvaluator.hpp
    ${APRG_ALGORITHM_DIR}/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.cpp
    ${APRG_ALGORITHM_DIR}/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp
    ${APRG_ALGORITHM_DIR}/src/LargeSorter/AlbaLargeSorter.hpp
    ${APRG_ALGORITHM_DIR}/src/LargeSorter/AlbaLargeSorterCache.hpp
    ${APRG_ALGORITHM_DIR}/src/LargeSorter/AlbaLargeSorterConfiguration.hpp
    ${APRG_ALGORITHM_DIR}/src/LargeSorter/AlbaLargeSorterTypes.hpp
    ${APRG_ALGORITHM_DIR}/src/LargeSorter/DataBlock.hpp
    ${APRG_ALGORITHM_DIR}/src/LargeSorter/DataBlockFileHandler.hpp
    ${APRG_ALGORITHM_DIR}/src/LargeSorter/DataBlockMemoryHandler.hpp
    ${APRG_ALGORITHM_DIR}/src/LargeSorter/DataBlocks.hpp
    ${APRG_ALGORITHM_DIR}/src/QuineMcCluskey/QuineMcCluskey.cpp
    ${APRG_ALGORITHM_DIR}/src/QuineMcCluskey/QuineMcCluskey.hpp
)

set(APRG_ALGORITHM_TESTS
    ${APRG_ALGORITHM_DIR}/tst/AlbaGrepStringEvaluator_unit.cpp
    ${APRG_ALGORITHM_DIR}/tst/AlbaLargeSorter_unit.cpp
    ${APRG_ALGORITHM_DIR}/tst/QuineMcCluskey_unit.cpp
)

set(APRG_ALGORITHM_SOURCES_AND_TESTS    ${APRG_ALGORITHM_SOURCES}
    ${APRG_ALGORITHM_TESTS}
)