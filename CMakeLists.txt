cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(kt_node_rt)

set(NODE_HOME "$ENV{NODE_HOME}")

set(CMAKE_CXX_STANDARD 17)

add_library(node_str_obj OBJECT src/NodeString.cpp)

if(DEFINED ENABLE_LINUX OR DEFINED ENABLE_MACOS)
    set(INCLUDE_DIRS ${NODE_HOME}/include ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

target_include_directories(node_str_obj PUBLIC ${INCLUDE_DIRS})

if(DEFINED ENABLE_LINUX)
    set(PLATFORM_MACRO KONAN_LINUX)
elseif(DEFINED ENABLE_MACOS)
    set(PLATFORM_MACRO KONAN_MACOSX)
    set(COMPILER_OPTION -undefined dynamic_lookup)
endif()

target_compile_definitions(node_str_obj PUBLIC ${PLATFORM_MACRO})

set_property(TARGET node_str_obj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(ktnodert_static STATIC $<TARGET_OBJECTS:node_str_obj>)
add_library(ktnodert_shared SHARED $<TARGET_OBJECTS:node_str_obj>)
target_compile_options(ktnodert_shared PUBLIC ${COMPILER_OPTION})