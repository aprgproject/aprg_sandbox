#Assign Definitions

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DAPRG_DEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DAPRG_RELEASE)
endif()

add_definitions(-DAPRG_DIR="${APRG_DIR}")

if(WIN32)
    add_definitions(-DOS_WINDOWS)
elseif(APPLE)
    add_definitions(-DOS_APPLE)
elseif(UNIX)
    add_definitions(-DOS_LINUX)
endif()
