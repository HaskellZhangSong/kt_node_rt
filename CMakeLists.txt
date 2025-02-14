cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(kt_node_rt)

if(DEFINED ENABLE_LINUX)
    message(WARNING "LINUX is selected")
    set(NODE_HOME "$ENV{NODE_HOME}")
    set(PLATFORM_MACRO KONAN_LINUX)
elseif(DEFINED ENABLE_MACOS)
    message(WARNING "MACOS is selected")
    set(NODE_HOME "$ENV{NODE_HOME}")
    set(PLATFORM_MACRO KONAN_MACOSX)
    set(COMPILER_OPTION -undefined dynamic_lookup)
elseif(DEFINED ENABLE_OHOS)
    set(OHOS_HOME "$ENV{OHOS_SDK_HOME}")
    set(PLATFORM_MACRO KONAN_OHOS)
endif()

set(CMAKE_CXX_STANDARD 17)

add_library(node_str_obj OBJECT src/NodeString.cpp)

if(DEFINED ENABLE_LINUX OR DEFINED ENABLE_MACOS)
    set(INCLUDE_DIRS ${NODE_HOME}/include )
elseif(DEFINED ENABLE_OHOS)
    set(INCLUDE_DIRS ${OHOS_HOME}/default/openharmony/native/sysroot/usr/include)
endif()

list(APPEND INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(node_str_obj PUBLIC ${INCLUDE_DIRS})
target_compile_definitions(node_str_obj PUBLIC ${PLATFORM_MACRO})

set_property(TARGET node_str_obj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(ktnodert_static STATIC $<TARGET_OBJECTS:node_str_obj>)

if(DEFINED ENABLE_LINUX OR DEFINED ENABLE_MACOS)
    add_library(ktnodert_shared SHARED $<TARGET_OBJECTS:node_str_obj>)
    target_link_options(ktnodert_shared PUBLIC ${COMPILER_OPTION})
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include/NodeString.h DESTINATION ${CMAKE_BINARY_DIR})