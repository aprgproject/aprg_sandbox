include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

set(Boost_DEBUG                  ON)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(BOOST_INCLUDEDIR    ${BOOST_DIR}/)
set(BOOST_LIBRARYDIR    ${BOOST_DIR}/boost/lib)
set(BOOST_ROOT          ${BOOST_DIR}/boost)

find_package(Boost COMPONENTS system locale filesystem iostreams)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})     LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
else()
    message(WARNING "Cmake cannot find boost. Please set Boost_DEBUG to ON for more info. Try checking: "Program Files\CMake\share\cmake-3.10\Modules\FindBoost.cmake" to investigate further.")
endif()
