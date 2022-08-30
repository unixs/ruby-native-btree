cmake_minimum_required(VERSION 3.18.0)

project(ruby-native-btree
	LANGUAGES C
	VERSION 0.1.0
  	HOMEPAGE_URL https://github.com/unixs/ruby-native-btree)

set(REQUIRED_RUBY_VERSION 2.6.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG " -O0 -ggdb3 -Wall -Wextra -Wpedantic -Wno-unused-parameter")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS "-pipe -march=native")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_SHARED_LIBRARY_PREFIX "")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
	set(CMAKE_SHARED_LIBRARY_SUFFIX ".bundle")
	set(CMAKE_FIND_FRAMEWORK LAST)
	message(STATUS "CMAKE_FIND_FRAMEWORK='${CMAKE_FIND_FRAMEWORK}'")
endif()

find_package(PkgConfig REQUIRED)

# Find Ruby
find_package(Ruby ${REQUIRED_RUBY_VERSION} REQUIRED)
include_directories(${Ruby_INCLUDE_DIRS})
link_libraries(${Ruby_LIBRARIES})
message("Ruby_INCLUDE_DIRS: ${Ruby_INCLUDE_DIRS}")

message("Find Ruby deps.")
# Find jemalloc
pkg_check_modules(JEMALLOC jemalloc)
if(JEMALLOC_FOUND)
	include_directories(${JEMALLOC_INCLUDE_DIRS})
	# link_libraries(${JEMALLOC_LIBRARIES})
endif()

# Attach extension dir
add_subdirectory("ext/native_btree")