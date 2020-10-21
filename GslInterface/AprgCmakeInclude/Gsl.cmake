#Assign GNU_WIN32_ directory, this needs aprg directory
set(GSL_INTERFACE_DIR ${APRG_DIR}/GslInterface/)

#Include GSL files and directories
set(GSL_INCLUDE_DIRECTORIES
    ${GSL_INTERFACE_DIR}/include/
)

include_directories(${GSL_INCLUDE_DIRECTORIES})
# add libraries
add_library(GSL SHARED IMPORTED)
set_property(TARGET GSL PROPERTY IMPORTED_IMPLIB ${GSL_INTERFACE_DIR}/lib/libgsl.a)
#set_property(TARGET GSL PROPERTY IMPORTED_LOCATION ${GNU_WIN32_DIR}/lib/)
#set_property(TARGET GSL PROPERTY IMPORTED_IMPLIB ${GNU_WIN32_DIR}/bin/libgslcblas.dll)
add_library(GSLCBLAS SHARED IMPORTED)
set_property(TARGET GSLCBLAS PROPERTY IMPORTED_IMPLIB ${GSL_INTERFACE_DIR}/lib/libgslcblas.a)