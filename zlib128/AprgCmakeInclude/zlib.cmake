#Assign curl directory, needs aprg directory
set(ZLIB_DIR ${APRG_DIR}/zlib128/zlib-1.2.8/)

#Include curl library
set(ZLIB_INCLUDE_DIRECTORIES
    ${ZLIB_DIR}
)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
include_directories(${ZLIB_INCLUDE_DIRECTORIES})
set(ZLIB_PUBLIC_HDRS
    ${ZLIB_DIR}/zconf.h
    ${ZLIB_DIR}/zlib.h
)
set(ZLIB_PRIVATE_HDRS
    ${ZLIB_DIR}/crc32.h
    ${ZLIB_DIR}/deflate.h
    ${ZLIB_DIR}/gzguts.h
    ${ZLIB_DIR}/inffast.h
    ${ZLIB_DIR}/inffixed.h
    ${ZLIB_DIR}/inflate.h
    ${ZLIB_DIR}/inftrees.h
    ${ZLIB_DIR}/trees.h
    ${ZLIB_DIR}/zutil.h
)
set(ZLIB_SRCS
    ${ZLIB_DIR}/adler32.c
    ${ZLIB_DIR}/compress.c
    ${ZLIB_DIR}/crc32.c
    ${ZLIB_DIR}/deflate.c
    ${ZLIB_DIR}/gzclose.c
    ${ZLIB_DIR}/gzlib.c
    ${ZLIB_DIR}/gzread.c
    ${ZLIB_DIR}/gzwrite.c
    ${ZLIB_DIR}/inflate.c
    ${ZLIB_DIR}/infback.c
    ${ZLIB_DIR}/inftrees.c
    ${ZLIB_DIR}/inffast.c
    ${ZLIB_DIR}/trees.c
    ${ZLIB_DIR}/uncompr.c
    ${ZLIB_DIR}/zutil.c
)
add_library(zlib STATIC ${ZLIB_SRCS} ${ZLIB_PUBLIC_HDRS} ${ZLIB_PRIVATE_HDRS})
set_target_properties(zlib PROPERTIES LINKER_LANGUAGE C)
