set(APRG_BITMAP_INCLUDE_DIRECTORIES
    ${APRG_BITMAP_DIR}/src
)

set(APRG_BITMAP_TEST_INCLUDE_DIRECTORIES
    ${APRG_BITMAP_DIR}/tst
)

set(APRG_BITMAP_SOURCES
    ${APRG_BITMAP_DIR}/src/AprgBitmap.cpp
    ${APRG_BITMAP_DIR}/src/AprgBitmap.hpp
    ${APRG_BITMAP_DIR}/src/AprgBitmapConfiguration.cpp
    ${APRG_BITMAP_DIR}/src/AprgBitmapConfiguration.hpp
    ${APRG_BITMAP_DIR}/src/AprgBitmapSnippet.cpp
    ${APRG_BITMAP_DIR}/src/AprgBitmapSnippet.hpp
    ${APRG_BITMAP_DIR}/src/CommonTypes.hpp
)

set(APRG_BITMAP_TESTS
    ${APRG_BITMAP_DIR}/tst/AprgBitmapReadTest_unit.cpp
    ${APRG_BITMAP_DIR}/tst/AprgBitmapWriteTest_unit.cpp
)

set(APRG_BITMAP_SOURCES_AND_TESTS
    ${APRG_BITMAP_SOURCES}
    ${APRG_BITMAP_TESTS}
)
