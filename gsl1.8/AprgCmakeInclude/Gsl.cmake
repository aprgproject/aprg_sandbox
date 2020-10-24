#Assign GNU_WIN32_ directory, this needs aprg directory
set(GSL_DIR ${APRG_DIR}/gsl1.8/)

#Include GSL files and directories
set(GSL_INCLUDE_DIRECTORIES
    ${GSL_DIR}/include/
)

include_directories(${GSL_INCLUDE_DIRECTORIES})
# add libraries
add_library(GSL SHARED IMPORTED)
set_property(TARGET GSL PROPERTY IMPORTED_IMPLIB ${GSL_DIR}/lib/libgsl.a)
add_library(GSLCBLAS SHARED IMPORTED)
set_property(TARGET GSLCBLAS PROPERTY IMPORTED_IMPLIB ${GSL_DIR}/lib/libgslcblas.a)