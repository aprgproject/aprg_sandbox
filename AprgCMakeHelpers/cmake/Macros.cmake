# -*- Makefile -*-


#=====================================#
# list all subdirectories from 1 dir  #
#=====================================#

MACRO(MACRO_GET_SUBDIRECTORIES_FROM_ONE_DIRECTORY result currdir )

        set (continuation 1)
        # set (exceptiondirs "-NOTFOUND")
        set (exceptiondirs)

        set(extra_macro_args ${ARGN})
        list(LENGTH extra_macro_args num_extra_args)
        if( ${num_extra_args} GREATER 0)
            SET(index_extra_args 0)
            while(${index_extra_args} LESS ${num_extra_args})
                list(GET extra_macro_args ${index_extra_args} __exceptiondir)
                SET(exceptiondirs ${exceptiondirs} ${__exceptiondir})
                MATH(EXPR index_extra_args "${index_extra_args} + 1")
            endwhile()
        endif()

        if(exceptiondirs)

            # MESSAGE("exception dirs are: ${exceptiondirs}")

            foreach(exceptiondir ${exceptiondirs})

                # MESSAGE("exception dir is: ${exceptiondir}")
                # MESSAGE("curr dir is     : ${currdir}")

                STRING( FIND ${currdir} ${exceptiondir} _POS )
                IF(_POS GREATER -1)
                    set (continuation 0)
                    break()
                endif()

            endforeach()

            # if (continuation EQUAL 0)
            #     MESSAGE("found exception dir!")
            # endif()

        endif()


        STRING( FIND ${currdir} "CMakeFiles" _POS )
        IF(_POS EQUAL -1 AND continuation EQUAL 1)

            IF(NOT("${currdir}" MATCHES ".svn$"))

                #MESSAGE(STATUS "Adding subdirectory: ${currdir}")
                LIST(APPEND ${result} ${currdir})

                FILE(GLOB children ${currdir}/*)

                FOREACH(child  ${children})

                    IF (IS_DIRECTORY ${child})

                        MACRO_GET_SUBDIRECTORIES_FROM_ONE_DIRECTORY(${result} ${child} ${exceptiondirs})

                    ENDIF()

                ENDFOREACH()

            ENDIF()

        ENDIF()

ENDMACRO()


#=========================#
# list all subdirectories #
#=========================#

MACRO(MACRO_GET_SUBDIRECTORIES result sub_dirs)

        FOREACH(sub ${${sub_dirs}})

                MESSAGE(STATUS "MACRO_GET_SUBDIRECTORIES_FROM_ONE_DIRECTORY: ${sub}")
                MACRO_GET_SUBDIRECTORIES_FROM_ONE_DIRECTORY(${result} ${sub})

        ENDFOREACH()

ENDMACRO()


#=====================================#
# list all files from dir and subdirs #
#=====================================#

MACRO(MACRO_GET_FILES result sub_dirs)

        FOREACH(sub ${${sub_dirs}})

                #MESSAGE(STATUS "Subdir: ${sub}")
                FILE(GLOB files ${sub}/*.cpp ${sub}/*.hpp ${sub}/*.c ${sub}/*.h ${sub}/*.py)

                FOREACH(filename ${files})

                        LIST(APPEND ${result} ${filename})
                        #MESSAGE(STATUS "Adding file: ${filename}")

                ENDFOREACH()

        ENDFOREACH()

ENDMACRO()


#===================================#
# list all sources from a given dir #
#===================================#
MACRO(MACRO_GET_SOURCE_DIR result dir)

    #MESSAGE(STATUS "Subdir: ${sub}")
    FILE(GLOB files ${dir}/*.cpp ${dir}/*.hpp ${dir}/*.c ${dir}/*.h)

    FOREACH(filename ${files})

        LIST(APPEND ${result} ${filename})
        # MESSAGE(STATUS "Adding file: ${filename}")

    ENDFOREACH()

ENDMACRO()

#=========================#
# Print elements #
#=========================#

MACRO(PRINT_ELEMENTS elements)

        FOREACH(element ${${elements}})

                MESSAGE(STATUS "Element: ${element}")

        ENDFOREACH()

ENDMACRO()
