#Assign Flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c17")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++17")

if(WIN32)
    #add -mwindows for windows GUI, do not add for console build
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

message("CMAKE_C_FLAGS are: [${CMAKE_C_FLAGS}]")
message("CMAKE_CXX_FLAGS are: [${CMAKE_CXX_FLAGS}]")
