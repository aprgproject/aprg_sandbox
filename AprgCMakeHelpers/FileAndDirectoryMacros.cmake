include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

# Subdirectory traverse implementation
macro(TRAVERSE_DIRECTORY resultingSubDirectories currentDirectory exclude_filter)
    file(GLOB children ${currentDirectory}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${child})
            if("${child}" MATCHES "^\\.svn$" OR (NOT("${exclude_filter}" STREQUAL "") AND "${child}" MATCHES "${exclude_filter}"))
                #PRINT_STATUS("[DEBUG] traverse - skipping: ${child}")
            else()
                #PRINT_STATUS("[DEBUG] traverse: ${child}")
                TRAVERSE_DIRECTORY(resultingSubDirectories ${child} "${exclude_filter}")
            endif()
        endif()
    endforeach()
    set(${resultingSubDirectories} ${${resultingSubDirectories}} ${currentDirectory})
endmacro()

# Subdirectory traverse (without exclusion filter), returns list of directories
macro(GET_SUB_DIRECTORY_LIST result currentDirectory)
    set(resultingSubDirectories "")
    TRAVERSE_DIRECTORY(resultingSubDirectories ${currentDirectory} "")
    set(${result} ${resultingSubDirectories})
endmacro()

# Subdirectory traverse with exclusion filter, returns list of directories
macro(GET_SUB_DIRECTORY_LIST_WITH_EXCLUSION result currentDirectory exclude_filter)
    set(resultingSubDirectories "")
    TRAVERSE_DIRECTORY(resultingSubDirectories ${currentDirectory} "${exclude_filter}")
    set(${result} ${resultingSubDirectories})
endmacro()

# Subdirectory source groups creator
macro(GET_SOURCE_FILES_FROM_DIRECTORIES outputSourceList sourceDirectory)
    foreach(directory ${${sourceDirectory}})
        #PRINT_STATUS("Adding source group ${directory}")
        file(GLOB files ${directory}/*.hpp ${directory}/*.cpp ${directory}/*.h ${directory}/*.c)
        foreach(filename ${files})
            list(APPEND ${outputSourceList} ${filename})
            #PRINT_STATUS("Adding file: ${filename}")
        endforeach()
    endforeach()
endmacro()

macro(GET_FILE_EXTENSION result target release)
    if(DEFINED target)
        if(${target} MATCHES "HOST")
            if(${release} MATCHES "REL2")
                set(result ".hr2")
            elseif(${release} MATCHES "REL3")
                set(result ".hr3")
            elseif(${release} MATCHES "REL4")
                set(result ".hr4")
            endif()
        else()
            if(${release} MATCHES "REL2")
                set(result ".tr2")
            elseif(${release} MATCHES "REL3")
                set(result ".tr3")
            elseif(${release} MATCHES "REL4")
                set(result ".tr4")
            endif()
        endif()
        PRINT_STATUS("Extension set to: ${result}")
    endif()
endmacro()
