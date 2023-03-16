#Assign GSL_DIR directory, this needs aprg directory
set(GSL_DIR ${APRG_DIR}/gsl/)

if(WIN32)
    #Include GSL files and directories
    set(GSL_INCLUDE_DIRECTORIES ${GSL_DIR}/include/gsl2.7/)

    include_directories(${GSL_INCLUDE_DIRECTORIES})
    # add libraries
    add_library(GSL SHARED IMPORTED)
    set_property(TARGET GSL PROPERTY IMPORTED_IMPLIB ${GSL_DIR}/lib/gsl2.7/libgsl.a)    add_library(GSLCBLAS SHARED IMPORTED)
    set_property(TARGET GSLCBLAS PROPERTY IMPORTED_IMPLIB ${GSL_DIR}/lib/gsl2.7/libgslcblas.a)
    set (GSL_LIBRARIES_TO_LINK GSL GSLCBLAS)
else()
    find_package(GSL REQUIRED)
    set (GSL_LIBRARIES_TO_LINK GSL::gsl GSL::gslcblas)
endif()
