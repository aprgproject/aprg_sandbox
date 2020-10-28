set(APRG_PROCESS_FILES_INCLUDE_DIRECTORIES
    ${APRG_PROCESS_FILES_DIR}/src
)

set(APRG_PROCESS_FILES_TEST_INCLUDE_DIRECTORIES
    ${APRG_PROCESS_FILES_DIR}/tst
)

set(APRG_PROCESS_FILES_SOURCES
    ${APRG_PROCESS_FILES_DIR}/src/CombineAndGrepFiles/AlbaCombineAndGrepFiles.cpp
    ${APRG_PROCESS_FILES_DIR}/src/CombineAndGrepFiles/AlbaCombineAndGrepFiles.hpp
    ${APRG_PROCESS_FILES_DIR}/src/CPlusPlusFileFixer/CPlusPlusFileFixer.cpp
    ${APRG_PROCESS_FILES_DIR}/src/CPlusPlusFileFixer/CPlusPlusFileFixer.hpp
    ${APRG_PROCESS_FILES_DIR}/src/SackReader/AlbaSackReader.cpp
    ${APRG_PROCESS_FILES_DIR}/src/SackReader/AlbaSackReader.hpp
    ${APRG_PROCESS_FILES_DIR}/src/SackReader/AlbaSackReaderParameter.cpp
    ${APRG_PROCESS_FILES_DIR}/src/SackReader/AlbaSackReaderParameter.hpp
    ${APRG_PROCESS_FILES_DIR}/src/SackReader/AlbaSackReaderType.cpp
    ${APRG_PROCESS_FILES_DIR}/src/SackReader/AlbaSackReaderType.hpp
)

set(APRG_PROCESS_FILES_TESTS
    ${APRG_PROCESS_FILES_DIR}/tst/AlbaCombineAndGrepFiles_unit.cpp
    ${APRG_PROCESS_FILES_DIR}/tst/AlbaSackReader_unit.cpp
    ${APRG_PROCESS_FILES_DIR}/tst/CPlusPlusFileFixer_unit.cpp
    ${APRG_PROCESS_FILES_DIR}/tst/DirectoryConstants.hpp
)

set(APRG_PROCESS_FILES_SOURCES_AND_TESTS
    ${APRG_PROCESS_FILES_SOURCES}
    ${APRG_PROCESS_FILES_TESTS}
)
