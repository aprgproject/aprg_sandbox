#Assign Definitions

add_definitions(-DAPRG_DIR="${APRG_DIR}")

if(WIN32)
    add_definitions(-DOS_WINDOWS)
elseif(APPLE)
    add_definitions(-DOS_APPLE)
elseif(UNIX)
    add_definitions(-DOS_LINUX)
endif()
