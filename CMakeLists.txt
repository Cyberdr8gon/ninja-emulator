cmake_minimum_required( VERSION 3.5 )
set( PROJECT_NAME_STR ninjaEm )
project( ${PROJECT_NAME_STR} C CXX)


# for gtest
find_package(Threads REQUIRED)


##
## Get Bytedness
##
#if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
#    MESSAGE( "64 bits compiler detected" )
#    SET( EX_PLATFORM 64 )
#    SET( EX_PLATFORM_NAME "x64" )
#else( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
#    MESSAGE( "32 bits compiler detected" )
#    SET( EX_PLATFORM 32 )
#    SET( EX_PLATFORM_NAME "x86" )
#endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )


#
# Compiler definitions
#

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-Wall -pthread )
endif()


if(MSVC)
  #vc 2012 fix for vararg templates
  set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif() 

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 ")

#
# Include files and ext folder
#

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)


#
# set bin output 
#

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#
# SDL2
#

set(SDL2_DIR ${EXT_PROJECTS_DIR}/sdl2.0.5 )
set(SDL2_INCLUDE_DIR ${SDL_DIR}/include )
set(SDL2_LIB_DIR ${SDL_DIR}/lib/x86 )

file( GLOB SDL2_LIBS ${SDL2_LIB_DIR}/*)


#
# Main executable
#

include_directories( ${COMMON_INCLUDES} ${SDL2_INCLUDE_DIR} )
file( GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp )
add_executable( ${PROJECT_NAME_STR} ${SRC_FILES} )
target_link_libraries( ${PROJECT_NAME_STR} SDL2_LIBS )


#
# Test
#

# need VERSION 3.6 cmake :(
# clang-tidy static analyzer

#if( CMAKE_CXX_CLANG_TIDY )
#  set_property( TARGET ${PROJECT_NAME_STR} PROPERTY CMAKE_CXX_CLANG_TIDY )
#endif()

# gtest

# add module source

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

add_definitions( ${MSVC_COMPILER_DEFS} )
enable_testing()
set( PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test )
include_directories( ${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES} ${SDL2_INCLUDE_DIR} )

file( GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp )
list( APPEND TEST_SRC_FILES ${SRC_FILES} )
list( REMOVE_ITEM TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp )

add_executable( ${PROJECT_TEST_NAME} ${TEST_SRC_FILES} )
add_dependencies( ${PROJECT_TEST_NAME} googletest )


if(NOT WIN32 OR MINGW)
  target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LIBS_DIR}/libgtest.a ${GTEST_LIBS_DIR}/libgtest_main.a)
else()
  target_link_libraries(${PROJECT_TEST_NAME}
                        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
                        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
                       )
  target_link_libraries(${PROJECT_TEST_NAME}
                        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
                        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
                       )
endif()

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT} ${SDL2_LIBS} )

add_test( gtests ${PROJECT_TEST_NAME} )
