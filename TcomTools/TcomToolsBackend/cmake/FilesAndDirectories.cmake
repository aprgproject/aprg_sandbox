set(TCOM_TOOLS_BACKEND_INCLUDE_DIRECTORIES
    ${TCOM_TOOLS_BACKEND_DIR}/src
)

set(TCOM_TOOLS_BACKEND_SOURCES
    ${TCOM_TOOLS_BACKEND_DIR}/src/BtsLogPrint.cpp
    ${TCOM_TOOLS_BACKEND_DIR}/src/BtsLogPrint.hpp
    ${TCOM_TOOLS_BACKEND_DIR}/src/BtsLogSorter.cpp
    ${TCOM_TOOLS_BACKEND_DIR}/src/BtsLogSorter.hpp
    ${TCOM_TOOLS_BACKEND_DIR}/src/BtsLogSorterConfiguration.hpp
    ${TCOM_TOOLS_BACKEND_DIR}/src/BtsLogTime.cpp
    ${TCOM_TOOLS_BACKEND_DIR}/src/BtsLogTime.hpp
    ${TCOM_TOOLS_BACKEND_DIR}/src/BtsPrintReaderWithRollback.cpp
    ${TCOM_TOOLS_BACKEND_DIR}/src/BtsPrintReaderWithRollback.hpp
)

set(TCOM_TOOLS_BACKEND_TESTS
    ${TCOM_TOOLS_BACKEND_DIR}/tst/BtsLogPrint_unit.cpp
    ${TCOM_TOOLS_BACKEND_DIR}/tst/BtsLogSorter_unit.cpp
    ${TCOM_TOOLS_BACKEND_DIR}/tst/BtsLogTime_unit.cpp
)

set(TCOM_TOOLS_BACKEND_SOURCES_AND_TESTS
    ${TCOM_TOOLS_BACKEND_SOURCES}
    ${TCOM_TOOLS_BACKEND_TESTS}
)
