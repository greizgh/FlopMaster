cmake_minimum_required (VERSION 2.8)
#Project config
project (FlopMaster)
set (fm_VERSION_MAJOR 2)
set (fm_VERSION_MINOR 1)
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(FM_DEBUG false)
else()
    set(FM_DEBUG true)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")
message("Build type: " ${CMAKE_BUILD_TYPE})
configure_file(
    "${PROJECT_SOURCE_DIR}/src/fm_config.cpp.in"
    "${PROJECT_BINARY_DIR}/src/fm_config.cpp"
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
    ${PROJECT_BINARY_DIR}/src/*
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
