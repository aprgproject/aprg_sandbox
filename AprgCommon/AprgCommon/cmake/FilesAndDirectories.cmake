set(APRG_COMMON_INCLUDE_DIRECTORIES
    ${APRG_COMMON_DIR}/src
    )

set(APRG_COMMON_TEST_INCLUDE_DIRECTORIES
    ${APRG_COMMON_DIR}/tst
    )

set(APRG_COMMON_MAIN_SOURCES
    ${APRG_COMMON_DIR}/src/Bit/AlbaBitConstants.hpp    ${APRG_COMMON_DIR}/src/Bit/AlbaBitManipulation.hpp
    ${APRG_COMMON_DIR}/src/Container/AlbaContainerHelper.cpp
    ${APRG_COMMON_DIR}/src/Container/AlbaContainerHelper.hpp
    ${APRG_COMMON_DIR}/src/Container/AlbaRange.hpp    ${APRG_COMMON_DIR}/src/Container/AlbaXY.hpp
    ${APRG_COMMON_DIR}/src/Debug/AlbaDebug.hpp
    ${APRG_COMMON_DIR}/src/File/AlbaFileReader.cpp
    ${APRG_COMMON_DIR}/src/File/AlbaFileReader.hpp
    ${APRG_COMMON_DIR}/src/Macros/AlbaMacros.hpp
    ${APRG_COMMON_DIR}/src/Math/AlbaMathHelper.cpp
    ${APRG_COMMON_DIR}/src/Math/AlbaMathHelper.hpp
    ${APRG_COMMON_DIR}/src/Math/AlbaMatrix.hpp
    ${APRG_COMMON_DIR}/src/Memory/AlbaMemoryBuffer.cpp
    ${APRG_COMMON_DIR}/src/Memory/AlbaMemoryBuffer.hpp
    ${APRG_COMMON_DIR}/src/Memory/AlbaRaiiafPointer.cpp
    ${APRG_COMMON_DIR}/src/Memory/AlbaRaiiafPointer.hpp
    ${APRG_COMMON_DIR}/src/Optional/AlbaOptional.cpp
    ${APRG_COMMON_DIR}/src/Optional/AlbaOptional.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaLocalPathHandler.cpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaLocalPathHandler.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaPathHandler.cpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaPathHandler.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWebPathHandler.cpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWebPathHandler.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/PathContantsAndTypes.hpp
    ${APRG_COMMON_DIR}/src/Randomizer/AlbaRandomizer.cpp
    ${APRG_COMMON_DIR}/src/Randomizer/AlbaRandomizer.hpp
    ${APRG_COMMON_DIR}/src/String/AlbaStringHelper.cpp
    ${APRG_COMMON_DIR}/src/String/AlbaStringHelper.hpp
    ${APRG_COMMON_DIR}/src/Time/AlbaDateTime.cpp
    ${APRG_COMMON_DIR}/src/Time/AlbaDateTime.hpp
    ${APRG_COMMON_DIR}/src/Time/AlbaDateTimeConstants.hpp
    ${APRG_COMMON_DIR}/src/Time/AlbaDateTimeHelper.cpp
    ${APRG_COMMON_DIR}/src/Time/AlbaDateTimeHelper.hpp
    ${APRG_COMMON_DIR}/src/Time/AlbaLocalTimer.cpp
    ${APRG_COMMON_DIR}/src/Time/AlbaLocalTimer.hpp
    ${APRG_COMMON_DIR}/src/User/AlbaDisplayTable.cpp
    ${APRG_COMMON_DIR}/src/User/AlbaDisplayTable.hpp
    ${APRG_COMMON_DIR}/src/User/AlbaLocalUserAutomation.cpp
    ${APRG_COMMON_DIR}/src/User/AlbaLocalUserAutomation.hpp
    ${APRG_COMMON_DIR}/src/User/AlbaUserInterface.cpp
    ${APRG_COMMON_DIR}/src/User/AlbaUserInterface.hpp
    )

