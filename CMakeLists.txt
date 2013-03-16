cmake_minimum_required (VERSION 2.8)
#Project config
project (FlopMaster)
set (fm_VERSION_MAJOR 1)
set (fm_VERSION_MINOR 0)
set (CMAKE_BUILD_TYPE Release)
configure_file(
    "${PROJECT_SOURCE_DIR}/src/fm_config.h.in"
    "${PROJECT_BINARY_DIR}/src/fm_config.h"
    )
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

Find_Package(Threads REQUIRED)
#Boost is needed
Find_Package(Boost REQUIRED system COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
if ( NOT Boost_FOUND)
    message(FATAL_ERROR "Boost lib not found!")
endif ( NOT Boost_FOUND)

#FlopMaster files
file(
    GLOB_RECURSE
    source_files
    src/*
    )
#FlopMaster executable
add_executable(
    FlopMaster
    ${source_files}
    )

#We are using c++11
add_definitions(-std=c++11)
#And alsa
Find_Package(ALSA)
if(ALSA_FOUND)
    set_target_properties(FlopMaster PROPERTIES COMPILE_FLAGS "-D__LINUX_ALSA__")
    target_link_libraries (FlopMaster ${ALSA_LIBRARIES})
endif()
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})
target_link_libraries(
    FlopMaster
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    )
