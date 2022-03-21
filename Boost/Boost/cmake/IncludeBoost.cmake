include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

#set boost flags
set(Boost_DEBUG                  ON)
if(WIN32)
    #set directories for boost in APRG
    PRINT_VARIABLE(BOOST_DIR)
    set(Boost_USE_STATIC_LIBS        ON)
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME    OFF)    set(BOOST_INCLUDEDIR    ${BOOST_DIR}/)
    set(BOOST_LIBRARYDIR    ${BOOST_DIR}/boost/lib)
    set(BOOST_ROOT          ${BOOST_DIR}/boost)
endif()
#Linux boost is installed as a library so no need to update location

find_package(Boost COMPONENTS system locale filesystem iostreams REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
else()
    message(WARNING "cmake cannot find boost. Please set Boost_DEBUG to ON for more info. Try checking: FindBoost.cmake to investigate further.")
endif()