set(APRG_COMMON_WINDOWS_SOURCES
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWindowsPathHandler.cpp    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWindowsPathHandler.hpp
    ${APRG_COMMON_DIR}/src/Time/AlbaWindowsTimer.cpp
    ${APRG_COMMON_DIR}/src/Time/AlbaWindowsTimer.hpp
    ${APRG_COMMON_DIR}/src/User/AlbaWindowsUserAutomation.cpp
    ${APRG_COMMON_DIR}/src/User/AlbaWindowsUserAutomation.hpp
    ${APRG_COMMON_DIR}/src/Windows/AlbaWindowsHelper.cpp
    ${APRG_COMMON_DIR}/src/Windows/AlbaWindowsHelper.hpp
    )

set(APRG_COMMON_MAIN_TESTS
    ${APRG_COMMON_DIR}/tst/BitTests/AlbaBitManipulation_unit.cpp    ${APRG_COMMON_DIR}/tst/ContainerTests/AlbaContainerHelper_unit.cpp
    ${APRG_COMMON_DIR}/tst/ContainerTests/AlbaRange_unit.cpp
    ${APRG_COMMON_DIR}/tst/ContainerTests/AlbaXY_unit.cpp
    ${APRG_COMMON_DIR}/tst/DebugTests/AlbaDebug_unit.cpp    ${APRG_COMMON_DIR}/tst/FileTests/AlbaFileReader_unit.cpp
    ${APRG_COMMON_DIR}/tst/MacrosTests/AlbaMacros_unit.cpp
    ${APRG_COMMON_DIR}/tst/MathTests/AlbaMathHelper_unit.cpp
    ${APRG_COMMON_DIR}/tst/MathTests/AlbaMatrix_unit.cpp
    ${APRG_COMMON_DIR}/tst/MemoryTests/AlbaMemoryBuffer_unit.cpp
    ${APRG_COMMON_DIR}/tst/MemoryTests/AlbaRaiiafPointer_unit.cpp
    ${APRG_COMMON_DIR}/tst/OptionalTests/AlbaOptional_unit.cpp
    ${APRG_COMMON_DIR}/tst/PathHandlerTests/AlbaPathHandler_unit.cpp
    ${APRG_COMMON_DIR}/tst/PathHandlerTests/AlbaWebPathHandler_unit.cpp
    ${APRG_COMMON_DIR}/tst/RandomizerTests/AlbaRandomizer_unit.cpp
    ${APRG_COMMON_DIR}/tst/StringTests/AlbaStringHelper_unit.cpp
    ${APRG_COMMON_DIR}/tst/TimeTests/AlbaDateTime_unit.cpp
    ${APRG_COMMON_DIR}/tst/TimeTests/AlbaDateTimeHelper_unit.cpp
    ${APRG_COMMON_DIR}/tst/UserTests/AlbaDisplayTable_unit.cpp
    ${APRG_COMMON_DIR}/tst/DirectoryConstants.hpp
    )

set(APRG_COMMON_WINDOWS_TESTS
    ${APRG_COMMON_DIR}/tst/PathHandlerTests/AlbaWindowsPathHandler_unit.cpp
    ${APRG_COMMON_DIR}/tst/TimeTests/AlbaWindowsTimer_unit.cpp
    ${APRG_COMMON_DIR}/tst/UserTests/AlbaWindowsUserAutomation_unit.cpp
    )

set(APRG_COMMON_SOURCES
    ${APRG_COMMON_MAIN_SOURCES}
    )

set(APRG_COMMON_TESTS
    ${APRG_COMMON_MAIN_TESTS}
    )

if(WIN32)
    set(APRG_COMMON_SOURCES
        ${APRG_COMMON_SOURCES}
        ${APRG_COMMON_WINDOWS_SOURCES}
        )

    set(APRG_COMMON_TESTS
        ${APRG_COMMON_TESTS}
        ${APRG_COMMON_WINDOWS_TESTS}
        )
endif()

set(APRG_COMMON_SOURCES_AND_TESTS
    ${APRG_COMMON_SOURCES}
    ${APRG_COMMON_TESTS}
    )